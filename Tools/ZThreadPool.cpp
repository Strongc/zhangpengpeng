/* ZThreadPool '(zhangpengpeng 2012/03/07)
 * Thread Pool
 */

#include "StdAfx.h"
#include "ZThreadPool.h"
#include <algorithm>

class CZTPOneLock
{
private:
	const HANDLE *m_pMutexOne;

public:
	CZTPOneLock(const HANDLE *pMutext) : m_pMutexOne(pMutext)
	{
		WaitForSingleObject(*m_pMutexOne, INFINITE);
	}

	~CZTPOneLock()
	{
		ReleaseMutex(*m_pMutexOne);
	}
};

CZThreadPool::CZThreadPool(void)
{
	m_lThreadNum = 0;
	m_lRunningNum = 0;

	m_iMaxThreadNum = 0;
	m_iInitThreadNum = 0;
	m_iIncreThreadNum = 0;
}

CZThreadPool::~CZThreadPool(void)
{
}

DWORD __stdcall _zthreadpool_Thread_Task(LPVOID lpParam)
{
	ZTHREADINFO *pInfo = (ZTHREADINFO*)lpParam;
	if (pInfo == NULL || pInfo->pPool== NULL)
		return 0;

	return pInfo->pPool->taskThread(pInfo);
}

int CZThreadPool::taskThread(ZTHREADINFO *pThreadInfo)
{
	HANDLE hEvents[3] = {m_hEventEndAll, m_hSemEnd, m_hSemTask};
	CZThreadTaskInterface *pTask = NULL; 

	while (1)
	{
		DWORD dwWait = WaitForMultipleObjects(3, hEvents, FALSE, INFINITE);
		if (dwWait == WAIT_OBJECT_0 || dwWait == (WAIT_OBJECT_0 + 1))
			break;				// exit the thread

		{
			InterlockedIncrement(&m_lRunningNum);
			if (m_lRunningNum >= m_lThreadNum)
				adjustThreadNum();

			{
				CZTPOneLock oneLock(&m_hMutexTask);
				if (m_TaskList.empty())
					continue;

				pTask = m_TaskList.front();
				m_TaskList.pop_front();
			}

			if (pTask != NULL)
			{
				pTask->Task_Do();	// do task
				pThreadInfo->uiCount++;
			}

			InterlockedDecrement(&m_lRunningNum);
			if (m_lRunningNum <= m_lThreadNum - m_iIncreThreadNum)
				adjustThreadNum();
		}

	}

	endThread(pThreadInfo);
	return 0;
}

int CZThreadPool::createThreads(int iNum)
{
	static int iThreadIndex = 0;

	if (m_lThreadNum >= m_iMaxThreadNum)
		return 0;

	int iSuccessNum = 0;
	while (iSuccessNum < iNum)
	{
		ZTHREADINFO *pThreadInfo = new ZTHREADINFO();
		pThreadInfo->iIndex = iThreadIndex++;
		pThreadInfo->pPool = this;
		pThreadInfo->uiCount = 0;
		pThreadInfo->hThread = CreateThread(NULL, 0, _zthreadpool_Thread_Task, pThreadInfo, 0, &pThreadInfo->dwThreadId);

		if (pThreadInfo->hThread == NULL)
		{
			delete pThreadInfo;
			break;
		}

		InterlockedIncrement(&m_lThreadNum);
		CZTPOneLock oneLock(&m_hMutexThread);
		m_ThreadList.push_back(pThreadInfo);
		iSuccessNum++;
	}
	return iSuccessNum;
}

int CZThreadPool::endThread(ZTHREADINFO *pThreadInfo)
{
	InterlockedDecrement(&m_lThreadNum);
	{
		CZTPOneLock oneLock(&m_hMutexThread);
		m_ThreadList.erase(find(m_ThreadList.begin(), m_ThreadList.end(), pThreadInfo));
	}

	TRACE(_T("\nThread[%d:%d:0x%x] end. Run times: %d. "), \
		pThreadInfo->iIndex, pThreadInfo->hThread, pThreadInfo->dwThreadId, pThreadInfo->uiCount);

	CloseHandle(pThreadInfo->hThread);
	pThreadInfo->hThread = NULL;
	delete pThreadInfo;

	if (m_lThreadNum == 0)
		SetEvent(m_hEventEndComplete);

	return 0;
}

bool CZThreadPool::adjustThreadNum()
{
	CZTPOneLock AdjustLock(&m_hMutexAdjust);

	long lThread = m_lThreadNum;
	long lTaskNum = m_lRunningNum - 1;
	{
		CZTPOneLock oneLock(&m_hMutexTask);
		lTaskNum += m_TaskList.size();
	}

	if (lTaskNum < (m_iInitThreadNum + m_iIncreThreadNum)
		&& lThread < (m_iInitThreadNum + m_iIncreThreadNum))		// perhaps most time this may be true
		return true;

	if (lTaskNum >= (lThread + m_iIncreThreadNum))
	{
		if (m_lThreadNum >= m_iMaxThreadNum)
			return false;

		if (createThreads(m_iIncreThreadNum) < m_iIncreThreadNum)
			return false;
	}
	else if (lTaskNum <= (lThread - m_iIncreThreadNum))
	{
		int iEndNum = (lThread - m_iIncreThreadNum) >= m_iInitThreadNum ? m_iIncreThreadNum : (lThread - m_iInitThreadNum);
		ReleaseSemaphore(m_hSemEnd, iEndNum, NULL);
	}
	
	return true;
}

bool CZThreadPool::Start(int iMaxThreadNum, int iInitThreadNum, int iIncreThreadNum)
{
	m_iMaxThreadNum = iMaxThreadNum;
	m_iInitThreadNum = iInitThreadNum;
	m_iIncreThreadNum = iIncreThreadNum;

	if (m_iIncreThreadNum < 1)
		return false;

	if (m_iInitThreadNum > m_iMaxThreadNum)
		return false;

	m_hEventEndAll = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hEventEndComplete = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hSemEnd = CreateSemaphore(NULL, 0, 0x7FFFFFFF, NULL);
	m_hSemTask = CreateSemaphore(NULL, 0, 0x7FFFFFFF, NULL);
	m_hMutexThread = CreateMutex(NULL, FALSE, NULL);
	m_hMutexTask = CreateMutex(NULL, FALSE, NULL);
	m_hMutexAdjust = CreateMutex(NULL, FALSE, NULL);

	ClearTasks();
	if (createThreads(m_iInitThreadNum) < m_iInitThreadNum)
	{
		Stop();
		return false;
	}

	return true;
}

bool CZThreadPool::Stop()
{
	ClearTasks();

	SetEvent(m_hEventEndAll);
	WaitForSingleObject(m_hEventEndComplete, INFINITE);

	if (m_hEventEndAll)
	{
		CloseHandle(m_hEventEndAll);
		m_hEventEndAll = NULL;
	}
	if (m_hEventEndComplete)
	{
		CloseHandle(m_hEventEndComplete);
		m_hEventEndComplete = NULL;
	}
	if (m_hSemEnd)
	{
		CloseHandle(m_hSemEnd);
		m_hSemEnd = NULL;
	}
	if (m_hSemTask)
	{
		CloseHandle(m_hSemTask);
		m_hSemTask = NULL;
	}
	if (m_hMutexThread)
	{
		CloseHandle(m_hMutexThread);
		m_hMutexThread = NULL;
	}
	if (m_hMutexTask)
	{
		CloseHandle(m_hMutexTask);
		m_hMutexTask = NULL;
	}
	if (m_hMutexAdjust)
	{
		CloseHandle(m_hMutexAdjust);
		m_hMutexAdjust = NULL;
	}

	return true;
}

bool CZThreadPool::AddTask(CZThreadTaskInterface *pTask)
{
	CZTPOneLock oneLock(&m_hMutexTask);
	m_TaskList.push_back(pTask);
	ReleaseSemaphore(m_hSemTask, 1, NULL);
	return true;
}

bool CZThreadPool::ClearTasks()
{
	CZTPOneLock oneLock(&m_hMutexTask);
	m_TaskList.clear();
	return true;
}
