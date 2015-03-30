// WebPluginActiveXCtrl.cpp : Implementation of the CWebPluginActiveXCtrl ActiveX Control class.

#include "stdafx.h"
#include "WebPluginActiveX.h"
#include "WebPluginActiveXCtrl.h"
#include "WebPluginActiveXPropPage.h"
#include "../WebPlugin/WebPlugin.h"

#pragma comment(lib, "../Release/WebPlugin.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CWebPluginActiveXCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CWebPluginActiveXCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_MESSAGE(WM_WEBEVENT, OnWebEvent)
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(CWebPluginActiveXCtrl, COleControl)
	DISP_FUNCTION_ID(CWebPluginActiveXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CWebPluginActiveXCtrl, "CallFun", dispidCallFun, CallFun, VT_I4, VTS_I4 VTS_BSTR)
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CWebPluginActiveXCtrl, COleControl)
	EVENT_CUSTOM_ID("FireWebEvent", eventidFireWebEvent, FireWebEvent, VTS_I4 VTS_BSTR)
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CWebPluginActiveXCtrl, 1)
	PROPPAGEID(CWebPluginActiveXPropPage::guid)
END_PROPPAGEIDS(CWebPluginActiveXCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CWebPluginActiveXCtrl, "WEBPLUGINACTIVEX.WebPluginActiveXCtrl.1",
	0x769e0ed3, 0xa72e, 0x465a, 0xb8, 0xcb, 0xd4, 0xae, 0x45, 0xd6, 0x9f, 0xd)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CWebPluginActiveXCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID BASED_CODE IID_DWebPluginActiveX =
		{ 0x699825D2, 0x88F3, 0x4159, { 0x8B, 0x1D, 0x3F, 0x64, 0xE8, 0x5F, 0x61, 0x29 } };
const IID BASED_CODE IID_DWebPluginActiveXEvents =
		{ 0x6CDB8D17, 0xA795, 0x4F69, { 0xAE, 0x2D, 0x1C, 0x55, 0x99, 0x1E, 0x71, 0xE0 } };



// Control type information

static const DWORD BASED_CODE _dwWebPluginActiveXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CWebPluginActiveXCtrl, IDS_WEBPLUGINACTIVEX, _dwWebPluginActiveXOleMisc)



// CWebPluginActiveXCtrl::CWebPluginActiveXCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CWebPluginActiveXCtrl

BOOL CWebPluginActiveXCtrl::CWebPluginActiveXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_WEBPLUGINACTIVEX,
			IDB_WEBPLUGINACTIVEX,
			afxRegApartmentThreading,
			_dwWebPluginActiveXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CWebPluginActiveXCtrl::CWebPluginActiveXCtrl - Constructor

CWebPluginActiveXCtrl::CWebPluginActiveXCtrl()
{
	InitializeIIDs(&IID_DWebPluginActiveX, &IID_DWebPluginActiveXEvents);
	// TODO: Initialize your control's instance data here.
	::WebPlugin_SetCallBack(CWebPluginActiveXCtrl::_Callback, this);
}



// CWebPluginActiveXCtrl::~CWebPluginActiveXCtrl - Destructor

CWebPluginActiveXCtrl::~CWebPluginActiveXCtrl()
{
	// TODO: Cleanup your control's instance data here.
}



// CWebPluginActiveXCtrl::OnDraw - Drawing function

void CWebPluginActiveXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: Replace the following code with your own drawing code.
	//pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//pdc->Ellipse(rcBounds);
}



// CWebPluginActiveXCtrl::DoPropExchange - Persistence support

void CWebPluginActiveXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
}



// CWebPluginActiveXCtrl::OnResetState - Reset control to default state

void CWebPluginActiveXCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}



// CWebPluginActiveXCtrl::AboutBox - Display an "About" box to the user

void CWebPluginActiveXCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_WEBPLUGINACTIVEX);
	dlgAbout.DoModal();
}



// CWebPluginActiveXCtrl message handlers

LONG CWebPluginActiveXCtrl::CallFun(LONG intValue, LPCTSTR strValue)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	::WebPlugin_CallFun((int)intValue, (const char*)strValue);

	return 0;
}

int __stdcall CWebPluginActiveXCtrl::_Callback(int int_param, const char *str_param, void *userdata)
{
	CWebPluginActiveXCtrl *pCtrl = (CWebPluginActiveXCtrl*)userdata;
	if (pCtrl == NULL)
		return -1;

	int str_len = strlen(str_param);
	char *str_temp = new char[str_len + 1];
	if (str_temp == NULL)
		return -1;
	memset(str_temp, 0, str_len + 1);
	strncpy(str_temp, str_param, str_len);

	::PostMessage(pCtrl->GetSafeHwnd(), WM_WEBEVENT, (WPARAM)int_param, (LPARAM)str_temp);
	return 0;
}

LRESULT CWebPluginActiveXCtrl::OnWebEvent( WPARAM wParam, LPARAM lParam )
{
	int int_param = (int)wParam;
	char *str_param = (char*)lParam;
	if (str_param == NULL)
		return -1;

	FireWebEvent(int_param, str_param);

	delete str_param;
	str_param = NULL;
	return 0;
}
