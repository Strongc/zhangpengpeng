/*
	张鹏鹏 040630416
第三次作业
哈夫曼编/译码器
*/

#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>

#define TRUE	1
#define FALSE	0
#define OK		1
#define ERROR	0
#define INFEASIBLE	-1
#define OVERFLOW	-2

typedef int Status;

typedef struct
{
	int weight;
	int parent,lchild,rchild;
}HTNode,*HuffmanTree;

				//全局变量
char Code[10];						//编码字符
HuffmanTree HT;						//哈夫曼树指针
int n;								//编码字符的个数
bool MemIf;							//内存中是否有哈夫曼树
bool InitIf;							//是否初始化过
fstream File,File2;					//指向某个文件
int position;						//用于打印哈夫曼树时调整对齐

Status Select(int &s1,int &s2)					//选出最小的两个节点
{
	int i;
	s1=1;s2=2;
	for(i=3;i<2*n&&HT[i].weight!=0;i++)
	{
		if(HT[i].parent!=0)
			continue;
		if(HT[s1].parent!=0)
			s1=i;
		else
			if(HT[s2].parent!=0)
				s2=i;
			else
				if(HT[s1].weight<=HT[s2].weight)
				{
					if(HT[i].weight<HT[s2].weight)
					s2=i;
				}
				else
				{
					if(HT[i].weight<HT[s1].weight)
					s1=i;
				}
	}
	return OK;
}

Status Inintialization()				//初始化
{
	cout<<"请输入新编码中字符的个数：";
	cin>>n;

	int m,i,s1,s2;
	if(n<=1)
		return ERROR;
	m=2*n-1;
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));		//0号单元未用
	HuffmanTree p;
	for(p=HT+1,i=1;i<=n;++i,++p)
	{
		cout<<"第"<<i<<"个字符及其权值：";
		cin>>Code[i-1];
		cin>>(*p).weight;
		(*p).parent=0;
		(*p).lchild=0;
		(*p).rchild=0;
	}
	for(;i<=m;++i,++p)
	{
		(*p).weight=0;
		(*p).parent=0;
		(*p).lchild=0;
		(*p).rchild=0;
	}

	for(i=n+1;i<=m;++i)									//建哈夫曼树
	{
		Select(s1,s2);
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}
															//写入文件
	File.open("hfmTree.dat",ios::out|ios::binary);
	if(!File)
	{
		cout<<"打开文件hfmTree.dat失败！";
		system("pause");
		exit(0);
	}
	File.write((char*)HT,(2*n)*sizeof(HTNode));
	File.write(Code,10*sizeof(char));
	File.write((char*)&n,sizeof(int));
	File.close();

	MemIf=true;
	InitIf=true;
	cout<<"初始化完毕！"<<endl;
	system("pause");
	return OK;
}

Status Encoding()			//编码
{
	if(MemIf==false)
	{															//读出哈夫曼树
		File.open ("hfmTree.dat",ios::in|ios::binary);
		if(!File)
		{
			cout<<"打开文件hfmTree.dat失败！";
			system("pause");
			exit(0);
		}
		File.read((char*)HT,(2*n)*sizeof(HTNode));
		File.read(Code,10*sizeof(char));
		File.read((char*)&n,sizeof(int));
		File.close();
		MemIf=true;
	}
	
	char c;
	int i,j;

	cout<<"下面开始编码："<<endl;
	File.open ("ToBeTran.txt",ios::in);
	if(!File)
	{
		cout<<"打开文件ToBeTran.txt失败！";
		system("pause");
		exit(0);
	}
	File2.open ("CodeFile.txt",ios::out);
	if(!File2)
	{
		cout<<"打开文件CodeFile.txt失败！";
		system("pause");
		exit(0);
	}

	File>>c;
	while(!File.eof())
	{
		for(i=0;i<n;i++)
			if(c==Code[i])
				break;
		for(i++,j=HT[i].parent;j!=0;i=j,j=HT[j].parent)		
			if(HT[j].lchild==i)
			{
				cout<<'0';
				File2<<'0';
			}
			else
			{
				cout<<'1';
				File2<<'1';
			}
		File>>c;
	}

	File.close();
	File2.close();
	cout<<endl;
	cout<<"编码结束，已保存到CodeFile.txt"<<endl;
	system("pause");		
	return OK;
}

Status Decoding()		//译码
{
	if(MemIf==false)
	{															//读出哈夫曼树
		File.open ("hfmTree.dat",ios::in|ios::binary);
		if(!File)
		{
			cout<<"打开文件hfmTree.dat失败！";
			system("pause");
			exit(0);
		}
		File.read((char*)HT,(2*n)*sizeof(HTNode));
		File.read(Code,10*sizeof(char));
		File.read((char*)&n,sizeof(int));
		File.close();
		MemIf=true;
	}
	
	cout<<"下面开始译码："<<endl;
	File.open ("TextFile.txt",ios::out);
	if(!File)
	{
		cout<<"打开文件TextFile.txt失败！";
		system("pause");
		exit(0);
	}
	File2.open ("CodeFile.txt",ios::in);
	if(!File2)
	{
		cout<<"打开文件CodeFile.txt失败！";
		system("pause");
		exit(0);
	}
	
	int m;
	m=2*n-1;
	char c;
	
	File2>>c;
	while(!File.eof())
	{
		if(c=='0')
			m=HT[m].lchild;
		else
			m=HT[m].rchild;

		if(!HT[m].lchild)
		{
			switch(m)
			{
				case 1 :
					cout<<Code[0];
					File2<<Code[0];
					break;
				case 2 :
					cout<<Code[1];
					File2<<Code[1];
					break;
				case 3 :
					cout<<Code[2];
					File2<<Code[2];
					break;
				case 4 :
					cout<<Code[3];
					File2<<Code[3];
					break;
				case 5 :
					cout<<Code[4];
					File2<<Code[4];
					break;
				case 6 :
					cout<<Code[5];
					File2<<Code[5];
					break;
				case 7 :
					cout<<Code[6];
					File2<<Code[6];
					break;
				case 8 :
					cout<<Code[7];
					File2<<Code[7];
					break;
				case 9 :
					cout<<Code[8];
					File2<<Code[8];
					break;
				case 10 :
					cout<<Code[9];
					File2<<Code[9];
					break;
				default :return ERROR;
			}
			m=2*n-1;
		}
		File2>>c;
	}

	File.close();
	File2.close();
	cout<<endl;
	cout<<"译码结束，已保存到TextFile.txt"<<endl;
	system("pause");
	return OK;
}


Status PrintHT(int root)			//打印哈夫曼树
{
	if(MemIf==false)
	{
																//读出哈夫曼树
		File.open ("hfmTree.dat",ios::in|ios::binary);
		if(!File)
		{
			cout<<"打开文件hfmTree.dat失败！";
			system("pause");
			exit(0);
		}
		File.read((char*)HT,(2*n)*sizeof(HTNode));
		File.read(Code,10*sizeof(char));
		File.read((char*)&n,sizeof(int));
		File.close();
		MemIf=true;
	}
	
	position++;
	for(int i=0;i<position;i++)
	cout<<'\t';
	cout<<HT[root].weight;
	if(HT[root].lchild==0)
	{
		cout<<'('<<Code[root-1]<<')'<<endl;
	}
	else
	{
		cout<<endl;
		PrintHT(HT[root].lchild);
		PrintHT(HT[root].rchild);
	}
	position--;	

	return OK;
}

void EndPrint()
{
	cout<<"\n\n\t\t      数据结构上机"<<endl
		<<"\t\t 第三次作业 哈夫曼编/译码器"<<endl
		<<"\t\t      By 张鹏鹏(040630416)"<<endl;
	system("pause");
}

void main()
{
	char c;

	MemIf=false;
	InitIf=false;

	while(1)
	{
		system("cls");
		cout<<"哈夫曼编/译码器"<<endl;									//选择菜单 首页
		cout<<"I:初始化"<<endl
			<<"E:编码"<<endl
			<<"D:译码"<<endl
			<<"T:打印哈夫曼树"<<endl
			<<"Q:退出"<<endl;
		if(InitIf==false)
			cout<<"说明：若不进行初始化，系统将调用hfmTree.dat文件中的默认代码，\n直到你重新初始化，将旧代码覆盖。"<<endl;
		cout<<"请输入你的选择(I,E,D,T,Q):";
		cin>>c;
		while(c!='i'&&c!='e'&&c!='d'&&c!='t'&&c!='q'&&c!='I'&&c!='E'&&c!='D'&&c!='T'&&c!='Q')
		{
			cout<<"请输入I,E,D,T,Q中的一个字母（不分大小写）:";
			cin>>c;
		}
		cout<<endl;
		system("cls");
		switch(c)
		{
			case 'i' :
			case 'I' :Inintialization();
					break;
			case 'e' :
			case 'E' :Encoding();
					break;
			case 'd' :
			case 'D' :Decoding();
					break;
			case 't' :
			case 'T' :position=0;
					PrintHT(2*n-1);
					cout<<"打印结束！"<<endl;
					system("pause");
					break;
			case 'q' :
			case 'Q' :EndPrint();
					exit(0);
			default:cout<<"错误！";
					exit(0);
		}
	}
}
		
