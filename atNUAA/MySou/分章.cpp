#include <iostream.h>
#include <fstream>
#include <string>
using namespace std;

void main()
{
	ifstream infile;
	ofstream outfile;
	int i=0,j,num1,num2,num3;
	char name[]="000.txt";
	string data;

	infile.open("x.txt");		//��Դ�ļ�
	if(!infile)
	{
		cout<<"Open failed!";
		exit(0);
	}
	outfile.open("000.txt");			//�������ļ�
	if(!outfile)
	{
		cout<<"Open failed!";
		exit(0);
	}

	while(!infile.eof())		//��ʼ����
	{		
		infile>>data;
		num1=data.find("��");
		num3=data.find("��");
		num2=data.find("��");
		if(num1!=0||num2<0||num3>0||(num2-num1)>15||(num2-num1)<0)
			outfile<<data;
		else
		{
			i++;
			j=i;						//���������ļ�������
			if(j<10)					
				name[2]='0'+j;
			else
				if(j<100)
				{	
					name[2]='0'+j%10;
					name[1]='0'+j/10;
				}
				else
				{
					name[2]='0'+j%10;
					j=j/10;
					name[1]='0'+j%10;
					name[0]='0'+j/10;
				}
			
			outfile.close();
			outfile.open(name);			//������һ���ļ�
			if(!outfile)
			{
				cout<<"Open failed!";
				exit(0);
			}
			cout<<name<<"\t";
			outfile<<data<<endl;
		}
	}
	outfile.close();			//�ر����һ���ļ�
	infile.close();

	cout<<endl;				//���������Ķ���
	system("pause");
}