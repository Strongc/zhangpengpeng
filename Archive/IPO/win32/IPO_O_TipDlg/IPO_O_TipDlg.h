
// IPO_O_TipDlg.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIPO_O_TipDlgApp:
// �йش����ʵ�֣������ IPO_O_TipDlg.cpp
//

class CIPO_O_TipDlgApp : public CWinApp
{
public:
	CIPO_O_TipDlgApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIPO_O_TipDlgApp theApp;