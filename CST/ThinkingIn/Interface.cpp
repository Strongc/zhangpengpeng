/* At the interface of a libray or other encapsulation,
 * pass param via struct or xml msg.
 */
Interface_Function(struct _st_PARAM *param);
Interface_Function(const char *xml_param);
/* xml参数甚至可以改成lisp格式 */

DoOper(const char *oper_name, const char *xmlParam);
DoOper(const char *xml_oper_param);
/* 接口统一成一个，参数一个为操作名，另一个为xml格式的原参数，
 甚至这两个参数可以合并成一个XML 报文 */

/* 写日志的基本类改成将内容回调，由上层处理，写文件还是打印。 */

// add/set extra info 
AddSetExtraParam(const char *key, const char *value);
AddSetExtraParam(const char *xml);
/* key 可以用:连接多个字段，来表示域或者父子字段的意思 */

// 用ProtoBuf来传递消息报文

