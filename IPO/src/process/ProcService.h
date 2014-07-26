/* IPO_Porcess Service '(zhangpengpeng 2014/05/10)
 * Get/Process/Send information
 */

#ifndef _PROCSERVICE_H_
#define _PROCSERVICE_H_

#include "../common/ZTaskBase.h"
#include "../common/ComProc.h"
#include <string>
using namespace std;

typedef struct _st_ProcTask
{
	int iTypeID;
	string strParam;
}ProcTask;

class CProcService : public CZTaskBase
{
private:
	ComProcClient m_ComClient;
	ComProcServer m_ComServer;

	int Task_Do(const void *pTask);

public:
	CProcService();
	~CProcService();

	static CProcService *GetInstance();
	static void FreeInstace();

	int Start();
	int Stop();

	int Input(const ProcTask *pTask);
};

#endif // _PROCSERVICE_H_
