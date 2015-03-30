/* IPO_Porcess Service Interface '(zhangpengpeng 2014/05/10)
 * Start or Stop the Porcess
 */
#include "ProcService.h"

int IPO_P_ServiceInit()
{
	return 0;
}

int IPO_P_ServiceFini()
{
	CProcService::FreeInstace();
	return 0;
}

int IPO_P_ServiceStart()
{
	return CProcService::GetInstance()->Start();
}

int IPO_P_ServiceStop()
{
	return CProcService::GetInstance()->Stop();
}
