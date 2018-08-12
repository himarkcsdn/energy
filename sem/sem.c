
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>

int ring[64];
sem_t blank_sem;
sem_t data_sem;

void* producter(void* arg)
{
    int step=0;
    int data=0;
    while(1)
    {
        sleep(1);  
        sem_wait(&blank_sem); //等待信号量 v
        data=rand()%123;   
        ring[step]=data;  
        ++step;
        step%=64;
        printf("product done:%d\n",data);
        sem_post(&data_sem);//发布信号量 p
    }
}

void* consumer(void* arg)
{
    int step=0;
    int data=0;
    while(1)
    {
        sem_wait(&data_sem); //等待信号量 v
        data=ring[step];
        ++step;
        step%=64;
        printf("consumer done:%d\n",data);
        sem_post(&blank_sem); //发布信号量p
    }
}

int main()
{
    sem_init(&blank_sem,0,64);//格子信号量的初始化
    sem_init(&data_sem,0,0); //数据信号量的初始化

    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,producter,NULL);
    pthread_create(&tid2,NULL,consumer,NULL);
    
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

    sem_destroy(&blank_sem);
    sem_destroy(&data_sem);
    return 0;
}
















