/**	@file TransportDlg.cpp
 *	@note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *	@brief CTransportDlg���ʵ���ļ�֮��
 *
 *	@author		������
 *	@date		2010/08/23
 *
 *	@note ʵ����CTransportDlg���ļ�����ĸ����
 */


#include "stdafx.h"
#include "Transport.h"
#include "TransportDlg.h"
#include "TransportData.h"

#define RecvBufCount	25


/* �����߳�ͬ���Ļ��������ź����Ķ���*/
HANDLE hMutexRecvBuf;			//only one thread can access RecvBuf 
HANDLE hSemaGet;				//semaphore for receive process
HANDLE hSemaDispose;			//semaphore for dispose prcess

/**	@fn	DWORD CTransportDlg::RecvFileProc(LPVOID lpParameter)
 *	@brief	�����ļ����ú���Ϊ��פ�߳�
 *	@param lpParameter �ļ������߳���Ҫ����������.
 *	@return	0
 */
DWORD CTransportDlg::RecvFileProc(LPVOID lpParameter)
{
	BOOL bRecvFileProcFinish = TRUE;		//have received all data

	//get parameter's information and release memory
	SOCKET sockBind = ((RECVPROCPARAM*)lpParameter)->sockBind;
	HWND hMainWnd = ((RECVPROCPARAM*)lpParameter)->hMainWnd;
	delete (RECVPROCPARAM*)lpParameter;

	//start listening
	listen(sockBind, 5);

	SOCKADDR_IN addrFrom;
	int len = sizeof(SOCKADDR);
	char RecvOneBuf[SIZEPERTRANS];
	int iRecvRealSize;				//real size of received data once

	//protected variables
	char RecvBuf[SIZEPERTRANS * RecvBufCount];	//receive buffer waiting for completed data
	int iRecvBufHead;				//head of RecvBuf's data
	int iRecvBufTail;				//tail of RecvBuf's data

	//access protect
	hMutexRecvBuf = CreateMutex(NULL, FALSE, "mutexRecvBuf");
	hSemaGet = CreateSemaphore(NULL, RecvBufCount, RecvBufCount, NULL);
	hSemaDispose = CreateSemaphore(NULL, 0, RecvBufCount, NULL);

	while (TRUE)
	{
		SOCKET sockConn = accept(sockBind, (SOCKADDR*)&addrFrom, &len);

		//transport one file
		iRecvBufHead = 0;
		iRecvBufTail = 0;
		bRecvFileProcFinish = FALSE;

		//startup disposing thread
		RECVPROCDISPOSEPARAM *pDisposeParam = new RECVPROCDISPOSEPARAM;
		pDisposeParam->hMainWnd = hMainWnd;
		pDisposeParam->RecvBuf = RecvBuf;
		pDisposeParam->piRecvBufHead = &iRecvBufHead;
		pDisposeParam->piRecvBufTail = &iRecvBufTail;
		pDisposeParam->pbRecvFileProcFinish = &bRecvFileProcFinish;
		CreateThread(NULL, 0, RecvFileProc_Dispose, (LPVOID)pDisposeParam, 0, NULL);

		while (bRecvFileProcFinish == FALSE)
		{
			memset(RecvOneBuf, 0, SIZEPERTRANS);
			iRecvRealSize = recv(sockConn, RecvOneBuf, SIZEPERTRANS, 0);	//get net-data
			TRACE("--------------------------------------%d, %d\n", iRecvRealSize, SIZEPERTRANS);

			if (iRecvRealSize <= 0)	//haven't get anything
			{
				Sleep(500);
			}


			//access protected section
			WaitForSingleObject(hSemaGet, INFINITE);
			WaitForSingleObject(hMutexRecvBuf, INFINITE);

			for (int i = 0; i < iRecvRealSize; i++)
			{
				*(RecvBuf + iRecvBufTail) = *(RecvOneBuf + i);
				iRecvBufTail = (iRecvBufTail + 1) % (SIZEPERTRANS * RecvBufCount);
				if ((iRecvBufTail % SIZEPERTRANS) == 0)	//count of useful buffer increase
				{
					ReleaseSemaphore(hSemaDispose, 1, NULL);
				}
			}
			ReleaseMutex(hMutexRecvBuf);
			//leave protected section

		}//while (TRUE)

	}

	closesocket(sockBind);
	CloseHandle(hMutexRecvBuf);
	CloseHandle(hSemaGet);
	CloseHandle(hSemaDispose);

	return 0;
}

/**	@fn	DWORD CTransportDlg::RecvFileProc_Dispose(LPVOID lpParameter)
 *	@brief	�����ļ��Ĵ��������ú�����Ӧ���߳����ļ������߳�����
 *	@param lpParameter �ļ����մ������߳���Ҫ����������.
 *	@return	0
 */
DWORD CTransportDlg::RecvFileProc_Dispose(LPVOID lpParameter)
{
	//get parameters
	HWND hMainWnd = ((RECVPROCDISPOSEPARAM*)lpParameter)->hMainWnd;
	char *RecvBuf = ((RECVPROCDISPOSEPARAM*)lpParameter)->RecvBuf;
	int *piRecvBufHead = ((RECVPROCDISPOSEPARAM*)lpParameter)->piRecvBufHead;
	int *piRecvBufTail = ((RECVPROCDISPOSEPARAM*)lpParameter)->piRecvBufTail;
	BOOL *pbRecvFileProcFinish = ((RECVPROCDISPOSEPARAM*)lpParameter)->pbRecvFileProcFinish;
	delete (RECVPROCDISPOSEPARAM*)lpParameter;

	BOOL bTransporting = FALSE;		//whether it is transporting
	int iErrorCount = 0;			//count of error
	CFile saveFile;
	CString strFileName;
	CTransportData *ctpData = new CTransportData();
	char *pDisposeBuf = new char[SIZEPERTRANS];

	while (*pbRecvFileProcFinish == FALSE || *piRecvBufHead != *piRecvBufTail)
	{
		//access protected section
		WaitForSingleObject(hSemaDispose, INFINITE);
		WaitForSingleObject(hMutexRecvBuf, INFINITE);

		for (int i = 0; i < SIZEPERTRANS; i++)
		{
			*(pDisposeBuf + i) = *(RecvBuf + *piRecvBufHead); 
			*piRecvBufHead = (*piRecvBufHead + 1) % (SIZEPERTRANS * RecvBufCount);
		}
		ReleaseSemaphore(hSemaGet, 1, NULL);
		ReleaseMutex(hMutexRecvBuf);
		//lease protected section

		ctpData->SetXmlString(pDisposeBuf);
		TRACE(">>>>>>>>>>>DISPOSE::%s\n", ctpData->GetCmd());

		//get the filename then begin to write
		if (ctpData->GetCmd() == "filename" && bTransporting == FALSE)
		{
			strFileName = ctpData->GetData();
			strFileName = strFileName.Right(strFileName.GetLength() - strFileName.ReverseFind('\\') - 1);	//remove path name
			TRACE("%s\n", strFileName);
			if (FALSE == saveFile.Open(strFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
			{
				AfxMessageBox("�����ļ�ʧ��");
				iErrorCount = 0;
				break;
			}
			bTransporting = TRUE;

			//notify main Wnd transmission starting
			char *pTempBuf = new char[200];
			sprintf(pTempBuf, " ��ʼ�����ļ� %s ", strFileName);
			::PostMessage(hMainWnd, WM_MYMSG_RECVCHATDATA, 0, (LPARAM)pTempBuf);
		} 
		else if (ctpData->GetCmd() == "filedata" && bTransporting == TRUE)	//get the filedata then continue to write
		{
			saveFile.Write(ctpData->GetData(), ctpData->GetDataSize());
		} 
		else if (ctpData->GetCmd() == "fileover" && bTransporting == TRUE)	//transport is over
		{
			saveFile.Close();
			bTransporting = FALSE;
			*pbRecvFileProcFinish = TRUE;
			iErrorCount = 0;

			//notify main Wnd transmission succeed
			char *pTempBuf = new char[200];
			sprintf(pTempBuf, " ���ܵ��ļ� %s ", strFileName);
			::PostMessage(hMainWnd, WM_MYMSG_RECVCHATDATA, 0, (LPARAM)pTempBuf);
		} 
		else	//illegal command
		{
			AfxMessageBox("�����������");
			iErrorCount++;
		}

		if (iErrorCount >= 10)	//too many errors so exit this transport
		{
			*pbRecvFileProcFinish = TRUE;
			iErrorCount = 0;
			AfxMessageBox("����̫��Σ��˳����δ���");
			break;
		}
	}

	delete ctpData;
	delete[] pDisposeBuf;
	
	return 0;
}

/**	@fn	DWORD CTransportDlg::SendFileProc(LPVOID lpParameter)
 *	@brief	�����ļ��������ú�����Ӧ���߳������߳�����
 *	@param lpParameter �ļ������߳���Ҫ����������.
 *	@return	0
 */
DWORD CTransportDlg::SendFileProc(LPVOID lpParameter)
{
	//get parameter's information and release memory
	DWORD dwIPOpposite = ((SENDPROCPARAM*)lpParameter)->dwIPOpposite;
	int iPort = ((SENDPROCPARAM*)lpParameter)->iPort;
	HWND hMainWnd = ((SENDPROCPARAM*)lpParameter)->hMainWnd;
	CString strFileName = ((SENDPROCPARAM*)lpParameter)->strFileName;
	int *piProcess_MainWnd = ((SENDPROCPARAM*)lpParameter)->piProcess;
	delete (SENDPROCPARAM*)lpParameter;

	float fProcess = 0;
	float fMaxProcess = 0;

	//create connecting socket
	SOCKET sockConn = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrTo;
	addrTo.sin_family = AF_INET;
	addrTo.sin_port = htons(iPort);
	addrTo.sin_addr.S_un.S_addr = htonl(dwIPOpposite);

	char readBuf[DATASIZEPERTRANS + 1];		//force to add zero at its tail
	char sendBuf[SIZEPERTRANS];
	CTransportData *ctpData = new CTransportData();

	//connect
	int len = sizeof(SOCKADDR);
	connect(sockConn, (SOCKADDR*)&addrTo, len);

	//send filename
	ctpData->SetXmlData("filename", strFileName, strFileName.GetLength() + 1);
	memset(sendBuf, 0, SIZEPERTRANS);
	strcpy(sendBuf, ctpData->GetXmlCharArray());
	send(sockConn, sendBuf, SIZEPERTRANS, 0);
	TRACE(">>>>>>>>>>>SEND::%s\n", ctpData->GetCmd());

	//notify main Wnd transmission starting
	char *pTempBuf = new char[200];
	sprintf(pTempBuf, " ��ʼ�����ļ� %s ", strFileName);
	::PostMessage(hMainWnd, WM_MYMSG_RECVCHATDATA, 0, (LPARAM)pTempBuf);

	//send filedata
	int iReadRealSize;
	CFile file(strFileName, CFile::modeRead | CFile::typeBinary);
	::PostMessage(hMainWnd, WM_MYMSG_PROCESSBAR, 1, (LPARAM)file.GetLength());	//show process bar
	fMaxProcess = file.GetLength();
	fProcess = 0;
	memset(readBuf, 0, DATASIZEPERTRANS + 1);
	iReadRealSize = file.Read(readBuf, DATASIZEPERTRANS);
	while(iReadRealSize == DATASIZEPERTRANS)		//file data is enough
	{
		ctpData->SetXmlData("filedata", readBuf, DATASIZEPERTRANS);
		memset(sendBuf, 0, SIZEPERTRANS);
		strcpy(sendBuf, ctpData->GetXmlCharArray());
		send(sockConn, sendBuf, SIZEPERTRANS, 0);
		//::PostMessage(hMainWnd, WM_MYMSG_PROCESSBAR, 2, (LPARAM)SIZEPERTRANS);	//not fit
		fProcess += iReadRealSize;
		*piProcess_MainWnd = 100 * (fProcess / fMaxProcess);
		TRACE(">>>>>>>>>>>SEND::%s\n", ctpData->GetCmd());

		memset(readBuf, 0, DATASIZEPERTRANS + 1);
		iReadRealSize = file.Read(readBuf, DATASIZEPERTRANS);
	}
	//last fragment
	ctpData->SetXmlData("filedata", readBuf, iReadRealSize);
	memset(sendBuf, 0, SIZEPERTRANS);
	strcpy(sendBuf, ctpData->GetXmlCharArray());
	send(sockConn, sendBuf, SIZEPERTRANS, 0);
	//::PostMessage(hMainWnd, WM_MYMSG_PROCESSBAR, 2, (LPARAM)iReadRealSize);	//not fit
	fProcess += iReadRealSize;
	*piProcess_MainWnd = 100 * (fProcess / fMaxProcess);
	TRACE(">>>>>>>>>>>SEND::%s\n", ctpData->GetCmd());

	//transport is over
	file.Close();
	ctpData->SetXmlData("fileover", "", 0);
	memset(sendBuf, 0, SIZEPERTRANS);
	strcpy(sendBuf, ctpData->GetXmlCharArray());
	send(sockConn, sendBuf, SIZEPERTRANS, 0);
	TRACE(">>>>>>>>>>>SEND::%s\n", ctpData->GetCmd());

	//notify main Wnd transmission succeed
	pTempBuf = new char[200];
	sprintf(pTempBuf, " �ļ� %s ���ͳɹ�", strFileName);
	::PostMessage(hMainWnd, WM_MYMSG_RECVCHATDATA, 0, (LPARAM)pTempBuf);
	::PostMessage(hMainWnd, WM_MYMSG_PROCESSBAR, 3, 0);		//hide prcess bar

	delete ctpData;
	closesocket(sockConn);

	return 0;
}

/**	@fn	void CTransportDlg::OnBnClickedBtnSendfile()
 *	@brief	���·����ļ���ť�������ļ������߳�
 */
void CTransportDlg::OnBnClickedBtnSendfile()
{
	//get file name
	CString strFileName;
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("�����ļ� (*.*)|*.*||"));
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
	pSendFileProcParam->piProcess = &m_iProcess;

	HANDLE hSendFileThread = CreateThread(NULL, 0, SendFileProc, (LPVOID)pSendFileProcParam, 0, NULL);
	CloseHandle(hSendFileThread);		//close this handle to release its counter
}

/**	@fn	void CTransportDlg::OnDropFiles(HDROP hDropInfo)
 *	@brief	�����ļ��������ڣ������ļ������̷߳����ļ�
 *	@param hDropInfo ϵͳ����.
 */
void CTransportDlg::OnDropFiles(HDROP hDropInfo)
{
	char *filename = new char[100];
	int count = ::DragQueryFile(hDropInfo, 0xffffffff, NULL, 512);	//get count of dropped files

	for (int i = 0; i < count; i++)
	{
		//get filename
		int nchar = DragQueryFile(hDropInfo, i, filename, 512);

		SENDPROCPARAM *pSendFileProcParam = new SENDPROCPARAM;
		pSendFileProcParam->dwIPOpposite = m_dwIPOpposite;
		pSendFileProcParam->iPort = SERVERPORT;
		pSendFileProcParam->hMainWnd = m_hWnd;
		pSendFileProcParam->strFileName = filename;
		pSendFileProcParam->piProcess = &m_iProcess;

		HANDLE hSendFileThread = CreateThread(NULL, 0, SendFileProc, (LPVOID)pSendFileProcParam, 0, NULL);
		CloseHandle(hSendFileThread);		//close this handle to release its counter

	}

	DragFinish(hDropInfo);
	delete[] filename;

	CDialog::OnDropFiles(hDropInfo);
}
