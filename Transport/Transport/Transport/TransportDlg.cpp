/**	@file TransportDlg.cpp
 *	@note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *	@brief CTransportDlg类的实现文件之一
 *
 *	@author		张鹏鹏
 *	@date		2010/08/23
 *
 *	@note 实现了CTransportDlg类除了文件传输的各项功能
 */


#include "stdafx.h"
#include "Transport.h"
#include "TransportDlg.h"
#include "DlgSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTransportDlg dialog


CTransportDlg::CTransportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransportDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTransportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESSBAR, m_ProcessBar);
	DDX_Control(pDX, IDC_CHATCONTENT, m_ceChatContent);
}

BEGIN_MESSAGE_MAP(CTransportDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_MYMSG_RECVCHATDATA, OnRecvChatData)
	ON_MESSAGE(WM_MYMSG_NOTIFYICON, OnNotifyIcon)
	ON_MESSAGE(WM_MYMSG_PROCESSBAR, OnProcessBar)
	ON_COMMAND_RANGE(ID_CONNECT, ID_EXIT, OnCommandRange)
	ON_BN_CLICKED(IDC_BTN_SEND, &CTransportDlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_SENDFILE, &CTransportDlg::OnBnClickedBtnSendfile)
	ON_WM_DROPFILES()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTransportDlg message handlers

BOOL CTransportDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	InitSocket();	//initial socket

	//create receiving chatting data thread
	RECVPROCPARAM *pRecvChatProcParam = new RECVPROCPARAM;
	pRecvChatProcParam->sockBind = m_socketChat;
	pRecvChatProcParam->hMainWnd = m_hWnd;
	HANDLE hRecvChatThread = CreateThread(NULL, 0, RecvChatProc, (LPVOID)pRecvChatProcParam, 0, NULL);
	CloseHandle(hRecvChatThread);		//close this handle to release its counter

	//create receiving file thread
	RECVPROCPARAM *pRecvFileProcParam = new RECVPROCPARAM;
	pRecvFileProcParam->sockBind = m_socketFile;
	pRecvFileProcParam->hMainWnd = m_hWnd;
	HANDLE hRecvFileThread = CreateThread(NULL, 0, RecvFileProc, (LPVOID)pRecvFileProcParam, 0, NULL);
	CloseHandle(hRecvFileThread);		//close this handle to release its counter

	//get config information
	NetConfig();

	//set notify icon
	SetNotifyIcon();

	//content edit control show initial content
	SetDlgItemText(IDC_CHATCONTENT, "-------------Welcome-------------------");

	//hide process bar by default
	m_ProcessBar.ShowWindow(SW_HIDE);
	SetTimer(1, 1000, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTransportDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	} 
	else if ((nID &0xFFF0) == SC_MINIMIZE)
	{
		ShowWindow(SW_HIDE);
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTransportDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTransportDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/**	@fn	BOOL CTransportDlg::InitSocket()
 *	@brief	初始化TCP和UDP的socket，一个用于接受传输来的文件，一个用于接受聊天信息
 *	@return	初始化成功与否
 */
BOOL CTransportDlg::InitSocket()
{
	//create socket for binding
	m_socketChat = socket(AF_INET, SOCK_DGRAM, 0);
	m_socketFile = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == m_socketChat || INVALID_SOCKET == m_socketFile)
	{
		MessageBox("套接字创建失败");
		return FALSE;
	}

	//bind 
	SOCKADDR_IN addrSock;
	addrSock.sin_family = AF_INET;
	addrSock.sin_port = htons(SERVERPORT);
	addrSock.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	int iResultBindChat = bind(m_socketChat, (SOCKADDR *)&addrSock, sizeof(SOCKADDR));
	int iResultBindFile = bind(m_socketFile, (SOCKADDR *)&addrSock, sizeof(SOCKADDR));
	if (SOCKET_ERROR == iResultBindChat || SOCKET_ERROR == iResultBindFile)
	{
		closesocket(m_socketChat);
		closesocket(m_socketFile);
		MessageBox("绑定失败");
		return FALSE;
	}
	
	return TRUE;
}

/**	@fn	BOOL CTransportDlg::NetConfig()
 *	@brief	配置发送对象的网络数据，目前这里进对IP进行了设置
 *	@return	配置成功与否
 */
BOOL CTransportDlg::NetConfig()
{
	CDlgSet dlgSet;

	if (IDOK != dlgSet.DoModal())
		return FALSE;

	//config essential net information
	m_dwIPOpposite = dlgSet.m_dwIPOpposite;

	return TRUE;
}

/**	@fn	BOOL CTransportDlg::SetNotifyIcon()
 *	@brief	设置系统托盘上的图标
 *	@return	设置成功与否
 */
BOOL CTransportDlg::SetNotifyIcon()
{
	m_NotifyData.cbSize = sizeof(NOTIFYICONDATA);
	m_NotifyData.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_NotifyData.hWnd = m_hWnd;
	lstrcpy(m_NotifyData.szTip, "网络传输工具");
	m_NotifyData.uCallbackMessage = WM_MYMSG_NOTIFYICON;
	m_NotifyData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP; 
	Shell_NotifyIcon(NIM_ADD, &m_NotifyData);

	return TRUE;
}

/**	@fn	DWORD CTransportDlg::RecvChatProc(LPVOID lpParameter)
 *	@brief	接受聊天信息，该函数为常驻线程
 *	@param lpParameter 聊天接受线程需要的启动参数.
 *	@return	0
 */
DWORD CTransportDlg::RecvChatProc(LPVOID lpParameter)
{
	//get parameter's information and release memory
	SOCKET sockBind = ((RECVPROCPARAM*)lpParameter)->sockBind;
	HWND hMainWnd = ((RECVPROCPARAM*)lpParameter)->hMainWnd;
	delete (RECVPROCPARAM*)lpParameter;

	SOCKADDR_IN addrFrom;
	int len = sizeof(SOCKADDR);
	char recvBuf[SIZEPERTRANS];

	while (TRUE)
	{
		//receive data
		if (SOCKET_ERROR == recvfrom(sockBind, recvBuf, SIZEPERTRANS, 0, (SOCKADDR*)&addrFrom, &len))
		{
			AfxMessageBox("接受失败");
			break;
		}
		char *pTempBuf = new char[SIZEPERTRANS];
		sprintf(pTempBuf, "%s say: %s", inet_ntoa(addrFrom.sin_addr), recvBuf);
		::PostMessage(hMainWnd, WM_MYMSG_RECVCHATDATA, 0, (LPARAM)pTempBuf);
	}
	closesocket(sockBind);

	return 0;
}

/**	@fn	LRESULT CTransportDlg::OnRecvChatData(WPARAM wParam, LPARAM lParam)
 *	@brief	更新聊天内容，响应WM_MYMSG_RECVCHATDATA消息进行更新
 *	@param wParam 没有用到.
 *	@param lParam 需要添加的信息.
 *	@return	0
 */
LRESULT CTransportDlg::OnRecvChatData(WPARAM wParam, LPARAM lParam)
{
	CString strRecvData;	//get received data
	CString strContent;
	strRecvData.Format("%s", ((char*)lParam));
	delete[] (char*)lParam;

	GetDlgItemText(IDC_CHATCONTENT, strContent);	//original content
	strContent += "\r\n";
	strContent += strRecvData;						//add new data
	SetDlgItemText(IDC_CHATCONTENT, strContent);	//show new content
	m_ceChatContent.LineScroll(m_ceChatContent.GetLineCount());	//scroll to last line
	

	//show window if hidden or lost focus
	SetForegroundWindow();
	ShowWindow(SW_SHOW);

	return 0;
}

/**	@fn	void CTransportDlg::OnBnClickedBtnSend()
 *	@brief	按下发送按钮，发出聊天信息
 */
void CTransportDlg::OnBnClickedBtnSend()
{
	SOCKADDR_IN addrTo;
	addrTo.sin_family = AF_INET;
	addrTo.sin_port = htons(SERVERPORT);
	addrTo.sin_addr.S_un.S_addr = htonl(m_dwIPOpposite);

	CString strSend;
	GetDlgItemText(IDC_EDIT_SEND, strSend);	//get sending data
	if (strSend.Compare("") == 0)
	{
		MessageBox("空白内容不得发送");
		return ;
	}
	sendto(m_socketChat, strSend, strSend.GetLength()+1, 0, (SOCKADDR*)&addrTo, sizeof(SOCKADDR));	//send data
	SetDlgItemText(IDC_EDIT_SEND, "");	//reset sending data

	//notify what has been sent
	char *pTempBuf = new char[200];
	sprintf(pTempBuf, "You say: %s", strSend.GetBuffer(strSend.GetLength()));
	strSend.ReleaseBuffer();
	::PostMessage(m_hWnd, WM_MYMSG_RECVCHATDATA, 0, (LPARAM)pTempBuf);
}

/**	@fn	void CTransportDlg::OnCommandRange(UINT nID)
 *	@brief	菜单项的响应，调用响应函数
 *	@param nID 菜单项ID.
 */
void CTransportDlg::OnCommandRange(UINT nID)
{
	switch(nID)
	{
	case ID_CONNECT:
		NetConfig();
		break;

	case ID_DISCONNECT:
		break;

	case ID_EXIT:
		//DestroyWindow();
		PostMessage(WM_CLOSE);
		//PostQuitMessage(0);
		break;

	default:
		break;
	}
}

/**	@fn	void CTransportDlg::OnDestroy()
 *	@brief	程序推出时，删除系统托盘上的图标
 */
void CTransportDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	Shell_NotifyIcon(NIM_DELETE, &m_NotifyData);
}

/**	@fn	LRESULT CTransportDlg::OnNotifyIcon(WPARAM wParam, LPARAM lParam)
 *	@brief	点击系统托盘上图标的响应函数
 *	@param wParam 没有用到.
 *	@param lParam 用于记录事件.
 *	@return	0
 */
LRESULT CTransportDlg::OnNotifyIcon(WPARAM wParam, LPARAM lParam)
{
	if (lParam == WM_LBUTTONUP)		//click with left button to show main wnd
	{
		SetForegroundWindow();
		ShowWindow(SW_SHOW);
	}
	else if (lParam == WM_RBUTTONUP)	//click with right button to show short-cut menu
	{
		CMenu menu;
		menu.LoadMenu(IDR_MENUMAIN);
		CPoint pt;
		GetCursorPos(&pt);
		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);
	}

	return 0;
}

/**	@fn	LRESULT CTransportDlg::OnProcessBar(WPARAM wParam, LPARAM lParam)
 *	@brief	响应WM_MYMSG_PROCESSBAR，更新进度条
 *	@param wParam 类型，具体见下面的描述.
 *	@param lParam 值，具体见下面的描述.
 *	@return	0
 */
LRESULT CTransportDlg::OnProcessBar(WPARAM wParam, LPARAM lParam)
{
	/* if wParam is 1, then make process bar shown , and set upper limit according lParam;
	 * if wParam is 2, then set process position of process bar according lParam as increment;
	 * if wParam is 3, then make process bar hidden;
	 */

	int iKey = (int)wParam;
	int iValue = (int)lParam;
	static int iUpperValue = 0;
	static float fProcess = 0;

	switch (iKey)
	{
	case 1:
		m_ProcessBar.ShowWindow(SW_SHOW);
		m_ProcessBar.SetRange(0, 100);
		iUpperValue = iValue;
		m_ProcessBar.SetPos(0);
		fProcess = 0;
		break;

	case 2:		//if send message at a high speed, don't use it directly. solution is in OnTimer	
		fProcess += iValue;
		m_ProcessBar.SetPos(100 * (fProcess / iUpperValue));
		break;

	case 3:
		m_ProcessBar.ShowWindow(SW_HIDE);
		break;

	default:
		break;
	}

	return 0;
}

/**	@fn	void CTransportDlg::OnTimer(UINT_PTR nIDEvent)
 *	@brief	定时函数
 *	@param nIDEvent 系统定义.
 */
void CTransportDlg::OnTimer(UINT_PTR nIDEvent)
{
	m_ProcessBar.SetPos(m_iProcess);	//useful when changing quickly

	CDialog::OnTimer(nIDEvent);
}
