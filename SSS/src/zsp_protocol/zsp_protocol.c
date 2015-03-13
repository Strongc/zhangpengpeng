/* zsp_protocol '(zhangpengpeng 20150101) 
 * structs and definitions of Z Stream Protocol
 */

#include "zsp_protocol.h"
#include "string.h"
#include "stdlib.h"

int zsp_head_new(zsp_head_t **phead)
{
	if (phead == NULL)
		return SSS_ERROR;

	zsp_head_t *new_head = malloc(sizeof(zsp_head_t));
	if (new_head == NULL)
		return SSS_ERROR;

	memset(new_head, 0, sizeof(zsp_head_t));
	strncpy(new_head->magic, ZSP_MAGIC, 4);
	new_head->hsize = sizeof(zsp_head_t);

	*phead = new_head;
	return SSS_OK;
}

int zsp_head_delete(zsp_head_t *head)
{
	if (head == NULL)
		return SSS_ERROR;

	free(head);
	head = NULL;
	return SSS_OK;
}

int zsp_head_get_chksum(zsp_head_t *head)
{
	if (head == NULL)
		return 0;

	char *p = (char*)&(head->session);
	int i = 0;
	int count = sizeof(zsp_head_t) - ((char*)&head->session - (char*)head->magic);
	int sum = 0;
	for (i = 0; i < count; i++)
	{
		int v = *(p + i);
		sum += v;
	}

	return sum;
}

int zsp_head_check(zsp_head_t *head)
{
	if (head == NULL)
		return SSS_FALSE;

	if (strncmp(head->magic, ZSP_MAGIC, 4) != 0)
		return SSS_FALSE;

	if (head->hsize != sizeof(zsp_head_t))
		return SSS_FALSE;

	if (head->chksum != zsp_head_get_chksum(head))
		return SSS_FALSE;

	return SSS_TRUE;
}
