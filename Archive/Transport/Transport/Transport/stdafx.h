// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#include <afxsock.h>            // MFC socket extensions

/***********************我的定义从这里开始*****************************************/

//server port
#define SERVERPORT							6001
#define DATASIZEPERTRANS					2000
#define SIZEPERTRANS						(DATASIZEPERTRANS / 3 * 4 + 200)


/**	@struct RECVPROCPARAM
 *  @brief 给接受线程发送的参数
 *
 * 接受线程所要用到的 绑定socket、主窗口句柄
 */
typedef struct struct_RecvProcParam
{
	SOCKET sockBind;	// binded socket
	HWND hMainWnd;		// handle to main wnd
} RECVPROCPARAM;

/**	@struct SENDPROCPARAM
 *  @brief 给发送线程发送的参数
 *
 * 发送线程所要用到的 对方IP和端口、主窗口句柄、发送的文件名、发送进度
 */
typedef struct struct_SendProcParam
{
	DWORD dwIPOpposite;	//opposite ip address
	int iPort;			//connect port
	HWND hMainWnd;		//handle to main Wnd
	CString strFileName;//name of file to be sent
	int *piProcess;		//process of sending files
}SENDPROCPARAM;

/**	@struct RECVPROCDISPOSEPARAM
 *  @brief 给接受线程的处理子线程发送的参数
 *
 * 处理子线程所要用到的 主窗口句柄、接受缓冲的指针、缓冲的头尾索引、以及是否结束的标志
 */
typedef struct struct_RecvProcDisposeParam
{
	HWND hMainWnd;				//handle to main Wnd
	char *RecvBuf;				//buffer of received data
	int *piRecvBufHead;			//head of RecvBuf's data
	int *piRecvBufTail;			//tail of RecvBuf's data
	BOOL *pbRecvFileProcFinish;	//have received all data
}RECVPROCDISPOSEPARAM;


//my messages
#define WM_MYMSG_RECVCHATDATA				WM_USER + 1	//send recv data to main wnd
#define WM_MYMSG_NOTIFYICON					WM_USER + 2	//used to show icon on system tray
#define WM_MYMSG_PROCESSBAR					WM_USER + 3	//give process information

//encoding like base64 to translate binary data to text
int Encode(char *data, char *code, int len);
int Decode(char *data, char *code);
//move memory according to my requirement
bool MyMemMove(char *dest, char *src, int count);

/***********************我的定义到这里结束*****************************************/


//#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
//#endif


