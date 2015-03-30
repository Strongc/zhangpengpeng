#ifndef _WEBPLUGIN_H_
#define _WEBPLUGIN_H_

#ifdef _WEBPLUGIN_REALIZATION_
	#define WEBPLUGIN_DLL_API extern "C" __declspec(dllexport)
#else
	#define WEBPLUGIN_DLL_API extern "C" __declspec(dllimport)
#endif

typedef int (__stdcall *WPFUN_CALLBACK)(int int_param, const char *str_param, void *userdata);

WEBPLUGIN_DLL_API int __stdcall WebPlugin_SetCallBack(WPFUN_CALLBACK pfun, void *userdata);
WEBPLUGIN_DLL_API int __stdcall WebPlugin_CallFun(int int_param, const char *str_param);

#endif // _WEBPLUGIN_H_
