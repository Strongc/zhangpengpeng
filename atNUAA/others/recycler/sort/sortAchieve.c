/*****************************************************
Zhang Pengpeng (rocflyhi@gmail.com)
  
 from 
Colleage of Information Science and Technology 
Nanjing University of Aeronautics and Astronautics
 
Comment: 
This program comes form my algorithm homework which is modified for linux and GCC.
*****************************************************/

#include "sort.h"
#include <stdlib.h>

/********following are archieve of each sort_algorithm*****************/

/***********************SELECTIONSORT************************sortMode=0
 * void selectionSort(compCount)
 * ************************SELECTIONSORT************************/
void selectionSort(int compCount)
{
	copyArr();
	countComp=0;

	int i,j,min;
	int forchange;

	for(i=0;i<numArr;i++)
	{	
		min=i;
		for(j=i+1;j<numArr;j++)
		{
			countComp++;
			if(A[j]<A[min])
			min=j;
		}
		if(min!=i)
		{
			forchange=A[min];
			A[min]=A[i];
			A[i]=forchange;
		}
	}
	compPerSort[0][compCount]=countComp;
}

/***********************INSERTIONSORT************************sortMode=1
 * void insertionSort(int compCount)
 * ************************INSERTIONSORT************************/

void insertionSort(int compCount)
{
	copyArr();
	countComp=0;
	int i,j,x;
	for(i=1;i<numArr;i++)
	{
		x=A[i];
		j=i-1;
		while(j>=0&&A[j]>x)
		{
			countComp++;
			A[j+1]=A[j];
			j--;
		}
		countComp++;
		A[j+1]=x;
	}
	compPerSort[1][compCount]=countComp;
}

/***********************BOTTOMUPSORT************************sortMode=2
 * void merge(int p,int q,int r)
* void bottomupSort(int compCount)
 * ************************BOTTOMUPSORT************************/

void merge(int p,int q,int r)
{
	int *B;
	B=(int*)malloc(sizeof(int)*5000);/*free later to save memory*/
	int s=p;
	int t=q+1;
	int k=p;
	int i;
	
	while(s<=q&&t<=r)
	{
		if(A[s]<=A[t])
		{
			B[k]=A[s];
			s++;
		}
		else
		{
			B[k]=A[t];
			t++;
		}
		k++;
		countComp++;
	}
	if(s==q+1)
		for(;t<=r;t++,k++)
			B[k]=A[t];
	else
		for(;s<=q;s++,k++)
			B[k]=A[s];

	for(i=p;i<=r;i++)
		A[i]=B[i];
	free(B);
}

void bottomupSort(int compCount)
{
	copyArr();
	countComp=0;

	int t,s,i;
	t=1;

	while(t<numArr)
	{
		s=t;
		t=2*s;
		i=0;
		while(i+t<=numArr)
		{
			merge(i+1-1,i+s-1,i+t-1);
			i=i+t;
		}
		if(i+s<numArr)
			merge(i+1-1,i+s-1,numArr-1);
	}
	compPerSort[2][compCount]=countComp;
}

/***********************MERGESORT************************sortMode=3
 * void mergeSort(int compCount)
 * void mergesortrec(low,high)
 * ************************MERGESORT************************/

void mergesortrec(int low,int high)
{
	int mid;
	if(low<high)
	{
		mid=(low+high)/2;
		mergesortrec(low,mid);
		mergesortrec(mid+1,high);
		merge(low,mid,high);
	}
}

void mergeSort(int compCount)
{
	copyArr();
	countComp=0;
	mergesortrec(0,numArr-1);
	compPerSort[3][compCount]=countComp;
}

/***********************QUICKSORT************************sortMode=4
 * int split(low,high)
 * void quickSortrec(int low,int high)
 * void quickSort(int compCount)
 * ************************QUICKSORT************************/

int split(int low,int high)
{
	int i=low;
	int x=A[low];
	int forchange;
	int j;
	
	for(j=low+1;j<=high;j++)
	{
		countComp++;
		if(A[j]<=x)
		{
			i++;
			if(i!=j)
			{
				forchange=A[i];
				A[i]=A[j];
				A[j]=forchange;
			}
		}
	}
	forchange=A[i];
	A[i]=A[low];
	A[low]=forchange;
	return i;
}

void quickSortrec(int low,int high)
{
	int w;
	if(low<high)
	{
		w=split(low,high);
		quickSortrec(low,w-1);
		quickSortrec(w+1,high);
	}
}

void quickSort(int compCount)
{
	copyArr();
	countComp=0;
	quickSortrec(0,numArr-1);
	compPerSort[4][compCount]=countComp;
}

