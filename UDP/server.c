/////////////////////////
//服务器逻辑
//
//1启动（初始化）
//进入一个死循环
//  a从socket中读取请求
//  b根据请求的内容计算生成回应
//  c把回应写到socket中
////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;

//     127.0.0.1   9090
int main(int argc, char* argv[])
{
    //校验命令行参数
    if(argc!=3)
    {
        printf("usage ./server [ip] [port]\n");
        return 2;
    }
    //服务器的初始化
    // a)创建socket
    // AF_INET: ipv4协议

    int fd=socket(AF_INET, SOCK_DGRAM, 0);
    if(fd<0)
    {
        perror("socket");
        return 1;
    }
    //b 绑定ip地址的端口号
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    //点分十进制字符串IP地址转换成数字（网络字节序)
    addr.sin_addr.s_addr=inet_addr(argv[1]);
    addr.sin_port=htons(atoi(argv[2]));
    int ret=bind(fd, (sockaddr*)&addr,sizeof(addr));
    if(ret<0)
    {
        perror("bind");
        return 1;
    }
    //2.进入死循环
    while(1)
    {
        //a读取请求
        struct sockaddr_in peer;
        socklen_t len=sizeof(peer);
        char buf[1024]={0};
        ssize_t read_size=recvfrom(fd, buf, sizeof(buf)-1,0, (sockaddr*)&peer, &len);
        if(read_size<0)
        {
            perror("recvfrom");
            continue;
        }
        buf[read_size]='\0';
        //b 根据请求计算（此处实现的是echo_server。所以省略）
        printf("[client %s:%d] say:%s\n", inet_ntoa(peer.sin_addr),ntohs(peer.sin_port),buf);
        //c 把响应结果写回到socket
        //缓冲区长度最好不要写成sizeof.由于我们只传输数据有效部分
        sendto(fd, buf, strlen(buf),0, (sockaddr*)&peer, sizeof(peer));
    }
    close(fd);
    return 0;

}


