#include<unistd.h>
#include<stdio.h>

int main()
{
    daemon(1,1);
    while(1);
    return 0;
}



