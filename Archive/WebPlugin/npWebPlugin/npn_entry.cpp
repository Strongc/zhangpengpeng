#include "npapi.h"
#include "npruntime.h"
#include "npfunctions.h"

extern NPNetscapeFuncs* npnfuncs;

bool NPN_SetProperty(NPP instance, NPObject* obj, NPIdentifier propertyName,
					 const NPVariant *value)
{
	return npnfuncs->setproperty(instance, obj, propertyName, value);
}

NPIdentifier NPN_GetIntIdentifier(int32_t intid)
{
	return npnfuncs->getintidentifier(intid);
}

void NPN_ReleaseVariantValue(NPVariant *variant)
{
	npnfuncs->releasevariantvalue(variant);
}

bool NPN_Evaluate(NPP instance, NPObject* obj, NPString* str, NPVariant* variant )
{
	return npnfuncs->evaluate(instance, obj, str, variant);
}

NPError NPN_GetValue(NPP instance, NPNVariable variable,void* ret_value)
{
	return npnfuncs->getvalue(instance, variable, ret_value);
}

NPObject *NPN_CreateObject(NPP npp, NPClass *aClass)
{
	return npnfuncs->createobject(npp, aClass);
}

NPObject *NPN_RetainObject(NPObject *obj)
{
	return npnfuncs->retainobject(obj);
}

NPError NPN_GetURL(NPP instance, const char *url, const char *target)
{
	return npnfuncs->geturl(instance, url, target);
}

NPError NPN_PostURL(NPP instance, const char* url, const char* window, uint32_t len, const char* buf, NPBool file)
{
	return npnfuncs->posturl(instance, url, window, len, buf, file);
} 

NPIdentifier NPN_GetStringIdentifier(const NPUTF8 *name)
{
	return npnfuncs->getstringidentifier(name);
}