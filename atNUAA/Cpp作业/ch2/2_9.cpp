/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年4月27日
			5月13日最后修改
章    节：第2章
题    号：习题9
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

//函数原型

void add(fstream &);
void show(fstream &);
void edit(fstream &);
void search(fstream &);
void del(fstream &);

void main()
{
	int choice;
	fstream people("info.dat",ios::in|ios::out|ios::binary);

	if(people.fail())
	{	cout<<"Fail to open file!";
		exit(0);
	};

	cout<<"\t\t同学录";
	cout<<setiosflags(ios::left);
	while(true)
	{
		cout<<"\n\t 1.add	2.show	3.edit	4.search	5.delete	6.exit"
			<<"\n Please enter 1 2 3 4 5 or 6"<<endl;
		cin>>choice;
		switch(choice)
		{
		case 1:add(people);
			break;
		case 2:show(people);
			break;
		case 3:edit(people);
			break;
		case 4:search(people);
			break;
		case 5:del(people);
			break;
		case 6:people.close();
			exit(0);
		}
	}
}

//add()增加记录
void add(fstream &file)
{
	info person;

	cout<<"\n增加一个人";

	cout<<"\n请输入姓名：";
	cin>>person.name;
	do{
		cout<<"\n年龄(0至200之间)：";
		cin>>person.age;
	}while(person.age<0||person.age>200);
	cout<<"\n地址：";
	cin>>person.address;
	cout<<"\n电话号码：";
	cin>>person.phone;
	cout<<"\n电子邮箱：";
	cin>>person.email;

	file.clear();
	file.seekp(0L,ios::end);
	file.write((char *)&person,sizeof(person));

	file.flush();

}

//show()显示记录
void show(fstream &file)
{
	info person;
	
	cout<<"\n显示记录";
	
	file.clear();
	file.seekg(0L,ios::beg);
	
	file.read((char *)&person,sizeof(person));
	while(!file.eof())
	{

		cout<<"\n姓名："<<setw(20)<<person.name;
		cout<<"\n年龄："<<setw(3)<<person.age;
		cout<<"\n地址："<<setw(50)<<person.address;
		cout<<"\n电话号码："<<setw(14)<<person.phone;
		cout<<"\n电子邮箱："<<setw(30)<<person.email<<endl;
		file.read((char *)&person,sizeof(person));
	}
}

//edit()修改记录

void edit(fstream &file)
{
	info person;
	long num;

	file.clear();
	cout<<"\n你想修改哪个人（0开始）：";
	cin>>num;
	file.seekg(num*sizeof(person),ios::beg);
	file.read((char*)&person,sizeof(person));

	//显示原数据
		cout<<"\n姓名："<<setw(20)<<person.name;
		cout<<"\n年龄："<<setw(3)<<person.age;
		cout<<"\n地址："<<setw(50)<<person.address;
		cout<<"\n电话号码："<<setw(14)<<person.phone;
		cout<<"\n电子邮箱："<<setw(30)<<person.email<<endl;
	//修改
	cout<<"请输入新信息：";
	cout<<"\n请输入姓名：";
	cin>>person.name;
	do{
		cout<<"\n年龄(0至200之间)：";
		cin>>person.age;
	}while(person.age<0||person.age>200);
	cout<<"\n地址：";
	cin>>person.address;
	cout<<"\n电话号码：";
	cin>>person.phone;
	cout<<"\n电子邮箱：";
	cin>>person.email;

	file.seekp(num*sizeof(person),ios::beg);
	file.write((char*)&person,sizeof(person));
	
	file.flush();
}

//search()查找
void search(fstream &file)
{
	char name[21];
	info person;

	cout<<"\n请输入你想查看的人的名字：";
	cin>>name;

	file.clear();
	file.seekg(0L,ios::beg);
	do  file.read((char*)&person,sizeof(person));
	while(strcmp(person.name,name)!=0);

		cout<<"\n姓名："<<setw(20)<<person.name;
		cout<<"\n年龄："<<setw(3)<<person.age;
		cout<<"\n地址："<<setw(50)<<person.address;
		cout<<"\n电话号码："<<setw(14)<<person.phone;
		cout<<"\n电子邮箱："<<setw(30)<<person.email<<endl;
}

//del删除
void del(fstream &file)
{
	char name[21];
	info person;

	cout<<"\n请输入你想删除的人的名字：";
	cin>>name;

	file.clear();
	file.seekg(0L,ios::beg);
	do   file.read((char*)&person,sizeof(person));
	while(strcmp(person.name,name)!=0);
	file.seekp((file.tellg()-sizeof(person)),ios::beg);		//调整写指针

	strcpy(person.name,"此人已被删除");
	person.age=0;
	person.address[0]='\0';
	person.phone[0]='\0';
	person.email[0]='\0';
	
	file.write((char*)&person,sizeof(person));
	file.flush();
}




/*
                同学录
         1.add  2.show  3.edit  4.search        5.delete        6.exit
 Please enter 1 2 3 4 5 or 6
1

增加一个人
请输入姓名：Roc

年龄(0至200之间)：20

地址：nuaa

电话号码：025

电子邮箱：rocflyhi@126.com

         1.add  2.show  3.edit  4.search        5.delete        6.exit
 Please enter 1 2 3 4 5 or 6
1

增加一个人
请输入姓名：zhang

年龄(0至200之间)：25

地址：nanjing

电话号码：025

电子邮箱：zhang@sina.com

         1.add  2.show  3.edit  4.search        5.delete        6.exit
 Please enter 1 2 3 4 5 or 6
1

增加一个人
请输入姓名：li

年龄(0至200之间)：38

地址：beijing

电话号码：010

电子邮箱：li@yahoo.com

         1.add  2.show  3.edit  4.search        5.delete        6.exit
 Please enter 1 2 3 4 5 or 6
2

显示记录
姓名：Roc
年龄：20
地址：nuaa
电话号码：025
电子邮箱：rocflyhi@126.com

姓名：zhang
年龄：25
地址：nanjing
电话号码：025
电子邮箱：zhang@sina.com

姓名：li
年龄：38
地址：beijing
电话号码：010
电子邮箱：li@yahoo.com

         1.add  2.show  3.edit  4.search        5.delete        6.exit
 Please enter 1 2 3 4 5 or 6
3

你想修改哪个人（0开始）：1

姓名：zhang
年龄：25
地址：nanjing
电话号码：025
电子邮箱：zhang@sina.com
请输入新信息：
请输入姓名：wang

年龄(0至200之间)：28

地址：chongqin

电话号码：023

电子邮箱：wang@163.com

         1.add  2.show  3.edit  4.search        5.delete        6.exit
 Please enter 1 2 3 4 5 or 6
2

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

姓名：li
年龄：38
地址：beijing
电话号码：010
电子邮箱：li@yahoo.com

         1.add  2.show  3.edit  4.search        5.delete        6.exit
 Please enter 1 2 3 4 5 or 6
4

请输入你想查看的人的名字：li

姓名：li
年龄：38
地址：beijing
电话号码：010
电子邮箱：li@yahoo.com

         1.add  2.show  3.edit  4.search        5.delete        6.exit
 Please enter 1 2 3 4 5 or 6
5

请输入你想删除的人的名字：li

         1.add  2.show  3.edit  4.search        5.delete        6.exit
 Please enter 1 2 3 4 5 or 6
2

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

         1.add  2.show  3.edit  4.search        5.delete        6.exit
 Please enter 1 2 3 4 5 or 6
6
Press any key to continue
*/