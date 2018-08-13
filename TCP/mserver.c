/////////////////////////////
//服务器基本流程（多进程）
//1 从sock中读取数据（请求）
//2 根据请求计算生成（回应）
//3 把回应写到客户端
//由于目前实现的是echo_server，省略请求的计算

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include<signal.h>
#include<netinet/in.h>
#include<arpa/inet.h>

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;

void ProcessConnect(int new_sock, sockaddr_in* peer)
{
    while(1)
    {
        int ret=fork();
        if(ret<0)
        {
            perror("fork");
            return ;
        }
        if(ret>0)
        {
             //父进程，考虑僵尸进程的问题，wait,waitpid是不行的
             //简单方案是忽略 SIGCHLD信号
             signal(SIGCHLD, SIG_IGN);
             //文件描述符需要父子进程都关闭
             close(new_sock);
             return ;
        }
        //子进程  
        //a 从客户端读取数据
        char buf[1024]={0};
        ssize_t read_size=read(new_sock, buf, sizeof(buf)-1);
        if(read_size<0)
        {
            perror("read");
            continue;
        }
        if(read_size==0)
        {
            //TCP中，read的返回值为0说明对端关闭了连接
            printf("[client %s: %d] disconnect!\n", inet_ntoa(peer->sin_addr),ntohs(peer->sin_port));
            close(new_sock);
            // 注意！！！、
            // 不能直接让函数返回，让子进程直接退出，
            // 如果是函数返回，子进程也会尝试进行accept
            // 这样的动作是没有必要的，父进程已经负责了accept
            //子进程只要把对应的客户端服务好就行了
            exit(0);
        }
        buf[read_size]='\0';
        //根据请求计算响应（忽略）
        printf("[client %s:%d] %s\n",inet_ntoa(peer->sin_addr),ntohs(peer->sin_port), buf);
        //把响应写回到客户端
        write(new_sock, buf,strlen(buf));
    }
}

//  ./server [ip] [port]
int main(int argc, char* argv[])
{
    if(argc!=3)
    {
        printf("usage ./server[ip] [port]\n");
        return 1;
    }
    //1.创建 socket
    int sock=socket(AF_INET, SOCK_STREAM,0);
    if(sock<0)
    {
        perror("socket");
        return 1;
    }
    //2 绑定端口号
    sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr(argv[1]);
    server.sin_port=htons(atoi(argv[2]));
    
    int ret=bind(sock, (sockaddr*)&server, sizeof(server));
    if(ret<0)
    {
        perror("bind");
        return 1;
    }

    //3 使用listen允许服务器被客户端连接
    ret=listen(sock, 5);
    if(ret<0)
    {
        perror("bind");
        return 1;
    }
    //4 服务器初始化完成，进入事件循环
    printf("Server Init OK！\n");
    while(1)
    {
        sockaddr_in peer;
        socklen_t len=sizeof(peer);
        int new_sock=accept(sock,(sockaddr*)&peer, &len);
        if(new_sock<0)
        {
            perror("accept");
            continue;
        }
        printf("[clien %s:%d] connect!\n", inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
        ProcessConnect(new_sock, &peer);
    }
    return 0;
}


























