//张鹏鹏  040630416
//回溯法实现子集和问题

#include <iostream.h>
#include <stdlib.h>

int X[10]={10,20,30,40,50,60,70,80,90,100};//X为所给的子集
int Y;//Y为给的和
int v[10]={0};//v为解向量,在这里已初始化，一次只能处理一个Y，如果想循环，还得重新初始化
bool flag;

void output()			//输出结果向量
{
	cout<<" v :";
	for(int i=0;i<10;i++)
		cout<<"  "<<v[i]<<",";
	cout<<endl;
	flag=true;
}

int getSum()			//计算和，判断是否为最终解
{
	int sum=0;
	int x=10;
	for(int i=0;i<10;i++)
		sum+=x*(i+1)*v[i];
	return sum;
}

void advance(int k)			//递归
{
	if(k<0) return;//k为-1时，确定已无解了，保存-1退出递归

	v[k]=1;
	if(getSum()==Y)
	{
		output();
		v[k]=0;
	}
	if(getSum()<Y)			//深度优先
	{
		if(k<9)
			advance(k+1);
	}
	else					//回溯
	{
		v[k]=0;
		for(;k>=0;k--)
			if(v[k]==1)
			{
				v[k]=0;
				advance(k+1);
			}
		if(k<0) advance(k);//k为-1时，确定已无解了，保存-1退出递归
	}
}

void main()
{
	cout<<"Please input a number(30~100):";
	cin>>Y;
	if(Y<30||Y>100)
	{
		cout<<"Input False!";
		system("pause");
		exit(0);
	}
	flag=false;
	cout<<" X : 10, 20, 30, 40, 50, 60, 70, 80, 90, 100"<<endl
		<<endl;
	advance(0);
	if(flag==false)
		cout<<"\n No Solution!";
	cout<<"\n----------END-----------"<<endl;
	system("pause");

}
