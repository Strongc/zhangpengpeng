/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��6��15��
��    �ڣ���5��
��    �ţ�ϰ��2
*/

#include "Employee.h"
#include <iostream.h>
#include <stdlib.h>
#include <string.h>



Employee::Employee(char *n)
{
	bool error1(char *num);					//�˴���������
	bool error2(char *da);					//�˴���������
	name=new char[strlen(n)+1];			//�������
	memError(name);
	strcpy(name,n);

	number=new char[6];					//��ù���
	memError(number);
	cout<<"������"
		<<name
		<<"�Ĺ��ţ���ʽXXX-L����";
	cin.getline(number,6);
	cin.ignore();
	while(!error1(number))
	{
		cout<<"��ע�⹤�Ÿ�ʽ��XXX-L����";
		cin.getline(number,6);
		cin.ignore();
	}

	date=new char[11];			//����ܹ�����
	memError(date);
	cout<<"������"
		<<name
		<<"���ܹ����ڣ���ʽYYYY/MM/DD����";
	cin.getline(date,11);
	cin.ignore();
	while(!error2(date))
	{
		cout<<"��ע�����ڸ�ʽ��YYYY/MM/DD����";
		cin.getline(date,11);
		cin.ignore();
	}
}

void Employee::memError(char *p)				//�����ڴ�����ж�
{
	if(p==NULL)
	{
		cout<<"�����ڴ�ʧ��\n";
		exit(0);
	}
}

bool error1(char *num)					//���������Ч�Լ���
{
	int i;
	bool b=true;

	if(num[3]!='-')
		b=false;
	else
		if(num[4]<'A'||num[4]>'z')
			b=false;
		else
			for(i=0;i<3;i++)
				if(num[i]<'0'||num[i]>'9')
				{
					b=false;
					break;
				}
	return b;
}
bool error2(char *da)					//����������Ч�Լ���
{
	int i;
	bool b=true;

	if(da[4]!='/'||da[7]!='/')
		b=false;
	else
		for(i=0;i<10;i++)
			if(i!=4&&i!=7)
				if(da[i]<'0'||da[i]>'9')
				{
					b=false;
					break;
				}
	return b;
}
