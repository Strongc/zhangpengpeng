/* zsp_handle '(zhangpengpeng 20150101) 
 * handle zsp protocol
 */

#include "zsp_protocol.h"
#include "zsp_handle.h"
#include "../common/comfuns.h"
#include "stdio.h"

typedef struct _st_handle_cmd_param
{
	zsp_session_t *session;

	int cmd;
	char *body;
	int body_len;

	int cmd_rep;
	char *response;
	int response_len;
} handle_cmd_param_t;

int zsp_handle_hello(handle_cmd_param_t *param)
{
	if (param == NULL)
		return SSS_ERROR;

	const char *hello_str = \
		"ZSP V1.0 \r\n"
		"Server: SSS V0.1 \r\n"
		"Support: HELLO BYE PLAY STOP HEARTBEAT PAUSE RESUME SETSPEED";

	param->cmd_rep = ZSP_REP_OK;
	new_copy_str(&param->response, hello_str, &param->response_len);
	
	return SSS_OK;
}

int zsp_handle_bye(handle_cmd_param_t *param)
{
	if (param == NULL)
		return SSS_ERROR;

	const char *bye_str = "Bye";

	param->cmd_rep = ZSP_REP_OK;
	new_copy_str(&param->response, bye_str, &param->response_len);

	return SSS_ERROR;	// to end the thread
}

int zsp_handle_play(handle_cmd_param_t *param)
{
	if (param == NULL)
		return SSS_ERROR;

	char *filename = param->body;
	if (filename == NULL || strlen(filename) == 0)
	{
		param->cmd_rep = ZSP_REP_NOTFOUND;
		new_copy_str(&param->response, "no filename", &param->response_len);
		return SSS_ERROR;
	}

	if (param->session->transport == NULL)
	{
		if (zsp_transport_new(&param->session->transport, param->session->sock) == SSS_ERROR)
		{
			param->cmd_rep = ZSP_REP_ERROR;
			new_copy_str(&param->response, "fail to new transport", &param->response_len);
			return SSS_ERROR;
		}
	}

	zsp_transport_start_return ret;
	memset(&ret, 0, sizeof(zsp_transport_start_return));
	if (zsp_transport_start(param->session->transport, filename, &ret) == SSS_ERROR)
	{
		param->cmd_rep = ZSP_REP_ERROR;
		new_copy_str(&param->response, "fail to start transport", &param->response_len);
		return SSS_ERROR;
	}

	param->cmd_rep = ZSP_REP_OK;
	param->response = (char*)malloc(1024);
	memset(param->response, 0, 1024);
	_snprintf(param->response, 1024, "start transport. file_size:%ld", ret.file_size);
	param->response_len = strlen(param->response) + 1;
	//new_copy_str(&param->response, "start transport", &param->response_len);

	return SSS_OK;
}

int zsp_handle_stop(handle_cmd_param_t *param)
{
	if (param == NULL)
		return SSS_ERROR;

	if (param->session->transport == NULL)
	{
		param->cmd_rep = ZSP_REP_ERROR;
		new_copy_str(&param->response, "no transport", &param->response_len);
		return SSS_ERROR;
	}

	if (zsp_transport_stop(param->session->transport) == SSS_ERROR)
	{
		param->cmd_rep = ZSP_REP_ERROR;
		new_copy_str(&param->response, "fail to stop transport", &param->response_len);
		return SSS_ERROR;
	}

	if (zsp_transport_delete(param->session->transport) == SSS_ERROR)
	{
		param->cmd_rep = ZSP_REP_ERROR;
		new_copy_str(&param->response, "fail to delete transport", &param->response_len);
		return SSS_ERROR;
	}
	param->session->transport = NULL;

	param->cmd_rep = ZSP_REP_OK;
	new_copy_str(&param->response, "stop transport", &param->response_len);
	return SSS_OK;
}

int zsp_handle_heartbeat(handle_cmd_param_t *param)
{
	if (param == NULL)
		return SSS_ERROR;

	if (param->session->transport == NULL)
	{
		param->cmd_rep = ZSP_REP_ERROR;
		new_copy_str(&param->response, "no transport", &param->response_len);
		return SSS_ERROR;
	}

	if (zsp_transport_heartbeat(param->session->transport) == SSS_ERROR)
	{
		param->cmd_rep = ZSP_REP_ERROR;
		new_copy_str(&param->response, "fail to heartbeat transport", &param->response_len);
		return SSS_ERROR;
	}

	param->cmd_rep = ZSP_REP_OK;
	new_copy_str(&param->response, "heartbeat", &param->response_len);
	return SSS_OK;
}

int zsp_handle_pause(handle_cmd_param_t *param, int is_pause)
{
	if (param == NULL)
		return SSS_ERROR;

	if (param->session->transport == NULL)
	{
		param->cmd_rep = ZSP_REP_ERROR;
		new_copy_str(&param->response, "no transport", &param->response_len);
		return SSS_ERROR;
	}

	if (zsp_transport_pause(param->session->transport, is_pause) == SSS_ERROR)
	{
		param->cmd_rep = ZSP_REP_ERROR;
		if (is_pause)
			new_copy_str(&param->response, "fail to pause transport", &param->response_len);
		else
			new_copy_str(&param->response, "fail to resume transport", &param->response_len);
		return SSS_ERROR;
	}

	param->cmd_rep = ZSP_REP_OK;
	if (is_pause)
		new_copy_str(&param->response, "pause transport", &param->response_len);
	else
		new_copy_str(&param->response, "resume transport", &param->response_len);
	return SSS_OK;
}

int zsp_handle_setspeed(handle_cmd_param_t *param)
{
	if (param == NULL)
		return SSS_ERROR;

	if (param->body == NULL || strlen(param->body) == 0)
	{
		param->cmd_rep = ZSP_REP_ERROR;
		new_copy_str(&param->response, "no param", &param->response_len);
		return SSS_ERROR;
	}

	int speed = atoi(param->body);

	if (param->session->transport == NULL)
	{
		param->cmd_rep = ZSP_REP_ERROR;
		new_copy_str(&param->response, "no transport", &param->response_len);
		return SSS_ERROR;
	}

	if (zsp_transport_setspeed(param->session->transport, speed) == SSS_ERROR)
	{
		param->cmd_rep = ZSP_REP_ERROR;
		new_copy_str(&param->response, "fail to set speed of transport", &param->response_len);
		return SSS_ERROR;
	}

	param->cmd_rep = ZSP_REP_OK;
	new_copy_str(&param->response, "set speed of transport", &param->response_len);
	return SSS_OK;
}

int zsp_handle_cmd(handle_cmd_param_t *param)
{
	if (param == NULL)
		return SSS_ERROR;

	int ret = SSS_ERROR;
	switch (param->cmd)
	{
	case ZSP_CMD_HELLO:
		ret = zsp_handle_hello(param);
		break;

	case ZSP_CMD_BYE:
		ret = zsp_handle_bye(param);
		break;

	case ZSP_CMD_PLAY:
		ret = zsp_handle_play(param);
		break;

	case ZSP_CMD_STOP:
		ret = zsp_handle_stop(param);
		break;

	case ZSP_CMD_HEARTBEAT:
		ret = zsp_handle_heartbeat(param);
		break;

	case ZSP_CMD_PAUSE:
		ret = zsp_handle_pause(param, 1);
		break;

	case ZSP_CMD_RESUME:
		ret = zsp_handle_pause(param, 0);
		break;

	case ZSP_CMD_SETSPEED:
		ret = zsp_handle_setspeed(param);
		break;

	default:
		param->cmd_rep = ZSP_REP_NOTFOUND;
		break;
	}

	return ret;
}

int zsp_handle(zsp_session_t *session)
{
	if (session == NULL)
		return SSS_ERROR;

	int head_len = sizeof(zsp_head_t);
	char *head_buf = NULL;
	char *body_buf = NULL;
	int body_len = 0;
	int len_recv = 0;

	zsp_head_t *head_rep = NULL;
	handle_cmd_param_t *param = NULL;

	int ret = SSS_ERROR;
	int needReply = 0;
	do
	{
		if (zsp_head_new(&head_rep) != SSS_OK || head_rep == NULL)
			break;

		if (zsp_session_recv(session, head_len, &head_buf, &len_recv) != SSS_OK)
			break;

		if (head_buf == NULL || len_recv != head_len)
			break;

		zsp_head_t *head = (zsp_head_t*)head_buf;
		if (zsp_head_check(head) != SSS_TRUE)
			break;

		head_rep->session = session->id;
		head_rep->seq = head->seq;
		head_rep->cmd = ZSP_REP_ERROR;
		head_rep->csize = 0;
		needReply = 1;

		if (head->cmd != ZSP_CMD_HELLO && head->session != session->id)
			break;

		len_recv = 0;
		body_len = head->csize;
		if (body_len > 0)
		{
			if (zsp_session_recv(session, body_len, &body_buf, &len_recv) != SSS_OK)
				break;

			if (body_buf == NULL || len_recv != body_len)
				break;
		}

		param = malloc(sizeof(handle_cmd_param_t));
		if (param == NULL)
			break;

		param->session = session;
		param->cmd = head->cmd;
		param->cmd_rep = ZSP_REP_ERROR;
		param->body = body_buf;
		param->body_len = body_len;
		param->response = NULL;
		param->response_len = 0;

		ret = zsp_handle_cmd(param);

		head_rep->cmd = param->cmd_rep;
		head_rep->csize = param->response_len;

	} while (0);

	if (needReply && head_rep != NULL)
	{
		head_rep->chksum = zsp_head_get_chksum(head_rep);

		int len_sent = 0;
		zsp_session_send(session, (char*)head_rep, head_len, &len_sent);

		if (param != NULL && param->response != NULL && param->response_len != 0)
			zsp_session_send(session, param->response, param->response_len, &len_sent);
	}

	SAFE_FREE(head_rep);
	SAFE_FREE(head_buf);
	SAFE_FREE(body_buf);
	if (param) SAFE_FREE(param->response);
	SAFE_FREE(param);

	if (ret == SSS_ERROR)
		session->isToEnd = 1;

	return ret;
}
