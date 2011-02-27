
/***************************************
   for my postgraduate student life
   by Zhang Pengpeng 
   rocflyhi@gmail.com
**************************************/
   

#include <stdio.h>

void printB(int data)	//print a int-type data using format of binary
{
	char joint='-'; //connect each 8 bits
	int i;
	int length;
	unsigned int co;
	length=8*sizeof(int);
	co=1<<(length-1);

	for(i=0;i<length;i++)
	{
		printf("%d",(data&co)==0?0:1);
		co=co>>1;

		if(((i+1)%8==0)&&((i+1)!=length))
			printf("%c",joint);
	}
}
/*
int main()
{
	int tmp;
	scanf("%d",&tmp);
	printf("\n%x\n",tmp);
	printB(tmp);
	tmp=tmp<<3;
	printf("\n%x\n",tmp);
	printB(tmp);
	printf("\n");
	return 0;
}
*/
