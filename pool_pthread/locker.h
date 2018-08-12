#pragma once

#include<exception>
#include<pthread.h>
#include<semaphore.h>

//信号量
class sem
{
public:
    sem();
    ~sem();
    bool wait();
    bool post();
private:
    sem_t m_sem;
        
};

//互斥锁
class locker
{
public:
    locker();
    ~locker();
    bool lock();
    bool unlock();

private:
    pthread_mutex_t m_mutex;
};

//条件变量
class cond
{
public:
    cond();
    ~cond();
    bool wait();
    bool signal();

private:

    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
};



