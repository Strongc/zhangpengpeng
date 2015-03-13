/* ZTaskBaset  '(zhangpengpeng 2012/03/07)
 * base class to do tasks
 */

#include "ZTaskBase.h"
#include "ZAutoLock.h"

ZTaskList::ZTaskList()
{
	InitializeCriticalSection(&cs);
}
ZTaskList::~ZTaskList()
{
	DeleteCriticalSection(&cs);
}

bool ZTaskList::Add(const void *task)
{
	ZAutoLock lock(&cs);
	taskQue.push(task);
	return true;
}

bool ZTaskList::Get(const void **task)
{
	ZAutoLock lock(&cs);
	if (taskQue.empty())
		return false;
	*task = taskQue.front();
	taskQue.pop();
	return true;
}

bool ZTaskList::ClearAll()
{
	ZAutoLock lock(&cs);
	while (!taskQue.empty())
	{
		const void *task = taskQue.front();
		if (task != NULL) delete task;
		taskQue.pop();
	}
	return true;
}

ZTaskBase::ZTaskBase(void)
{
	hThread = NULL;
	hEventEndThread = CreateEvent(NULL, FALSE, FALSE, NULL);
	hEventNewTask = CreateEvent(NULL, TRUE, FALSE, NULL);
}

ZTaskBase::~ZTaskBase(void)
{
	if (hEventEndThread)
	{
		CloseHandle(hEventEndThread);
		hEventEndThread = NULL;
	}

	if (hEventNewTask)
	{
		CloseHandle(hEventNewTask);
		hEventNewTask = NULL;
	}
}

DWORD __stdcall _ztaskbase_Thread_Task(LPVOID param)
{
	ZTaskBase *taskBase = (ZTaskBase*)param;
	if (taskBase == NULL)
		return 0;

	return taskBase->taskThread();
}

int ZTaskBase::taskThread()
{
	HANDLE hEvents[2] = {hEventEndThread, hEventNewTask};
	const void *task = NULL; 

	while (1)
	{
		if (WaitForMultipleObjects(2, hEvents, FALSE, INFINITE) == WAIT_OBJECT_0)
			break;				// exit the thread

		while (taskList.Get(&task) != false)
		{
			if (task == NULL)
				continue;

			Task_Do(task);		// do task
		}

		ResetEvent(hEventNewTask);
	}

	return 0;
}

bool ZTaskBase::Task_Start()
{
	hThread = CreateThread(NULL, 0, _ztaskbase_Thread_Task, this, 0, NULL);
	if (hThread ==  NULL)
		return false;

	Task_Clear();
	return true;
}

bool ZTaskBase::Task_Stop()
{
	Task_Clear();
	if (hThread)
	{
		SetEvent(hEventEndThread);
		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);
		hThread = NULL;
	}

	return true;
}

bool ZTaskBase::Task_Add(const void *task)
{
	bool bRet = false;
	bRet = taskList.Add(task);
	if (bRet)
		SetEvent(hEventNewTask);

	return bRet;
}

bool ZTaskBase::Task_Clear()
{
	ResetEvent(hEventNewTask);
	return taskList.ClearAll();
}
