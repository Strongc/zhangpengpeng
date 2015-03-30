/* Communicate between processes  '(zhangpengpeng 2014/05/11)
 * include Client and Server
 */

#include "ComProc.h"
#include <string>
using namespace std;

DWORD __stdcall _comprocserver_thread_listen(LPVOID pParam)
{
	if (pParam == NULL)
		return -1;
	ComProcServer *pServer = (ComProcServer *)pParam;
	pServer->listen();
	return 0;
}

ComProcServer::ComProcServer(const char *szName)
{
	m_strPipeName = "\\\\.\\pipe\\";
	m_strPipeName += szName;
	
	m_hNamedPipe = CreateNamedPipe(m_strPipeName.c_str(),  
		PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE,  
		1, 0, 0, 1000, NULL);

	m_hThread = CreateThread(NULL, 0, _comprocserver_thread_listen, this, 0, NULL);
	m_hEventEndThread = CreateEvent(NULL, FALSE, FALSE, NULL);
}

ComProcServer::~ComProcServer()
{
	if (m_hThread)
	{
		SetEvent(m_hEventEndThread);
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}

	if (m_hEventEndThread)
	{
		CloseHandle(m_hEventEndThread);
		m_hEventEndThread = NULL;
	}

	CloseHandle(m_hNamedPipe);
}

void ComProcServer::listen()
{
	OVERLAPPED olpConnectPipe;
	memset(&olpConnectPipe, 0, sizeof(OVERLAPPED));
	olpConnectPipe.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	HANDLE hArray[2] = {m_hEventEndThread, olpConnectPipe.hEvent};

	while (1)
	{
		ConnectNamedPipe(m_hNamedPipe, &olpConnectPipe);

		if (WaitForMultipleObjects(2, hArray, FALSE, INFINITE) == WAIT_OBJECT_0)
			break;

		char pBuf[1024] = {0};
		DWORD dwReadSize = 0;
		ReadFile(m_hNamedPipe, pBuf, 1024, &dwReadSize, NULL);

		void *pReplyBuf = NULL;
		int iReplySize = 0;
		m_pfRecvCallBack(pBuf, dwReadSize, &pReplyBuf, &iReplySize, m_pUserdata);

		if (pReplyBuf != NULL && iReplySize > 0)
		{
			DWORD dwWriteSize = 0;
			WriteFile(m_hNamedPipe, pReplyBuf, iReplySize, &dwWriteSize, NULL);
			delete pReplyBuf;
			pReplyBuf = NULL;
		}

		DisconnectNamedPipe(m_hNamedPipe);
	}

	CloseHandle(olpConnectPipe.hEvent);
}

void ComProcServer::SetRecvFun(COMPROC_RECV_FUN pfRecvCallback, void *pUserdata)
{
	m_pfRecvCallBack = pfRecvCallback;
	m_pUserdata = pUserdata;
}





ComProcClient::ComProcClient( const char *szName )
{
	m_strPipeName = "\\\\.\\pipe\\";
	m_strPipeName += szName;
}

ComProcClient::~ComProcClient()
{

}

int ComProcClient::SendWithReply( const void *pData, int iSize, void **ppRecvData, int *iRecvSize )
{
	if (WaitNamedPipe(m_strPipeName.c_str(), 3000) == FALSE)
		return -1;

	HANDLE hNamedPipe = CreateFile(m_strPipeName.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ,  
		NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD dwWrite = 0;
	WriteFile(hNamedPipe, pData, iSize, &dwWrite, NULL);
	
	char pRecv[1024] = {0};
	DWORD dwRead = 0;
	ReadFile(hNamedPipe, pRecv, 1024, &dwRead, NULL);

	if (dwRead > 0 && ppRecvData != NULL)
	{
		*iRecvSize = dwRead;
		*ppRecvData = new char[dwRead];
		memcpy(*ppRecvData, pRecv, dwRead);
	}

	CloseHandle(hNamedPipe);
	return 0;
}
