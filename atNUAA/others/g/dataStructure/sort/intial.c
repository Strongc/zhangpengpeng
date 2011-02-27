
/***************************************
   for my postgraduate student life
   by Zhang Pengpeng 
   rocflyhi@gmail.com
**************************************/
   
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

void intialList(SqList **L)
{
	int i;
	int temp;
	
	*L=(SqList *)malloc(sizeof(SqList));
	srand(time(NULL));
	temp=(int)(rand());
	for(i=1;i<=MAXSIZE;)
	{
		if(temp>10)
		{
			(*L)->r[i].key=temp%100;
			i++;
		}
		else
		{
			srand(temp);
			temp=(int)(rand());
		}

		temp=temp/100;
	}
}

void showAll(SqList *L)
{
	int i;
	for(i=1;i<=MAXSIZE;i++)
		printf("%d,",L->r[i].key);
	printf("\n");
}
