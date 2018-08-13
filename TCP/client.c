/////////////////////////////
//客户端处理
//1 从标准输入读入字符串
//2 把读入的字符串发送给服务器
//3 尝试从服务器读取响应数据
//4 把响应结果打印到标准输出上
///////////////////////////

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;

int main(int argc, char* argv[])
{
    if(argc!=3)
    {
        printf("usage ./server [ip][port]\n");
        return 1;
    }
    // 1 创建socket
    int fd=socket(AF_INET, SOCK_STREAM,0);
    if(fd<0)
    {
        perror("socket");
        return 1;
    }
    //2 获取连接
    sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=inet_addr(argv[1]);
    server_addr.sin_port=htons(atoi(argv[2]));
    
    int ret=connect(fd, (sockaddr*)&server_addr, sizeof(server_addr));
    if(ret<0)
    {
        perror("connect");
        return 1;
    }
    // 进入循环
    while(1)
    {
        //a从标准输入读入字符串
        char buf[1024]={0};
        ssize_t read_size=read(0,buf,sizeof(buf)-1);
        if(read_size<0)
        {
            perror("read");
            return 1;
        }
        if(read_size==0)
        {
            printf("read done!\n");
            return 0;
        }
        buf[read_size]='\0';
        //b)把读入的字符串发送给服务器
        write(fd, buf, strlen(buf));
        //c)尝试从服务器读取响应数据
        char buf_resp[1024]={0};
        read_size =read(fd, buf_resp, sizeof(buf_resp)-1);
        if(read_size<0)
        {
            perror("read_size");
            return 1;
        }
        if(read_size==0)
        {
            printf("server close socket!\n");
            return 0;
        }
        buf_resp[read_size]='\0';
        //d)把响应结果打印到标准输出上
        printf("server resp: %s\n",buf_resp);
    }
    return 0;
}




















