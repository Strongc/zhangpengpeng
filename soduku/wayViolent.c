/* violent way to solve soduku
   '(zhangpengpeng 2011-1-20)
   use recursion
   */

#include "soduku.h"

int wayViolent_rec(SDKNODE soduku[9][9], int i, int j)
{
	if (i > 8 || j > 8)
		return 0;

	int ii = 0;
	int jj = 0;
	if ( j == 8) {
		ii = i + 1;
		jj = 0;
	} else	{
		ii = i;
		jj = j + 1;
	}

	if (soduku[i][j].state == ORIGIN)
		return wayViolent_rec(soduku, ii, jj);

	int value;
	for (value = 1; value <= 9; value++) {
		soduku[i][j].answer = value;
		soduku[i][j].state = FIX;
		if (checkRules(soduku) == 0)
			if (wayViolent_rec(soduku, ii, jj) == 0)
				return 0;
	}
	soduku[i][j].answer = 0;
	soduku[i][j].state = NONE;
	return -1;
}

int wayViolent(SDKNODE soduku[9][9])
{
	return wayViolent_rec(soduku, 0, 0);
}
