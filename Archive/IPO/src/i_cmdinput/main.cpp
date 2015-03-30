#include <stdio.h>
#include <stdlib.h>
#include "../common/ComProc.h"

int main()
{
	ComProcClient client("IPO_I_CmdInput");
	char szSendBuf[1024] = {0};
	void *szRecvBuf = NULL;
	int iRecvSize;
	scanf(" %s", szSendBuf);
	client.SendWithReply(szSendBuf, strlen(szSendBuf) + 1, &szRecvBuf, &iRecvSize);
	printf("WriteFileResult: %s\n", (char*)szRecvBuf);
	if (szRecvBuf != NULL)
	{
		delete szRecvBuf;
		szRecvBuf = NULL;
	}
	system("pause");

	return 0;
}

