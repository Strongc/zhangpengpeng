#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/************** main function ***************/

int main()
{
	int sortMode;
	int compCount;
	time_t tm;
	
	printf("Please input the number of the array(from 500 to 5000):");
	scanf("%d",&numArr);
	if(numArr<500||numArr>5000)
	{
		printf("The given number is out of range!\n");
		exit(0);
	}

	tm=time(NULL);
	for(compCount=0;compCount<numArr;compCount++)	/*sort and compare*/
	{
		if((compCount+1)%100==0)
			printf("%d\n",compCount+1);
		getArr();
		selectionSort(compCount);
		insertionSort(compCount);
		bottomupSort(compCount);
		mergeSort(compCount);
		quickSort(compCount);
	}
	for(sortMode=0;sortMode<5;sortMode++) 
		statistics(sortMode);
	output();
	tm=time(NULL)-tm;
	printf("\nTotall cost of time:%ld minutes ,%ld seconds\n\n",tm/60,tm%60); 
	return 0;

}

