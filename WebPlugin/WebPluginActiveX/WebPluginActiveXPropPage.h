#pragma once

// WebPluginActiveXPropPage.h : Declaration of the CWebPluginActiveXPropPage property page class.


// CWebPluginActiveXPropPage : See WebPluginActiveXPropPage.cpp for implementation.

class CWebPluginActiveXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CWebPluginActiveXPropPage)
	DECLARE_OLECREATE_EX(CWebPluginActiveXPropPage)

// Constructor
public:
	CWebPluginActiveXPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_WEBPLUGINACTIVEX };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

