/**	@file TransprotDlg.h
 *	@note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *	@brief 该程序的主窗口类。
 *
 *	@author		张鹏鹏
 *	@date		2010/08/23
 *
 *	@note 这里为该程序主窗口类的头文件
 */

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


/**	@class CTransportDlg [TransportDlg.h, TransportDlg.cpp]
 *	@brief 窗口类，该程序的主窗口。
 *
 * 包含了聊天功能，能够启动文件传输功能，以及主窗口的各种消息响应。
 */

class CTransportDlg : public CDialog
{
// Construction
public:
	CTransportDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TRANSPORT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedBtnSend();
	afx_msg void OnBnClickedBtnSendfile();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg LRESULT OnRecvChatData(WPARAM wParam, LPARAM lParam);	//process when receive data
	afx_msg LRESULT OnNotifyIcon(WPARAM wParam, LPARAM lParam);		//when click notify icon
	afx_msg LRESULT OnProcessBar(WPARAM wParam, LPARAM lParam);		//give process information
	afx_msg void OnCommandRange(UINT nID);							//process a range of commands from menu items
	DECLARE_MESSAGE_MAP()

private:
	SOCKET m_socketChat;			//chatting socket for binding
	SOCKET m_socketFile;			//socket for binding to transport files
	DWORD m_dwIPOpposite;			//opposite ip address
	CEdit m_ceChatContent;			//edit control for show chat content and other warnning information
	CProgressCtrl m_ProcessBar;		//show process info
	NOTIFYICONDATA m_NotifyData;	//notify icon on system tray
	int m_iProcess;					//process of sending file

	BOOL InitSocket();		// initial socket
	BOOL NetConfig();		// config net option
	BOOL SetNotifyIcon();	// set notify icon on system tray

public:
	static DWORD WINAPI RecvChatProc(LPVOID lpParameter);			//recv chatting data thread function
	static DWORD WINAPI RecvFileProc(LPVOID lpParameter);			//recv file thread function
	static DWORD WINAPI SendFileProc(LPVOID lpParameter);			//send file thread function
	static DWORD WINAPI RecvFileProc_Dispose(LPVOID lpParameter);	//dispose the received buffer

};
