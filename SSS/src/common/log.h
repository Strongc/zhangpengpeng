/* running log '(zhangpengpeng 2015/02/08) */

#ifndef _LOG_H_
#define _LOG_H_


#ifdef __GNUC__
#define LOG_CHECK_FMT(a, b) __attribute__((format(printf, a, b)))
#else
#define LOG_CHECK_FMT(a, b)
#endif

#ifdef _WIN32
	#define LOG(lvl, fmt, ...)			_AddLog(lvl, __FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)
	#define LOG_DEBUG(fmt, ...)			_AddLog(DEBUG_LVL, __FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)
	#define LOG_INFO(fmt, ...)			_AddLog(INFO_LVL, __FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)
	#define LOG_WARN(fmt, ...)			_AddLog(WARN_LVL, __FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)
	#define LOG_ERROR(fmt, ...)         _AddLog(ERROR_LVL, __FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)
#else
    #define LOG(lvl, fmt, args...)		_AddLog(lvl, __FILE__, __LINE__, __FUNCTION__, fmt, ##args)
    #define LOG_DEBUG(fmt, args...)		_AddLog(DEBUG_LVL, __FILE__, __LINE__, __FUNCTION__, fmt, ##args)
    #define LOG_INFO(fmt, args...)		_AddLog(INFO_LVL, __FILE__, __LINE__, __FUNCTION__, fmt, ##args)
    #define LOG_WARN(fmt, args...)		_AddLog(WARN_LVL, __FILE__, __LINE__, __FUNCTION__, fmt, ##args)
    #define LOG_ERROR(fmt, args...)		_AddLog(ERROR_LVL, __FILE__, __LINE__, __FUNCTION__, fmt, ##args)
#endif


typedef enum _em_LOG_LEVEL {
	DEBUG_LVL,
	INFO_LVL,
	WARN_LVL,
	ERROR_LVL
}LOG_LEVEL;

extern int _AddLog(LOG_LEVEL lvl, 
	const char *file_name, const unsigned int line_num, const char *func_name, 
	const char *format, ...) LOG_CHECK_FMT(5, 6);

#endif // _LOG_H_
