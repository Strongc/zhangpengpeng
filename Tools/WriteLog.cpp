#include "stdafx.h"

// begin of Log tool '(zhangpengpeng 2012/09/14)
#define WRITELOG(fmt, ...)  _write_log(__FUNCTION__, fmt, ##__VA_ARGS__)
int _write_log(const char *csFunction, const char *format, ...);
// end of Log tool '(zhangpengpeng 2012/09/14)


int _write_log(const char *csFunction, const char *format, ...)
{
#define MAX_PER_LOG_TATALL	512
	char szStr[MAX_PER_LOG_TATALL] = {0};

	// get current time 
	const char *pTimeFormat = "%Y-%m-%d %H:%M:%S";
	time_t tNow = time(NULL);
	struct tm timePara;
	if (0 != localtime_s(&timePara, &tNow))
		return -1;        
	if (0 == (DWORD)strftime(szStr, (size_t)25, pTimeFormat, &timePara))
		return -1;

	// add function name
	size_t nNowLen = strlen(szStr);
	sprintf_s(szStr + nNowLen, (MAX_PER_LOG_TATALL -2 - nNowLen), " [PrjName](%s): ", csFunction);

	// format infomation string
	va_list args;
	va_start(args, format);
	nNowLen = strlen(szStr);
	_vsnprintf_s(szStr + nNowLen, (MAX_PER_LOG_TATALL -2 - nNowLen), _TRUNCATE, format, args);
	va_end(args);
	nNowLen = strlen(szStr);
	strncat(szStr + nNowLen, "\n", 1);

	// output
	szStr[MAX_PER_LOG_TATALL - 1] = '\0';
	OutputDebugString(szStr);

	return 0;
}