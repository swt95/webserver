#pragma once
#include<pthread.h>
#include<exception>
#include<semaphore.h>

using namespace std;

class Locker{
public:
    //构造
    Locker()
    {
        //初始化互斥锁
        if(pthread_mutex_init(&m_mutex, NULL) != 0)
        {
            throw std::exception();
        }
    }
    //析构
    ~Locker()
    {
        //销毁锁
        pthread_mutex_destroy(&m_mutex);
    }

    //加锁
    bool lock()
    {
        return pthread_mutex_lock(&m_mutex) == 0;

    }

    //解锁
    bool unlock()
    {
        return pthread_mutex_unlock(&m_mutex) == 0;
    }
    //获取锁
    pthread_mutex_t * get()
    {
        return & m_mutex;
    }
private:
    pthread_mutex_t m_mutex;

}


//条件变量
class Cond
{
public:
    //构造
    Cond()
    {
        if(pthread_cond_init(&m_cond, NULL) != 0)
        {
            throw std::exception();
        }
    }
    //析构
    ~Cond()
    {
        pthread_cond_destroy(&m_cond);
    }
    //阻塞wait
    bool wait(pthread_mutex_t * mutex)
    {
        return pthread_cond_wait(&m_cond, mutex) == 0;
    }
    //唤醒signal
    bool signal()
    {
        return pthread_cond_signal(&m_cond) == 0;
    }
    //唤醒所有
    bool broadcast()
    {
        return pthread_cond_broadcast(&m_cond) == 0;
    }
    //设置超时时间timedwait
    bool timedwait(pthread_mutex_t * mutex, struct timespec t)
    {
        return pthread_cond_timedwait(&m_cond, mutex, &t) == 0;
    }
private:
    pthread_cond_t m_cond;
}

//信号量
class Sem
{
public:
    //默认构造
    Sem()
    {
        if(sem_init(&m_sem,0,0) != 0)
        {
            throw std::exception();
        }
    }
    //有参构造
    Sem(int num)
    {
        if(sem_init(&m_sem,0,num) != 0)
        {
            throw std::exception();
        }
    }
    //析构
    ~Sem()
    {
        sem_destroy(&m_sem);
    }
    //加锁
    bool wait()
    {
        return sem_wait(&m_sem) == 0;
    }
    //解锁
    bool post()
    {
        return sem_post(&m_sem) == 0;
    }

private:
    sem_t m_sem;
}