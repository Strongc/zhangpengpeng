/* zsp_listener '(zhangpengpeng 20140630) 
 * create socket
 * bind
 * listen
 * create accept_thread
 * accept
 * new session
 */

#ifndef _ZSP_LISTENER_H_
#define _ZSP_LISTENER_H_

#include "../sys_layer/sys_net.h"
#include "../sys_layer/sys_thread.h"

typedef struct _st_zsp_listener
{
	void *server;

	SOCKET sock;
	thread_t *thread;

	int port;
} zsp_listener_t;

int zsp_listener_new(zsp_listener_t **plistener, void *server);
int zsp_listener_delete(zsp_listener_t *listener);

int zsp_listener_start(zsp_listener_t *listener, int port);
int zsp_listener_stop(zsp_listener_t *listener);

#endif // _ZSP_LISTENER_H_
