/* rules: value soduku by rules
   '(zhangpengpeng 2011-1-20)
   true return 0, otherwise non-0
   */

#include "soduku.h"

int checkRules(SDKNODE soduku[9][9])
{
	int r1 = rule1(soduku);
	int r2 = rule2(soduku);
	int r3 = rule3(soduku);

	//printf("%d, %d, %d\n", r1, r2, r3);
	int ret = (r1 / 100) * 1000 + (r2 % 10) * 100 
		+ (r3 / 100) * 10 + (r3 % 10);
	return ret;
}

int rule1(SDKNODE soduku[9][9])
{
	int i;	/*row*/
	int j;	/*col*/
	int answer;
	int refer[10];
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 10; j++)
			refer[j] = 0;

		for (j = 0; j < 9; j++) {
			answer = soduku[i][j].answer;
			if (answer >= 1 && answer <= 9) {
				if (refer[answer] == 0)
					refer[answer] = 1;
				else
					return (i + 1) * 100 + j + 1;
			}
		}
	}

	return 0;
}

int rule2(SDKNODE soduku[9][9])
{
	int i;	/*col*/
	int j;	/*row*/
	int answer;
	int refer[10];
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 10; j++)
			refer[j] = 0;

		for (j = 0; j < 9; j++) {
			answer = soduku[j][i].answer;
			if (answer >= 1 && answer <= 9) {
				if (refer[answer] == 0)
					refer[answer] = 1;
				else
					return (j + 1) * 100 + i + 1;
			}
		}
	}

	return 0;
}

int rule3(SDKNODE soduku[9][9])
{
	int bi;	/*block row*/
	int bj;	/*block col*/
	int i;	/*block num row*/
	int j;	/*block num col*/
	int k;
	int answer;
	int refer[10];
	for (bi = 0; bi < 3; bi++) {
		for (bj = 0; bj < 3; bj++) {
			for (k = 0; k < 10; k++)
				refer[k] = 0;
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 3; j++) {
					answer = soduku[bi * 3 + i][bj * 3 + j].answer;
					if (answer >= 1 && answer <= 9) {
						if (refer[answer] == 0)
							refer[answer] = 1;
						else
							return (bi * 3 + i + 1) * 100 + (bj * 3 + j + 1);
					}
				}
			}
		}
	}

	return 0;
}

