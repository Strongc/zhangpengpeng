//040630416张鹏鹏
//用Fleury算法求欧拉回路

#include <iostream.h>
#include <stdlib.h>

#define maxV 20				//最多20个点
#define lx 1  				//定义图的类型，1为无向图，0为有向图

int matrix[maxV][maxV];		//保存图形
int ma[maxV][maxV];			//矩阵相乘求和时的辅助矩阵
int mb[maxV][maxV];

void getMatrix(int &v,int &e)						//输入图形，返回顶点数、边数
{
	cout<<"请输入图形的顶点数：";
	cin>>v;
	cout<<"请输入图形的边数：";
	cin>>e;
	int i,j;
	cout<<endl<<"下面请依次输入各边："<<endl;
	for(int k=e;k>0;)
	{
		cin>>i>>j;
		if(i<=v&&j<=v&&i>0&&j>0)
		{
			matrix[i-1][j-1]=1;
			if(lx)
				matrix[j-1][i-1]=1;
			k--;
		}
		else
			cout<<"此边输入无效，请重新输入！"<<endl;
	}
}

void multiMatrix(int v)	//矩阵乘法函数：mb乘以matrix赋值给mb
{
	int i,j,k,sum=0;

	for(i=0;i<v;i++)			//ma=mb
		for(j=0;j<v;j++)
			ma[i][j]=mb[i][j];

	for(i=0; i<v; ++i)
		for(j=0;j<v;++j)
		{
			for(k=0; k<v; ++k)
				sum+=ma[i][k]*matrix[k][j];
			mb[i][j]=sum;
			sum=0;
		}
}

bool isBridge(int vi ,int vj,int v)				//判断Eij是否为桥,v为顶点数
{
	matrix[vi][vj]=0;//去掉需判断的边
	if(lx)
		matrix[vj][vi]=0;

	int i,j;
	for(i=0;i<v;i++)			//ma=matrix,mb=ma
		for(j=0;j<v;j++)
			mb[i][j]=matrix[i][j];
	for(i=0;i<v;i++)		//A+A*A+A*A*A+A*A*A*A=A(1+A(1+A(1+A)))

	{
		for(j=0; j<v; ++j)
			mb[j][j]+=1;
		multiMatrix(v);
	}

			

	if(mb[vi][vj]==0)		//判断非零
	{
		matrix[vi][vj]=1; //还原
		if(lx)
			matrix[vj][vi]=1;
	return true;
	}
	matrix[vi][vj]=1; //还原
	if(lx)
		matrix[vj][vi]=1;
	return false;
}

void main()								//主函数
{

	cout<<endl;
	cout<<"\t   ．．．．．嘿．．．．．．．．嘿．．．．．．   "<<endl;
	cout<<"\t．．．．嘿．．嘿．．．．．嘿．嘿．．．．．   "<<endl;
	cout<<"\t．．．．．嘿．．嘿．．．．嘿．．嘿．．．．   "<<endl;
	cout<<"\t．．．．．．嘿．．嘿．．嘿．嘿．嘿．．．． .   "<<endl;
	cout<<"\t．．．．．嘿．．．．．．．．． 嘿．．．．   "<<endl;
	cout<<"\t．．．嘿．．．．．．．．．．．．．嘿．．．   "<<endl;
	cout<<"\t．．嘿．．．．．．．．．．．．．．．嘿．．   "<<endl;
	cout<<"\t．嘿．．．．．．．．．．．．．．．．．嘿．   "<<endl;
	cout<<"\t嘿．．．．．．．．．．．．．．．．．．．嘿   "<<endl;
	cout<<"\t嘿．．．．．．．．．．．．．．．．．．．嘿   "<<endl;
	cout<<"\t嘿．．．．．∩．．．．．．．∩．．．．．嘿   "<<endl;
	cout<<"\t嘿． ．．．．．．．．．．．．．．．． ．嘿   "<<endl;
	cout<<"\t嘿． ．．．◎．．．．u．．．．◎．．．．嘿   "<<endl;
	cout<<"\t．嘿．．．．．．．．．．．．．．．．．嘿．   "<<endl;
	cout<<"\t．．嘿嘿．．．．．．．．．．．．．嘿嘿．．.   "<<endl;
	cout<<"\t．．．．嘿．嘿．嘿．嘿．嘿．嘿．嘿．． "<<endl<<endl;
	cout<<"\t         欢迎使用 用Fleury算法求欧拉回路 "<<endl;
	cout<<"\t                            By 张鹏鹏 040630416"<<endl;
	system("pause");
	system("cls");
	cout<<"\t 用Fleury算法求欧拉回路   By 张鹏鹏 040630416"<<endl<<endl;;

	int numV;		//记录顶点数
	int numE;		//记录边数
	getMatrix(numV,numE);

	int euler[maxV];		//记录欧拉回路		
	euler[0]=0;        //起始点V0
	int i;
	int j;
	int k;
	for(i=0,j=0,k=0;i<numE;i++)				//算法主体
	{
		j=0;
		while(j<numV&&(matrix[euler[i]][j]==0))
			j++;
		if(j==numV)
		{
			cout<<"很遗憾，这图中没有欧拉回路。"<<endl;
			system("pause");
			exit(0);
		}
		else
		{
			k=j;
			while(k<numV&&isBridge(euler[i],k,numV))		//查找下一个邻接顶点
			{
				do
					k++;
				while(k<numV&&(matrix[euler[i]][k]==0));
				if(k<numV)
					j=k;
			}
			euler[i+1]=j;
			matrix[euler[i]][j]=0;
			if(lx)
				matrix[j][euler[i]]=0;
		}
	}

	if(euler[i]!=euler[0])//检验是否回到起点，构成回路
	{
		cout<<"很遗憾，这图中没有欧拉回路。"<<endl;
		system("pause");
		exit(0);
	}

	cout<<endl<<endl;
	cout<<"太棒了，找到一条!"<<endl;
	cout<<"欧拉回路："
		<<(euler[0]+1);
	for(i=1;i<=numE;i++)
	{
		cout<<"→";
		cout<<(euler[i]+1);
	}

	cout<<endl<<endl;
	cout<<endl;
	cout<<"\t``╭╮　　　　　　　╭╮　　╭╮   "<<endl;
	cout<<"\t　││　　　　　　　││　　│└╮   "<<endl;
	cout<<"\t╭┴┴———————┴┴╮～└—╯   "<<endl;
	cout<<"\t│　　　　　　　　　　　│　　　╭—————╮"<<endl;   
	cout<<"\t│　　　　　　　　　　　│　　　│谢谢使用!!│   "<<endl;
	cout<<"\t│　●　　　　　　　●　│　╭╮│　　．^^．│   "<<endl;
	cout<<"\t│○　　╰┬┬┬╯　　○│ｏ╰╯╰—————╯   "<<endl;
	cout<<"\t│　　　　╰—╯　　　　│　   "<<endl;
	cout<<"\t╰——┬ｏ———ｏ┬——╯   "<<endl;
	cout<<"\t　 　╭╮　　　　╭╮　　　　   "<<endl;
	cout<<"\t　 　╰┴————┴╯ "<<endl;
	cout<<endl;
	system("pause");
	exit(0);
}




		

