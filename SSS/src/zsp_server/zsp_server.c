/* zsp_server '(zhangpengpeng 20140630) 
 * include listener session_mgr/sessions transport
 */

#include "../common/comtypes.h"
#include "zsp_server_interface.h"
#include "zsp_server.h"
#include "../sys_layer/sys_net.h"
#include <stdlib.h>

int zsp_server_init()
{
	if (socket_init() == SSS_ERROR)
		return SSS_ERROR;

	return SSS_OK;
}

int zsp_server_fini()
{
	if (socket_fini() == SSS_ERROR)
		return SSS_ERROR;

	return SSS_OK;
}

int zsp_server_new(SSS_Handle *handle)
{
	if (handle == NULL)
		return SSS_ERROR;

	zsp_server_t *new_server = malloc(sizeof(zsp_server_t));
	if (new_server == NULL)
		return SSS_ERROR;
	memset(new_server, 0, sizeof(zsp_server_t));
	static int s_id = 0;
	new_server->id = s_id++;
	new_server->is_runing = 0;

	if (zsp_session_mgr_new(&new_server->session_mgr) == SSS_ERROR
		|| zsp_listener_new(&new_server->listener, new_server) == SSS_ERROR)
	{
		zsp_server_delete(new_server);
		return SSS_ERROR;
	}

	*handle = (SSS_Handle)new_server;
	return SSS_OK;
}

int zsp_server_delete(SSS_Handle handle)
{
	zsp_server_t *server = (zsp_server_t*)handle;
	if (server == NULL)
		return SSS_ERROR;

	server->id = -1;
	server->is_runing = 0;
	if (server->listener != NULL)
	{
		zsp_listener_delete(server->listener);
		server->listener = NULL;
	}
	if (server->session_mgr != NULL)
	{
		zsp_session_mgr_delete(server->session_mgr);
		server->session_mgr = NULL;
	}

	free(server);
	server = NULL;

	return SSS_OK;
}

int zsp_server_start(SSS_Handle handle)
{
	zsp_server_t *server = (zsp_server_t*)handle;
	if (_zsp_server_check_valid(server) != SSS_TRUE)
		return SSS_ERROR;

	if (zsp_listener_start(server->listener, 1120) == SSS_ERROR)
		return SSS_ERROR;

	if (zsp_session_mgr_start(server->session_mgr) == SSS_ERROR)
		return SSS_ERROR;

	server->is_runing = 1;
	return SSS_OK;
}

int zsp_server_stop(SSS_Handle handle)
{
	zsp_server_t *server = (zsp_server_t*)handle;
	if (_zsp_server_check_valid(server) != SSS_TRUE)
		return SSS_ERROR;

	server->is_runing = 0;
	zsp_listener_stop(server->listener);
	zsp_session_mgr_stop(server->session_mgr);

	return SSS_OK;
}

int _zsp_server_check_valid(zsp_server_t *server)
{
	if (server == NULL
		|| server->id < 0
		|| server->session_mgr == NULL
		|| server->listener == NULL
		)
		return SSS_FALSE;
	return SSS_TRUE;
}

int zsp_server_new_session(zsp_server_t *server, zsp_session_param_t *param)
{
	if (_zsp_server_check_valid(server) != SSS_TRUE)
		return SSS_ERROR;

	return zsp_session_mgr_new_session(server->session_mgr, param);
}
