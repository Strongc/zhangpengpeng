/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��4��27��
			5��13������޸�
��    �ڣ���2��
��    �ţ�ϰ��9
*/

#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
#include <iomanip.h>
#include <string.h>

struct info{					//һ���˵���Ϣ
	char name[21];
	int age;
	char address[51];
	char phone[14];
	char email[31];
};

//����ԭ��

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

	cout<<"\t\tͬѧ¼";
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

//add()���Ӽ�¼
void add(fstream &file)
{
	info person;

	cout<<"\n����һ����";

	cout<<"\n������������";
	cin>>person.name;
	do{
		cout<<"\n����(0��200֮��)��";
		cin>>person.age;
	}while(person.age<0||person.age>200);
	cout<<"\n��ַ��";
	cin>>person.address;
	cout<<"\n�绰���룺";
	cin>>person.phone;
	cout<<"\n�������䣺";
	cin>>person.email;

	file.clear();
	file.seekp(0L,ios::end);
	file.write((char *)&person,sizeof(person));

	file.flush();

}

//show()��ʾ��¼
void show(fstream &file)
{
	info person;
	
	cout<<"\n��ʾ��¼";
	
	file.clear();
	file.seekg(0L,ios::beg);
	
	file.read((char *)&person,sizeof(person));
	while(!file.eof())
	{

		cout<<"\n������"<<setw(20)<<person.name;
		cout<<"\n���䣺"<<setw(3)<<person.age;
		cout<<"\n��ַ��"<<setw(50)<<person.address;
		cout<<"\n�绰���룺"<<setw(14)<<person.phone;
		cout<<"\n�������䣺"<<setw(30)<<person.email<<endl;
		file.read((char *)&person,sizeof(person));
	}
}

//edit()�޸ļ�¼

void edit(fstream &file)
{
	info person;
	long num;

	file.clear();
	cout<<"\n�����޸��ĸ��ˣ�0��ʼ����";
	cin>>num;
	file.seekg(num*sizeof(person),ios::beg);
	file.read((char*)&person,sizeof(person));

	//��ʾԭ����
		cout<<"\n������"<<setw(20)<<person.name;
		cout<<"\n���䣺"<<setw(3)<<person.age;
		cout<<"\n��ַ��"<<setw(50)<<person.address;
		cout<<"\n�绰���룺"<<setw(14)<<person.phone;
		cout<<"\n�������䣺"<<setw(30)<<person.email<<endl;
	//�޸�
	cout<<"����������Ϣ��";
	cout<<"\n������������";
	cin>>person.name;
	do{
		cout<<"\n����(0��200֮��)��";
		cin>>person.age;
	}while(person.age<0||person.age>200);
	cout<<"\n��ַ��";
	cin>>person.address;
	cout<<"\n�绰���룺";
	cin>>person.phone;
	cout<<"\n�������䣺";
	cin>>person.email;

	file.seekp(num*sizeof(person),ios::beg);
	file.write((char*)&person,sizeof(person));
	
	file.flush();
}

//search()����
void search(fstream &file)
{
	char name[21];
	info person;

	cout<<"\n����������鿴���˵����֣�";
	cin>>name;

	file.clear();
	file.seekg(0L,ios::beg);
	do  file.read((char*)&person,sizeof(person));
	while(strcmp(person.name,name)!=0);

		cout<<"\n������"<<setw(20)<<person.name;
		cout<<"\n���䣺"<<setw(3)<<person.age;
		cout<<"\n��ַ��"<<setw(50)<<person.address;
		cout<<"\n�绰���룺"<<setw(14)<<person.phone;
		cout<<"\n�������䣺"<<setw(30)<<person.email<<endl;
}

//delɾ��
void del(fstream &file)
{
	char name[21];
	info person;

	cout<<"\n����������ɾ�����˵����֣�";
	cin>>name;

	file.clear();
	file.seekg(0L,ios::beg);
	do   file.read((char*)&person,sizeof(person));
	while(strcmp(person.name,name)!=0);
	file.seekp((file.tellg()-sizeof(person)),ios::beg);		//����дָ��

	strcpy(person.name,"�����ѱ�ɾ��");
	person.age=0;
	person.address[0]='\0';
	person.phone[0]='\0';
	person.email[0]='\0';
	
	file.write((char*)&person,sizeof(person));
	file.flush();
}




/*
                ͬѧ¼
         1.add  2.show  3.edit  4.search        5.delete        6.exit
 Please enter 1 2 3 4 5 or 6
1

����һ����
������������Roc

����(0��200֮��)��20

��ַ��nuaa

�绰���룺025

�������䣺rocflyhi@126.com

         1.add  2.show  3.edit  4.search        5.delete        6.exit
 Please enter 1 2 3 4 5 or 6
1

����һ����
������������zhang

����(0��200֮��)��25

��ַ��nanjing

�绰���룺025

�������䣺zhang@sina.com

         1.add  2.show  3.edit  4.search        5.delete        6.exit
 Please enter 1 2 3 4 5 or 6
1

����һ����
������������li

����(0��200֮��)��38

��ַ��beijing

�绰���룺010

�������䣺li@yahoo.com

         1.add  2.show  3.edit  4.search        5.delete        6.exit
 Please enter 1 2 3 4 5 or 6
2

��ʾ��¼
������Roc
���䣺20
��ַ��nuaa
�绰���룺025
�������䣺rocflyhi@126.com

������zhang
���䣺25
��ַ��nanjing
�绰���룺025
�������䣺zhang@sina.com

������li
���䣺38
��ַ��beijing
�绰���룺010
�������䣺li@yahoo.com

         1.add  2.show  3.edit  4.search        5.delete        6.exit
 Please enter 1 2 3 4 5 or 6
3

�����޸��ĸ��ˣ�0��ʼ����1

������zhang
���䣺25
��ַ��nanjing
�绰���룺025
�������䣺zhang@sina.com
����������Ϣ��
������������wang

����(0��200֮��)��28

��ַ��chongqin

�绰���룺023

�������䣺wang@163.com

         1.add  2.show  3.edit  4.search        5.delete        6.exit
 Please enter 1 2 3 4 5 or 6
2

��ʾ��¼
������Roc
���䣺20
��ַ��nuaa
�绰���룺025
�������䣺rocflyhi@126.com

������wang
���䣺28
��ַ��chongqin
�绰���룺023
�������䣺wang@163.com

������li
���䣺38
��ַ��beijing
�绰���룺010
�������䣺li@yahoo.com

         1.add  2.show  3.edit  4.search        5.delete        6.exit
 Please enter 1 2 3 4 5 or 6
4

����������鿴���˵����֣�li

������li
���䣺38
��ַ��beijing
�绰���룺010
�������䣺li@yahoo.com

         1.add  2.show  3.edit  4.search        5.delete        6.exit
 Please enter 1 2 3 4 5 or 6
5

����������ɾ�����˵����֣�li

         1.add  2.show  3.edit  4.search        5.delete        6.exit
 Please enter 1 2 3 4 5 or 6
2

��ʾ��¼
������Roc
���䣺20
��ַ��nuaa
�绰���룺025
�������䣺rocflyhi@126.com

������wang
���䣺28
��ַ��chongqin
�绰���룺023
�������䣺wang@163.com

�����������ѱ�ɾ��
���䣺0
��ַ��
�绰���룺
�������䣺

         1.add  2.show  3.edit  4.search        5.delete        6.exit
 Please enter 1 2 3 4 5 or 6
6
Press any key to continue
*/