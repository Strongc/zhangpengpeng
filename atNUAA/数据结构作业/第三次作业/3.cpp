/*
	������ 040630416
��������ҵ
��������/������
*/

#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>
#include <iomanip.h>

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

				//ȫ�ֱ���
char Code[10];						//�����ַ�
HuffmanTree HT;						//��������ָ��
int n;								//�����ַ��ĸ���
bool InitIf;						//�Ƿ��ʼ����
int position;						//���ڴ�ӡ��������ʱ��������

Status Select(int &s1,int &s2)					//ѡ����С�������ڵ�
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

Status Inintialization()				//��ʼ��
{
	cout<<"�������±������ַ��ĸ�����";
	cin>>n;

	int m,i,s1,s2;
	if(n<=1)
		return ERROR;
	m=2*n-1;
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));		//0�ŵ�Ԫδ��
	HuffmanTree p;
	for(p=HT+1,i=1;i<=n;++i,++p)
	{
		cout<<"��"<<i<<"���ַ�����Ȩֵ��";
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

	for(i=n+1;i<=m;++i)									//����������
	{
		Select(s1,s2);
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}

	InitIf=true;
	cout<<"��ʼ����ϣ�"<<endl;
	system("pause");
	return OK;
}

Status Encoding()			//����
{

	char ch[20],*c,co[20];
	int i,j,k;

	cout<<"���濪ʼ���룬������ԭ�ģ�"<<endl;
	cin>>setw(20)>>ch;
	cout<<"����Ϊ��  "<<endl;
	cout<<"\t";
	for(c=ch;*c!='\0';c++)
	{
		for(i=0;i<n;i++)
			if(*c==Code[i])
				break;
		for(i++,k=0,j=HT[i].parent;j!=0;i=j,j=HT[j].parent,k++)			//i++,��Code�±�ת��ΪHT�±�
			if(HT[j].lchild==i)
				co[k]='0';
			else
				co[k]='1';
		for(k--;k>=0;k--)
		cout<<co[k];
	}
	cout<<endl;
	cout<<"���������"<<endl;
	system("pause");		
	return OK;
}

Status Decoding()		//����
{
	int m;
	m=2*n-1;
	char ch[100],*c;

	cout<<"���濪ʼ���룬���������ģ�"<<endl;
	cin>>setw(100)>>ch;
	cout<<"ԭ��Ϊ��  "<<endl;
	cout<<"\t";
	for(c=ch;*c!='\0';c++)
	{
		if(*c=='0')
			m=HT[m].lchild;
		else
			m=HT[m].rchild;

		if(!HT[m].lchild)
		{
			switch(m)
			{
				case 1 :
					cout<<Code[0];
					break;
				case 2 :
					cout<<Code[1];
					break;
				case 3 :
					cout<<Code[2];
					break;
				case 4 :
					cout<<Code[3];
					break;
				case 5 :
					cout<<Code[4];
					break;
				case 6 :
					cout<<Code[5];
					break;
				case 7 :
					cout<<Code[6];
					break;
				case 8 :
					cout<<Code[7];
					break;
				case 9 :
					cout<<Code[8];
					break;
				case 10 :
					cout<<Code[9];
					break;
				default :return ERROR;
			}
			m=2*n-1;
		}
	}

	cout<<endl;
	cout<<"���������"<<endl;
	system("pause");
	return OK;
}


Status PrintHT(int root)			//��ӡ��������
{
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

Status PreInit()										//Ԥ����
{	
	Code[0]='A';
	Code[1]='B';
	Code[2]='C';
	Code[3]='D';
	n=4;
	HT=(HuffmanTree)malloc(8*sizeof(HTNode));
	HT[1].weight=5;
	HT[1].parent=5;
	HT[1].lchild=0;
	HT[1].rchild=0;
	HT[2].weight=7;
	HT[2].parent=5;
	HT[2].lchild=0;
	HT[2].rchild=0;
	HT[3].weight=6;
	HT[3].parent=6;
	HT[3].lchild=0;
	HT[3].rchild=0;
	HT[4].weight=8;
	HT[4].parent=6;
	HT[4].lchild=0;
	HT[4].rchild=0;
	HT[5].weight=12;
	HT[5].parent=7;
	HT[5].lchild=1;
	HT[5].rchild=2;
	HT[6].weight=14;
	HT[6].parent=7;
	HT[6].lchild=3;
	HT[6].rchild=4;
	HT[7].weight=26;
	HT[7].parent=0;
	HT[7].lchild=5;
	HT[7].rchild=6;

	return OK;

}
void main()
{
	char c;
	InitIf=false;
	PreInit();

	while(1)
	{
		system("cls");
		cout<<"\t\t\t��������/������"<<endl;									//ѡ��˵� ��ҳ
		cout<<"\t\tI: ��ʼ��"<<endl
			<<"\t\tE: ����"<<endl
			<<"\t\tD: ����"<<endl
			<<"\t\tT: ��ӡ��������"<<endl
			<<"\t\tQ: �˳�"<<endl;
		if(InitIf==false)
			cout<<"˵�����������г�ʼ����ϵͳ������Ĭ�ϴ��룬ֱ�������³�ʼ�������ɴ��븲�ǡ�"<<endl;
		cout<<"\t���������ѡ��(I,E,D,T,Q):";
		cin>>c;
		while(c!='i'&&c!='e'&&c!='d'&&c!='t'&&c!='q'&&c!='I'&&c!='E'&&c!='D'&&c!='T'&&c!='Q')
		{
			cout<<"������I,E,D,T,Q�е�һ����ĸ�����ִ�Сд��:";
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
					cout<<"��ӡ������"<<endl;
					system("pause");
					break;
			case 'q' :
			case 'Q' :cout<<"\t\tллʹ�ã�"<<endl;
					system("pause");
					exit(0);
			default:cout<<"����";
					exit(0);
		}
	}
}
		
