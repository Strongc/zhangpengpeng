/* '(zhangpengpeng 2014/03/17) */
#ifndef _HANDLES_H_
#define _HANDLES_H_

int common_handle_add(void *data);
void common_handle_del(int handle);
void* common_handle_get(int handle);


/****************************/
#define HANDLE_TYPE		long
#include <map>

class Handle_Base
{
public:
	HANDLE_TYPE handle;		// 句柄，add时自动赋值
};

class Handles_Mgt
{
private:
	std::map<HANDLE_TYPE, Handle_Base*> handle_map;
	HANDLE_TYPE next_handle;

public:
	Handles_Mgt() {next_handle = 0;}

	HANDLE_TYPE Add(Handle_Base *data);
	void Del(HANDLE_TYPE handle);
	Handle_Base* Get(HANDLE_TYPE handle);
};

class Handle_XXX : public Handle_Base
{
public:
	int iPlatUserHandle;	// platform使用的句柄
};
extern Handles_Mgt handle_XXX_mgt;


#endif	// _HANDLES_H_

