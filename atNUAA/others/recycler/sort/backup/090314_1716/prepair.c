#include "sort.h"
#include <stdio.h>
#include <time.h>

/********************Follow is preparation*********************/

void getArr()		/*produce random array*/
{
	int i;
	srand (time(NULL));
	for(i=0;i<numArr;i++)
		Arr[i]=rand();
}

void copyArr()	/*copy date to protect original date*/
{
	int i;
	for(i=0;i<numArr;i++)
		A[i]=Arr[i];
}

void statistics(int sortMode)/*get average sortMode is the sort method*/
{
	double sum=0;
	int compCount;
	for(compCount=0;compCount<numArr;compCount++)
		sum+=compPerSort[sortMode][compCount];
	countAver[sortMode]=sum/numArr;
}

void output()		/*print the result*/
{
	int sortMode;
	printf("\n\nNow print the average times of comparison \neach sort_algorithm take to deal with %d random numbers\n",numArr);
	printf("SELECTIONSORT,INSERTIONSORT, BOTTOMUPSORT,    MERGESORT,    QUICKSORT\n");
	for(sortMode=0;sortMode<5;sortMode++)
		printf("%13.2f,",countAver[sortMode]);
	printf("\n\n");
}

