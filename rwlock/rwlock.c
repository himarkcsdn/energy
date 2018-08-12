#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

pthread_rwlock_t rwlock;//定义一把读写锁
int buf=0;

void* reader(void* arg)//读者句柄
{
    pthread_detach(pthread_self());//线程分离
    while(1)
    {
        //try lock by reader;
        if(pthread_relock_trywrlock(&rwlock)!=0)
        {
            printf("writer is writing,reader waiting...\n");//读者获取锁资源失败
        }
        else
        {
            printf("writer is %lu,value is %d\n",pthread_self(),buf);
            pthread_rwlock_unlock(&rwlock); //读者读完数据后释放锁资源
        }
        sleep(2);
    }
}

void* writer(void* arg) //写者句柄
{
    pthread_detach(pthread_self());//线程分离
    while(1)
    {
        if(pthread_rwlock_tryrdlock(&rwlock)!=0)
        {
            printf("reader is reading ,writer waiting...\n");//获取锁资源失败i
            sleep(1);
        }
        else
        {
            buf++; //write
            printf("writer is %lu, the value is %d\n",pthread_self(),buf);
            pthread_rwlock_unlock(&rwlock);//写者写完之后释放锁资源
        }
        sleep(2);
    }
}
int main()
{
    pthread_rwlock_init(&rwlock,NULL);//初始化锁
    pthread_t read,write; 
    int i=0;
    for(;i<2;++i)  //创建2个读者线程
    {
        pthread_create(&read,NULL,reader,NULL);
    }
    for(i=0;i<3;++i)//创建3个写者线程
    {
        pthread_create(&write,NULL,writer,NULL);
    }
    for(i=0;i<2;++i) //对读者线程进行等待
    {
        pthread_join(read,NULL);
    }
    for(i=0;i<3;++i)//对写者线程进行等待
    {
        pthread_join(write,NULL);
    }

    pthread_rwlock_destroy(&rwlock); //销毁读写锁
    return 0;
}








