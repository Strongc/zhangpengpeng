// WebPluginActiveXPropPage.cpp : Implementation of the CWebPluginActiveXPropPage property page class.

#include "stdafx.h"
#include "WebPluginActiveX.h"
#include "WebPluginActiveXPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CWebPluginActiveXPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CWebPluginActiveXPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CWebPluginActiveXPropPage, "WEBPLUGINACTIV.WebPluginActivPropPage.1",
	0xfc9ca311, 0x7961, 0x4e3d, 0x95, 0x80, 0x7c, 0xca, 0x5b, 0x5a, 0x4a, 0x7f)



// CWebPluginActiveXPropPage::CWebPluginActiveXPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CWebPluginActiveXPropPage

BOOL CWebPluginActiveXPropPage::CWebPluginActiveXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_WEBPLUGINACTIVEX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CWebPluginActiveXPropPage::CWebPluginActiveXPropPage - Constructor

CWebPluginActiveXPropPage::CWebPluginActiveXPropPage() :
	COlePropertyPage(IDD, IDS_WEBPLUGINACTIVEX_PPG_CAPTION)
{
}



// CWebPluginActiveXPropPage::DoDataExchange - Moves data between page and properties

void CWebPluginActiveXPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CWebPluginActiveXPropPage message handlers
