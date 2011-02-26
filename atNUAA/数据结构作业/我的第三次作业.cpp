/*
	������ 040630416
��������ҵ
��������/������
Dec 21 2007 Succeed to Compile with Visual C++ 2008
*/

#include <stdlib.h>
#include <iostream>

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
	std::cout<<"�������±������ַ��ĸ�����";
	std::cin>>n;

	int m,i,s1,s2;
	if(n<=1)
		return ERROR;
	m=2*n-1;
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));		//0�ŵ�Ԫδ��
	HuffmanTree p;
	for(p=HT+1,i=1;i<=n;++i,++p)
	{
		std::cout<<"��"<<i<<"���ַ�����Ȩֵ��";
		std::cin>>Code[i-1];
		std::cin>>(*p).weight;
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
	std::cout<<"��ʼ����ϣ�"<<std::endl;
	system("pause");
	return OK;
}

Status Encoding()			//����
{

	char ch[20],*c,co[20];
	int i,j,k;

	std::cout<<"���濪ʼ���룬������ԭ�ģ�"<<std::endl;
	std::cin>>ch;
	std::cout<<"����Ϊ��  "<<std::endl;
	std::cout<<"\t";
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
		std::cout<<co[k];
	}
	std::cout<<std::endl;
	std::cout<<"���������"<<std::endl;
	system("pause");		
	return OK;
}

Status Decoding()		//����
{
	int m;
	m=2*n-1;
	char ch[100],*c;

	std::cout<<"���濪ʼ���룬���������ģ�"<<std::endl;
	std::cin>>ch;
	std::cout<<"ԭ��Ϊ��  "<<std::endl;
	std::cout<<"\t";
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
					std::cout<<Code[0];
					break;
				case 2 :
					std::cout<<Code[1];
					break;
				case 3 :
					std::cout<<Code[2];
					break;
				case 4 :
					std::cout<<Code[3];
					break;
				case 5 :
					std::cout<<Code[4];
					break;
				case 6 :
					std::cout<<Code[5];
					break;
				case 7 :
					std::cout<<Code[6];
					break;
				case 8 :
					std::cout<<Code[7];
					break;
				case 9 :
					std::cout<<Code[8];
					break;
				case 10 :
					std::cout<<Code[9];
					break;
				default :return ERROR;
			}
			m=2*n-1;
		}
	}

	std::cout<<std::endl;
	std::cout<<"���������"<<std::endl;
	system("pause");
	return OK;
}


Status PrintHT(int root)			//��ӡ��������
{
	position++;
	for(int i=0;i<position;i++)
	std::cout<<'\t';
	std::cout<<HT[root].weight;
	if(HT[root].lchild==0)
	{
		std::cout<<'('<<Code[root-1]<<')'<<std::endl;
	}
	else
	{
		std::cout<<std::endl;
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
		std::cout<<"\t\t\t��������/������"<<std::endl;									//ѡ��˵� ��ҳ
		std::cout<<"\t\tI: ��ʼ��"<<std::endl
			<<"\t\tE: ����"<<std::endl
			<<"\t\tD: ����"<<std::endl
			<<"\t\tT: ��ӡ��������"<<std::endl
			<<"\t\tQ: �˳�"<<std::endl;
		if(InitIf==false)
			std::cout<<"˵�����������г�ʼ����ϵͳ������Ĭ�ϴ��룬ֱ�������³�ʼ�������ɴ��븲�ǡ�"<<std::endl;
		std::cout<<"\t���������ѡ��(I,E,D,T,Q):";
		std::cin>>c;
		while(c!='i'&&c!='e'&&c!='d'&&c!='t'&&c!='q'&&c!='I'&&c!='E'&&c!='D'&&c!='T'&&c!='Q')
		{
			std::cout<<"������I,E,D,T,Q�е�һ����ĸ�����ִ�Сд��:";
			std::cin>>c;
		}
		std::cout<<std::endl;
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
					std::cout<<"��ӡ������"<<std::endl;
					system("pause");
					break;
			case 'q' :
			case 'Q' :std::cout<<"\t\tллʹ�ã�"<<std::endl;
					system("pause");
					exit(0);
			default:std::cout<<"����";
					exit(0);
		}
	}
}
		
