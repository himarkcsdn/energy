#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<assert.h>
#include<pthread.h>  //线程
#include<netinet/in.h>  //网络 I
#include<arpa/inet.h>  //I
#include<sys/socket.h>  //I
#include<sys/types.h>  // I
#include<sys/stat.h>
#include<sys/sendfile.h>
#include<fcntl.h>

#define MAX 1024
#define HOME_PAGE "index.html"
#define PAGE_404 "wwwroot/404.html"
//  ./httpd 80



static int usage(const char* proc)
{
    printf("\nUsage: \n\t%s port\n\n",proc);
}

int get_line(int sock, char line[], int num)
{
    assert(line);   //合法性校验
    assert(num>0);//每次读一个字符，如果读到\n读完了一行的换行符 如果读到\r 进行判断下一个字符 体现了面向字节流的思想
    int i=0;
    char c='A';
    while(c!='\n'& i<num-1)   //num-1 预留\0的位置
    {
        ssize_t s=recv(sock, &c, 1, 0);         // 函数recv 读取tcp的流式接口 flag=0 和read方式一样（阻塞式读）
        if(s>0)   //读成功
        {
            if(c=='\r')   //\r,\r\n -> \n                  //当前读到\r 需要判断接收缓冲区的下一个字符是否为\n 提前窥探下一个字符，如果是\n则读取到line中，如果不是\r则不拿 
            {                                                     //recv的 flag= MSG_PEEK(窥探功能)
                recv(sock, &c,1, MSG_PEEK);
                if(c=='\n')             //如果下一个字符是\n  则再读一次把\n读到line中
                {
                    recv(sock,&c,1, 0);                
                }
                else     // 走到这里是 \n
                {
                    c='\n';
                }
            }
            //else     //正常字符 ，或者换行符\n
            line[i++]=c;   //读一个放一个  如果读到\n放到缓冲区，下一次循环时不满足条件则结束
        }
    }
    line[i]='\0';           //i永远指向下一个位置
    return i;      //只要读到空行则以后一定是\n 因为已经对上面的三种换行符进行处理过转化为\n了
}
//======================================请求数据==========================
void clear_header(int sock)
{
    char line[MAX];
    do
    {
        get_line(sock,line,sizeof(line));
    //    printf("%s",line);
    }while(strcmp(line,"\n")!=0);  //循环读，读到空行停下来 
}

//================================
void show_404(int sock)
{
    char line[1024];
    sprintf(line,"HTTP/1.0 404 NOT FOUND\r\n");
    send(sock,line,strlen(line),0);

    sprintf(line,"Content-type:text/html;charset=ISO-8859-1\r\n");
    send(sock,line,strlen(line),0);
    sprintf(line, "\r\n");
    send(sock,line,strlen(line),0);          //响应报头已经发好了

    struct stat st;
    stat(PAGE_404,&st);
    int fd=open(PAGE_404, O_RDONLY);  //把页面返回回去 sendfile
    sendfile(sock,fd,NULL,st.st_size);
    close(fd);

}
//========================================错误码==========================
void echo_error(int sock, int code)
{
    switch(code)
    {
        case 400:
            //
            break;
        case 403:
            //
            break;
        case 404:
            show_404(sock);
            break;
        case 500:
            //
            break;
        case 503:
            //
            break;
        default:
            break;
    }
}
//============================把请求的资源写回客户端=======================
int echo_www(int sock, char* path, int size)          
{

    int fd=open(path, O_RDONLY);
    if(fd<0)
    {
        return 404;//打开文件失败，认为文件不存在
    }  
    clear_header(sock);     
    char line[MAX];
    sprintf(line,"HTTP/1.0 200 OK\r\n");
    send(sock, line, strlen(line), 0);  //发送单纯的行到缓冲区
    sprintf(line,"Content-type:text/html;charset=ISO-8859-1\r\n");
    send(sock,line,strlen(line),0);
    sprintf(line, "\r\n");
    send(sock,line,strlen(line),0);          //响应报头已经发好了

   // 高效的发正文  sendfile函数（从一个文件描述符拷贝到另一个文件描述符）不用经过用户   （之前是先把文件打开，再调用read函数从内核读取到用户，再从用户写到网卡里）  

    sendfile(sock,fd,NULL,size);
    close(fd);
    return 200;
}

int exe_cgi(int sock, char* method, char* path, char* query_string)
{               

    char line[MAX];
    char method_env[MAX/10];    
    char query_string_env[MAX];
    int content_length=-1;
    char content_length_env[MAX/10];
   
    if(strcasecmp(method,"GET")==0) 
    {
        clear_header(sock);     //处理掉报头 
    }
    else  //POST  从正文中读参数 ，通过报头的Content-Length 确定正文的长度。
    {
        do
        {    
            get_line(sock,line,sizeof(line));
            // Content-Length: 12
            if(strncmp(line,"Content-Length: ",16)==0)
            {
                content_length=atoi(line+16);  //字符串首元素1的地址

            }
         }while(strcmp(line,"\n"));  //清理直到走到\n 
        if(content_length==-1)  //走到这里报头被清完了，空行也被清理了，要么读正文要么读完了
        {
            return 400; //没有content-length，说明客户端的问题
        }
    }

    // 创建两个管道， 站在子进程的角度
    int input[2];   //child 角度
    int output[2];
    
    pipe(input);
    pipe(output);


    //方法 get post 模式一定是cgi path已经知道
    pid_t id=fork();
    if(id<0)
    {
        return 503;  //走到这里请求已经搞定，创建子进程失败（服务器压力太大了）
    }
    else if(id==0) //子进程
    {
        close(input[1]);
        close(output[0]);

        dup2(input[0],0); //标准输入重定向到input管道中
        dup2(output[1],1);//把标准输出重定向到output管道中
        
        sprintf(method_env, "METHOD=%s",method);//构建环境变量，我们把将指定的环境变量方法导到子进程的地址空间
        putenv(method_env);//如果是post方法 ,把Post构建的环境变量导入

        if(strcasecmp(method,"GET")==0) //如果是get 方法需要把query_string作为环境变量导入
        {
            sprintf(query_string_env,"QUERY_STRING=%s",query_string);
            putenv(query_string_env);
        }
        else //post只拿到长度，接下来从管道拿数据
        {
            sprintf(content_length_env,"CONTENT_LENGTH=%d",content_length);
            putenv(content_length_env);//导入构建的长度的环境变量
        }


        //exec*
        execl(path,path,NULL);  //第一个执行谁， 第二个要怎么执行（直接执行/或者带路径执行），
        exit(1);
    }
    else  
    {
        close(input[0]);
        close(output[1]);       //把子进程进行文件描述符重定向，程序替换不会替换文件描述符。
        
        char c;
        if(strcasecmp(method,"POST")==0)// 等于0才需要读

        {
            int i=0; //从父进程的角度,从网络里读content_length的数据，通过管道把参数给子进程，
            for(;i<content_length;i++)  
            {
                recv(sock, &c, 1, 0);
                write(input[1], &c, 1); //
            }
        }
        sprintf(line,"HTTP/1.0 200 ok\r\n");
        send(sock, line, strlen(line),0); 
        sprintf(line,"Content-type:text/html;charset=ISO-8859-1\r\n");
        send(sock,line,strlen(line),0);
        sprintf(line, "\r\n");
        send(sock,line,strlen(line),0);          //响应报头已经发好了

        
        while(read(output[0],&c, 1)>0)
        {
            send(sock, &c, 1, 0);//发送给客户端
        }


        waitpid(id,NULL,0);  //线程在等不会影响其他操作
        close(input[1]);
        close(output[0]);
    }
    return 200;
    //cgi只做了两件事。  目前只显示了正文行
//cgi相近一切办法把子进程跑起来，把参数送给子进程， 
//把子进程的结果拿出来，返回给客户端 
//http 响应有报头格式 ，  所以要加上 状态行，响应行，空行 ，正文
}

void* handler_request(void* arg)  //对线程进行处理，先读（对文本根据协议分析）后写  http服务器进行文本分析
{
    int sock=(int)arg;
    char line[MAX];
    char method[MAX/10]; //请求方法
    char url[MAX];         //请求的第二个部分
    char path[MAX]={0};   //拼接路径
    int i=0;
    int j=0;
    int status_code=200;  //设置响应状态吗

    int cgi=0; 
    char* query_string=NULL;   
     
    get_line(sock,line, sizeof(line)); //按行读取  读的内容放在line里面， 读sizeof(line)行     line-> \r,\r\n,\n ->\n  不确定文本获取接口（fgets gets） 它会认为换行符\r ，会漏掉\n，下次读取会多读取到\n 会产生粘包问题。
    //GET /a/b/c?name=zhangsan&    
    while(i<sizeof(method)-1 && j<sizeof(line) && !isspace(line[j]))  //下标不能超过数组对应的范围 ，读到第一个空格的时候停下来  //strlen太低效要调用函数->换成sizeof 编译时确定了大小
    {
        method[i]=line[j];
        i++,j++;
    }
    method[i]='\0';    //提取到了方法 判断是GET方法还是POST方法 
    if(strcasecmp(method,"GET")==0)    //
    {
    
    }
    else if(strcasecmp(method,"POST")==0)    
    {
        cgi=1;
    }
    else          // （不是get,也不是pos）方法
    {
        clear_header(sock); //把http的头部信息清理完毕      
        status_code=400;                            //请求处理完再处理响应（设置状态码)
        goto end;                              
    }
    
    i=0;  //i清理0 指向url
    while(j<sizeof(line) && isspace(line[j]))  //过滤掉空格
    {
        j++; 
    }
    //  j指向不是空格
    i=0;
    while(i<sizeof(url)-1 && j<sizeof(line) && !isspace(line[j])) //开始放下一个位置 如果不是空格才往后走
    {
        url[i]=line[j];
        i++,j++;
    }
    url[i]='\0';   //第二列已经放入到url当中，保证url也是一个字符串以'\0'结尾

#ifdef DEBUG      
    
    printf("line: %s\n",line);
    printf("method: %s, url: %s\n", method, url);
#endif

    //method url cgi
    if(strcasecmp(method, "GET")==0)
    {
        query_string=url; 
        while(*query_string)            //  参数?资源  ?->'\0'
        {
            if(*query_string=='?')   // ='?' 说明有参数  
            {
                *query_string='\0';                    //如果没有参数走到字符串结尾'\0'结束
                query_string++; // 指向下一个字符串
                cgi=1;                     //url 指向前半部分的路径
                break;   //走到这里将资源和参数分离了
            }
            query_string++;  
        }
    }
    //method GET/POST   url, GET(参数在：query_string中)     cgi     
    //路径拼接  strcpy strcat (太笨拙)  这里采用 sprintf
    sprintf(path, "wwwroot%s",url);  // path(wwwroot/, wwwroot/a/b/c.html)  //如果请求自u和一个字符是/根目录，则默认给它返回(拼接)首页
    if(path[strlen(path)-1]=='/')       
    {
        strcat(path,HOME_PAGE); 
    }

    struct stat st;  //结构体
    if(stat(path, &st)<0)                    //判断资源（文件）是否存在  stat(提取文件属性信息)   文件（属性+内容）  属性放在inode里，为了标示唯一的属性信息就有了一个唯一的inode编号
    {
        clear_header(sock);
        status_code=404;  //访问的资源不存在
        goto end;
    }
    else    //找到了   //如果请求的是目录，重新给一个目录的首页      //如果请求的资源是二进制的可执行程序，返回可执行程序的结果（CGI的方式运行）。 
    {
        if(S_ISDIR(st.st_mode))     //判断是否是目录 
        {
            strcat(path, HOME_PAGE);
        }
        else
        {   
            if((st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH))               //判断是否是可执行程序  按位与（当前，其他，组，用户）
            {
                cgi=1;
            }
           else
            {
                ;//DO NOTHING    //走到这里资源存在，不是目录，不是可执行程序。 是普通文件
            }
        }   
        //one line处理
        if(cgi)
        {
            status_code=exe_cgi(sock,method,path,query_string);

        }
        else
        {
            status_code= echo_www(sock, path, st.st_size);  //把资源响应回去客户端，即写回到socket

        }
    }

end:
    
    if(status_code!=200)
    {
        echo_error(sock, status_code);   //往那个链接里传，传那个错误码
    }
    close(sock);     //tcp基于请求响应， 线程做了一件事 读到一行，然后把文件描述符关掉
}

int startup(int port)
{
    int sock=socket(AF_INET, SOCK_STREAM,0);
    if(sock<0)
    {
        perror("socket");
        exit(2); 
    }
    int  opt=1;   //
    setsockopt(sock,SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    struct sockaddr_in local;
    local.sin_family=AF_INET;
    local.sin_addr.s_addr=htonl(INADDR_ANY);
    local.sin_port=htons(port);
    
    if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0) //绑定
    {
        perror("bind");
        exit(3);
    }

    if(listen(sock,5)<0)   //设置监听
    {
        perror("listen");
        exit(4);
    }
    return sock;
}
int main(int argc ,char * argv[])
{
    if(argc!=2)
    {
        usage(argv[0]);
        return 1;
    }
    //基于tcp的多线程 http  创建监听套接字
    int listen_sock=startup(atoi(argv[1]));

    for(;;)  //循环事件检测
    {
        struct sockaddr_in client;
        socklen_t len=sizeof(client);

        int sock=accept(listen_sock, (struct sockaddr*)&client, &len);
        if(sock<0)
        {
            perror("accpet");
            continue;
        }
        printf("get a new client!\n");              

        pthread_t tid;    //获得链接 ，创建线程   处理请求和响应
        pthread_create(&tid, NULL, handler_request,(void*)sock);
        pthread_detach(tid);
    }
}
