//040630416������
//��Fleury�㷨��ŷ����·

#include <iostream.h>
#include <stdlib.h>

#define maxV 20				//���20����
#define lx 1  				//����ͼ�����ͣ�1Ϊ����ͼ��0Ϊ����ͼ

int matrix[maxV][maxV];		//����ͼ��
int ma[maxV][maxV];			//����������ʱ�ĸ�������
int mb[maxV][maxV];

void getMatrix(int &v,int &e)						//����ͼ�Σ����ض�����������
{
	cout<<"������ͼ�εĶ�������";
	cin>>v;
	cout<<"������ͼ�εı�����";
	cin>>e;
	int i,j;
	cout<<endl<<"����������������ߣ�"<<endl;
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
			cout<<"�˱�������Ч�����������룡"<<endl;
	}
}

void multiMatrix(int v)	//����˷�������mb����matrix��ֵ��mb
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

bool isBridge(int vi ,int vj,int v)				//�ж�Eij�Ƿ�Ϊ��,vΪ������
{
	matrix[vi][vj]=0;//ȥ�����жϵı�
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

			

	if(mb[vi][vj]==0)		//�жϷ���
	{
		matrix[vi][vj]=1; //��ԭ
		if(lx)
			matrix[vj][vi]=1;
	return true;
	}
	matrix[vi][vj]=1; //��ԭ
	if(lx)
		matrix[vj][vi]=1;
	return false;
}

void main()								//������
{

	cout<<endl;
	cout<<"\t   �����������٣����������������٣�����������   "<<endl;
	cout<<"\t���������٣����٣����������٣��٣���������   "<<endl;
	cout<<"\t�����������٣����٣��������٣����٣�������   "<<endl;
	cout<<"\t�������������٣����٣����٣��٣��٣������� .   "<<endl;
	cout<<"\t�����������٣����������������� �٣�������   "<<endl;
	cout<<"\t�������٣��������������������������٣�����   "<<endl;
	cout<<"\t�����٣������������������������������٣���   "<<endl;
	cout<<"\t���٣����������������������������������٣�   "<<endl;
	cout<<"\t�٣���������������������������������������   "<<endl;
	cout<<"\t�٣���������������������������������������   "<<endl;
	cout<<"\t�٣����������ɣ��������������ɣ�����������   "<<endl;
	cout<<"\t�٣� �������������������������������� ����   "<<endl;
	cout<<"\t�٣� �������򣮣�����u���������򣮣�������   "<<endl;
	cout<<"\t���٣����������������������������������٣�   "<<endl;
	cout<<"\t�����ٺ٣��������������������������ٺ٣���.   "<<endl;
	cout<<"\t���������٣��٣��٣��٣��٣��٣��٣��� "<<endl<<endl;
	cout<<"\t         ��ӭʹ�� ��Fleury�㷨��ŷ����· "<<endl;
	cout<<"\t                            By ������ 040630416"<<endl;
	system("pause");
	system("cls");
	cout<<"\t ��Fleury�㷨��ŷ����·   By ������ 040630416"<<endl<<endl;;

	int numV;		//��¼������
	int numE;		//��¼����
	getMatrix(numV,numE);

	int euler[maxV];		//��¼ŷ����·		
	euler[0]=0;        //��ʼ��V0
	int i;
	int j;
	int k;
	for(i=0,j=0,k=0;i<numE;i++)				//�㷨����
	{
		j=0;
		while(j<numV&&(matrix[euler[i]][j]==0))
			j++;
		if(j==numV)
		{
			cout<<"���ź�����ͼ��û��ŷ����·��"<<endl;
			system("pause");
			exit(0);
		}
		else
		{
			k=j;
			while(k<numV&&isBridge(euler[i],k,numV))		//������һ���ڽӶ���
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

	if(euler[i]!=euler[0])//�����Ƿ�ص���㣬���ɻ�·
	{
		cout<<"���ź�����ͼ��û��ŷ����·��"<<endl;
		system("pause");
		exit(0);
	}

	cout<<endl<<endl;
	cout<<"̫���ˣ��ҵ�һ��!"<<endl;
	cout<<"ŷ����·��"
		<<(euler[0]+1);
	for(i=1;i<=numE;i++)
	{
		cout<<"��";
		cout<<(euler[i]+1);
	}

	cout<<endl<<endl;
	cout<<endl;
	cout<<"\t``�q�r���������������q�r�����q�r   "<<endl;
	cout<<"\t���������������������������������r   "<<endl;
	cout<<"\t�q�ةء��������������ةبr�������s   "<<endl;
	cout<<"\t���������������������������������q�����������r"<<endl;   
	cout<<"\t����������������������������������ллʹ��!!��   "<<endl;
	cout<<"\t�����񡡡������������񡡩����q�r��������^^����   "<<endl;
	cout<<"\t���𡡡��t�ЩЩШs�����𩦣�t�s�t�����������s   "<<endl;
	cout<<"\t�����������t���s������������   "<<endl;
	cout<<"\t�t�����У������С����s   "<<endl;
	cout<<"\t�� ���q�r���������q�r��������   "<<endl;
	cout<<"\t�� ���t�ء��������بs "<<endl;
	cout<<endl;
	system("pause");
	exit(0);
}




		

