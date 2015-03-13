/* common functions '(zhangpengpeng 20141228) */

#include "comtypes.h"
#include <string.h>
#include <stdlib.h>

int new_copy_str(char **pdst, const char *src, int *dst_len_out)
{
	if (pdst == NULL || src == NULL)
		return SSS_ERROR;

	int src_len = strlen(src);
	if (src_len == 0)
		return SSS_ERROR;

	*pdst = (char*)malloc(src_len + 1);
	if (*pdst == NULL)
		return SSS_ERROR;

	memset(*pdst, 0, src_len + 1);
	strncpy(*pdst, src, src_len);

	if (dst_len_out != NULL)
		*dst_len_out = src_len + 1;

	return SSS_OK;
}
