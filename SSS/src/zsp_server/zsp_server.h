/* zsp_server '(zhangpengpeng 20140630)
 * include listener session_mgr/sessions transport
 */

#ifndef _ZSP_SERVER_H_
#define _ZSP_SERVER_H_

#include "../common/comtypes.h"
#include "zsp_session_mgr.h"
#include "zsp_listener.h"

typedef struct _st_zsp_server
{
	int id;
	int is_runing;

	zsp_session_mgr_t *session_mgr;
	zsp_listener_t *listener;

} zsp_server_t;

int _zsp_server_check_valid(zsp_server_t *server);

int zsp_server_new_session(zsp_server_t *server, zsp_session_param_t *param);

#endif // _ZSP_SERVER_H_
