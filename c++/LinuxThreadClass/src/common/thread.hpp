/*
 * thread.h
 *
 *  Created on: 2017年8月11日
 *      Author: harvey
 */

#ifndef SRC_THREAD_H_
#define SRC_THREAD_H_

#include <pthread.h>

class Thread {
public:
	//构造函数
	Thread();
	//析构函数
	virtual ~Thread();
	//线程的运行实体
	virtual void Run(void)=0;
	//开始执行线程
	bool Start(void);
	//获取线程ID
	pthread_t GetThreadID(void);
	//获取线程状态
	int GetState(void);
	//等待线程直至退出
	void Join(void);
	//等待线程退出或者超时
	void Join(unsigned long millisTime);
	//线程退出
	void Cancel(void);
	//设置线程join属性
	void SetJoinable(bool flag = true);
    //设置调度策略 policy : SCHED_RR or SCHED_OTHER or SCHED_FIFO
    void SetPolicy(int policy);
    //获取调度策略
    int GetPolicy();
	//设置优先级
	void SetPrioriry(int priority);
	//获取优先级
	int GetPrioriry();

private:
	//获取执行方法的指针
	static void * thread_proxy_func(void * args);

public:
	enum {
        //线程的状态－新建
        THREAD_STATUS_NEW = 0,
        //线程的状态－正在运行
        THREAD_STATUS_RUNNING
	};

private:
	//线程id;
	pthread_t m_tid;
	//线程属性
	pthread_attr_t attr;

};
#endif /* SRC_THREAD_H_ */
