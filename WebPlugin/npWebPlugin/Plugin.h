#pragma once

#include "npapi.h"
#include "npruntime.h"
#include "npfunctions.h"

class ScriptablePluginObject: NPObject
{
public:
	ScriptablePluginObject(NPP instance);
	static NPObject* Allocate(NPP instance, NPClass* npclass);
	static void Deallocate(NPObject* obj);
	static bool HasMethod(NPObject* obj, NPIdentifier methodName);
	static bool InvokeDefault(NPObject* obj, const NPVariant* args, uint32_t argCount, NPVariant* result);
	static bool Invoke(NPObject* obj, NPIdentifier methodName, const NPVariant* args, uint32_t argCount, NPVariant* result);
	static bool HasProperty(NPObject* obj, NPIdentifier propertyName); static bool GetProperty(NPObject* obj, NPIdentifier propertyName, NPVariant* result);

	NPP npp;
};

class CPlugin
{
private:
	NPP m_pNPInstance;
	NPWindow * m_Window;
	NPBool m_bInitialized;
	ScriptablePluginObject *m_pScriptableObject;

#ifdef _WINDOWS
	HWND m_hWnd; 
#endif

protected:
	static int __stdcall _Callback(int int_param, const char *str_param, void *userdata);
	int _Callback(int int_param, const char *str_param);

public:
	CPlugin(NPP pNPInstance);
	~CPlugin();

#ifdef _WINDOWS
	HWND GetHWnd()	{ 	return m_hWnd; }
#endif

	NPBool init(NPWindow* pNPWindow);
	NPBool isInitialized();
	ScriptablePluginObject *GetScriptableObject();

	NPError GetValue( NPPVariable variable, void *value);
	virtual NPError SetValue(NPNVariable variable, void *value)       { return NPERR_NO_ERROR; }

	int CallFun(int int_param, const char *str_param);
};
