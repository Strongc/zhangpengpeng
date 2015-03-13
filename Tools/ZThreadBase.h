/* ZTaskBase  '(zhangpengpeng 2014/09/18)
 * base class to create to do sth
 */

#ifndef _ZTHREADBASE_H_
#define _ZTHREADBASE_H_

//#include <Windows.h>

class ZThreadBase
{
public:
	bool StartTask();
	bool StopTask();
	void SetIntervalTime(int t)		{ intervalTime = t; }

protected:
	virtual bool doTask() = 0;
	bool isToEnd;

private:
	HANDLE hThread;
	HANDLE hExitEvent;
	int intervalTime;

public:
	ZThreadBase(void);
	~ZThreadBase(void);
	void _doTask();
};

typedef bool (*ZTBT_THREAD_FUN)(void *param, const bool &isToEnd);

class ZThreadBaseTask : public ZThreadBase
{
public:
	void SetFun(ZTBT_THREAD_FUN fun, void *param);

private:
	ZTBT_THREAD_FUN pfTaskFun;
	void *pParam;

protected:
	virtual bool doTask();

public:
	ZThreadBaseTask();
	~ZThreadBaseTask();
};

#endif // _ZTHREADBASE_H_
