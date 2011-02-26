/*
    C++课程设计
程序作者：张鹏鹏
学    号：040630416
*/
#include "Sale.h"
#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#include <fstream.h>
#include <iomanip.h>

int showMainmenu();					//函数申明
void showmsg();
int ensurePosi(int );		//保证非负数
float ensurePosi(float );	//保证非负数
void fileopen(fstream &);
Sale *newSale();
BookData *newBookData();

#include "cash.h"					//子函数
#include "stackmgr.h"
#include "reports.h"


void main()	
{
	cout.precision(2);		//设置精度
	cout.setf(ios::fixed|ios::left);
	while(1)
	{
		switch(showMainmenu())
			{
				case 1 :cash();
						break;
				case 2 :stackmgr();
						break;
				case 3 :reports();
						break;
				case 4 :showmsg();
						exit(0);
						break;
			}
	}

}


//申明函数的实现

int showMainmenu()
{
	int choice;
	system("cls");				//清屏

	cout<<"	 			 书店图书管理系统						\n"
		<<"	 				 主菜单								\n"
		<<"	 	 1. 收银模块									\n"
		<<"	 	 2. 书库管理模块								\n"
		<<"		 3. 报表模块									\n"
		<<"		 4. 退出系统									\n"
		<<"														\n"
		<<"			  输入选择：								\n"
		<<"			  请输入1～4之间的数:";
	cin>>choice;		//Bug:不能输入字母，否则死循环，why?
	cin.clear();		//处理上面这个bug
	cin.ignore();
	while(choice<1||choice>4)
	{
		cout<<"			  请输入1～4之间的数:";
		cin>>choice;
		cin.clear();
		cin.ignore();
	}
	return choice;
}

void showmsg()
{
	system("cls");
	cout<<"	 			 书店图书管理系统						\n"
		<<"	 													\n"
		<<"	 			南京航空航天大学						\n"
		<<"	 			信息科学与技术学院						\n"
		<<"		 		   学号：040630416						\n"
		<<"				   姓名：张鹏鹏							\n"
		<<"				   指导老师：皮德常						\n"
		<<"														\n"<<endl;
	system("pause");

}

int ensurePosi(int in)
{
	int temp=in;
	while(temp<0)
	{
		cout<<"请输入一个非负数：";
		cin>>temp;
	}
	return temp;
}
float ensurePosi(float fl)
{
	float temp=fl;
	while(temp<0)
	{
		cout<<"请输入一个非负数：";
		cin>>temp;

	}
	return temp;
}



void fileopen(fstream &file)			//在子函数中，都有异常处理
{
	file.open("Info.dat",ios::out|ios::in|ios::binary);
	if(!file)
		throw "打开文件失败！";
}

Sale *newSale()					//在子函数中，都有异常处理
{
	Sale *pr;
	pr=new Sale;
	if(pr==NULL)
		throw "分配内存失败！";
	return pr;
}
BookData *newBookData()			//在子函数中，都有异常处理
{
	BookData *pr;
	pr=new BookData;
	if(pr==NULL)
		throw "分配内存失败！";
	return pr;
}


/*
123456
147852
369852
145632
123654
369741
987456
*/