/* main function file
   '(zhangpengpeng 2011-1-20)
   */

#include <stdio.h>
#include "soduku.h"

int main()
{
	SDKNODE soduku[9][9];
	initSoduku(soduku);
	
	int originSdk[9][9] = {
		6, 0, 0, 2, 0, 0, 0, 0, 4,
		2, 0, 8, 4, 5, 1, 6, 0, 0,
		3, 0, 0, 0, 8, 0, 0, 1, 0,
		1, 0, 0, 8, 6, 0, 3, 0, 0,
		0, 0, 9, 0, 0, 0, 1, 0, 0,
		0, 0, 6, 0, 1, 3, 0, 0, 8,
		0, 1, 0, 0, 7, 0, 0, 0, 2,
		0, 0, 2, 1, 4, 8, 5, 0, 3,
		5, 0, 0, 0, 0, 2, 0, 0, 1
		};
	copySoduku(soduku, originSdk);
	showSoduku(soduku);
	printf("rule: %d\n", checkRules(soduku));

	printf("------answer:\n");
	wayViolent(soduku);
	showSoduku(soduku);
	printf("rule: %d\n", checkRules(soduku));

	return 0;
}
