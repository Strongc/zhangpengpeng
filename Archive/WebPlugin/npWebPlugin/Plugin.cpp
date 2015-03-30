#include "Plugin.h"
#include "../WebPlugin/WebPlugin.h"

#pragma comment(lib, "../Release/WebPlugin.lib")

#ifdef WIN32
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <vector>
#include <sstream>
#endif

extern NPNetscapeFuncs* npnfuncs;

static NPIdentifier s_CallFun_id;

static NPClass plugin_ref_obj = {
	NP_CLASS_STRUCT_VERSION,
	ScriptablePluginObject::Allocate,
	ScriptablePluginObject::Deallocate,
	NULL,
	ScriptablePluginObject::HasMethod,
	ScriptablePluginObject::Invoke,
	ScriptablePluginObject::InvokeDefault,
	ScriptablePluginObject::HasProperty,
	ScriptablePluginObject::GetProperty,
	NULL,
	NULL,
	NULL, 
	NULL
};

ScriptablePluginObject::ScriptablePluginObject(NPP instance)
: npp(instance)
{
}

NPObject* ScriptablePluginObject::Allocate(NPP instance, NPClass* npclass)
{
	return (NPObject*)(new ScriptablePluginObject(instance));
}

void ScriptablePluginObject::Deallocate(NPObject* obj)
{
	delete (ScriptablePluginObject*)obj;
}

bool ScriptablePluginObject::HasMethod(NPObject* obj, NPIdentifier methodName)
{
	return (methodName == s_CallFun_id);
}

bool ScriptablePluginObject::InvokeDefault(NPObject* obj, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
	return true;
}

bool ScriptablePluginObject::Invoke(NPObject* obj, NPIdentifier methodName, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
	//DebugBreak();
	ScriptablePluginObject *thisObj = (ScriptablePluginObject*)obj;
	if (thisObj == NULL)
		return false;
	CPlugin *plugin = (CPlugin*)thisObj->npp->pdata;
	if (plugin == NULL)
		return false;

	if (s_CallFun_id == methodName)
	{
		int ret = -1;
		if(args != NULL && argCount >= 2)
		{
			int intValue = 0;
			if (NPVARIANT_IS_INT32(args[0]))
			{
				intValue = NPVARIANT_TO_INT32(args[0]);
			}
			else if (NPVARIANT_IS_DOUBLE(args[0]))
			{
				intValue = (int)NPVARIANT_TO_DOUBLE(args[0]);
			}

			unsigned int strValueLen = NPVARIANT_TO_STRING(args[1]).UTF8Length;
			const char* strValueOrigin = NPVARIANT_TO_STRING(args[1]).UTF8Characters;
			char strValue[1024] = {0};
			memcpy(strValue, strValueOrigin, strValueLen);	// UTF8 to ANSI when necessary

			ret = plugin->CallFun(intValue, strValue);
		}
		BOOLEAN_TO_NPVARIANT(ret, *result);
		return true;
	}

	return true;
}

bool ScriptablePluginObject::HasProperty(NPObject* obj, NPIdentifier propertyName)
{
	return false;
}

bool ScriptablePluginObject::GetProperty(NPObject* obj, NPIdentifier propertyName, NPVariant* result)
{
	return false;
}

CPlugin::CPlugin(NPP pNPInstance)
: m_pNPInstance(pNPInstance)
, m_bInitialized(false)
, m_pScriptableObject(NULL) 
{
#ifdef _WINDOWS
	m_hWnd = NULL;
#endif

	s_CallFun_id = NPN_GetStringIdentifier("CallFun");

	WebPlugin_SetCallBack(CPlugin::_Callback, this);
}

CPlugin::~CPlugin(void)
{
}

NPBool CPlugin::init(NPWindow* pNPWindow)
{
	if(pNPWindow == NULL)
		return false;
#ifdef _WINDOWS
	m_hWnd = (HWND)pNPWindow->window;
	if(m_hWnd == NULL)
		return false;
#endif
	m_Window = pNPWindow;
	m_bInitialized = true;
	return true;
}

NPBool CPlugin::isInitialized()
{
	return m_bInitialized;
}

ScriptablePluginObject * CPlugin::GetScriptableObject()
{
	if (!m_pScriptableObject) 
	{
		m_pScriptableObject = (ScriptablePluginObject*)NPN_CreateObject(m_pNPInstance, &plugin_ref_obj);
	}

	if (m_pScriptableObject) 
	{
		NPN_RetainObject((NPObject *)m_pScriptableObject);
	}

	return m_pScriptableObject;
}

NPError CPlugin::GetValue( NPPVariable variable, void *value )
{
	switch(variable)
	{
	case NPPVpluginNameString:
		*((char **)value) = "WebPlugin";
		break;

	case NPPVpluginDescriptionString:
		*((char **)value) = "WebPlugin by Roc";
		break;

	case NPPVpluginScriptableNPObject:
		*(NPObject **)value = (NPObject*)GetScriptableObject();
		break;

	case NPPVpluginNeedsXEmbed:
		*((char *)value) = 1;
		break;

	default:
		return NPERR_GENERIC_ERROR;
		break;
	}

	return NPERR_NO_ERROR;
}

int __stdcall CPlugin::_Callback(int int_param, const char *str_param, void *userdata)
{
	CPlugin *plugin = (CPlugin*)userdata;
	if (plugin == NULL)
		return -1;

	return plugin->_Callback(int_param, str_param);
}

int CPlugin::_Callback(int int_param, const char *str_param)
{
	char temp[1024] = {0};
	sprintf(temp, "javascript:FireEvent(%d,'%s')", int_param, str_param);
	NPN_GetURL(m_pNPInstance, temp, "_self");

	return 0;
}

int CPlugin::CallFun(int int_param, const char *str_param)
{
	return ::WebPlugin_CallFun(int_param, str_param);
}
