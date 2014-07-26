#ifdef _OPERLAYER_REALIZATION
        #define OPERLAYER_DECLARE extern "C" _declspec(dllexport)
#else
        #define OPERLAYER_DECLARE extern "C" _declspec(dllimport)
#endif

#ifndef WIN_API
#define WIN_API __stdcall
#endif

// 初始化
OPERLAYER_DECLARE int WIN_API OperLayer_Init(const char *szKey, const char *szDllPath, const char *szParam);
// 反初始化
OPERLAYER_DECLARE int WIN_API OperLayer_UnInit(int iOLHandle);

OPERLAYER_DECLARE int WIN_API OperLayer_Dosth(int iOLHandle, const char *szParam);
