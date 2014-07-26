/**	@file tools.h
 *	@note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *	@brief 工具集
 *
 *	@author		zhangpengpeng
 *	@date		2012/09/20
 *
 *	@note 各种工具
 */
#include <Windows.h>

class OL_Lock
{
private:
	CRITICAL_SECTION m_csOper;
public:
	OL_Lock();
	~OL_Lock();
	void Lock();
	void UnLock();
};

class OL_AutoLock
{
private:
	OL_Lock *m_pLock;
public:
	OL_AutoLock(OL_Lock *pLock);
	~OL_AutoLock();
};
