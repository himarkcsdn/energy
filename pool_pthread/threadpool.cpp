#include<iostream>
#include<pthread.h>
#include<cstdio>
#include<list>
#include<exception>


#include"locker.h"

template<typename T>
class threadpool
{
public:
    threadpool(int thread_number=8, int max_requests=1000);
    ~threadpool();
    bool append(T* request);  //向请求队列中添加请求

private:
    static void* worker(void *arg); //线程执行函数
    void run(); 

private:
    int m_thread_number;    //线程的数量
    int m_max_request;   //请求队列的最大容量
    pthread_t *m_threads;  // 指向管理线程tid的数组
    std::list<T*> m_workqueue;  //请求队列
    locker m_queuelocker;     //保护请求队列的互斥锁
    sem m_queuestat;  //请求队列中是否有任务要处理
    bool m_stop;    //是否结束线程

};


template<typename T>
threadpool<T>::threadpool(int thread_number, int max_requests)
    :m_thread_number(thread_number)
     ,m_max_request(max_requests)
     ,m_stop(false)
     ,m_threads(NULL)
{
    //如果线程数量小于0或者请求队列容量小于0
    if((thread_number<=0)||(max_requests<=0))
    {
        throw std::exception();
    }

    //为管理线程tid数组开辟空间
    m_threads=new pthread_t[thread_number];
    if(!m_threads) 
    {
        throw std::exception();
    }
    //创建thread_number个线程，将状态设置为分离
    for(int i=0;i<thread_number;i++)
    {
        if(pthread_create(m_threads+i,NULL,worker,(void*)this)!=0) 
        {
            delete[] m_threads;
            throw std::exception();
        }

        if(pthread_detach(m_threads[i]))
        {
            delete[] m_threads; 
            throw  std::exception();
        }
    }
}

template<typename T>
threadpool<T>::~threadpool()
{
    delete [] m_threads;
    m_stop=true;
}

    
template<typename T>
bool threadpool<T>::append(T* request) //向请求队列中添加请求任务
{
    
    m_queuelocker.lock();
    if(m_workqueue.size()>m_max_request) //确保请求队列任务没有被堆满
    {
        m_queuelocker.unlock();
        return false;
    }
    m_workqueue.push_back(request);
    m_queuelocker.unlock();
    m_queuestat.post();   //每添加一个请求让信号量增加
    return true;
}

template<typename T>
void threadpool<T>::run()
{
    while(!m_stop)
    {
        m_queuestat.wait();
        m_queuelocker.lock();
        if(m_workqueue.empty())
        {
            m_queuelocker.unlock();
            continue;
        }
        
        T* request=m_workqueue.front();
        m_workqueue.pop_front();
        m_queuelocker.unlock();
        request->process(); 
    }
}














