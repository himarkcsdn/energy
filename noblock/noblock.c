#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>


void SetNoBlock(int fd)
{
    int fl=fcntl(fd,F_GETFL); //获取文件描述符标记
    if(fl<0)
    {
        perror("fcntl");
        return ;
    }
    fcntl(fd,F_GETFL,fl|O_NONBLOCK); //设置为非阻塞
}
int main()
{
    SetNoBlock(0);
    while(1)
    {
        char buf[1024]={0};
        ssize_t read_size=read(0,buf,sizeof(buf)-1);
        if(read_size<0)
        {
            perror("read_size\n");
            sleep(1);
            continue;
        }
        printf("input: %s\n",buf);
    }
    return 0;
}










