/* zsp_session_manager '(zhangpengpeng 20141228) 
 * add and manage sessions
 */

#include "../common/comtypes.h"
#include "zsp_session_mgr.h"

int zsp_session_mgr_new(zsp_session_mgr_t **pmgr)
{
	if (pmgr == NULL)
		return SSS_ERROR;

	zsp_session_mgr_t *new_mgr = (zsp_session_mgr_t*)malloc(sizeof(zsp_session_mgr_t));
	if (new_mgr == NULL)
		return SSS_ERROR;
	memset(new_mgr, 0, sizeof(zsp_session_mgr_t));

	*pmgr = new_mgr;
	return SSS_OK;
}

int zsp_session_mgr_delete(zsp_session_mgr_t *mgr)
{
	if (mgr == NULL)
		return SSS_ERROR;

	zsp_session_mgr_clear(mgr);
	if (mgr->thread != NULL)
	{
		zsp_session_mgr_stop(mgr);
	}

	free(mgr);
	mgr = NULL;
	return SSS_OK;
}

int _zsp_session_mgr_thread(void *param)
{
	zsp_session_mgr_t *mgr = (zsp_session_mgr_t *)param;
	if (mgr == NULL)
		return SSS_ERROR;

	if (mgr->session_list == NULL)
		return SSS_OK;

	zsp_session_mgr_check(mgr);

	return SSS_OK;
}

int zsp_session_mgr_start(zsp_session_mgr_t *mgr)
{
	if (mgr == NULL)
		return SSS_ERROR;

	int is_ok = SSS_ERROR;
	do
	{
		if (thread_new(&mgr->thread) == SSS_ERROR)
			break;

		thread_set_interval_time(mgr->thread, 100);
		if (thread_start(mgr->thread, _zsp_session_mgr_thread, mgr) == SSS_ERROR)
			break;

		is_ok = SSS_OK;
	} while (0);

	if (is_ok == SSS_ERROR)
	{
		zsp_session_mgr_stop(mgr);
	}

	return is_ok;
}

int zsp_session_mgr_stop(zsp_session_mgr_t *mgr)
{
	if (mgr == NULL)
		return SSS_ERROR;

	if (mgr->thread != NULL)
	{
		thread_stop(mgr->thread);
		thread_delete(mgr->thread);
		mgr->thread = NULL;
	}
	zsp_session_mgr_clear(mgr);

	return SSS_OK;
}

int zsp_session_mgr_new_session(zsp_session_mgr_t *mgr, zsp_session_param_t *param)
{
	if (mgr == NULL || param == NULL)
		return SSS_ERROR;

	zsp_session_t *session = NULL;
	if (zsp_session_new(&session) == SSS_ERROR)
		return SSS_ERROR;

	session->sock = param->rsock;
	session->next = NULL;

	if (zsp_session_start(session) == SSS_ERROR)
		return SSS_ERROR;

	if (mgr->session_list == NULL)
	{
		mgr->session_list = session;
	}
	else
	{
		zsp_session_t *tail = mgr->session_list;
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = session;
	}

	return SSS_OK;
}

int zsp_session_mgr_remove(zsp_session_mgr_t *mgr, int id)
{
	if (mgr == NULL || id < 0)
		return SSS_ERROR;

	if (mgr->session_list == NULL)
		return SSS_ERROR;

	if (mgr->session_list->id == id)
	{
		zsp_session_t *session_delete = mgr->session_list;
		mgr->session_list = mgr->session_list->next;

		zsp_session_stop(session_delete);
		zsp_session_delete(session_delete);
		session_delete = NULL;
		return SSS_OK;
	}

	zsp_session_t *s = mgr->session_list;
	while (s->next != NULL)
	{
		if (s->next->id == id)
		{
			zsp_session_t *session_delete = s->next;
			s->next = s->next->next;

			zsp_session_stop(session_delete);
			zsp_session_delete(session_delete);
			session_delete = NULL;
			return SSS_OK;
		}
		else
		{
			s = s->next;
		}
	}

	return SSS_OK;
}

int zsp_session_mgr_clear(zsp_session_mgr_t *mgr)
{
	if (mgr == NULL)
		return SSS_ERROR;

	while (mgr->session_list != NULL)
	{
		zsp_session_t *temp = mgr->session_list;
		mgr->session_list = mgr->session_list->next;
		
		zsp_session_stop(temp);
		zsp_session_delete(temp);
		temp = NULL;
	}

	return SSS_OK;
}

int zsp_session_mgr_check(zsp_session_mgr_t *mgr)
{
	if (mgr == NULL)
		return SSS_ERROR;

	if (mgr->session_list == NULL)
		return SSS_OK;

	if (mgr->session_list->isToEnd)
	{
		zsp_session_t *session_delete = mgr->session_list;
		mgr->session_list = mgr->session_list->next;

		zsp_session_stop(session_delete);
		zsp_session_delete(session_delete);
		session_delete = NULL;
		return SSS_OK;
	}

	zsp_session_t *s = mgr->session_list;
	while (s->next != NULL)
	{
		if (s->next->isToEnd)
		{
			zsp_session_t *session_delete = s->next;
			s->next = s->next->next;

			zsp_session_stop(session_delete);
			zsp_session_delete(session_delete);
			session_delete = NULL;
			return SSS_OK;
		}
		else
		{
			s = s->next;
		}
	}

	return SSS_OK;
}
