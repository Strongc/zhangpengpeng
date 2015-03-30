// WebPluginActiveX.cpp : Implementation of CWebPluginActiveXApp and DLL registration.

#include "stdafx.h"
#include "WebPluginActiveX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CWebPluginActiveXApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x7279F726, 0x4F7F, 0x4F25, { 0xA8, 0xB0, 0x18, 0x4B, 0x5C, 0x26, 0x5, 0x91 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CWebPluginActiveXApp::InitInstance - DLL initialization

BOOL CWebPluginActiveXApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CWebPluginActiveXApp::ExitInstance - DLL termination

int CWebPluginActiveXApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
