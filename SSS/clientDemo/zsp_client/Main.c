#include <stdio.h>
#include <stdlib.h>
#include "../../src/common/comtypes.h"
#include "../../src/common/comfuns.h"
#include "../../src/sys_layer/sys_net.h"
#include "../../src/zsp_protocol/zsp_protocol.h"

struct {
	int seq;
	SOCKET sock;
	int session;
} global_param;

int comm_to_server(int cmd, const char *send_buf, int send_len, char **resp_buf, int *resp_len)
{
	zsp_head_t *head = NULL;
	char *resp_content = NULL;

	int ret = SSS_ERROR;
	do
	{
		zsp_head_new(&head);
		if (head == NULL)
			break;

		head->session = global_param.session;
		head->seq = ++global_param.seq;
		head->cmd = cmd;
		head->csize = send_len;
		head->chksum = zsp_head_get_chksum(head);

		int outlen = 0;
		if (socket_send(global_param.sock, (char*)head, sizeof(zsp_head_t), &outlen) == SSS_ERROR)
			break;

		if (send_buf != NULL && send_len > 0)
		{
			if (socket_sendn(global_param.sock, send_buf, send_len, &outlen, 5000) == SSS_ERROR)
				break;
		}

		memset(head, 0, sizeof(zsp_head_t));
		if (socket_recv(global_param.sock, (char*)head, sizeof(zsp_head_t), &outlen) == SSS_ERROR)
			break;

		if (zsp_head_check(head) == SSS_FALSE || head->csize <= 0)
			break;

		if (global_param.session == -1)
			global_param.session = head->session;

		resp_content = (char*)malloc(head->csize);
		if (resp_content == NULL)
			break;
		memset(resp_content, 0, head->csize);

		if (socket_recvn(global_param.sock, (char*)resp_content, head->csize, &outlen, 5000) == SSS_ERROR)
			break;

		printf("\nResponse:\n");
		printf(resp_content);
		printf("\n");

		if (resp_buf != NULL && resp_len != NULL)
		{
			*resp_buf = resp_content;
			*resp_len = outlen;
		}
		else
		{
			SAFE_FREE(resp_content);
		}

		ret = SSS_OK;
	} while (0);

	if (head != NULL)
	{
		zsp_head_delete(head);
		head = NULL;
	}

	return ret;
}

int recv_file_from_server(long file_len)
{
	const int buf_len = 1024;
	char buf[1028] = { 0 };

	long recv_len = 0;
	printf("\nFile Content:\n");

	while (1)
	{
		int outlen = 0;
		int remain = file_len - recv_len;
		int once_len = buf_len < remain ? buf_len : remain;

		memset(buf, 0, buf_len + 4);
		socket_recvn(global_param.sock, buf, once_len, &outlen, 5000);
		printf(buf);

		recv_len += once_len;

		if (recv_len >= file_len)
			return SSS_OK;

		if (outlen < once_len)
			return SSS_ERROR;
	}

	return SSS_ERROR;
}

int main()
{
	memset(&global_param, 0, sizeof(global_param));
	global_param.session = -1;

	socket_init();
	socket_new(&global_param.sock, SOCKET_TCP_TYPE);
	socket_connect(global_param.sock, "127.0.0.1", 1120);

	do
	{
		if (comm_to_server(ZSP_CMD_HELLO, NULL, 0, NULL, NULL) == SSS_ERROR)
			break;

		const char *filename = "E:/a.txt";
		char *resp_buf = NULL;
		int resp_len = 0;
		if (comm_to_server(ZSP_CMD_PLAY, filename, strlen(filename) + 1, &resp_buf, &resp_len) == SSS_ERROR)
			break;

		char *file_size_str = "file_size:"; 
		char *p = strstr(resp_buf, file_size_str);
		p += strlen(file_size_str);
		long file_len = atol(p);
		if (p <= 0)
			break;

		recv_file_from_server(file_len);

		if (comm_to_server(ZSP_CMD_BYE, NULL, 0, NULL, NULL) == SSS_ERROR)
			break;

	} while (0);

	socket_delete(global_param.sock);
	socket_fini();

	system("pause");
	return 0;
}
