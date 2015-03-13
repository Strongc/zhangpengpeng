/* zsp_protocol '(zhangpengpeng 20150101) 
 * structs and definitions of Z Stream Protocol
 */

#ifndef _ZSP_PROTOCOL_H_
#define _ZSP_PROTOCOL_H_

#include "../common/comtypes.h"

#define ZSP_MAGIC					"zsp"

typedef struct _st_zsp_head
{
	char			magic[4];		/* ZSP_MAGIC: "zsp" */
	unsigned int	hsize;			/* head_size */
	int				chksum;			/* checksum from session to the end*/
	int				session;		/* session id */
	unsigned int	seq;			/* sequence */
	unsigned int	cmd;			/* command */
	int				reserverd[3];
	unsigned int	csize;			/* content_size */
} zsp_head_t;

int zsp_head_new(zsp_head_t **phead);		/* new zsp_head_t, and auto-set magic, hsize; */
int zsp_head_delete(zsp_head_t *head);
int zsp_head_get_chksum(zsp_head_t *head);
int zsp_head_check(zsp_head_t *head);

/* begin of comands */ 
#define ZSP_CMD_UNKNOWN				0

#define ZSP_CMD_HELLO				10
#define ZSP_CMD_BYE					20
#define ZSP_CMD_PLAY				30
#define ZSP_CMD_STOP				40
#define ZSP_CMD_HEARTBEAT			50

#define ZSP_CMD_PAUSE				110
#define ZSP_CMD_RESUME				120
#define ZSP_CMD_SETSPEED			130

#define ZSP_REP_OK					1010
#define ZSP_REP_ERROR				1020
#define ZSP_REP_NOTFOUND			1030
#define ZSP_REP_NOTSUPPORT			1040

/* end of comands */ 

#endif // _ZSP_PROTOCOL_H_
