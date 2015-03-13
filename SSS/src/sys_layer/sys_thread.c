/* sys_thread '(zhangpengpeng 20141228) 
 * create thread
 */

#include "../common/comtypes.h"
#include "sys_thread.h"

int thread_new(thread_t **pthread)
{
	if (pthread == NULL)
		return SSS_ERROR;

	thread_t *new_thread = malloc(sizeof(thread_t));
	if (new_thread == NULL)
		return SSS_ERROR;

	memset(new_thread, 0, sizeof(thread_t));
	*pthread = new_thread;
	return SSS_OK;
}

int thread_delete(thread_t *thread)
{
	if (thread == NULL)
		return SSS_ERROR;

	free(thread);
	thread = NULL;
	return SSS_OK;
}

#ifdef _WIN32
DWORD WINAPI _sys_thread_t_fun_(LPVOID param)
#endif
{
	thread_t *thread = (thread_t*)param;
	if (thread == NULL || thread->fun == NULL)
		return 0;

	do
	{
		if (thread->fun(thread->param) == SSS_ERROR)
			break;
#ifdef _WIN32
	} while (WaitForSingleObject(thread->exit_event, thread->interval_time) == WAIT_TIMEOUT);
#endif

	return 0;
}

int thread_start(thread_t *thread, thread_fun_t fun, void *param)
{
	if (thread == NULL || fun == NULL)
		return SSS_ERROR;

	thread->fun = fun;
	thread->param = param;

#ifdef _WIN32
	thread->exit_event = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (thread->exit_event == NULL)
		return SSS_ERROR;

	thread->thread_handle = CreateThread(NULL, 0, _sys_thread_t_fun_, thread, 0, NULL);
	if (thread == NULL)
	{
		CloseHandle(thread->exit_event);
		thread->exit_event = NULL;
		return SSS_ERROR;
	}
#endif // _WIN32

	return SSS_OK;
}


int thread_stop(thread_t *thread)
{
	if (thread == NULL)
		return SSS_ERROR;

#ifdef _WIN32
	if (thread->thread_handle != NULL)
	{
		SetEvent(thread->exit_event);
		WaitForSingleObject(thread->thread_handle, INFINITE);
		thread->thread_handle = NULL;
	}
	if (thread->exit_event != NULL)
	{
		CloseHandle(thread->exit_event);
		thread->exit_event = NULL;
	}
#endif // _WIN32

	return SSS_OK;
}

int thread_set_interval_time(thread_t *thread, int interval_time)
{
	if (thread == NULL || interval_time < 0)
		return SSS_ERROR;

	thread->interval_time = interval_time;
	return SSS_OK;
}
