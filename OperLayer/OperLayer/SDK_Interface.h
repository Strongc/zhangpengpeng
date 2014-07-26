#ifndef WIN_API
#define WIN_API __stdcall
#endif

typedef int (WIN_API *OL_Init)(const char *szParam);
typedef int (WIN_API *OL_UnInit)();
typedef int (WIN_API *OL_Dosth)(const char *szParam);


typedef struct _st_SDK_Interface
{
	OL_Init init;
	OL_UnInit unInit;
	OL_Dosth dosth;
} SDK_INTERFACE;
