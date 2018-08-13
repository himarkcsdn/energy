/////////////////////////
//服务器基本流程
//从socket中读取数据（请求）
//2 根据请求计算生成  （回应）
//3 把回应写入到客户端
//由于目前实现的是  echo_server。省略 回应的步骤
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;

void* ThreadEntry(void* arg)
{
    int new_sock=(int)arg;
    while(1)
    {
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
            //TCP中说明，对端关闭了连接
            printf("[client %lu] disconnetc!\n", new_sock);
            close(new_sock);
            return NULL;
        }
        buf[read_size]='\0';
        //b 根据请求计算响应（忽略）
        printf("[client %lu] %s \n", new_sock, buf);
        //c 把响应写回到客户端
        write(new_sock, buf,strlen(buf));
    }
    return NULL;
}

void ProcessConnect(int new_sock)
{
    //创建线程完成和客户端的交互
    //
    //完成一次连接的处理
    //需要循环的处理客户端发送来的数据
    pthread_t tid;
    pthread_create(&tid, NULL,ThreadEntry,(void*)new_sock);
    pthread_detach(tid);
}






int main(int argc, char* argv[])
{
    if(argc!=3)
    {
        printf("usage ./server [ip] [port]\n");
        return 1;
    }

    //1 创建socket
    int listen_sock=socket(AF_INET,SOCK_STREAM,0);
    if(listen_sock<0)
    {
        perror("socket");
        return 1;
    }

    //2 绑定端口号
    sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr(argv[1]);
    server.sin_port=htons(atoi(argv[2]));
    int ret=bind(listen_sock, (sockaddr*)&server, sizeof(server));
    if(ret<0)
    {
        perror("bind");
        return 1;
    }

    //3 使用listen 允许服务器被客户端连接
    ret =listen(listen_sock, 5);
    if(ret<0)
    {
        perror("listen");
        return 1;
    }
    //4 服务器初始化完成，进入事件循环
    printf("Server Init OK!\n");
    while(1)
    {
        sockaddr_in peer;
        socklen_t len=sizeof(peer);
        int new_sock=accept(listen_sock, (sockaddr*)&peer, &len);
        if(new_sock<0)
        {
            perror("accept");
            continue;
        }
        printf("[client %d] connect!\n", new_sock);
        ProcessConnect(new_sock);
    }
    return 0;
}













