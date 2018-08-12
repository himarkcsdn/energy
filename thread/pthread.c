#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>

void *rout(void *_val)
{
        printf("I am %s pid is : %d , tid is : %u\n",(char*)_val,(int)getpid(),(unsigned long long)pthread_self());
        return NULL;
}
int main()
{
    pthread_t tid;
    int ret;
    ret=pthread_create(&tid,NULL,rout,"pthread1");
    if(ret!=0)
    {
        fprintf(stderr, "pthread_create: %s\n",strerror(ret));
        exit(EXIT_FAILURE);
    }
        printf("I am main thread pid is : %d , tid is %u\n",(int)getpid(),(unsigned long long)pthread_self());
        sleep(1);
        return 0;
}






