/* ZThreadPool '(zhangpengpeng 2012/03/07)
 * Thread Pool
 */

#ifndef _ZTHREADPOOL_H_
#define _ZTHREADPOOL_H_

#include <deque>
using namespace std;

class CZThreadTaskInterface
{
// collect do_func and params together
// private: 
//	params;
public:
	virtual int Task_Do() = 0;
};

class CZThreadPool;
typedef struct struct_ZThreadInfo
{
	int iIndex;						// inner id
	HANDLE hThread;					// thread handle
	DWORD dwThreadId;				// thread id
	CZThreadPool *pPool;			// pointer to thread pool
	unsigned int uiCount;			// run times count
}ZTHREADINFO;

class CZThreadPool
{
public:
	bool Start(int iMaxThreadNum, int iInitThreadNum, int iIncreThreadNum);
	bool Stop();
	bool AddTask(CZThreadTaskInterface *pTask);
	bool ClearTasks();

public:
	CZThreadPool(void);
	~CZThreadPool(void);
	int taskThread(ZTHREADINFO *pThreadInfo);

private:
	int createThreads(int iNum);
	int endThread(ZTHREADINFO *pThreadInfo);
	bool adjustThreadNum();

private:
	deque<ZTHREADINFO*> m_ThreadList;
	deque<CZThreadTaskInterface*> m_TaskList;

	long m_lThreadNum;
	long m_lRunningNum;

	int m_iMaxThreadNum;
	int m_iInitThreadNum;
	int m_iIncreThreadNum;

	HANDLE m_hEventEndAll;
	HANDLE m_hEventEndComplete;
	HANDLE m_hSemEnd;
	HANDLE m_hSemTask;
	HANDLE m_hMutexThread;
	HANDLE m_hMutexTask;
	HANDLE m_hMutexAdjust;
};

#endif // _ZTHREADPOOL_H_
