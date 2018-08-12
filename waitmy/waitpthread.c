#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>


void *thread1(void *val1)
{
    printf("thread 1 returning .....\n");
    printf("%s:pid is %d,tid is %u\n",(char*)val1,getpid(),pthread_self());
    return (void*)0; //线程终止方式1，用return返回
}

void *thread2(void *val2)
{
    printf("thread 2 exiting .....\n");
    printf("%s:pid is %d,tid is %u\n",(char*)val2,getpid(),pthread_self());
    pthread_exit ((void*)2);//线程终止方式2，调用pthread_exit
}

void *thread3(void *val3)
{
    printf("%s:pid is %d,tid is %u\n",(char*)val3,getpid(),pthread_self());
    while(1)
    {
        printf("thread 3 is running....\n");
        sleep(1);
    }
                    //线程终止方式3，用pthread_exit退i出
}


int main()
{
    pthread_t tid1; 
    pthread_t tid2;
    pthread_t tid3;
    void *ret;

    //thread 1 return 
    pthread_create(&tid1,NULL,thread1,"thread1"); //线程1创建
    pthread_join(tid1,&ret);                 //wait 线程1  ret指向单元存放thread1的返回值
    printf("thread1 return return code:%d\n",(int)ret);


    //thread 2 exit
    pthread_create(&tid2,NULL,thread2,"thread2"); //线程2创建
    pthread_join(tid2,&ret);                 //wait线程2  ret指向单元存放传给pthread_exit的参数
    printf("thread exit, exit code:%d\n",(int)ret);


    //thread 3 pthread_cancel
    pthread_create(&tid3,NULL,thread3,"thread3"); //线程3创建
    sleep(3);
    pthread_cancel(tid3);                 //线程3被其他线程用pthread_cancel取消了
    pthread_join(tid3,&ret);              //wait 线程3  ret指向单元存放PTHREAD_CANCELED
    if(ret==PTHREAD_CANCELED)
    {
        printf("thread  3 cancel ,cancel code id %d\n",(int)ret);
    }
    printf("main thread run: pid is %d , tid is %u\n", getpid(),pthread_self());
    return 0;

}



















