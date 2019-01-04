/*
 * thread.cpp
 *
 *  Created on: 2017年8月11日
 *      Author: harvey
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include "thread.hpp"

Thread::Thread() :
        m_tid(0) {
    // TODO Auto-generated constructor stub
    pthread_attr_init(&attr);
}

Thread::~Thread() {
    // TODO Auto-generated destructor stub
    pthread_attr_destroy(&attr);
}

bool Thread::Start() {
    int iRet = 0;

    if (GetState() == THREAD_STATUS_NEW) {
        iRet = pthread_create(&m_tid, &attr, thread_proxy_func, this);
        if (iRet != 0) {
            printf("pthread_create:(%d)%s", errno, strerror(errno));
            return false;
        }
    }

    return true;
}

pthread_t Thread::GetThreadID() {
    return m_tid;
}

int Thread::GetState() {
    if (m_tid > 0) {
        int ret = pthread_kill(m_tid, 0);
        printf("ret = %d\n", ret);
        if (ret == 0) {
            return THREAD_STATUS_RUNNING;
        }
    }

    return THREAD_STATUS_NEW;
}

void Thread::Join() {
    pthread_join(m_tid, NULL);
}

void Thread::Join(unsigned long millisTime) {
    unsigned long k = 0;
    while (GetState() == Thread::THREAD_STATUS_RUNNING && k < millisTime) {
        usleep(100);
        k++;
    }

    if (GetState() != THREAD_STATUS_RUNNING) {
        pthread_join(m_tid, NULL);
    }
}

void Thread::Cancel(void) {
    pthread_cancel(m_tid);
}

void Thread::SetJoinable(bool flag) {
    pthread_attr_setdetachstate(&attr, flag ? PTHREAD_CREATE_JOINABLE : PTHREAD_CREATE_DETACHED);
}

//设置调度策略 policy : SCHED_RR or SCHED_OTHER or SCHED_FIFO
void Thread::SetPolicy(int policy) {
    pthread_attr_setschedpolicy(&attr, policy);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED); //要使优先级其作用必须要有这句话
}

//获取调度策略
int Thread::GetPolicy() {
    int policy;
    struct sched_param param;
    pthread_getschedparam(m_tid, &policy, &param);
    return policy;
}

//设置优先级
void Thread::SetPrioriry(int priority) {
    struct sched_param param;
    param.sched_priority = priority;
    pthread_attr_setschedparam(&attr, &param);
}

//获取优先级
int Thread::GetPrioriry() {
    int policy;
    struct sched_param param;
    pthread_getschedparam(m_tid, &policy, &param);
    return param.__sched_priority;
}


void * Thread::thread_proxy_func(void * args) {
    Thread * pThread = static_cast<Thread *>(args);

    pThread->Run();

    return NULL;
}

