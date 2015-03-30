/*	 Operlayer Realization
	'(zhangpengpeng 2012/09/05)
	*/

#define _OPERLAYER_REALIZATION
#include "OperLayer.h"
#include "SdkMgr.h"

OPERLAYER_DECLARE int WIN_API OperLayer_Init(const char *szKey, const char *szDllPath, const char *szParam)
{
	int iOLHandle = -1;
	int iCount = SM_LoadSdk(&iOLHandle, szKey, szDllPath);
	if (iCount <= 0 || iOLHandle < 0) // fail to load or init
	{
		SM_FreeSdk(iOLHandle, 1);
		return -1;
	}

	if (iCount == 1) // load at first time
	{
		OL_Init fInit = SM_GetSDK(iOLHandle)->init;
		if (fInit != NULL)
		{
			if (fInit(szParam) != 0)
				return -1;
		}
	}
	return iOLHandle;
}

OPERLAYER_DECLARE int WIN_API OperLayer_UnInit(int iOLHandle)
{
	if (SM_FreeSdk(iOLHandle, 0) == 0)
	{
		OL_UnInit fUnInit = SM_GetSDK(iOLHandle)->unInit;
		if (fUnInit != NULL)
		{
			fUnInit();
		}
		SM_FreeSdk(iOLHandle, 1);
	}
	return 0;
}

OPERLAYER_DECLARE int WIN_API OperLayer_Dosth(int iOLHandle, const char *szParam)
{
	OL_Dosth fDosth = SM_GetSDK(iOLHandle)->dosth;
	if (fDosth != NULL)
	{
		return fDosth(szParam);
	}
	return -1;
}

