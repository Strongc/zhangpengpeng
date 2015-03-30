/*****************************************************
Zhang Pengpeng (rocflyhi@gmail.com)
  
 from 
Colleage of Information Science and Technology 
Nanjing University of Aeronautics and Astronautics
 
Comment: 
This program comes form my algorithm homework which is modified for linux and GCC.
*****************************************************/

#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/************** sort function ***************/

int sort()
{
	int sortMode;
	int compCount;
	time_t tm;
	
	if(numArr<500||numArr>5000)
	{
		printf("The given number is out of range!\n");
		exit(0);
	}

	tm=time(NULL);
	for(compCount=0;compCount<numArr;compCount++)	/*sort and compare*/
	{
		if((compCount+1)%100==0)
			printf("%d%% \n",((compCount+1)*100)/numArr);
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
	printf("\t////Totall cost of time:%ld minutes ,%ld seconds//////\n\n",tm/60,tm%60); 
	return 0;

}


/************** main function ***************/
int main(int argc, char *argv[])
{
	int temp;

	if(argc<2)
	{
		printf("Please input the number of the array(from 500 to 5000):");
		scanf("%d",&numArr);
		sort();
	}
	else
		for(temp=1;temp<argc;temp++)
		{
			numArr=atoi(argv[temp]);
			printf("\n*******Now No.%d section(%d random numbers):\n",temp,numArr); 
			sort();
		}
	
	return 0;
}
