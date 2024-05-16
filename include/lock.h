//线程同步：互斥锁、条件变量、信号量

#include<iostream>
#include<pthread.h>
#include<exception>
#include<semaphore.h>

using namespace std;

//==================互斥锁========================
class Locker
{
public:
	//构造函数进行初始化操作
	Locker()
	{
		int ret = pthread_mutex_init(&mutex, NULL);
		if(ret != 0)
		{
			throw exception();
		}	
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
		return &m_mutex;
	}

	//析构函数销毁互斥锁
	~Locker()
	{
		pthread_mutex_destroy(&m_mutex);
	}

private:
	pthread_mutex_t m_mutex;

}


//======================条件变量=====================

class Cond
{
public:
	//构造函数初始化
	Cond()
	{
		int ret = pthread_cond_init(&m_cond, NULL);
		if(ret != 0)
		{
			throw exception();
		}
	}

	
	//阻塞等待
	bool wait(pthread_mutex_t * m_mutex)
	{
		return pthread_cond_wait(&m_cond, m_mutex) == 0;
	}

	//通知
	bool signal()
	{
		return pthread_cond_signal(&m_cond) == 0;
	}

	//析构函数销毁条件变量
	~Cond()
	{
		pthread_cond_destroy(&m_cond);
	}


private:
	pthread_cond_t m_cond;
	pthread_mutex_t m_mutex;
}

//=============================信号量==================================

class Sem
{
public:
	//构造函数初始化
	Sem()
	{
		int ret = sem_init(&m_sem, 0, 0);
		if(ret != 0)
		{
			throw exception();
		}
	}

	Sem(int num)
	{
		int ret = sem_init(&m_sem, 0, num);
		if(ret != 0)
		{
			throw exception();
		}
	}

	//-1
	bool wait()
	{
		return sem_wait(&m_sem) == 0;
	}

	//+1
	bool post()
	{
		return sem_post(&m_sem) == 0;
	}


	~Sem()
	{
		sem_destroy(&m_sem);
	}


private:
	sem_t m_sem;
}
