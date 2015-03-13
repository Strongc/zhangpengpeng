/* zsp_transport '(zhangpengpeng 20140630) 
 * create trans_session
 * open file
 * create transport_thread
 * read data
 * send packet
 */

#ifndef _ZSP_TRANSPORT_H_
#define _ZSP_TRANSPORT_H_

#include "../common/comtypes.h"
#include "../sys_layer/sys_net.h"
#include "../sys_layer/sys_thread.h"

typedef struct _st_zsp_transport
{
	int is_sending;
	int is_paused;
	int cur_speed;

	SOCKET sock;
	thread_t *thread;

	void *file_handle;
	void *buf;
	int buf_len;

} zsp_transport_t;

typedef struct _st_zsp_transport_start_return
{
	long file_size;
} zsp_transport_start_return;

int zsp_transport_new(zsp_transport_t **ptransport, SOCKET sock);
int zsp_transport_delete(zsp_transport_t *transport);

int zsp_transport_start(zsp_transport_t *transport, const char *filename, zsp_transport_start_return *ret);
int zsp_transport_stop(zsp_transport_t *transport);
int zsp_transport_heartbeat(zsp_transport_t *transport);
int zsp_transport_pause(zsp_transport_t *transport, int is_pause);
int zsp_transport_setspeed(zsp_transport_t *transport, int speed);

#endif // _ZSP_TRANSPORT_H_
