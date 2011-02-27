
/***************************************
   for my postgraduate student life
   by Zhang Pengpeng 
   rocflyhi@gmail.com
**************************************/
   

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n=5;
	int A[5]={0,1,3,4,5};
	printf("%d\n",linearSearch(A,5,3));
	printf("%d\n",binarySearch(A,5,4));

	return 0;
}

int linearSearch(int A[] , int n,int x)
{
	int j;
	for(j=0;j<n;j++)
	{
		if(A[j]==x)
			break;
	}
	if(j<n)
		return j;
	else
		return 0;
}

int binarySearch(int A[] , int n , int x)
{
	int low,high,mid,j;
	low=0;
	high=n-1;
	mid=low;
	j=0;
	while(low<=high)
	{
		mid = (low+high)/2;
		if(x==A[mid])
		{
			j = mid;
			break;
		}
		else
			if(x<A[mid])
				high=mid-1;
			else
				low=mid+1;
	}
	
	return j;
}

int merge(int A[],int p, int q, int r)
{
	int *B;
	B=(int *)malloc((r-p+1)*sizeof(int));
	int s,t,k;
	s=q;
	t=q+1;
	k=p;
	while(s<=q && t<=r)
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
	}
	if(s==(q+1))
		while(t<=r)
		{
			B[k]=A[t];
			t++;
			k++;
		}
	else
		while(s<=q)
		{
			B[k]=A[s];
			s++;
			k++;
		}

	for(k=p;k<=r;k++)
		A[k]=B[k];
	return 1;
}


