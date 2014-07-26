/*	class to manage dll and interfaces
	'(zhangpengpeng 2012/09/05)
	*/

#include "SdkMgr.h"
#include "tools.h"
#include <vector>
using namespace std;

#define TSM_RET_ERROR		-1
#define TSM_RET_UNLOADOK	-100
static vector <ENCDLLLOADINFO> g_vecDllLoadInfo;
static int g_iHandleCount = 0;
static OL_Lock g_OperLock;

int SDKIF_LoadFunAddress(SDK_INTERFACE *pSdk, HINSTANCE hModule);

int SM_LoadSdk(int *iOLHandle, const char *szKey, const char *szDllPath)
{
	OL_AutoLock lock(&g_OperLock);

	if (iOLHandle == NULL || szKey == NULL || szDllPath == NULL || \
		strnlen(szKey, KEY_LEN) == 0)
		return TSM_RET_ERROR;

	for (vector<ENCDLLLOADINFO>::iterator iter = g_vecDllLoadInfo.begin();
		iter != g_vecDllLoadInfo.end(); iter++)
	{
		if (strcmp(iter->szKey, szKey) == 0)		// already loaded
		{
			*iOLHandle = iter->iOLHandle;
			return ++iter->iLoadCount;
		}
	}

	if (strnlen(szDllPath, MAX_PATH) != 0)
	{
		const int PATH_ENV_LEN = 1024;
		char szPATHENV[PATH_ENV_LEN] = "PATH=";
		strncat(szPATHENV, getenv("PATH"), PATH_ENV_LEN);
		strncat(szPATHENV, ";", PATH_ENV_LEN);
		strncat(szPATHENV, szDllPath, PATH_ENV_LEN);
		_putenv(szPATHENV);
	}

	int iRet = TSM_RET_ERROR;
	char szDllFullPath[MAX_PATH] = {0};
	sprintf_s(szDllFullPath, "%sOL_%s.dll", szDllPath, szKey);
	OutputDebugString(szDllFullPath);
	HINSTANCE hModule = ::LoadLibrary(szDllFullPath);

	if (hModule)
	{
		ENCDLLLOADINFO dllInfo;
		memset(&dllInfo, 0, sizeof(ENCDLLLOADINFO));

		dllInfo.iOLHandle = g_iHandleCount++;
		strncpy_s(dllInfo.szKey, szKey, KEY_LEN);
		dllInfo.hModule = hModule;
		dllInfo.iLoadCount = 1;
		SDKIF_LoadFunAddress(&(dllInfo.sdk), hModule);

		g_vecDllLoadInfo.push_back(dllInfo);
		*iOLHandle = dllInfo.iOLHandle;
		iRet = dllInfo.iLoadCount;
	}

	return iRet;
}

int SM_FreeSdk(int iOLHandle, int iIsFreeDll)
{
	OL_AutoLock lock(&g_OperLock);

	vector<ENCDLLLOADINFO>::iterator iter = g_vecDllLoadInfo.begin();
	for (;iter != g_vecDllLoadInfo.end(); iter++)
	{
		if (iter->iOLHandle == iOLHandle)
		{
			break;
		}
	}
	if (iter == g_vecDllLoadInfo.end())
		return TSM_RET_ERROR;		// not exist

	if (iIsFreeDll == 1)
	{
		::FreeLibrary(iter->hModule);
		g_vecDllLoadInfo.erase(iter);
		return TSM_RET_UNLOADOK;
	}

	iter->iLoadCount--;
	return iter->iLoadCount;
}


SDK_INTERFACE *SM_GetSDK(int iOLHandle)
{
	OL_AutoLock lock(&g_OperLock);

	vector<ENCDLLLOADINFO>::iterator iter = g_vecDllLoadInfo.begin();
	for (;iter != g_vecDllLoadInfo.end(); iter++)
	{
		if (iter->iOLHandle == iOLHandle)	// already loaded
		{
			return &(iter->sdk);
		}
	}

	// empty interfaces
	static SDK_INTERFACE emptyIf;
	memset(&emptyIf, 0, sizeof(SDK_INTERFACE));
	return &emptyIf;
}
