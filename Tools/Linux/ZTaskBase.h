/* ZTaskBaset  '(zhangpengpeng 2012/03/07)
 * base class to do tasks
 * run as a thread or process
 * modified for linux '(zhangpengpeng 2012/04/07)
 */

#ifndef _ZTASKBASET_H_
#define _ZTASKBASET_H_

#include <pthread.h>
#include <semaphore.h>
#include <deque>
using namespace std;

class ZLock {
private:
#ifdef ZOS_TYPE_WIN
	CRITICAL_SECTION m_crtSetion;
#else
	pthread_mutex_t oper_mutex;
#endif

public:
	ZLock();
	~ZLock();
	void lock();
	void unlock();
};

class ZTaskList { //class to mgt taks list
private:
	ZLock oper_lock;
	deque<const void*> task_queue;

public:
	ZTaskList();
	virtual ~ZTaskList();

	bool add(const void *pTask);
	bool get(const void **ppTask);
	bool clear();
};

class ZTaskBase
{
public:
	virtual int Task_Do(const void *pTask) = 0;

	bool Task_Start();
	bool Task_Stop();
	bool Task_Add(const void *pTask);
	bool Task_Clear();

public:
	ZTaskBase(void);
	virtual ~ZTaskBase(void);
	int taskThread();

private:
	ZTaskList task_list;
	bool isEnd_Thread;
	pthread_t thread_id;
	sem_t sem_tasklist;
};

#endif // _ZTASKBASET_H_

