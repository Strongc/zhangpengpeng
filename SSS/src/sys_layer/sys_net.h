/* sys_net '(zhangpengpeng 20141228) 
 * to use network
 */

#ifndef _SYS_NET_H_
#define _SYS_NET_H_

#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#endif

typedef enum _em_SOCKET_TYPE
{
	SOCKET_TCP_TYPE,
	SOCKET_UDP_TYPE
} SOCKET_TYPE;

int socket_init();
int socket_fini();

int socket_new(SOCKET *sock, SOCKET_TYPE type);
int socket_delete(SOCKET sock);

int socket_bind(SOCKET sock, int port);
int socket_listen(SOCKET sock);
int socket_accept(SOCKET sock, SOCKET *rsock);

int socket_connect(SOCKET sock, const char *ip, int port);

int socket_send(SOCKET sock, const char *buf, int len, int *outlen);
int socket_recv(SOCKET sock, char *buf, int len, int *outlen);

int socket_send_timeo(SOCKET sock, const char *buf, int len, int *outlen, int msec);
int socket_recv_timeo(SOCKET sock, char *buf, int len, int *outlen, int msec);

int socket_sendn(SOCKET sock, const char *buf, int len, int *outlen, int msec);
int socket_recvn(SOCKET sock, char *buf, int len, int *outlen, int msec);

int socket_shutdown(SOCKET sock);

#endif // _SYS_NET_H_
