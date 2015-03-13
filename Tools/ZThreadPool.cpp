/* ZThreadPool '(zhangpengpeng 2012/03/07)
 * Thread Pool
 */

#include "ZThreadPool.h"
#include <algorithm>

class ZTPOneLock
{
private:
	const HANDLE *mutexOne;

public:
	ZTPOneLock(const HANDLE *mt) : mutexOne(mt)
	{
		WaitForSingleObject(*mutexOne, INFINITE);
	}

	~ZTPOneLock()
	{
		ReleaseMutex(*mutexOne);
	}
};

class _zThreadTask_private : public ZThreadTaskInterface
{
private:
	ZTP_TASKDO_FUN fun;
	void *param;

public:
	_zThreadTask_private(ZTP_TASKDO_FUN f, void *p) : fun(f), param(p) {}
	virtual int Task_Do() 
	{
		if (fun) 
			return fun(param);
		return -1;
	}

};

ZThreadPool::ZThreadPool(void)
{
	threadNum = 0;
	runningNum = 0;

	maxThreadNum = 0;
	initThreadNum = 0;
	increThreadNum = 0;

	eventEndAll = NULL;
	eventEndComplete = NULL;
	semEnd = NULL;
	semTask = NULL;
	mutexThread = NULL;
	mutexTask = NULL;
	mutexAdjust = NULL;
}

ZThreadPool::~ZThreadPool(void)
{
}

DWORD __stdcall _zthreadpool_Thread_Task(LPVOID lpParam)
{
	ZTHREADINFO *pInfo = (ZTHREADINFO*)lpParam;
	if (pInfo == NULL || pInfo->pool== NULL)
		return 0;

	return pInfo->pool->taskThread(pInfo);
}

int ZThreadPool::taskThread(ZTHREADINFO *threadInfo)
{
	HANDLE hEvents[3] = {eventEndAll, semEnd, semTask};
	ZThreadTaskInterface *pTask = NULL; 

	while (1)
	{
		DWORD dwWait = WaitForMultipleObjects(3, hEvents, FALSE, INFINITE);
		if (dwWait == WAIT_OBJECT_0 || dwWait == (WAIT_OBJECT_0 + 1))
			break;				// exit the thread

		{
			InterlockedIncrement(&runningNum);
			if (runningNum >= threadNum)
				adjustThreadNum();

			{
				ZTPOneLock oneLock(&mutexTask);
				if (taskList.empty())
					continue;

				pTask = taskList.front();
				taskList.pop_front();
			}

			if (pTask != NULL)
			{
				pTask->Task_Do();	// do task
				threadInfo->count++;
			}

			InterlockedDecrement(&runningNum);
			if (runningNum <= threadNum - increThreadNum)
				adjustThreadNum();
		}

	}

	endThread(threadInfo);
	return 0;
}

int ZThreadPool::createThreads(int iNum)
{
	static int iThreadIndex = 0;

	if (threadNum >= maxThreadNum)
		return 0;

	int iSuccessNum = 0;
	while (iSuccessNum < iNum)
	{
		ZTHREADINFO *pThreadInfo = new ZTHREADINFO();
		pThreadInfo->index = iThreadIndex++;
		pThreadInfo->pool = this;
		pThreadInfo->count = 0;
		pThreadInfo->hThread = CreateThread(NULL, 0, _zthreadpool_Thread_Task, pThreadInfo, 0, &pThreadInfo->threadId);

		if (pThreadInfo->hThread == NULL)
		{
			delete pThreadInfo;
			break;
		}

		InterlockedIncrement(&threadNum);
		ZTPOneLock oneLock(&mutexThread);
		threadList.push_back(pThreadInfo);
		iSuccessNum++;
	}
	return iSuccessNum;
}

int ZThreadPool::endThread(ZTHREADINFO *threadInfo)
{
	InterlockedDecrement(&threadNum);
	{
		ZTPOneLock oneLock(&mutexThread);
		threadList.erase(find(threadList.begin(), threadList.end(), threadInfo));
	}

	//TRACE(_T("\nThread[%d:%d:0x%x] end. Run times: %d. "), \
	//	threadInfo->index, threadInfo->hThread, threadInfo->threadId, threadInfo->count);

	CloseHandle(threadInfo->hThread);
	threadInfo->hThread = NULL;
	delete threadInfo;

	if (threadNum == 0)
		SetEvent(eventEndComplete);

	return 0;
}

bool ZThreadPool::adjustThreadNum()
{
	ZTPOneLock AdjustLock(&mutexAdjust);

	long lThread = threadNum;
	long lTaskNum = runningNum - 1;
	{
		ZTPOneLock oneLock(&mutexTask);
		lTaskNum += taskList.size();
	}

	if (lTaskNum < (initThreadNum + increThreadNum)
		&& lThread < (initThreadNum + increThreadNum))		// perhaps most time this may be true
		return true;

	if (lTaskNum >= (lThread + increThreadNum))
	{
		if (threadNum >= maxThreadNum)
			return false;

		if (createThreads(increThreadNum) < increThreadNum)
			return false;
	}
	else if (lTaskNum <= (lThread - increThreadNum))
	{
		int iEndNum = (lThread - increThreadNum) >= initThreadNum ? increThreadNum : (lThread - initThreadNum);
		ReleaseSemaphore(semEnd, iEndNum, NULL);
	}
	
	return true;
}

bool ZThreadPool::Start(int maxThreadNum, int initThreadNum, int increThreadNum)
{
	this->maxThreadNum = maxThreadNum;
	this->initThreadNum = initThreadNum;
	this->increThreadNum = increThreadNum;

	if (increThreadNum < 1)
		return false;

	if (initThreadNum > maxThreadNum)
		return false;

	eventEndAll = CreateEvent(NULL, TRUE, FALSE, NULL);
	eventEndComplete = CreateEvent(NULL, FALSE, FALSE, NULL);
	semEnd = CreateSemaphore(NULL, 0, 0x7FFFFFFF, NULL);
	semTask = CreateSemaphore(NULL, 0, 0x7FFFFFFF, NULL);
	mutexThread = CreateMutex(NULL, FALSE, NULL);
	mutexTask = CreateMutex(NULL, FALSE, NULL);
	mutexAdjust = CreateMutex(NULL, FALSE, NULL);

	ClearTasks();
	if (createThreads(initThreadNum) < initThreadNum)
	{
		Stop();
		return false;
	}

	return true;
}

bool ZThreadPool::Stop()
{
	ClearTasks();

	SetEvent(eventEndAll);
	WaitForSingleObject(eventEndComplete, INFINITE);

	if (eventEndAll)
	{
		CloseHandle(eventEndAll);
		eventEndAll = NULL;
	}
	if (eventEndComplete)
	{
		CloseHandle(eventEndComplete);
		eventEndComplete = NULL;
	}
	if (semEnd)
	{
		CloseHandle(semEnd);
		semEnd = NULL;
	}
	if (semTask)
	{
		CloseHandle(semTask);
		semTask = NULL;
	}
	if (mutexThread)
	{
		CloseHandle(mutexThread);
		mutexThread = NULL;
	}
	if (mutexTask)
	{
		CloseHandle(mutexTask);
		mutexTask = NULL;
	}
	if (mutexAdjust)
	{
		CloseHandle(mutexAdjust);
		mutexAdjust = NULL;
	}

	return true;
}

bool ZThreadPool::AddTask(ZThreadTaskInterface *task)
{
	ZTPOneLock oneLock(&mutexTask);
	taskList.push_back(task);
	ReleaseSemaphore(semTask, 1, NULL);
	return true;
}

bool ZThreadPool::AddTask(ZTP_TASKDO_FUN fun, void *param)
{
	_zThreadTask_private *task = new _zThreadTask_private(fun, param);
	if (task == NULL)
		return false;

	return AddTask(task);
}

bool ZThreadPool::ClearTasks()
{
	ZTPOneLock oneLock(&mutexTask);
	taskList.clear();
	return true;
}
