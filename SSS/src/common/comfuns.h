/* common functions '(zhangpengpeng 20141228) */

#ifndef _COMFUNS_H_
#define _COMFUNS_H_

#define SAFE_FREE(p) do { if (p != NULL) { free(p); p = NULL; } } while (0)

int new_copy_str(char **pdst, const char *src, int *dst_len_out);

#endif // _COMFUNS_H_
