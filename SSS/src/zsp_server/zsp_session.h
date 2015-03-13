/* zsp_session '(zhangpengpeng 20140630) 
 * create session_thread
 * recv msg
 * proc msg
 * proc_msg_XXX
 * send response
 * create tranport
 */

#ifndef _ZSP_SESSION_H_
#define _ZSP_SESSION_H_

#include "../sys_layer/sys_net.h"
#include "../sys_layer/sys_thread.h"
#include "../zsp_transport/zsp_transport.h"

typedef struct _st_zsp_session
{
	int id;
	zsp_transport_t *transport;

	SOCKET sock;
	thread_t *thread;
	int isToEnd;

	struct _st_zsp_session *next;
} zsp_session_t;

typedef struct _st_zsp_session_param
{
	SOCKET rsock;
} zsp_session_param_t;

int zsp_session_new(zsp_session_t **psession);
int zsp_session_delete(zsp_session_t *session);

int zsp_session_start(zsp_session_t *session);
int zsp_session_stop(zsp_session_t *session);

int zsp_session_send(zsp_session_t *session, const char *buf, int len, int *len_sent);
int zsp_session_recv(zsp_session_t *session, int len, char **pbuf, int *len_recv);

#endif // _ZSP_SESSION_H_
