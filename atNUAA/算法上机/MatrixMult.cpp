//张鹏鹏  040630416@nuaa  信息科学与技术学院

#include <iostream.h>
#include <time.h>
#include <stdlib.h>

/************************全局变量*********************/
int ArT[10000][10000]			//数据数组，对此进行传统算法
int ArS[10000][10000];			//与ArT一样，对此进行STRASSEN算法
int numArr;						//数组元素个数，手动输入,（100～10000）
double countMul;				//算法执行乘法的次数
double countAdd;				//算法执行加法的次数
double notes[4][10000];			//记录numArr次比较的次数
double countAver[4];			//记录每个算法sortMode各个规模的平均比较次数
								//0和1时记录传统算法的乘法和加法，2和3类似，记为operMode

/**************************准备工作**********************
void getArr()					//生成随机数组
void statistics(int sortMode)	//统计平均次数
void output()					//输出结果
*********************************************************/

void getArr()					//生成随机数组
{
	srand (time(NULL));
	for(int i=0;i<numArr;i++)
		for(int j=0;j<numArr;j++)
		{
			ArT[i]=rand();
			ArS[i]=ArT[i];
		}
}

void statistics()				//统计平均次数
{
	double sum;
	int compCount,operMode;
	for(operMode=0;operMode<4;operMode++)
	{
		sum=0;
		for(compCount=0;compCount<numArr;compCount++)
			sum+=notes[operMode][compCount];
		countAver[operMode]=sum/numArr;
	}
}
void output()					//输出结果
{
	cout<<endl;
	cout<<"\n\n\t 以下依次输出"<<numArr<<"个数据规模下"<<endl;
	cout<<"传统算法的乘法次数、加法次数，STRASSEN算法的乘法次数、加法次数："<<endl;
	for(int operMode;operMode<4;operMode++)
		cout<<countAver[operMode]<<",    ";
	cout<<endl;
	cout<<"************End************"<<endl;
}


/**********************************主函数*****************************/
void main ()
{
	cout<<"请输入n×n矩阵的单行元素个数n（500～5000）：";
	cin>>numArr;
	if(numArr==0)	exit(0);	//可以退出
	int compCount;
	for(compCount=0;compCount<numArr;compCount++)			//执行比较
	{
		if((compCount+1)%100==0)
			cout<<compCount+1<<endl;
		getArr();



	statistics();
	output();
}