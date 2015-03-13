/* zsp_session '(zhangpengpeng 20141228) 
 * create session_thread
 * recv msg
 * proc msg
 * proc_msg_XXX
 * send response
 * create tranport
 */

#include "../common/comtypes.h"
#include "zsp_session.h"
#include "../zsp_protocol/zsp_handle.h"

int zsp_session_new(zsp_session_t **psession)
{
	if (psession == NULL)
		return SSS_ERROR;

	zsp_session_t *new_session = (zsp_session_t*)malloc(sizeof(zsp_session_t));
	if (new_session == NULL)
		return SSS_ERROR;
	memset(new_session, 0, sizeof(zsp_session_t));
	static int s_id = 0;
	new_session->id = s_id++;
	new_session->transport = NULL;
	new_session->isToEnd = 0;

	*psession = new_session;
	return SSS_OK;
}

int zsp_session_delete(zsp_session_t *session)
{
	if (session == NULL)
		return SSS_ERROR;

	if (session->sock != NULL || session->thread != NULL)
	{
		zsp_session_stop(session);
	}

	free(session);
	session = NULL;
	return SSS_OK;
}

int _zsp_session_thread(void *param)
{
	zsp_session_t *session = (zsp_session_t*)param;
	if (session == NULL)
		return SSS_ERROR;

	return zsp_handle(session);
}

int zsp_session_start(zsp_session_t *session)
{
	if (session == NULL)
		return SSS_ERROR;

	int is_ok = SSS_ERROR;
	do
	{
		if (thread_new(&session->thread) == SSS_ERROR)
			break;

		thread_set_interval_time(session->thread, 0);
		session->isToEnd = 0;
		if (thread_start(session->thread, _zsp_session_thread, session) == SSS_ERROR)
			break;

		is_ok = SSS_OK;
	} while (0);

	if (is_ok == SSS_ERROR)
	{
		zsp_session_stop(session);
	}

	return is_ok;
}

int zsp_session_stop(zsp_session_t *session)
{
	if (session == NULL)
		return SSS_ERROR;

	if (session->transport != NULL)
	{
		zsp_transport_stop(session->transport);
		zsp_transport_delete(session->transport);
		session->transport = NULL;
	}

	if (session->sock != NULL)
	{
		socket_delete(session->sock);
		session->sock = NULL;
	}
	if (session->thread != NULL)
	{
		thread_stop(session->thread);
		thread_delete(session->thread);
		session->thread = NULL;
	}

	return SSS_OK;
}

int zsp_session_send(zsp_session_t *session, const char *buf, int len, int *len_sent)
{
	if (session == NULL)
		return SSS_ERROR;

	if (session->sock == NULL)
		return SSS_ERROR;

	if (buf == NULL || len == 0)
		return SSS_ERROR;

	if (socket_send(session->sock, buf, len, len_sent) == SSS_ERROR)
		return SSS_ERROR;

	return SSS_OK;
}

int zsp_session_recv(zsp_session_t *session, int len, char **pbuf, int *len_recv)
{
	if (session == NULL)
		return SSS_ERROR;

	if (session->sock == NULL)
		return SSS_ERROR;

	if (len == 0 || pbuf == NULL)
		return SSS_ERROR;

	*pbuf = malloc(len);
	if (*pbuf == NULL)
		return SSS_ERROR;
	memset(*pbuf, 0, len);

	if (socket_recv(session->sock, *pbuf, len, len_recv) == SSS_ERROR)
		return SSS_ERROR;

	return SSS_OK;
}
