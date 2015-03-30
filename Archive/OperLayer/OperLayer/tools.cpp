/**	@file tools.cpp
 *	@note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *	@brief 工具集
 *
 *	@author		zhangpengpeng
 *	@date		2012/09/20
 *
 *	@note 各种工具
 */

#include "tools.h"

OL_Lock::OL_Lock()
{
	InitializeCriticalSection(&m_csOper);
}
OL_Lock::~OL_Lock()
{
	DeleteCriticalSection(&m_csOper);
}
void OL_Lock::Lock()
{
	EnterCriticalSection(&m_csOper);
}
void OL_Lock::UnLock()
{
	LeaveCriticalSection(&m_csOper);
}

OL_AutoLock::OL_AutoLock(OL_Lock *pLock)
: m_pLock(pLock)
{
	if (m_pLock)
		m_pLock->Lock();
}

OL_AutoLock::~OL_AutoLock()
{
	if (m_pLock)
		m_pLock->UnLock();
}
