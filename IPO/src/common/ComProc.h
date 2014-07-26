/* Communicate between processes  '(zhangpengpeng 2014/05/11)
 * include Client and Server
 */

#include <windows.h>
#include <string>
using namespace std;

typedef int (*COMPROC_RECV_FUN)(void *pData, int iSize, void **ppReplyData, int *iReplySize, void *pUserdata);

class ComProcServer
{
private:
	string m_strPipeName;
	HANDLE m_hNamedPipe;
	HANDLE m_hThread;
	HANDLE m_hEventEndThread;

	COMPROC_RECV_FUN m_pfRecvCallBack;
	void *m_pUserdata;

public:
	ComProcServer(const char *szName);
	~ComProcServer();
	void listen();

	void SetRecvFun(COMPROC_RECV_FUN pfRecvCallback, void *pUserdata);
};

class ComProcClient
{
private:
	string m_strPipeName;
	
public:
	ComProcClient(const char *szName);
	~ComProcClient();

	int SendWithReply(const void *pData, int iSize, void **ppRecvData, int *iRecvSize);
};