
/***************************************
   for my postgraduate student life
   by Zhang Pengpeng 
   rocflyhi@gmail.com
**************************************/
   

#include <stdio.h>
#include "mylib.h"

void print(int x)
{
	printB(x);
	printf("  _____________");
	printf("[10]:%d,[8]:%o,[16]:%x",x,x,x);
	printf("\n");
}

void multiply(int *x, int *y, int *mul)
{
	int i;
	int temp=(*x)<<16;
	for(i=0;i<16;i++)
	{
		if((*mul)&1)
			*mul=*mul+temp;
		*mul=*mul>>1;
		printf("%2dmul: ",i+1);
		print(*mul);
	}
}

int main()
{
	int x, y, mul;
	x=101;
	y=1412;

	printf("    X: ");
	print(x);
	printf("    Y: ");
	print(y);
	printf("0 mul: ");
	mul=(0<<16)+y;
	print(mul);

	multiply(&x,&y,&mul);
	printf("\n  MUL: ");
	print(mul);

	return 0;
}
	
