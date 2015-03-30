#include <stdio.h>
#include "npapi.h"
#include "npfunctions.h"

NPNetscapeFuncs* npnfuncs = NULL;

#ifdef __cplusplus
extern "C" {
#endif
#ifndef HIBYTE
#define HIBYTE(x) ((((unsigned short)(x)) & 0xff00) >> 8)
#endif
  
NPError OSCALL NP_GetEntryPoints(NPPluginFuncs* nppfuncs)
{
  nppfuncs->version = (NP_VERSION_MAJOR << 8) | NP_VERSION_MINOR;
  nppfuncs->newp = NPP_New;
  nppfuncs->destroy = NPP_Destroy;
  nppfuncs->getvalue = NPP_GetValue;
  nppfuncs->setvalue = NPP_SetValue;
  nppfuncs->setwindow = NPP_SetWindow;
  nppfuncs->event = NPP_HandleEvent;
  nppfuncs->newstream = NPP_NewStream;
  nppfuncs->destroystream = NPP_DestroyStream;
  return NPERR_NO_ERROR;
}

NPError OSCALL NP_GetValue(void* npp, NPPVariable variable, void* value)
{
  return NPP_GetValue((NPP)npp, variable, value);
}

NPError OSCALL NP_Initialize(NPNetscapeFuncs* npnf
#if !defined(_WINDOWS) && !defined(WEBKIT_DARWIN_SDK)
							 , NPPluginFuncs *nppfuncs) 
#else
							 ) 
#endif
{
	if(npnf == NULL)
	{
		return NPERR_INVALID_FUNCTABLE_ERROR;
	}
	if(HIBYTE(npnf->version) > NP_VERSION_MAJOR)
	{
		return NPERR_INCOMPATIBLE_VERSION_ERROR;
	}

	npnfuncs = npnf;
#if !defined(_WINDOWS) && !defined(WEBKIT_DARWIN_SDK)
	NP_GetEntryPoints(nppfuncs);
#endif

	return NPERR_NO_ERROR;
}

NPError  OSCALL NP_Shutdown()
{
	return NPERR_NO_ERROR;
}

//char* NP_GetMIMEDescription(void) {
//  return "application/npwebplugin";
//}


#ifdef __cplusplus
}
#endif