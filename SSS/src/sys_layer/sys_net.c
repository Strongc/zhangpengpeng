/* sys_net '(zhangpengpeng 20141228) 
 * to use network
 */

#include "../common/comtypes.h"
#include "sys_net.h"

#ifdef _WIN32
#pragma comment(lib, "ws2_32.lib")
#endif 

#define SOCKET_TIMEOUT		5000

int socket_init()
{
#ifdef _WIN32
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSADATA wsaData;
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
		return SSS_ERROR;

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return SSS_ERROR;
	}

	return SSS_OK;
#endif
}

int socket_fini()
{
#ifdef _WIN32
	WSACleanup();
#endif
	return SSS_OK;
}

int socket_new(SOCKET *sock, SOCKET_TYPE type)
{
	if (sock == NULL)
		return SSS_ERROR;

	if (type == SOCKET_TCP_TYPE)
		*sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	else if (type == SOCKET_UDP_TYPE)
		*sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	else
		return SSS_ERROR;

#ifdef _WIN32
	if (*sock == INVALID_SOCKET)
	{
		*sock = NULL;			// set to NULL if failed
		return SSS_ERROR;
	}
#endif 

	return SSS_OK;
}

int socket_delete(SOCKET sock)
{
	if (sock == NULL)
		return SSS_ERROR;

	closesocket(sock);
	return SSS_OK;
}

int socket_bind(SOCKET sock, int port)
{
	if (sock == NULL)
		return SSS_ERROR;

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	int ret = bind(sock, (SOCKADDR*)&addr, sizeof(SOCKADDR));
#ifdef _WIN32
	if (ret != 0)
#endif 
		return SSS_ERROR;
	
	return SSS_OK;
}

int socket_listen(SOCKET sock)
{
	if (sock == NULL)
		return SSS_ERROR;

	int ret = listen(sock, 32);
#ifdef _WIN32
	if (ret != 0)
#endif 
		return SSS_ERROR;
	return SSS_OK;
}

int socket_accept(SOCKET sock, SOCKET *rsock)
{
	if (sock == NULL)
		return SSS_ERROR;

	SOCKADDR_IN remote_addr;
	int len = sizeof(SOCKADDR);
	SOCKET remote_sock = accept(sock, (SOCKADDR*)&remote_addr, &len);
#ifdef _WIN32
	if (remote_sock == INVALID_SOCKET)
#endif 
		return SSS_ERROR;

	int set_ret = 0;
	do
	{
		int send_size = 512 * 1024;
		set_ret = setsockopt(remote_sock, SOL_SOCKET, SO_SNDBUF, (char*)&send_size, sizeof(int));
		if (set_ret == SOCKET_ERROR)
			break;

		int recv_size = 512 * 1024;
		set_ret = setsockopt(remote_sock, SOL_SOCKET, SO_RCVBUF, (char*)&recv_size, sizeof(int));
		if (set_ret == SOCKET_ERROR)
			break;

		int send_timeout = 5000;
		set_ret = setsockopt(remote_sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&send_timeout, sizeof(int));
		if (set_ret == SOCKET_ERROR)
			break;

		int recv_timeout = 5000;
		set_ret = setsockopt(remote_sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&recv_timeout, sizeof(int));
		if (set_ret == SOCKET_ERROR)
			break;

		int no_delay = 1;
		set_ret = setsockopt(remote_sock, IPPROTO_TCP, TCP_NODELAY, (char*)&no_delay, sizeof(int));
		if (set_ret == SOCKET_ERROR)
			break;

		struct linger lgr;
		lgr.l_onoff = 1;
		lgr.l_linger = 5;
		set_ret = setsockopt(remote_sock, SOL_SOCKET, SO_LINGER, (char*)&lgr, sizeof(struct linger));
		if (set_ret == SOCKET_ERROR)
			break;

	} while (0);

	if (set_ret == SOCKET_ERROR)
	{
		closesocket(remote_sock);
		return SSS_ERROR;
	}

	if (rsock != NULL)
		*rsock = remote_sock;

	return SSS_OK;
}

int socket_connect(SOCKET sock, const char *ip, int port)
{
	if (sock == NULL)
		return SSS_ERROR;

	if (ip == NULL || strlen(ip) == 0 || port == 0)
		return SSS_ERROR;

	unsigned long flag = 1;
	if (ioctlsocket(sock, FIONBIO, &flag) == SOCKET_ERROR)
		return SSS_ERROR;

	int is_connected = 0;
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);
	int ret = connect(sock, (SOCKADDR*)&addr, sizeof(SOCKADDR));
	if (ret == 0)
	{
		is_connected = 1;
	}
	else
	{
		fd_set fdset;
		FD_ZERO(&fdset);
		FD_SET(sock, &fdset);

		struct timeval timeout;
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		if (select(sock + 1, &fdset, &fdset, NULL, &timeout) > 0)
			is_connected = 1;
	}

	flag = 0;
	if (ioctlsocket(sock, FIONBIO, &flag) == SOCKET_ERROR)
		return SSS_ERROR;

	if (is_connected == 0)
		return SSS_ERROR;

	{
		int send_size = 512 * 1024;
		int set_ret = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&send_size, sizeof(int));
		if (set_ret == SOCKET_ERROR)
			return SSS_ERROR;

		int recv_size = 512 * 1024;
		set_ret = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&recv_size, sizeof(int));
		if (set_ret == SOCKET_ERROR)
			return SSS_ERROR;

		int send_timeout = 5000;
		set_ret = setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&send_timeout, sizeof(int));
		if (set_ret == SOCKET_ERROR)
			return SSS_ERROR;

		int recv_timeout = 5000;
		set_ret = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&recv_timeout, sizeof(int));
		if (set_ret == SOCKET_ERROR)
			return SSS_ERROR;

		int no_delay = 1;
		set_ret = setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&no_delay, sizeof(int));
		if (set_ret == SOCKET_ERROR)
			return SSS_ERROR;
	}

	return SSS_OK;
}

int socket_send(SOCKET sock, const char *buf, int len, int *outlen)
{
	if (sock == NULL || buf == NULL || len == 0)
		return SSS_ERROR;

	int len_sent = send(sock, buf, len, 0);
	if (len_sent == SOCKET_ERROR)
		return SSS_ERROR;

	if (outlen != NULL)
		*outlen = len_sent;

	return SSS_OK;
}

int socket_recv(SOCKET sock, char *buf, int len, int *outlen)
{
	if (sock == NULL || buf == NULL || len == 0)
		return SSS_ERROR;

	int len_recv = recv(sock, buf, len, 0);
	if (len_recv == SOCKET_ERROR)
		return SSS_ERROR;

	if (outlen != NULL)
		*outlen = len_recv;

	return SSS_OK;
}

int socket_send_timeo(SOCKET sock, const char *buf, int len, int *outlen, int msec)
{
	if (sock == NULL || buf == NULL || len == 0)
		return SSS_ERROR;

	fd_set fdset;
	FD_ZERO(&fdset);
	FD_SET(sock, &fdset);

	struct timeval timeout;
	timeout.tv_sec = msec / 1000;
	timeout.tv_usec = msec % 1000;

	if (select(sock + 1, NULL, &fdset, NULL, &timeout) <= 0)
		return SSS_ERROR;

	return socket_send(sock, buf, len, outlen);
}

int socket_recv_timeo(SOCKET sock, char *buf, int len, int *outlen, int msec)
{
	if (sock == NULL || buf == NULL || len == 0)
		return SSS_ERROR;

	fd_set fdset;
	FD_ZERO(&fdset);
	FD_SET(sock, &fdset);

	struct timeval timeout;
	timeout.tv_sec = msec / 1000;
	timeout.tv_usec = msec % 1000;

	if (select(sock + 1, &fdset, NULL, NULL, &timeout) <= 0)
		return SSS_ERROR;

	return socket_recv(sock, buf, len, outlen);
}

int socket_sendn(SOCKET sock, const char *buf, int len, int *outlen, int msec)
{
	if (sock == NULL || buf == NULL || len == 0)
		return SSS_ERROR;

	int all_sent_len = 0;
	int timeout_count = 0;
	while (all_sent_len < len && timeout_count < 3)
	{
		int once_sent_len = 0;
		if (socket_send_timeo(sock, buf + all_sent_len, len - all_sent_len, &once_sent_len, msec) == SSS_ERROR
			|| once_sent_len == 0)
			timeout_count++;

		all_sent_len += once_sent_len;
	}

	if (outlen != NULL)
		*outlen = all_sent_len;

	if (all_sent_len != len)
		return SSS_ERROR;

	return SSS_OK;
}

int socket_recvn(SOCKET sock, char *buf, int len, int *outlen, int msec)
{
	if (sock == NULL || buf == NULL || len == 0)
		return SSS_ERROR;

	int all_recv_len = 0;
	int timeout_count = 0;
	while (all_recv_len < len && timeout_count < 3)
	{
		int once_recv_len = 0;
		if (socket_recv_timeo(sock, buf + all_recv_len, len - all_recv_len, &once_recv_len, msec) == SSS_ERROR
			|| once_recv_len == 0)
			timeout_count++;

		all_recv_len += once_recv_len;
	}

	if (outlen != NULL)
		*outlen = all_recv_len;

	if (all_recv_len != len)
		return SSS_ERROR;

	return SSS_OK;
}

int socket_shutdown(SOCKET sock)
{
	if (sock == NULL)
		return SSS_ERROR;

	int ret = shutdown(sock, SD_BOTH);
	if (ret == SOCKET_ERROR)
		return SSS_ERROR;
	return SSS_OK;
}
