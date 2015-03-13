/* zsp_transport '(zhangpengpeng 20141228) 
 * create trans_session
 * open file
 * create transport_thread
 * read data
 * send packet
 */

#include "zsp_transport.h"
#include "stdio.h"

int zsp_transport_new(zsp_transport_t **ptransport, SOCKET sock)
{
	if (ptransport == NULL)
		return SSS_ERROR;

	zsp_transport_t *new_transport = (zsp_transport_t*)malloc(sizeof(zsp_transport_t));
	if (new_transport == NULL)
		return SSS_ERROR;
	memset(new_transport, 0, sizeof(zsp_transport_t));
	new_transport->sock = sock;
	
	if (thread_new(&new_transport->thread) == SSS_ERROR)
	{
		free(new_transport);
		new_transport = NULL;
		return SSS_ERROR;
	}

	*ptransport = new_transport;
	return SSS_OK;
}

int zsp_transport_delete(zsp_transport_t *transport)
{
	if (transport == NULL)
		return SSS_ERROR;

	if (transport->thread != NULL)
	{
		thread_delete(transport->thread);
		transport->thread = NULL;
	}
	
	free(transport);
	transport = NULL;
	return SSS_OK;
}

int _zsp_transport_thread(void *param)
{
	zsp_transport_t *transport = (zsp_transport_t*)param;
	if (transport == NULL)
		return SSS_ERROR;

	FILE *file = (FILE*)transport->file_handle;
	if (file == NULL)
		return SSS_ERROR;

	char *buf = transport->buf;
	int buf_len = transport->buf_len;
	memset(buf, 0, buf_len);

	int ret = SSS_OK;
	size_t read_size = fread(buf, 1, buf_len, file);
	if (read_size == 0)
	{
		if (feof(file))
		{
			//strncpy(buf, "FILEENDFILEENDFILEENDFILEEND", buf_len);
			//read_size = strlen(buf) + 1;
		}
		else
		{
			strncpy(buf, "READERRORREADERRORREADERRORREADERRORREADERROR", buf_len);
			read_size = strlen(buf) + 1;
		}
		ret = SSS_ERROR;
	}

	int outlen = 0;
	socket_send(transport->sock, buf, read_size, &outlen);

	return ret;
}

int zsp_transport_start(zsp_transport_t *transport, const char *filename, zsp_transport_start_return *ret)
{
	if (transport == NULL)
		return SSS_ERROR;

	if (transport->is_sending == SSS_TRUE)
		zsp_transport_stop(transport);

	if (filename == NULL || strlen(filename) == 0)
		return SSS_ERROR;

	FILE *file = fopen(filename, "rb");
	if (file == NULL)
		return SSS_ERROR;

	fseek(file, 0, SEEK_END);
	long file_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	if (ret != NULL)
		ret->file_size = file_size;

	transport->file_handle = file;
	transport->buf_len = 1024;
	transport->buf = malloc(transport->buf_len);
	if (transport->buf == NULL)
		return SSS_ERROR;

	thread_set_interval_time(transport->thread, 0);
	if (thread_start(transport->thread, _zsp_transport_thread, transport) == SSS_ERROR)
	{
		fclose((FILE*)transport->file_handle);
		transport->file_handle = NULL;
		return SSS_ERROR;
	}
	transport->is_sending = SSS_TRUE;

	return SSS_OK;
}

int zsp_transport_stop(zsp_transport_t *transport)
{
	if (transport == NULL)
		return SSS_ERROR;

	if (transport->is_sending != SSS_TRUE)
		return SSS_ERROR;

	if (transport->thread != NULL)
	{
		thread_stop(transport->thread);
		transport->thread = NULL;
	}

	if (transport->file_handle != NULL)
	{
		fclose((FILE*)transport->file_handle);
		transport->file_handle = NULL;
	}

	if (transport->buf != NULL)
	{
		free(transport->buf);
		transport->buf = NULL;
	}

	return SSS_OK;
}

int zsp_transport_heartbeat(zsp_transport_t *transport)
{
	return SSS_OK;
}

int zsp_transport_pause(zsp_transport_t *transport, int is_pause)
{
	return SSS_ERROR;
}

int zsp_transport_setspeed(zsp_transport_t *transport, int speed)
{
	return SSS_ERROR;
}
