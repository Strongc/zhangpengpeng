/* class CZLog '(zhangpengpeng 2011-3-24)
 * my logger tools
 * independent thread to write log
 */

#include "StdAfx.h"
#include "ZLog.h"
#include <time.h>
#include <sys/stat.h>
#include <fstream>
#include <string>
using namespace std;


#define ZLOG_OUTPUT_DEBUG													// whether show debug info
#define MAX_PER_LOG				512											// max length of info per log
#define MAX_PER_LOG_TATALL		(MAX_PER_LOG + 64 + 1)						// max length per log
#define MAX_FILE_LENGTH			(1024 * 1024 * 5)							// max length of file
#define MAX_LOGFILE_COUNT		3											// max count of log files

fstream g_file;																// file stream
string g_filenames[] = {"zLog1.txt", "zLog2.txt", "zLog3.txt"};							// file name
static CZLog *g_pZLog = NULL;


#ifdef _WIN32
#define strncpy		strncpy_s
#endif

class CZLogLock {
private:
	CRITICAL_SECTION m_crtSetion;
public:
	CZLogLock() {
		InitializeCriticalSection(&m_crtSetion);
	}
	~CZLogLock() {
		DeleteCriticalSection(&m_crtSetion);
	}

	void Lock() {
		EnterCriticalSection(&m_crtSetion);
	}
	void UnLock() {
		LeaveCriticalSection(&m_crtSetion);
	}
};

CZLog::CZLog(unsigned long lMode)
: m_bRun(false)
, m_ulMode(0)
, m_hThread(NULL)
, m_LogInfoList(NULL)
{
	m_ulMode = lMode;
	m_pcLockMutex = new CZLogLock();
	m_uiFileCount = 0;
	m_bRun = true;
	chooseLogFile(true);
	m_hThread = CreateThread(NULL, 0, LogThread, this, 0, NULL);
}

CZLog::~CZLog()
{
	m_bRun = false;
	if (m_hThread != NULL)
	{
		WaitForSingleObject(m_hThread, INFINITE);
		m_hThread = NULL;
	}

	delete m_pcLockMutex;
	closeFile();
}

CZLog *CZLog::Instance()
{
	if (g_pZLog == NULL)
	{
		g_pZLog = new CZLog(LOGMODE_OUTPUT | LOGMODE_WRITEFILE);
		ZLOG(INFO_LVL, "ZLog Startup");
	}

	return g_pZLog;
}

bool CZLog::AddLog(ZLOG_LEVEL eLevel, const char *csFunction, const char *format, ...)
{
	char *csStr = new char[MAX_PER_LOG_TATALL];
	memset(csStr, 0, MAX_PER_LOG_TATALL);

	const char *pTimeFormat = "%Y-%m-%d %H:%M:%S";
    // get current time 
	time_t tNow = time(NULL);
	struct tm timePara;
	if (0 != localtime_s(&timePara, &tNow))
		return false;        
	if (0 == (DWORD)strftime(csStr, (size_t)25, pTimeFormat, &timePara))
		return false;

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

	//加入log信息
    va_list args;
    va_start(args, format);
    int nBuf = _vsnprintf_s(csStr + strlen(csStr), MAX_PER_LOG_TATALL - strlen(csStr), _TRUNCATE, format, args);
    csStr[MAX_PER_LOG_TATALL - 1] = '\0';
    va_end(args);

	// add to list
	LOGINFO *pInfo = new LOGINFO();
	pInfo->eLevel = eLevel;
	pInfo->csInfo = csStr;
	pInfo->pNext = NULL;
	addLogToList(pInfo);

	return true;
}

DWORD WINAPI LogThread(LPVOID pParam)
{
	CZLog *pZlog = (CZLog*)pParam;
	int ret = pZlog->LogThread_Do();
	return (DWORD)ret;
}

int CZLog::LogThread_Do()
{
	unsigned int uiCount = 0;

	while (1)
	{
		// check whether to stop
		if ((!m_bRun) && (m_LogInfoList == NULL))
			break;

		// process
		LOGINFO *pLog;
		if (getLogFromList(&pLog))
		{
			processLog(pLog);
		}
		else
		{
			Sleep(300);
		}

		// check log file
		uiCount++;
		if (uiCount >= 100)
		{
			uiCount = 0;
			chooseLogFile();
		}
	}

	return 0;
}

bool CZLog::addLogToList(LOGINFO *pLog)
{
	m_pcLockMutex->Lock();

	if (m_LogInfoList == NULL)
		m_LogInfoList = pLog;
	else
	{
		LOGINFO *pTemp = m_LogInfoList;
		while (pTemp->pNext != NULL)
			pTemp = pTemp->pNext;
		pTemp->pNext = pLog;
	}

	m_pcLockMutex->UnLock();
	return true;
}

bool CZLog::getLogFromList(LOGINFO **ppLog)
{
	m_pcLockMutex->Lock();
	bool bRet = false;

	if (m_LogInfoList == NULL)
		bRet = false;
	else
	{
		*ppLog = m_LogInfoList;
		m_LogInfoList = m_LogInfoList->pNext;
		bRet = true;
	}

	m_pcLockMutex->UnLock();
	return bRet;
}

bool CZLog::processLog(LOGINFO *pLog)
{
	do 
	{

#ifndef ZLOG_OUTPUT_DEBUG
		if (pLog->eLevel == DEBUG_LVL)
			break;
#endif

		// output log
		if ((m_ulMode & LOGMODE_OUTPUT) != 0)
			sysPrint(pLog->csInfo);
		if ((m_ulMode & LOGMODE_WRITEFILE) != 0)
			fileWirte(pLog->csInfo);
	} while (0);

	// release memory
	delete pLog->csInfo;
	delete pLog;

	return true;
}

bool CZLog::chooseLogFile(bool bFirstOpen /* = false */)
{
	if (!g_file.is_open())
	{
		if (!openFile(g_filenames[m_uiFileCount].c_str()))
			return false;

		m_uiFileCount++;
		m_uiFileCount %= MAX_LOGFILE_COUNT;
	}

	// get file length
	fstream::pos_type curPos = g_file.tellp();
	g_file.seekp(0L, ios::end);
	fstream::pos_type endPos = g_file.tellp();
	fpos_t len = endPos.seekpos();
	g_file.seekp(curPos, ios::beg);

	// choose file
	if (len > MAX_FILE_LENGTH)
	{
		closeFile();
		if (m_uiFileCount != 0 && bFirstOpen)	// not the first log file, and first open
			chooseLogFile(bFirstOpen);	// choose next one, this is recursive
		else
		{
			// overwrite from the first one
			if (!openFile(g_filenames[m_uiFileCount].c_str(), true))
				return false;
			m_uiFileCount++;
			m_uiFileCount %= MAX_LOGFILE_COUNT;
		}
	}

	return true;
}

bool CZLog::sysPrint(const char* str)
{
	OutputDebugString(str);
	OutputDebugString("\n");
	return true;
}

bool CZLog::fileWirte(const char* str)
{
	g_file.write(str, strlen(str));
	g_file.write("\n", strlen("\n"));
	g_file.flush();
	return true;
}

bool CZLog::openFile(const char *str, bool bOverWrite /* = false */)
{
	if (!bOverWrite)
		g_file.open(str, ios::app | ios::out);
	else
		g_file.open(str, ios::out);
	return true;
}

bool CZLog::closeFile()
{
	g_file.flush();
	g_file.close();
	return true;
}


/* g_pZLog改为指针，ZLog根据需要才会创建
 * 避免在切换工作目录前就已经打开日志文件
 * 为了让g_pZLog自动释放内存，写此类
 */
class CAutoDeleteZLog
{
public:
	CAutoDeleteZLog() {}
	~CAutoDeleteZLog()
	{
		if (g_pZLog)
		{
			ZLOG(INFO_LVL, "ZLog Shutdown\n\n");
			delete g_pZLog;
			g_pZLog = NULL;
		}
	}
};
CAutoDeleteZLog AutoDeleteZLog;
