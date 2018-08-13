#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


int main()
{
    int fds[2];
    char buf[100];
    int len;

    if(pipe(fds)==-1)
    {
        perror("make pipe");
        exit(1);
    }
    //get键盘输入，写入管道
    while(fgets(buf,100,stdin))
    {
        len=strlen(buf);
        if(write(fds[1],buf,len)!=len)
        {
            perror("write to pipe");
            exit(1);
        }

        memset(buf,0x00,sizeof(buf));
        //读取官道， 写入屏幕
        if((len=read(fds[0],buf,100))==-1)
        {
            perror("read pipe");
            break;
        }
        if(write(fds[1],buf,len)!=len)
        {
            perror("write stdout");
            break;
        }
    }   
}
