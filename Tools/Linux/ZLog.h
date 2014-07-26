/* class CZLog '(zhangpengpeng 2011-3-24)
 * my logger tools
 * independent thread to write log
 */

#ifndef _ZLOG_H_
#define _ZLOG_H_

#ifdef _WIN32
#define ZOS_TYPE_WIN
#else
#define ZOS_TYPE_GUNC
#endif

#ifdef ZOS_TYPE_WIN
#define LOG_CHECK_FMT(a, b)
#else
#define LOG_CHECK_FMT(a, b) __attribute__((format(printf, a, b)))
#define CALLBACK
#endif

#ifdef ZOS_TYPE_WIN
	#define ZLOG(lvl, fmt, ...)         ZLog::Instance()->AddLog(lvl, __FUNCTION__, fmt, ##__VA_ARGS__)
	#define ZLOG_INFO(fmt, ...)         ZLog::Instance()->AddLog(INFO_LVL, __FUNCTION__, fmt, ##__VA_ARGS__)
#else
    #define ZLOG(lvl, fmt, args...)     ZLog::Instance()->AddLog(lvl, __FUNCTION__, fmt, ##args)
    #define ZLOG_INFO(fmt, args...)     ZLog::Instance()->AddLog(INFO_LVL, __FUNCTION__, fmt, ##args)
#endif

typedef CALLBACK void (*LOG_INFO_CALLBACK)(int lvl, const char *log_info);

#include "ZTaskBase.h"

typedef enum _em_ZLogLevel {	// log level
	DEBUG_LVL = 0,
	INFO_LVL,
	WARN_LVL,
	ERROR_LVL
}ZLogLevel;

typedef struct _st_ZLogInfo {			// each log info
	ZLogLevel eLevel;					// log level
	char *csInfo;						// log info
}ZLogInfo;

class ZLog : public ZTaskBase
{
private:
	LOG_INFO_CALLBACK fun_log_info_cb;	// pointer of function to callback log info

	int Task_Do(const void *pTask);
	int processLog(ZLogInfo *pLog);

public:
	ZLog(LOG_INFO_CALLBACK fun = NULL);
	virtual ~ZLog();
	static ZLog *Instance();

	static int Init(LOG_INFO_CALLBACK fun);
	static int UnInit();
	int AddLog(ZLogLevel eLevel, const char *csFunction, const char *format, ...) LOG_CHECK_FMT(4, 5);
};

#endif	// _ZLOG_H_
