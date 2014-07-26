/* ZErrorMgt '(zhangpengpeng 2014/04/28)
 * my tool to manage error infomation
 */

#include <string.h>
#include "ZErrorMgt.h"
#include "ZAutoLock.h"
#include "ZLog.h"

#ifndef NO_ERROR
#define NO_ERROR		0
#endif

ZErrorMgt err_mgt;		// one instance of this class

ZErrorMgt::ZErrorMgt()
{
	InitializeCriticalSection(&cs);
}

ZErrorMgt::~ZErrorMgt()
{
	DeleteCriticalSection(&cs);
	mapError.clear();
}

ZErrorMgt::ThreadID ZErrorMgt::getCurrentThreadID()
{
	return (ThreadID)::GetCurrentThreadId();
}

void ZErrorMgt::set(int error, const char *more_info/* = ""*/)
{
	ErrorInfo errInfo;
	errInfo.error_id = error;
	errInfo.more_info = more_info;
	ThreadID tid = getCurrentThreadID();
	
	{
		CZAutoLock al(&cs);
		mapError[tid] = errInfo;
	}

	if (0 == strlen(more_info) && error != NO_ERROR)
		ZLOG(ERROR_LVL, "Thread %d, Error %d", tid, error);
	else
		ZLOG(ERROR_LVL, "Thread %d, Error %d, Info: %s", tid, error, more_info);
}

void ZErrorMgt::reset()
{
	set(NO_ERROR);
}

int ZErrorMgt::getLastError()
{
	ThreadID tid = getCurrentThreadID();

	CZAutoLock al(&cs);
	std::map<ThreadID, ErrorInfo>::iterator iter = mapError.find(tid);
	if(iter != mapError.end())
	{
		return iter->second.error_id;
	}
	return NO_ERROR;
}

const char* ZErrorMgt::getMoreInfo()
{
	ThreadID tid = getCurrentThreadID();

	CZAutoLock al(&cs);
	std::map<ThreadID, ErrorInfo>::iterator iter = mapError.find(tid);
	if(iter != mapError.end())
	{
		return iter->second.more_info.c_str();
	}
	return "";
}
