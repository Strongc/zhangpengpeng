/* c file to soduku.h
   '(zhangpengpeng 2011-1-20)
   */

#include <stdio.h>
#include "soduku.h"

void initSoduku(SDKNODE soduku[9][9])
{
	int i;
	int j;
	int k;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			soduku[i][j].answer = 0;
			soduku[i][j].state = NONE;
			for (k = 0; k < 0; k++) {
				soduku[i][j].cand[k] = 0;
			}
		}
	}
}

void showSoduku(SDKNODE soduku[9][9])
{
	int i;
	int j;
	int k;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			switch (soduku[i][j].state) {
			case FIX:
			case ORIGIN:
				printf("%d ", soduku[i][j].answer);
				break;
			case CAND:
			case NONE:
				//printf("%d ", soduku[i][j].answer);
				printf("_ ");
				break;
			default:
				break;
			}
		}
		printf("\n");
	}
}

void copySoduku(SDKNODE soduku[9][9], int sdk[9][9])
{
	int i;
	int j;
	int k;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if (sdk[i][j] >= 1 && sdk[i][j] <= 9) {
				soduku[i][j].answer = sdk[i][j];
				soduku[i][j].state = ORIGIN;
			}
		}
	}
}

