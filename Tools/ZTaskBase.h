/* ZTaskBaset  '(zhangpengpeng 2012/03/07)
 * base class to do tasks
 * run as a thread or process
 */

#ifndef _ZTASKBASET_H_
#define _ZTASKBASET_H_

#include <queue>
using namespace std;

class CZTaskList { //class to mgt taks list
private:
	queue<const void*> m_dTaskQue;
	CRITICAL_SECTION m_cs;

public:
	CZTaskList();
	virtual ~CZTaskList();

	bool Add(const void *pTask);
	bool Get(const void **ppTask);
	bool ClearAll();
};

class CZTaskBase
{
public:
	virtual int Task_Do(const void *pTask) = 0;

	bool Task_Start();
	bool Task_Stop();
	bool Task_Add(const void *pTask);
	bool Task_Clear();

public:
	CZTaskBase(void);
	virtual ~CZTaskBase(void);
	int taskThread();

private:
	CZTaskList m_TaskList;
	HANDLE m_hThread;
	HANDLE m_hEventEndThread;		// event handle to end thread
	HANDLE m_hEventNewTask;			// event handle to tip new task
};

#endif // _ZTASKBASET_H_
