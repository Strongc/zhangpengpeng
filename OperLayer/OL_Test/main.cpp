#include "../OperLayer/OperLayer.h"
#pragma comment(lib, "OperLayer.lib")

int main()
{
	int iOLHandle = OperLayer_Init("XXX", "", "");
	OperLayer_Dosth(iOLHandle, "xmlParams");
	OperLayer_UnInit(iOLHandle);
	return 0;
}