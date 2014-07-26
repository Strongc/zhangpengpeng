/* ZTaskBaset  '(zhangpengpeng 2012/03/07)
 * base class to do tasks
 */

#include "StdAfx.h"
#include "ZTaskBase.h"
#include "ZAutoLock.h"

CZTaskList::CZTaskList()
{
	InitializeCriticalSection(&m_cs);
}
CZTaskList::~CZTaskList()
{
	DeleteCriticalSection(&m_cs);
}

bool CZTaskList::Add(const void *pTask)
{
	CZAutoLock lock(&m_cs);
	m_dTaskQue.push(pTask);
	return true;
}

bool CZTaskList::Get(const void **ppTask)
{
	CZAutoLock lock(&m_cs);
	if (m_dTaskQue.empty())
		return false;
	*ppTask = m_dTaskQue.front();
	m_dTaskQue.pop();
	return true;
}

bool CZTaskList::ClearAll()
{
	CZAutoLock lock(&m_cs);
	while (!m_dTaskQue.empty())
	{
		const void *ppTask = m_dTaskQue.front();
		if (ppTask != NULL) delete ppTask;
		m_dTaskQue.pop();
	}
	return true;
}

CZTaskBase::CZTaskBase(void)
{
	m_hThread = NULL;
	m_hEventEndThread = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hEventNewTask = CreateEvent(NULL, TRUE, FALSE, NULL);
}

CZTaskBase::~CZTaskBase(void)
{
	if (m_hEventEndThread)
	{
		CloseHandle(m_hEventEndThread);
		m_hEventEndThread = NULL;
	}

	if (m_hEventNewTask)
	{
		CloseHandle(m_hEventNewTask);
		m_hEventNewTask = NULL;
	}
}

DWORD __stdcall _ztaskbase_Thread_Task(LPVOID lpParam)
{
	CZTaskBase *pTaskBase = (CZTaskBase*)lpParam;
	if (pTaskBase == NULL)
		return 0;

	return pTaskBase->taskThread();
}

int CZTaskBase::taskThread()
{
	HANDLE hEvents[2] = {m_hEventEndThread, m_hEventNewTask};
	const void *pTask = NULL; 

	while (1)
	{
		if (WaitForMultipleObjects(2, hEvents, FALSE, INFINITE) == WAIT_OBJECT_0)
			break;				// exit the thread

		while (m_TaskList.Get(&pTask) != false)
		{
			if (pTask == NULL)
				continue;

			Task_Do(pTask);		// do task
		}

		ResetEvent(m_hEventNewTask);
	}

	return 0;
}

bool CZTaskBase::Task_Start()
{
	m_hThread = CreateThread(NULL, 0, _ztaskbase_Thread_Task, this, 0, NULL);
	if (m_hThread ==  NULL)
		return false;

	Task_Clear();
	return true;
}

bool CZTaskBase::Task_Stop()
{
	Task_Clear();
	if (m_hThread)
	{
		SetEvent(m_hEventEndThread);
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}

	return true;
}

bool CZTaskBase::Task_Add(const void *pTask)
{
	bool bRet = false;
	bRet = m_TaskList.Add(pTask);
	if (bRet)
		SetEvent(m_hEventNewTask);

	return bRet;
}

bool CZTaskBase::Task_Clear()
{
	ResetEvent(m_hEventNewTask);
	return m_TaskList.ClearAll();
}
