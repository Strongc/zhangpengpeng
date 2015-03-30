#include "plugin.h"

NPError NPP_New(NPMIMEType pluginType, NPP instance,
				uint16_t mode, int16_t argc, char* argn[],
				char* argv[], NPSavedData* saved)
{
	if(instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR;

	CPlugin * pPlugin = new CPlugin(instance);
	if(pPlugin == NULL)
		return NPERR_OUT_OF_MEMORY_ERROR;

	instance->pdata = (void *)pPlugin;

	return NPERR_NO_ERROR;
}

NPError NPP_Destroy(NPP instance, NPSavedData** save)
{
	if(instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR;

	CPlugin * pPlugin = (CPlugin *)instance->pdata;
	if(pPlugin != NULL)
		delete pPlugin;

	return NPERR_NO_ERROR;
}

NPError NPP_SetWindow(NPP instance, NPWindow* window) {
	if(instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR;

	if(window == NULL)
		return NPERR_GENERIC_ERROR;

	CPlugin * pPlugin = (CPlugin *)instance->pdata;
	if(pPlugin == NULL) 
		return NPERR_GENERIC_ERROR;

	// window just created
	if(!pPlugin->isInitialized() && (window->window != NULL))
	{ 
		if(!pPlugin->init(window))
		{
			delete pPlugin;
			pPlugin = NULL;
			return NPERR_MODULE_LOAD_FAILED_ERROR;
		}
	}

	return NPERR_NO_ERROR;
}

NPError	NPP_GetValue(NPP instance, NPPVariable variable, void *value)
{
	if (!instance)
		return NPERR_INVALID_INSTANCE_ERROR;

	CPlugin * pPlugin = (CPlugin *)instance->pdata;
	if (!pPlugin) 
		return NPERR_GENERIC_ERROR;

	return pPlugin->GetValue(variable, value);
}

NPError NPP_SetValue(NPP instance, NPNVariable variable, void *value)
{
	if (!instance)
		return NPERR_INVALID_INSTANCE_ERROR;

	CPlugin * pPlugin = (CPlugin *)instance->pdata;
	if (!pPlugin) 
		return NPERR_GENERIC_ERROR;

	return pPlugin->SetValue(variable, value);
}

NPError NPP_NewStream(NPP instance, NPMIMEType type, NPStream* stream,
					  NPBool seekable, uint16_t* stype)
{
	return NPERR_GENERIC_ERROR;
}

NPError NPP_DestroyStream(NPP instance, NPStream* stream, NPReason reason)
{
	return NPERR_GENERIC_ERROR;
}

int16_t NPP_HandleEvent(NPP instance, void* event)
{
	return NPERR_NO_ERROR;
}