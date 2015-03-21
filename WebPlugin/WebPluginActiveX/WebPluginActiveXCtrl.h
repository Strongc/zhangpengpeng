#pragma once

// WebPluginActiveXCtrl.h : Declaration of the CWebPluginActiveXCtrl ActiveX Control class.

#define WM_WEBEVENT		WM_USER + 100

// CWebPluginActiveXCtrl : See WebPluginActiveXCtrl.cpp for implementation.

class CWebPluginActiveXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CWebPluginActiveXCtrl)

// Constructor
public:
	CWebPluginActiveXCtrl();

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	~CWebPluginActiveXCtrl();

	DECLARE_OLECREATE_EX(CWebPluginActiveXCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CWebPluginActiveXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CWebPluginActiveXCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CWebPluginActiveXCtrl)		// Type name and misc status

// Message maps
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
		eventidFireWebEvent = 1L,
		dispidCallFun = 1L
	};

protected:
	static int __stdcall _Callback(int int_param, const char *str_param, void *userdata);
	afx_msg LRESULT OnWebEvent(WPARAM wParam, LPARAM lParam);

protected:
	LONG CallFun(LONG intValue, LPCTSTR strValue);

	void FireWebEvent(LONG intValue, LPCTSTR strValue)
	{
		FireEvent(eventidFireWebEvent, EVENT_PARAM(VTS_I4 VTS_BSTR), intValue, strValue);
	}
};

