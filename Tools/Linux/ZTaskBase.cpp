/* ZTaskBaset  '(zhangpengpeng 2012/03/07)
 * base class to do tasks
 */

#include "ZTaskBase.h"

ZLock::ZLock()
{
#ifdef ZOS_TYPE_WIN
		InitializeCriticalSection(&m_crtSetion);
#else
		pthread_mutex_init(&oper_mutex, NULL);
#endif
}

ZLock::~ZLock()
{
#ifdef ZOS_TYPE_WIN
		DeleteCriticalSection(&m_crtSetion);
#else
		pthread_mutex_destroy(&oper_mutex);
#endif
}

void ZLock::lock()
{
#ifdef ZOS_TYPE_WIN
		EnterCriticalSection(&m_crtSetion);
#else
		pthread_mutex_lock(&oper_mutex);
#endif
}

void ZLock::unlock()
{
#ifdef ZOS_TYPE_WIN
		LeaveCriticalSection(&m_crtSetion);
#else
		pthread_mutex_unlock(&oper_mutex);
#endif
}

ZTaskList::ZTaskList()
{
}
ZTaskList::~ZTaskList()
{
}

bool ZTaskList::add(const void *pTask)
{
	oper_lock.lock();
	task_queue.push_back(pTask);
	oper_lock.unlock();
	return true;
}

bool ZTaskList::get(const void **ppTask)
{
	oper_lock.lock();
	if (task_queue.empty())
	{
		oper_lock.unlock();
		return false;
	}

	*ppTask = task_queue.front();
	task_queue.pop_front();
	oper_lock.unlock();
	return true;
}

bool ZTaskList::clear()
{
	oper_lock.lock();
	task_queue.clear();
	oper_lock.unlock();
	return true;
}

ZTaskBase::ZTaskBase(void)
{
	thread_id = 0;
	isEnd_Thread = false;
	sem_init(&sem_tasklist, 0, 0);
}

ZTaskBase::~ZTaskBase(void)
{
	sem_destroy(&sem_tasklist);
}

//DWORD __stdcall _ztaskbase_Thread_Task(LPVOID lpParam)
void *_ztaskbase_Thread_Task(void *lpParam)
{
	ZTaskBase *pTaskBase = (ZTaskBase*)lpParam;
	if (pTaskBase == NULL)
		return NULL;

	pTaskBase->taskThread();
	return NULL;
}

int ZTaskBase::taskThread()
{
	const void *pTask = NULL; 

	while (!isEnd_Thread)
	{
		//ZLOG_INFO("Before enter sem_tasklist.\n");
		sem_wait(&sem_tasklist);
		//ZLOG_INFO("after enter sem_tasklist.\n");

		if (task_list.get(&pTask))
		{
			if (isEnd_Thread)	// pTask == NULL, when post stop msg
				break;

			if (pTask == NULL)
				continue;

			Task_Do(pTask);		// do task
		}
	}

	return 0;
}

bool ZTaskBase::Task_Start()
{
	if (0 != pthread_create(&thread_id, NULL, _ztaskbase_Thread_Task, this))
	{
		thread_id = 0;
		return false;
	}

	Task_Clear();
	return true;
}

bool ZTaskBase::Task_Stop()
{
	Task_Clear();
	if (thread_id != 0)
	{
		isEnd_Thread = true;
		Task_Add(NULL);

		int *temptr = NULL;
		pthread_join(thread_id, (void**)&temptr);
		thread_id = 0;
	}

	return true;
}

bool ZTaskBase::Task_Add(const void *pTask)
{
	// if pTask == NULL, set Exit singal before.

	bool bRet = false;
	bRet = task_list.add(pTask);
	if (bRet)
	{
		sem_post(&sem_tasklist);
	}

	return bRet;
}

bool ZTaskBase::Task_Clear()
{
	return task_list.clear();
}

