/* class CZLog '(zhangpengpeng 2011-3-24)
 * my logger tools
 * independent thread to write log
 */

#include "ZLog.h"
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#define MAX_PER_LOG				512											// max length of info per log
#define MAX_PER_LOG_TATALL		(MAX_PER_LOG + 64 + 1)						// max length per log

#ifdef ZOS_TYPE_WIN
#define strncpy		strncpy_s
#endif


ZLog::ZLog(LOG_INFO_CALLBACK fun/* = NULL*/)
{
	fun_log_info_cb = fun;
	Task_Start();
}

ZLog::~ZLog()
{
	Task_Stop();
}

static ZLog *g_pZLog = NULL;			// 只在本文件中使用的该类的指针
int ZLog::Init(LOG_INFO_CALLBACK fun)
{
	if (g_pZLog == NULL)
	{
		g_pZLog = new ZLog(fun);
		ZLOG(INFO_LVL, "ZLog Startup");
	}
	return 0;
}

int ZLog::UnInit()
{
	if (g_pZLog)
	{
		ZLOG(INFO_LVL, "ZLog Shutdown\n\n");
		delete g_pZLog;
		g_pZLog = NULL;
	}
	return 0;
}

ZLog *ZLog::Instance()
{
	return g_pZLog;
}

int ZLog::AddLog(ZLogLevel eLevel, const char *csFunction, const char *format, ...)
{
	char *csStr = new char[MAX_PER_LOG_TATALL];
	if (csStr == NULL)
		return -1;
	memset(csStr, 0, MAX_PER_LOG_TATALL);

    // get current time 
	time_t tNow = time(NULL);
	const char *pTimeFormat = "%Y-%m-%d %H:%M:%S";

#ifdef ZOS_TYPE_WIN
	struct tm timePara;
	if (0 != localtime_s(&timePara, &tNow))
		return -1;        
	if (0 == (DWORD)strftime(csStr, (size_t)25, pTimeFormat, &timePara))
		return -1;
#else
	struct tm *local_time = NULL;
	local_time = localtime(&tNow);
	if (0 == strftime(csStr, (size_t)25, pTimeFormat, local_time))
		return -1;
#endif

	// translate level to its name
	const unsigned int LenOfLevelName = 10;
	char csLevelName[LenOfLevelName];
	memset(csLevelName, 0, LenOfLevelName);
	switch (eLevel)
	{
	case DEBUG_LVL:
		strncpy(csLevelName, "Debug", LenOfLevelName);
		break;
	case INFO_LVL:
		strncpy(csLevelName, "Info", LenOfLevelName);
		break;
	case WARN_LVL:
		strncpy(csLevelName, "Warn", LenOfLevelName);
		break;
	case ERROR_LVL:
		strncpy(csLevelName, "Error", LenOfLevelName);
		break;
	default:
		strncpy(csLevelName, "UnKnown", LenOfLevelName);
		break;
	}

	// consist
	sprintf(csStr + strlen(csStr), " [%s](%s): ", csLevelName, csFunction);

	// add log info 
    va_list args;
    va_start(args, format);
    //int nBuf = _vsnprintf_s(csStr + strlen(csStr), MAX_PER_LOG_TATALL - strlen(csStr), _TRUNCATE, format, args);
	vsnprintf(csStr + strlen(csStr), MAX_PER_LOG_TATALL - strlen(csStr), format, args);
    csStr[MAX_PER_LOG_TATALL - 1] = '\0';
    va_end(args);

	// add to list
	ZLogInfo *pInfo = new ZLogInfo();
	pInfo->eLevel = eLevel;
	pInfo->csInfo = csStr;
	Task_Add(pInfo);

	return 0;
}

int ZLog::Task_Do(const void *pTask)
{
	do {
		if (pTask == NULL)
			break;

		// process
		ZLogInfo *pLog = (ZLogInfo*)pTask;
		processLog(pLog);

		// release memory
		if (pLog->csInfo != NULL)
		{
			delete pLog->csInfo;
			pLog->csInfo = NULL;
		}
		delete pLog;

	} while (0);

	return 0;
}

int ZLog::processLog(ZLogInfo *pLog)
{
	if (fun_log_info_cb != NULL)
	{
		fun_log_info_cb((int)pLog->eLevel, pLog->csInfo);
	}
	return 0;
}
