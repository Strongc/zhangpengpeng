#pragma once
#include "../../src/common/ComProc.h"

class CIPO_O_TipDlgDlg : public CDialogEx
{
private:
	NOTIFYICONDATA NotifyIcon;
	ComProcServer m_ComServer;

	void _ShowWnd();

protected:
	HICON m_hIcon;
	enum { IDD = IDD_IPO_O_TIPDLG_DIALOG };
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnNotifyIcon(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowTip(WPARAM wParam, LPARAM lParam);

public:
	CIPO_O_TipDlgDlg(CWnd* pParent = NULL);	// 标准构造函数

};
