// TransportDlg.cpp : implementation file
//

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
}

BEGIN_MESSAGE_MAP(CTransportDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_MYMSG_RECVCHATDATA, OnRecvChatData)
	ON_COMMAND_RANGE(ID_CONNECT, ID_DISCONNECT, OnCommandRange)
	ON_BN_CLICKED(IDC_BTN_SEND, &CTransportDlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_SENDFILE, &CTransportDlg::OnBnClickedBtnSendfile)
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

	//content edit control show initial content
	SetDlgItemText(IDC_CHATCONTENT, "-------------Welcome-------------------");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTransportDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
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

BOOL CTransportDlg::NetConfig()
{
	CDlgSet dlgSet;

	if (IDOK != dlgSet.DoModal())
		return FALSE;

	//config essential net information
	m_dwIPOpposite = dlgSet.m_dwIPOpposite;

	return TRUE;
}

DWORD CTransportDlg::RecvChatProc(LPVOID lpParameter)
{
	//get parameter's information and release memory
	SOCKET sockBind = ((RECVPROCPARAM*)lpParameter)->sockBind;
	HWND hMainWnd = ((RECVPROCPARAM*)lpParameter)->hMainWnd;
	delete lpParameter;

	SOCKADDR_IN addrFrom;
	int len = sizeof(SOCKADDR);
	char recvBuf[SIZEPERTRANS];

	while (TRUE)
	{
		//receive data
		if (SOCKET_ERROR == recvfrom(sockBind, recvBuf, SIZEPERTRANS, 0, (SOCKADDR*)&addrFrom, &len))
		{
			//MessageBox("接受失败");
			break;
		}
		char *pTempBuf = new char[SIZEPERTRANS];
		sprintf(pTempBuf, "%s say: %s", inet_ntoa(addrFrom.sin_addr), recvBuf);
		::PostMessage(hMainWnd, WM_MYMSG_RECVCHATDATA, 0, (LPARAM)pTempBuf);
	}
	closesocket(sockBind);

	return 0;
}

DWORD CTransportDlg::RecvFileProc(LPVOID lpParameter)
{
	//get parameter's information and release memory
	SOCKET sockBind = ((RECVPROCPARAM*)lpParameter)->sockBind;
	HWND hMainWnd = ((RECVPROCPARAM*)lpParameter)->hMainWnd;
	delete lpParameter;

	//start listening
	listen(sockBind, 5);

	SOCKADDR_IN addrFrom;
	int len = sizeof(SOCKADDR);
	char sendBuf[SIZEPERTRANS];
	char recvBuf[SIZEPERTRANS];
	char fileName[SIZEPERTRANS];
	CString strFileName;

	while (TRUE)
	{
		SOCKET sockConn = accept(sockBind, (SOCKADDR*)&addrFrom, &len);

		//get filename
		strcpy(sendBuf, "transport file name");
		send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);
		recv(sockConn, fileName, SIZEPERTRANS, 0);
		strFileName.Format("%s", fileName);
		strFileName = strFileName.Right(strFileName.GetLength() - strFileName.ReverseFind('\\') - 1);
		TRACE("%s\n", strFileName);	
		
		//get file data
		strcpy(sendBuf, "transport file data");
		send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);
		CFile saveFile(strFileName, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeBinary);
		saveFile.SeekToEnd();	//write new data to the end
		int iRecvRealSize;
		iRecvRealSize = recv(sockConn, recvBuf, SIZEPERTRANS, 0);
		while (iRecvRealSize == SIZEPERTRANS)
		{
			saveFile.Write(recvBuf, SIZEPERTRANS);
			iRecvRealSize = recv(sockConn, recvBuf, SIZEPERTRANS, 0);
		}
		saveFile.Write(recvBuf, iRecvRealSize);		//last fragment
		saveFile.Close();

		//notify main Wnd transmission succeed
		char *pTempBuf = new char[200];
		sprintf(pTempBuf, " 接受到文件 %s ", strFileName);
		::PostMessage(hMainWnd, WM_MYMSG_RECVCHATDATA, 0, (LPARAM)pTempBuf);
	}
	closesocket(sockBind);

	return 0;
}

DWORD CTransportDlg::SendFileProc(LPVOID lpParameter)
{
	//get parameter's information and release memory
	DWORD dwIPOpposite = ((SENDPROCPARAM*)lpParameter)->dwIPOpposite;
	int iPort = ((SENDPROCPARAM*)lpParameter)->iPort;
	HWND hMainWnd = ((SENDPROCPARAM*)lpParameter)->hMainWnd;
	CString strFileName = ((SENDPROCPARAM*)lpParameter)->strFileName;
	delete lpParameter;

	//create connecting socket
	SOCKET sockConn = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrTo;
	addrTo.sin_family = AF_INET;
	addrTo.sin_port = htons(iPort);
	addrTo.sin_addr.S_un.S_addr = htonl(dwIPOpposite);

	//connect
	int len = sizeof(SOCKADDR);
	connect(sockConn, (SOCKADDR*)&addrTo, len);

	//get require-filename order
	char sendBuf[SIZEPERTRANS];
	char recvBuf[SIZEPERTRANS];
	recv(sockConn, recvBuf, SIZEPERTRANS, 0);
	if (strcmp(recvBuf, "transport file name") == 0)
	{
		strcpy(sendBuf, strFileName.GetBuffer(strFileName.GetLength()));
		send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);
	}

	//get require-file data order
	recv(sockConn, recvBuf, SIZEPERTRANS, 0);
	if (strcmp(recvBuf, "transport file data") == 0)
	{
		int iReadRealSize;
		CFile saveFile(strFileName, CFile::modeRead | CFile::typeBinary);
		iReadRealSize = saveFile.Read(sendBuf, SIZEPERTRANS);
		while(iReadRealSize == SIZEPERTRANS)
		{
			send(sockConn, sendBuf, SIZEPERTRANS, 0);
			iReadRealSize = saveFile.Read(sendBuf, SIZEPERTRANS);
		}
		send(sockConn, sendBuf, iReadRealSize, 0);	//last fragment

		saveFile.Close();
	}

	//notify main Wnd transmission succeed
	char *pTempBuf = new char[200];
	sprintf(pTempBuf, " 文件 %s 发送成功", strFileName);
	::PostMessage(hMainWnd, WM_MYMSG_RECVCHATDATA, 0, (LPARAM)pTempBuf);

	closesocket(sockConn);

	return 0;
}

LRESULT CTransportDlg::OnRecvChatData(WPARAM wParam, LPARAM lParam)
{
	CString strRecvData;	//get received data
	CString strContent;
	strRecvData.Format("%s", ((char*)lParam));
	delete (char*)lParam;

	GetDlgItemText(IDC_CHATCONTENT, strContent);	//original content
	strContent += "\r\n";
	strContent += strRecvData;						//add new data
	SetDlgItemText(IDC_CHATCONTENT, strContent);	//show new content

	return 0;
}

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
	::PostMessage(m_hWnd, WM_MYMSG_RECVCHATDATA, 0, (LPARAM)pTempBuf);
}

void CTransportDlg::OnCommandRange(UINT nID)
{
	switch(nID)
	{
	case ID_CONNECT:
		NetConfig();
		break;

	case ID_DISCONNECT:
		break;

	default:
		break;
	}
}

void CTransportDlg::OnBnClickedBtnSendfile()
{
	//get file name
	CString strFileName;
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("所有文件 (*.*)|*.*||"));
	if (IDOK == fileDlg.DoModal())
	{
		strFileName = fileDlg.GetPathName();		//get the opened file name
	}
	else
		return;

	SENDPROCPARAM *pSendFileProcParam = new SENDPROCPARAM;
	pSendFileProcParam->dwIPOpposite = m_dwIPOpposite;
	pSendFileProcParam->iPort = SERVERPORT;
	pSendFileProcParam->hMainWnd = m_hWnd;
	pSendFileProcParam->strFileName = strFileName;

	HANDLE hSendFileThread = CreateThread(NULL, 0, SendFileProc, (LPVOID)pSendFileProcParam, 0, NULL);
	CloseHandle(hSendFileThread);		//close this handle to release its counter
}
