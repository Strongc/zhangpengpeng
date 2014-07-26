/* class CZAutoLock  '(zhangpengpeng 2013/09/10)
 * my one lock tool
 */

#ifndef _ZONELOCK_H_
#define _ZONELOCK_H_


// CRITICAL_SECTION cs;
// InitializeCriticalSection(&cs);
// DeleteCriticalSection(&cs);

class CZAutoLock
{
private:
	CRITICAL_SECTION *m_pCS;

public:
	CZAutoLock(CRITICAL_SECTION *pCS) : m_pCS(pCS)
	{
		EnterCriticalSection(m_pCS);
	}

	~CZAutoLock(void)
	{
		LeaveCriticalSection(m_pCS);
	}
};

#endif // _ZONELOCK_H_