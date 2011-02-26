/*
	������ 040630416
��������ҵ
��������/������
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

				//ȫ�ֱ���
char Code[10];						//�����ַ�
HuffmanTree HT;						//��������ָ��
int n;								//�����ַ��ĸ���
bool MemIf;							//�ڴ����Ƿ��й�������
bool InitIf;							//�Ƿ��ʼ����
fstream File,File2;					//ָ��ĳ���ļ�
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
															//д���ļ�
	File.open("hfmTree.dat",ios::out|ios::binary);
	if(!File)
	{
		cout<<"���ļ�hfmTree.datʧ�ܣ�";
		system("pause");
		exit(0);
	}
	File.write((char*)HT,(2*n)*sizeof(HTNode));
	File.write(Code,10*sizeof(char));
	File.write((char*)&n,sizeof(int));
	File.close();

	MemIf=true;
	InitIf=true;
	cout<<"��ʼ����ϣ�"<<endl;
	system("pause");
	return OK;
}

Status Encoding()			//����
{
	if(MemIf==false)
	{															//������������
		File.open ("hfmTree.dat",ios::in|ios::binary);
		if(!File)
		{
			cout<<"���ļ�hfmTree.datʧ�ܣ�";
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

	cout<<"���濪ʼ���룺"<<endl;
	File.open ("ToBeTran.txt",ios::in);
	if(!File)
	{
		cout<<"���ļ�ToBeTran.txtʧ�ܣ�";
		system("pause");
		exit(0);
	}
	File2.open ("CodeFile.txt",ios::out);
	if(!File2)
	{
		cout<<"���ļ�CodeFile.txtʧ�ܣ�";
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
	cout<<"����������ѱ��浽CodeFile.txt"<<endl;
	system("pause");		
	return OK;
}

Status Decoding()		//����
{
	if(MemIf==false)
	{															//������������
		File.open ("hfmTree.dat",ios::in|ios::binary);
		if(!File)
		{
			cout<<"���ļ�hfmTree.datʧ�ܣ�";
			system("pause");
			exit(0);
		}
		File.read((char*)HT,(2*n)*sizeof(HTNode));
		File.read(Code,10*sizeof(char));
		File.read((char*)&n,sizeof(int));
		File.close();
		MemIf=true;
	}
	
	cout<<"���濪ʼ���룺"<<endl;
	File.open ("TextFile.txt",ios::out);
	if(!File)
	{
		cout<<"���ļ�TextFile.txtʧ�ܣ�";
		system("pause");
		exit(0);
	}
	File2.open ("CodeFile.txt",ios::in);
	if(!File2)
	{
		cout<<"���ļ�CodeFile.txtʧ�ܣ�";
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
	cout<<"����������ѱ��浽TextFile.txt"<<endl;
	system("pause");
	return OK;
}


Status PrintHT(int root)			//��ӡ��������
{
	if(MemIf==false)
	{
																//������������
		File.open ("hfmTree.dat",ios::in|ios::binary);
		if(!File)
		{
			cout<<"���ļ�hfmTree.datʧ�ܣ�";
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
	cout<<"\n\n\t\t      ���ݽṹ�ϻ�"<<endl
		<<"\t\t ��������ҵ ��������/������"<<endl
		<<"\t\t      By ������(040630416)"<<endl;
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
		cout<<"��������/������"<<endl;									//ѡ��˵� ��ҳ
		cout<<"I:��ʼ��"<<endl
			<<"E:����"<<endl
			<<"D:����"<<endl
			<<"T:��ӡ��������"<<endl
			<<"Q:�˳�"<<endl;
		if(InitIf==false)
			cout<<"˵�����������г�ʼ����ϵͳ������hfmTree.dat�ļ��е�Ĭ�ϴ��룬\nֱ�������³�ʼ�������ɴ��븲�ǡ�"<<endl;
		cout<<"���������ѡ��(I,E,D,T,Q):";
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
			case 'Q' :EndPrint();
					exit(0);
			default:cout<<"����";
					exit(0);
		}
	}
}
		
