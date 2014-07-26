// TransportDlg.h : header file
//

#pragma once


// CTransportDlg dialog
class CTransportDlg : public CDialog
{
// Construction
public:
	CTransportDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TRANSPORT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedBtnSend();
	afx_msg LRESULT OnRecvChatData(WPARAM wParam, LPARAM lParam);	//process when receive data
	afx_msg void OnCommandRange(UINT nID);						//process a range of commands from menu items
	DECLARE_MESSAGE_MAP()

private:
	SOCKET m_socketChat;	//chatting socket for binding
	SOCKET m_socketFile;	//socket for binding to transport files
	DWORD m_dwIPOpposite;		//opposite ip address
	BOOL InitSocket();
	BOOL NetConfig();

public:
	static DWORD WINAPI RecvChatProc(LPVOID lpParameter);	//recv chatting data thread function
	static DWORD WINAPI RecvFileProc(LPVOID lpParameter);	//recv file thread function
	static DWORD WINAPI SendFileProc(LPVOID lpParameter);	//send file thread function

	afx_msg void OnBnClickedBtnSendfile();
};
