/*	class to manage dll and interfaces
	'(zhangpengpeng 2012/09/05)
	*/

#ifndef _SDKMGR_H_
#define _SDKMGR_H_

#include <Windows.h>
#include "SDK_Interface.h"

#define KEY_LEN		32

typedef struct _st_EncDllLoadInfo
{
	int iOLHandle;
	char szKey[KEY_LEN];
	int iLoadCount;
	HINSTANCE hModule;
	SDK_INTERFACE sdk;
}ENCDLLLOADINFO;


// functions of SdkMgr
int SM_LoadSdk(int *iOLHandle, const char *szKey, const char *szDllPath);
int SM_FreeSdk(int iOLHandle, int iIsFreeDll);
SDK_INTERFACE *SM_GetSDK(int iOLHandle);

#endif // _SDKMGR_H_
