//张鹏鹏  040630416@nuaa  信息科学与技术学院

#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

/***********************全局变量************************/

int Arr[5000];					//数据数组
int A[5000];					//与Arr一样，每次对此进行排序，可以保留原数据
int numArr;						//数组元素个数，手动输入,（500～5000）
double countComp;				//算法执行比较的次数
double compPerSort[5][5000];		//记录numArr次比较的次数
double countAver[5];			//记录每个算法sortMode各个规模的平均比较次数


/***********************以下是准备工作************************
 * void getArr()	//生成随机数组
 * void copyArr()	//复制数据，保留原数据
 * void statistics(int sortMode)		//每个算法结束后统计平均次数，sortMode为排序方法
 * void output()	//输出结果
 * ************************以下是准备工作***************************/

void getArr()					//生成随机数组
{
	srand (time(NULL));
	for(int i=0;i<numArr;i++)
		Arr[i]=rand();
}

void copyArr()					//复制数据，保留原数据
{
	for(int i=0;i<numArr;i++)
		A[i]=Arr[i];
}

void statistics(int sortMode)				//每个算法结束后统计平均次数，sortMode为排序方法
{
	double sum=0;
	for(int compCount=0;compCount<numArr;compCount++)
		sum+=compPerSort[sortMode][compCount];
	countAver[sortMode]=sum/numArr;
}

void output()					//输出结果
{
	cout<<endl;
	cout<<"\n\n\t 以下依次输出"<<numArr<<"个数据规模下"<<endl;
	cout<<"SELECTIONSORT,INSERTIONSORT,BOTTOMUPSORT,MERGESORT,QUICKSORT算法的平均比较次数："<<endl;
	for(int sortMode=0;sortMode<5;sortMode++)
		cout<<countAver[sortMode]<<",    ";
	cout<<endl;
	cout<<"************End************"<<endl;
}


/***********************以下是各个算法的实现************************/

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
			countComp++;
			A[j+1]=x;
		}
		compPerSort[1][compCount]=countComp;
	}
}

/***********************BOTTOMUPSORT************************sortMode=2
 * void merge(int p,int q,int r)
* void bottomupSort(int compCount)
 * ************************BOTTOMUPSORT************************/

void merge(int p,int q,int r)
{
	int *B;
	B=new int[5000];			//这样申请空间是为了能方便的释放，减少内存的压力
	int s=p;
	int t=q+1;
	int k=p;
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

	for(int i=p;i<=r;i++)
		A[i]=B[i];
	delete B;
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
			merge(i+1-1,i+s-1,i+t-1);	//减一是为了与C语言的数组下标习惯统一
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
 * void split(low,high)
 * void quickSortrec(int low,int high)
 * void quickSort(int compCount)
 * ************************QUICKSORT************************/

int split(int low,int high)
{
	int i=low;
	int x=A[low];
	int forchange;
	for(int j=low+1;j<=high;j++)
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


/***********************主函数************************/

int main()
{
	cout<<"请输入数组元素的个数（500～5000）：";
	cin>>numArr;
	if(numArr==0)	exit(0);	//可以退出

	system("uptime");
	int compCount;
	for(compCount=0;compCount<numArr;compCount++)			//执行比较
	{
		if((compCount+1)%100==0)
			cout<<compCount+1<<endl;
		getArr();
		selectionSort(compCount);
		insertionSort(compCount);
		bottomupSort(compCount);
		mergeSort(compCount);
		quickSort(compCount);
	}
	for(int sortMode=0;sortMode<5;sortMode++)
		statistics(sortMode);
	output();
	system("uptime");
	return 0;

}

