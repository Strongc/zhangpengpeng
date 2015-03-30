#include <stdio.h>

#ifndef WIN_API
#define WIN_API __stdcall
#endif


int WIN_API OL_Init(const char *szParam)
{
	printf("OL_Init at OL_XXX\n");
	return 0;
}

int WIN_API OL_UnInit()
{
	printf("OL_UnInit at OL_XXX\n");
	return 0;
}

int WIN_API OL_Dosth(const char *szParam)
{
	printf("OL_Dosth [%s] at OL_XXX\n", szParam);
	return 0;
}
