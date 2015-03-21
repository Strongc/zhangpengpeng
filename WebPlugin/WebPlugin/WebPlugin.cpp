#define _WEBPLUGIN_REALIZATION_
#include "WebPlugin.h"

struct {
	WPFUN_CALLBACK pfun;
	void *userdata;
} global_data;

WEBPLUGIN_DLL_API int __stdcall WebPlugin_SetCallBack(WPFUN_CALLBACK pfun, void *userdata)
{
	global_data.pfun = pfun;
	global_data.userdata = userdata;
	return 0;
}

WEBPLUGIN_DLL_API int __stdcall WebPlugin_CallFun(int int_param, const char *str_param)
{
	if (global_data.pfun == 0)
		return -1;

	return global_data.pfun(int_param++, str_param, global_data.userdata);
}
