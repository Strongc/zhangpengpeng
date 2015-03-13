/* zsp_server '(zhangpengpeng 20140630)
 */

#ifndef _ZSP_SERVER_INTERFACE_H_
#define _ZSP_SERVER_INTERFACE_H_

#include "../common/comtypes.h"

int zsp_server_init();
int zsp_server_fini();

int zsp_server_new(SSS_Handle *handle);
int zsp_server_delete(SSS_Handle handle);

int zsp_server_start(SSS_Handle handle);
int zsp_server_stop(SSS_Handle handle);

#endif // _ZSP_SERVER_INTERFACE_H_
