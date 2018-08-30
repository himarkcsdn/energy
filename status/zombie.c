#include<stdio.h>
#include<stdlib.h>

int main()
{
    int ret=fork();
    if(ret<0)
    {
        perror("fork");
        return 1;
    }
    else if(ret ==0)
    {
        printf("wo shi child\n");
        sleep(20);
    }
    else
    {
        printf("wo shi parent\n");
        sleep(5);
        exit(0);
    }
    return 0;
}





