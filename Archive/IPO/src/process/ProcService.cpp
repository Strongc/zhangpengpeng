/* IPO_Porcess Service '(zhangpengpeng 2014/05/10)
 * Get/Process/Send information
 */

#include "ProcService.h"
#include "../ConstID.h"

int ProcService_RecvFun(void *pData, int iSize, void **ppReplyData, int *iReplySize, void *pUserdata)
{
	if (pUserdata == NULL)
		return -1;

	CProcService *pService = (CProcService *)pUserdata;

	ProcTask *pTask = new ProcTask();
	pTask->iTypeID = PROCTASKTYPE_TIP;
	pTask->strParam = (char*)pData;
	pService->Input(pTask);

	const char *szReplyOk = "200 OK";
	*iReplySize = strlen(szReplyOk) + 1;
	*ppReplyData = new char[*iReplySize];
	memcpy(*ppReplyData, szReplyOk, *iReplySize);

	return 0;
}

CProcService::CProcService()
	: m_ComServer("IPO_I_CmdInput")
	, m_ComClient("IPO_O_TipDlg")
{
	m_ComServer.SetRecvFun(ProcService_RecvFun, this);
}

CProcService::~CProcService()
{

}

int CProcService::Task_Do(const void *pTask)
{
	if (pTask == NULL)
		return -1;

	ProcTask *pProcTask = (ProcTask*)pTask;
	if (pProcTask->iTypeID = PROCTASKTYPE_TIP)
	{
		void *pRecvData = NULL;
		int iRecvSize = 0;
		m_ComClient.SendWithReply(pProcTask->strParam.c_str(), pProcTask->strParam.size() + 1, \
			&pRecvData, &iRecvSize);
	}
	return 0;
}

static CProcService *gs_pProcService = NULL;
CProcService * CProcService::GetInstance()
{
	if (gs_pProcService == NULL)
		gs_pProcService = new CProcService();
	return gs_pProcService;
}

void CProcService::FreeInstace()
{
	if (gs_pProcService != NULL)
	{
		delete gs_pProcService;
		gs_pProcService = NULL;
	}
}

int CProcService::Start()
{
	if (!Task_Start())
		return -1;
	return 0;
}

int CProcService::Stop()
{
	if (!Task_Stop())
		return -1;
	return 0;
}

int CProcService::Input( const ProcTask *pTask )
{
	if (!Task_Add((void *)pTask))
		return -1;
	return 0;
}

