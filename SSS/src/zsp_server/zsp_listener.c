/* zsp_listener '(zhangpengpeng 20141228) 
 * create socket
 * bind
 * listen
 * create accept_thread
 * accept
 * new session
 */

#include "../common/comtypes.h"
#include "zsp_listener.h"
#include "zsp_server.h"

int zsp_listener_new(zsp_listener_t **plistener, void *server)
{
	if (plistener == NULL || server == NULL)
		return SSS_ERROR;

	zsp_listener_t *new_listener = malloc(sizeof(zsp_listener_t));
	if (new_listener == NULL)
		return SSS_ERROR;
	memset(new_listener, 0, sizeof(zsp_listener_t));
	new_listener->server = server;

	*plistener = new_listener;
	return SSS_OK;
}

int zsp_listener_delete(zsp_listener_t *listener)
{
	if (listener == NULL)
		return SSS_ERROR;

	if (listener->sock != NULL || listener->thread != NULL)
	{
		zsp_listener_stop(listener);
	}
	listener->server = NULL;
	listener->port = 0;

	free(listener);
	listener = NULL;
	return SSS_OK;
}

int _zsp_listener_thread(void *param)
{
	zsp_listener_t *listener = (zsp_listener_t*)param;
	if (listener == NULL)
		return SSS_ERROR;

	SOCKET rsock;
	if (socket_accept(listener->sock, &rsock) == SSS_ERROR)
		return SSS_OK;

	zsp_session_param_t session_param;
	memset(&session_param, 0, sizeof(zsp_session_param_t));
	session_param.rsock = rsock;
	zsp_server_new_session((zsp_server_t*)listener->server, &session_param);

	return SSS_OK;
}

int zsp_listener_start(zsp_listener_t *listener, int port)
{
	if (listener == NULL || port <= 0)
		return SSS_ERROR;

	int is_ok = SSS_ERROR;
	do
	{
		if (socket_new(&listener->sock, SOCKET_TCP_TYPE) == SSS_ERROR)
			break;

		if (thread_new(&listener->thread) == SSS_ERROR)
			break;

		listener->port = port;
		if (socket_bind(listener->sock, port) == SSS_ERROR)
			break;

		if (socket_listen(listener->sock) == SSS_ERROR)
			break;

		thread_set_interval_time(listener->thread, 0);
		if (thread_start(listener->thread, _zsp_listener_thread, listener) == SSS_ERROR)
			break;

		is_ok = SSS_OK;
	} while (0);

	if (is_ok == SSS_ERROR)
	{
		zsp_listener_stop(listener);
	}

	return is_ok;
}

int zsp_listener_stop(zsp_listener_t *listener)
{
	if (listener == NULL)
		return SSS_ERROR;

	if (listener->sock != NULL)
	{
		socket_shutdown(listener->sock);
		socket_delete(listener->sock);
		listener->sock = NULL;
	}
	if (listener->thread != NULL)
	{
		thread_stop(listener->thread);
		thread_delete(listener->thread);
		listener->thread = NULL;
	}
	listener->port = 0;

	return SSS_OK;
}
