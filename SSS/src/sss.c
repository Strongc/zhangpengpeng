/* SuperStreamServer SSS '(zhangpengpeng 20140630) */

#include "sss.h"
#include <stdio.h>
#include "common/log.h"
#include "zsp_server/zsp_server_interface.h"

int main()
{
	LOG_INFO("SSS v0.1.0 by Zhangpengpeng");

	LOG_INFO("SSS Starting...");

	SSS_Handle server = NULL;
	zsp_server_init();
	zsp_server_new(&server);
	zsp_server_start(server);

	LOG_INFO("SSS Started.");

	while (1)
	{
		char ch = getch();
		if (ch == 'q' || ch == 'Q')
			break;
	}

	LOG_INFO("SSS Stopping...");

	zsp_server_stop(server);
	zsp_server_delete(server);
	zsp_server_fini();

	LOG_INFO("SSS Stopped.");

	return 0;
}
