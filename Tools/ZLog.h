/* class CZLog '(zhangpengpeng 2011-3-24)
 * my logger tools
 * independent thread to write log
 */

#ifndef _ZLOG_H_
#define _ZLOG_H_

#define LOGMODE_OUTPUT			0x00000001	//printf or outputdebugstring
#define LOGMODE_WRITEFILE		0x00000002	//write log to file

#ifdef __GNUC__
#define LOG_CHECK_FMT(a, b) __attribute__((format(printf, a, b)))
#define CALLBACK
#else
#define LOG_CHECK_FMT(a, b)
#endif

#ifdef _WIN32
	#define ZLOG(lvl, fmt, ...)         CZLog::Instance()->AddLog(lvl, __FUNCTION__, fmt, ##__VA_ARGS__)
	#define ZLOG_INFO(fmt, ...)         CZLog::Instance()->AddLog(INFO_LVL, __FUNCTION__, fmt, ##__VA_ARGS__)
	#define ZLOG_ERROR(fmt, ...)         CZLog::Instance()->AddLog(ERROR_LVL, __FUNCTION__, fmt, ##__VA_ARGS__)
#else
    #define ZLOG(lvl, fmt, args...)     CZLog::Instance()->AddLog(lvl, __FUNCTION__, fmt, ##args)
    #define ZLOG_INFO(fmt, args...)     CZLog::Instance()->AddLog(INFO_LVL, __FUNCTION__, fmt, ##args)
    #define ZLOG_ERROR(fmt, args...)     CZLog::Instance()->AddLog(ERROR_LVL, __FUNCTION__, fmt, ##args)
#endif

class CZLogLock;

typedef enum enum_ZLogLevel {	// log level
	DEBUG_LVL,
	INFO_LVL,
	WARN_LVL,
	ERROR_LVL
}ZLOG_LEVEL;

typedef struct struct_LogInfo {	// each log info
	ZLOG_LEVEL eLevel;					// log level
	char *csInfo;						// log info
	struct struct_LogInfo *pNext;		// next log's ptr
}LOGINFO;

class CZLog
{
private:
	bool m_bRun;						// whether run the log thread
	unsigned long m_ulMode;				// log mode 

	LOGINFO *m_LogInfoList;				// log list to write
	CZLogLock *m_pcLockMutex;			// lock for mutual exclude

	bool addLogToList(LOGINFO *pLog);
	bool getLogFromList(LOGINFO **ppLog);
	bool processLog(LOGINFO *pLog);

	HANDLE m_hThread;					// thread to run

	unsigned int m_uiFileCount;			// count to choose which file

	bool chooseLogFile(bool bFirstOpen = false);				// choose which file to write log
	bool openFile(const char *str, bool bOverWrite = false);
	bool closeFile();

protected:
	bool sysPrint(const char *str);
	bool fileWirte(const char *str);

public:
	CZLog(unsigned long lMode);
	~CZLog();
	int LogThread_Do();		//main function to precess log
	static CZLog *Instance();

	bool AddLog(ZLOG_LEVEL eLevel, const char *csFunction, const char *format, ...) LOG_CHECK_FMT(5, 6);
};

DWORD WINAPI LogThread(LPVOID pParam);

#endif	// _ZLOG_H_