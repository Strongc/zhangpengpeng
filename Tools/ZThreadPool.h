/* ZThreadPool '(zhangpengpeng 2012/03/07)
 * Thread Pool
 */

#ifndef _ZTHREADPOOL_H_
#define _ZTHREADPOOL_H_

#include <Windows.h>
#include <deque>
using namespace std;

typedef int (*ZTP_TASKDO_FUN)(void *param);

class ZThreadTaskInterface
{
// collect do_func and params together
// private: 
//	params;
public:
	virtual int Task_Do() = 0;
};

class ZThreadPool;
typedef struct struct_ZThreadInfo
{
	int index;						// inner id
	HANDLE hThread;					// thread handle
	DWORD threadId;					// thread id
	ZThreadPool *pool;				// pointer to thread pool
	unsigned int count;				// run times count
}ZTHREADINFO;

class ZThreadPool
{
public:
	bool Start(int maxThreadNum, int initThreadNum, int increThreadNum);
	bool Stop();
	bool AddTask(ZThreadTaskInterface *task);
	bool AddTask(ZTP_TASKDO_FUN fun, void *param);
	bool ClearTasks();

public:
	ZThreadPool(void);
	~ZThreadPool(void);
	int taskThread(ZTHREADINFO *threadInfo);

private:
	int createThreads(int iNum);
	int endThread(ZTHREADINFO *threadInfo);
	bool adjustThreadNum();

private:
	deque<ZTHREADINFO*> threadList;
	deque<ZThreadTaskInterface*> taskList;

	long threadNum;
	long runningNum;

	int maxThreadNum;
	int initThreadNum;
	int increThreadNum;

	HANDLE eventEndAll;
	HANDLE eventEndComplete;
	HANDLE semEnd;
	HANDLE semTask;
	HANDLE mutexThread;
	HANDLE mutexTask;
	HANDLE mutexAdjust;
};

#endif // _ZTHREADPOOL_H_
