/* class ZAutoLock  '(zhangpengpeng 2013/09/10)
 * my one lock tool
 */

#ifndef _ZONELOCK_H_
#define _ZONELOCK_H_


// CRITICAL_SECTION cs;
// InitializeCriticalSection(&cs);
// DeleteCriticalSection(&cs);

class ZAutoLock
{
private:
	CRITICAL_SECTION *cs;

public:
	ZAutoLock(CRITICAL_SECTION *s) : cs(s)
	{
		EnterCriticalSection(cs);
	}

	~ZAutoLock(void)
	{
		LeaveCriticalSection(cs);
	}
};

#endif // _ZONELOCK_H_