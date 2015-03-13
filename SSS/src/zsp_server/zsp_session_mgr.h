/* zsp_session_manager '(zhangpengpeng 20140630) 
 * add and manage sessions
 */

#ifndef _ZSP_SESSION_MGR_H_
#define _ZSP_SESSION_MGR_H_

#include "zsp_session.h"

typedef struct _st_zsp_session_mgr
{
	zsp_session_t *session_list;
	thread_t *thread;

} zsp_session_mgr_t;


int zsp_session_mgr_new(zsp_session_mgr_t **pmgr);
int zsp_session_mgr_delete(zsp_session_mgr_t *mgr);

int zsp_session_mgr_start(zsp_session_mgr_t *mgr);
int zsp_session_mgr_stop(zsp_session_mgr_t *mgr);

int zsp_session_mgr_new_session(zsp_session_mgr_t *mgr, zsp_session_param_t *param);

int zsp_session_mgr_remove(zsp_session_mgr_t *mgr, int id);
int zsp_session_mgr_clear(zsp_session_mgr_t *mgr);
int zsp_session_mgr_check(zsp_session_mgr_t *mgr);

#endif // _ZSP_SESSION_MGR_H_
