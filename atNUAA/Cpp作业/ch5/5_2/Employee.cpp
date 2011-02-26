/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年6月15日
章    节：第5章
题    号：习题2
*/

#include "Employee.h"
#include <iostream.h>
#include <stdlib.h>
#include <string.h>



Employee::Employee(char *n)
{
	bool error1(char *num);					//此处必须申明
	bool error2(char *da);					//此处必须申明
	name=new char[strlen(n)+1];			//获得姓名
	memError(name);
	strcpy(name,n);

	number=new char[6];					//获得工号
	memError(number);
	cout<<"请输入"
		<<name
		<<"的工号（格式XXX-L）：";
	cin.getline(number,6);
	cin.ignore();
	while(!error1(number))
	{
		cout<<"请注意工号格式（XXX-L）：";
		cin.getline(number,6);
		cin.ignore();
	}

	date=new char[11];			//获得受雇日期
	memError(date);
	cout<<"请输入"
		<<name
		<<"的受雇日期（格式YYYY/MM/DD）：";
	cin.getline(date,11);
	cin.ignore();
	while(!error2(date))
	{
		cout<<"请注意日期格式（YYYY/MM/DD）：";
		cin.getline(date,11);
		cin.ignore();
	}
}

void Employee::memError(char *p)				//分配内存错误判断
{
	if(p==NULL)
	{
		cout<<"分配内存失败\n";
		exit(0);
	}
}

bool error1(char *num)					//编号输入有效性检验
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
bool error2(char *da)					//日期输入有效性检验
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
