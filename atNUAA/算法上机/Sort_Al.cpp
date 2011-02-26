//������  040630416@nuaa  ��Ϣ��ѧ�뼼��ѧԺ

#include <iostream.h>
#include <stdlib.h>

/***********************ȫ�ֱ���************************/
int Arr[5000];					//��������
int A[5000];					//��Arrһ����ÿ�ζԴ˽������򣬿��Ա���ԭ����
int numArr;						//����Ԫ�ظ������ֶ�����,��500��5000��
long int countComp;				//�㷨ִ�бȽϵĴ���
long int compPerSort[5][5000];		//��¼numArr�αȽϵĴ���
long int countAver[5];			//��¼ÿ���㷨sortMode������ģ��ƽ���Ƚϴ���


/***********************������׼������************************
void getArr()	//�����������
void copyArr()	//�������ݣ�����ԭ����
void statistics(int sortMode)		//ÿ���㷨������ͳ��ƽ��������sortModeΪ���򷽷�
void output()	//������
************************������׼������***************************/

void getArr()					//�����������
{
	srand (time(NULL));
	for(int i=0;i<numArr;i++)
		Arr[i]=rand();
}
void copyArr()					//�������ݣ�����ԭ����
{
	for(int i=0;i<numArr;i++)
		A[i]=Arr[i];
}

void statistics(int sortMode)				//ÿ���㷨������ͳ��ƽ��������sortModeΪ���򷽷�
{
	double sum=0;
	for(int compCount=0;compCount<numArr;compCount++)
		sum+=compPerSort[sortMode][compCount];
	countAver[sortMode]=sum/numArr;
}

void output()					//������
{
	cout<<"\n\n\t �����������"<<numArr<<"�����ݹ�ģ��"<<endl;
	cout<<"SELECTIONSORT,INSERTIONSORT,BOTTOMUPSORT,MERGESORT,QUICKSORT�㷨��ƽ���Ƚϴ�����"<<endl;
	for(int sortMode=0;sortMode<5;sortMode++)
		cout<<countAver[sortMode]<<",";
	cout<<endl;
	cout<<"************End************";
}

/***********************�����Ǹ����㷨��ʵ��************************/

/***********************SELECTIONSORT************************sortMode=0
void selectionSort(compCount)
************************SELECTIONSORT************************/
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
			forchang=A[min];
			A[min]=A[i];
			A[i]=forchange;
		}
	}
	compPerSort[0][compCount]=countComp;
}
/***********************INSERTIONSORT************************sortMode=1
void insertionSort(int compCount)
************************INSERTIONSORT************************/
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
void bottomupSort(int compCount)
void merge(int p,int q,int r)
************************BOTTOMUPSORT************************/
void bottomupSort(int compCount)
{
	copyArr();
	countComp=0;

	int t,s,i;
	t=1;
	while(t<n)
	{
		s=t;
		t=2s;
		i=0;
		while(i+t<=n)
		{
			merge(i+1-1,i+s-1,i+t-1);	//��һ��Ϊ����C���Ե������±�ϰ��ͳһ
			i=i+t;
		}
		if(i+s<n)
			merge(i+1-1,i+s-1,n-1);
	}

	compPerSort[2][compCount]=countComp;
}

void merge(int p,int q,int r)
{
	int *B;
	B=new int[5000];			//��������ռ���Ϊ���ܷ�����ͷţ������ڴ��ѹ��
	int s=p;
	int t=q+1;
	int k=p;
	while(s<=q&&int t<=r)
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

/***********************MERGESORT************************sortMode=3
void mergeSort(int compCount)
void mergesortrec(low,high)
************************MERGESORT************************/
void mergeSort(int compCount)
{
	copyArr();
	countComp=0;

	mergesortrec(1,n);

	compPerSort[3][compCount]=countComp;
}

void mergesortrec(low,high)
{
	if(low<high)
	{
		mid=(low+high)/2;
		mergesortrec(low,mid);
		mergesortrec(mid+1,high);
		merge(low,mid,high);
	}
}
/***********************QUICKSORT************************sortMode=4
************************QUICKSORT************************/
void quickSort(int compCount)
{
	copyArr();
	countComp=0;


	compPerSort[4][compCount]=countComp;
}




/***********************������************************/
void main()
{
	cout<<"����������Ԫ�صĸ�����500��5000����";
	cin>>numArr;
	if(num==0)	exit(0);	//�����˳�
	int compCount;
	for(compCount=0;compCount<numArr;compCount++)			//ִ�бȽ�
	{
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
}




