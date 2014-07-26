/* ZErrorMgt '(zhangpengpeng 2014/04/28)
 * my tool to manage error infomation
 */

#ifndef _ERRORMGT_H_
#define _ERRORMGT_H_

#define ERROR_SET		err_mgt.set
#define ERROR_RESET		err_mgt.reset

#include <string>
#include <map>
#include <Windows.h>

class ZErrorMgt
{
	typedef struct _st_ErrorInfo {
		int error_id;
		std::string more_info;
	}ErrorInfo;

	typedef unsigned long ThreadID;

private:
	std::map<ThreadID, ErrorInfo> mapError;
	CRITICAL_SECTION cs;

	ThreadID getCurrentThreadID();

public:
	ZErrorMgt();
	~ZErrorMgt();

	void set(int error, const char *more_info = "");
	void reset();

	int getLastError();
	const char* getMoreInfo();
};

extern ZErrorMgt err_mgt;

#endif 	// _ERRORMGT_H_
