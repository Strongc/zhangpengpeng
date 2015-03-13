/* sys_thread '(zhangpengpeng 20141228) 
 * create thread
 */

#ifndef _SYS_THREAD_H_
#define _SYS_THREAD_H_

#ifdef _WIN32
#include <Windows.h>
#endif

typedef int(*thread_fun_t)(void *param);

typedef struct _st_thread
{
#ifdef _WIN32
	HANDLE thread_handle;
	HANDLE exit_event;
#endif	// _WIN32

	thread_fun_t fun;
	void *param;
	int interval_time;
} thread_t;

int thread_new(thread_t **pthread);
int thread_delete(thread_t *thread);

int thread_set_interval_time(thread_t *thread, int interval_time);
int thread_start(thread_t *thread, thread_fun_t fun, void *param);
int thread_stop(thread_t *thread);

#endif // _SYS_THREAD_H_
