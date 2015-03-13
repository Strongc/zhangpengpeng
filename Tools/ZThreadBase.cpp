/* ZTaskBase  '(zhangpengpeng 2014/09/18)
 * base class to create to do sth
 */

#include "stdafx.h"
#include "ZThreadBase.h"
#pragma warning(disable:4996)

ZThreadBase::ZThreadBase(void)
{
	hThread = NULL;
	hExitEvent = NULL;
	intervalTime = 1000;
	isToEnd = false;
}

ZThreadBase::~ZThreadBase(void)
{
	StopTask();
}

DWORD WINAPI _thread_zthreadbase_dotask(LPVOID param)
{
	ZThreadBase *ms = (ZThreadBase *)param;
	if (ms != NULL)
		ms->_doTask();
	return 0;
}

void ZThreadBase::_doTask()
{
	do
	{
		if (!doTask())
			break;

	} while (WaitForSingleObject(hExitEvent, intervalTime) == WAIT_TIMEOUT);
}

bool ZThreadBase::StartTask()
{
	isToEnd = false;
	hExitEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	hThread = CreateThread(NULL, 0, _thread_zthreadbase_dotask, this, 0, NULL);
	if (hThread == NULL)
		return false;
	return true;
}

bool ZThreadBase::StopTask()
{
	if (hThread != NULL)
	{
		isToEnd = true;
		SetEvent(hExitEvent);
		WaitForSingleObject(hThread, INFINITE);
		hThread = NULL;
	}
	if (hExitEvent != NULL)
	{
		CloseHandle(hExitEvent);
		hExitEvent = NULL;
	}

	return true;
}

ZThreadBaseTask::ZThreadBaseTask()
{
	pfTaskFun = NULL;
	pParam = NULL;
}

ZThreadBaseTask::~ZThreadBaseTask()
{
}

void ZThreadBaseTask::SetFun( ZTBT_THREAD_FUN fun, void *param )
{
	pfTaskFun = fun;
	pParam = param;
}

bool ZThreadBaseTask::doTask()
{
	if (pfTaskFun == NULL)
		return false;
	return pfTaskFun(pParam, isToEnd);
}
