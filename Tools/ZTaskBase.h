/* ZTaskBaset  '(zhangpengpeng 2012/03/07)
 * base class to do tasks
 * run as a thread or process
 */

#ifndef _ZTASKBASET_H_
#define _ZTASKBASET_H_

#include <Windows.h>
#include <queue>
using namespace std;

class ZTaskList { //class to mgt taks list
private:
	queue<const void*> taskQue;
	CRITICAL_SECTION cs;

public:
	ZTaskList();
	virtual ~ZTaskList();

	bool Add(const void *task);
	bool Get(const void **task);
	bool ClearAll();
};

class ZTaskBase
{
public:
	virtual int Task_Do(const void *task) = 0;

	bool Task_Start();
	bool Task_Stop();
	bool Task_Add(const void *task);
	bool Task_Clear();

public:
	ZTaskBase(void);
	virtual ~ZTaskBase(void);
	int taskThread();

private:
	ZTaskList taskList;
	HANDLE hThread;
	HANDLE hEventEndThread;		// event handle to end thread
	HANDLE hEventNewTask;			// event handle to tip new task
};

#endif // _ZTASKBASET_H_
