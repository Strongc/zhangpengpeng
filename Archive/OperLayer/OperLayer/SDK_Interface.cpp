#include <Windows.h>
#include "SDK_Interface.h"

int SDKIF_LoadFunAddress(SDK_INTERFACE *pSdk, HINSTANCE hModule)
{
	if (pSdk == NULL || hModule == NULL)
		return -1;

	pSdk->init = (OL_Init)::GetProcAddress(hModule, "OL_Init");
	pSdk->unInit = (OL_UnInit)::GetProcAddress(hModule, "OL_UnInit");
	pSdk->dosth = (OL_Dosth)::GetProcAddress(hModule, "OL_Dosth");
	return 0;
}
