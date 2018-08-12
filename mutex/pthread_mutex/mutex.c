#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<sched.h>

int ticket=100;
pthread_mutex_t mutex; //定义互斥量

void* route(void *arg)
{
    char *id=(char*)arg;
    while(1)
    {
        pthread_mutex_lock(&mutex);//互斥量加锁
        if(ticket>0)
        {
            usleep(200000);
            printf("%s sells ticket: %d\n",id,ticket);
            ticket--;
            pthread_mutex_unlock(&mutex); //互斥量解锁
        }
        else
        {
            pthread_mutex_unlock(&mutex);//互斥量解锁，退出
            break;
        }
    }
}


int main()
{
    pthread_t t1, t2, t3, t4;

    pthread_mutex_init(&mutex,NULL);
    
    pthread_create(&t1,NULL,route,"pthread1");//创建线程 1，2，3，4，
    pthread_create(&t2,NULL,route,"pthread2");
    pthread_create(&t3,NULL,route,"pthread3");
    pthread_create(&t4,NULL,route,"pthread4");

    pthread_join(t1,NULL);  //线程1，2，3，4，等待
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);

    pthread_mutex_destroy(&mutex); //销毁互斥量
}






