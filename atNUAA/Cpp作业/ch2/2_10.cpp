/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年5月13日
章    节：第2章
题    号：习题10
*/

#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
#include <iomanip.h>
#include <string.h>

struct info{					//一个人的信息
	char name[21];
	int age;
	char address[51];
	char phone[14];
	char email[31];
};

void main()
{	
	int num=0,agesum=0;				//agesum记录总年龄
	float aver;					//aver为平均年龄
	info person;

	fstream file("info.dat",ios::in|ios::binary);

	if(file.fail())
	{	cout<<"Fail to open file!";
		exit(0);
	};

	file.clear();
	file.seekg(0L,ios::beg);
	
	file.read((char *)&person,sizeof(person));
	while(!file.eof())
	{
		if(strcmp(person.name,"此人已被删除")){
			num++;
			agesum+=person.age;
		}
		file.read((char *)&person,sizeof(person));
	}
	
	aver=((float)agesum)/num;
	cout<<"通讯录中共有"<<num<<"个学生"<<endl;
	cout<<"他们的平均年龄为"<<aver<<"岁"<<endl;
}




/*
通讯录中共有2个学生
他们的平均年龄为24岁
Press any key to continue

//****
以下为info.dat中的数据：

显示记录
姓名：Roc
年龄：20
地址：nuaa
电话号码：025
电子邮箱：rocflyhi@126.com

姓名：wang
年龄：28
地址：chongqin
电话号码：023
电子邮箱：wang@163.com

姓名：此人已被删除
年龄：0
地址：
电话号码：
电子邮箱：
*/