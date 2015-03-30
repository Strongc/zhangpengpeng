
// IPO_O_TipDlgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IPO_O_TipDlg.h"
#include "IPO_O_TipDlgDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CIPO_O_TipDlgDlg �Ի���


int O_TipDlgDlg_RecvFun(void *pData, int iSize, void **ppReplyData, int *iReplySize, void *pUserdata)
{
	if (pUserdata == NULL)
		return -1;

	CIPO_O_TipDlgDlg *pDlg = (CIPO_O_TipDlgDlg *)pUserdata;
	if (!IsWindow(pDlg->GetSafeHwnd()))
		return -2;

	pDlg->PostMessage(WM_SHOWTIP, 0, (LPARAM)(LPCTSTR)(char*)pData);

	const char *szReplyOk = "200 OK";
	*iReplySize = strlen(szReplyOk) + 1;
	*ppReplyData = new char[*iReplySize];
	memcpy(*ppReplyData, szReplyOk, *iReplySize);

	return 0;
}

CIPO_O_TipDlgDlg::CIPO_O_TipDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIPO_O_TipDlgDlg::IDD, pParent)
	, m_ComServer("IPO_O_TipDlg")
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ComServer.SetRecvFun(O_TipDlgDlg_RecvFun, this);
}

void CIPO_O_TipDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIPO_O_TipDlgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_NOTIFYICON, OnNotifyIcon)
	ON_MESSAGE(WM_SHOWTIP, OnShowTip)
END_MESSAGE_MAP()


// CIPO_O_TipDlgDlg ��Ϣ�������

BOOL CIPO_O_TipDlgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	NotifyIcon.cbSize = sizeof(NOTIFYICONDATA);
	NotifyIcon.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	NotifyIcon.hWnd = m_hWnd;
	lstrcpy(NotifyIcon.szTip,"IPO_O_TipDlg");
	NotifyIcon.uCallbackMessage = WM_NOTIFYICON;
	NotifyIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	Shell_NotifyIcon(NIM_ADD, &NotifyIcon);

	MoveWindow(0, 0, 0, 0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CIPO_O_TipDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CIPO_O_TipDlgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CIPO_O_TipDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CIPO_O_TipDlgDlg::OnNotifyIcon( WPARAM wParam,LPARAM lParam )
{
	if ((lParam == WM_LBUTTONDOWN) || (lParam == WM_RBUTTONDOWN))
	{ 
		_ShowWnd();
	}
	return 0;
}

void CIPO_O_TipDlgDlg::_ShowWnd()
{
	static BOOL bFirst = TRUE;
	if (bFirst)
	{
		int iScreenWidth  = GetSystemMetrics(SM_CXSCREEN);
		int iScreenHeigth = GetSystemMetrics(SM_CYSCREEN);
		int iTipDlgWidth = 300;
		int iTipDlgHeigth = 200;
		MoveWindow(iScreenWidth - iTipDlgWidth - 10, iScreenHeigth - iTipDlgHeigth - 50, iTipDlgWidth, iTipDlgHeigth);

		bFirst = FALSE;
	}
	SetForegroundWindow();
	ShowWindow(SW_SHOW);
}

LRESULT CIPO_O_TipDlgDlg::OnShowTip( WPARAM wParam, LPARAM lParam )
{
	CString strTip = (LPCTSTR)lParam;
	GetDlgItem(IDC_STATIC_TIP)->SetWindowText(strTip);
	_ShowWnd();
	return 0;
}

