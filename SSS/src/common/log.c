/* running log '(zhangpengpeng 2015/02/08) */

#include "log.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "comtypes.h"

#define MAXLEN_EACH_LOG 1024

const char *_get_levlename(LOG_LEVEL lvl)
{
	switch (lvl)
	{
	case DEBUG_LVL:
		return "Debug";
		break;
	case INFO_LVL:
		return "Info";
		break;
	case WARN_LVL:
		return "Warn";
		break;
	case ERROR_LVL:
		return "Error";
		break;
	default:
		return "UnKnown";
		break;
	}
	return "";
}

const char *_get_short_filename(const char *file_name)
{
	char *pos = strrchr(file_name, '\\');
	if (pos == NULL)
		return file_name;
	else
		return pos + 1;
}

int _AddLog(LOG_LEVEL lvl, 
	const char *file_name, const unsigned int line_num, const char *func_name, 
	const char *format, ...) LOG_CHECK_FMT(5, 6)
{
	char *str_buf = malloc(MAXLEN_EACH_LOG);
	if (str_buf == NULL)
		return SSS_ERROR;
	memset(str_buf, 0, MAXLEN_EACH_LOG);

	const char *time_format = "%Y-%m-%d %H:%M:%S";
	time_t t_now = time(NULL);
	struct tm tm_now;
	if (0 != localtime_s(&tm_now, &t_now))
		return SSS_ERROR;        
	if (0 == strftime(str_buf, (size_t)25, time_format, &tm_now))
		return SSS_ERROR;

	sprintf(str_buf + strlen(str_buf), \
		" [%s](%s, %s %d): ", \
		_get_levlename(lvl), func_name, _get_short_filename(file_name), line_num);

    va_list args;
    va_start(args, format);
    _vsnprintf_s(str_buf + strlen(str_buf), MAXLEN_EACH_LOG - strlen(str_buf), _TRUNCATE, format, args);
    va_end(args);

    str_buf[MAXLEN_EACH_LOG - 1] = '\0';

	printf(str_buf);
	printf("\n");
	/* new a thread to display or write file; */

	return SSS_OK;
}
