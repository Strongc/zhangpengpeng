// main function  '(zhangpengpeng 2014/05/10)

#include "ServiceInterface.h"

#include <stdlib.h>

int main()
{
	IPO_P_ServiceInit();

	IPO_P_ServiceStart();

	system("pause");
	
	IPO_P_ServiceStop();

	IPO_P_ServiceFini();

	return 0;
}