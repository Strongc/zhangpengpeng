/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��5��13��
��    �ڣ���2��
��    �ţ�ϰ��10
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

void main()
{	
	int num=0,agesum=0;				//agesum��¼������
	float aver;					//averΪƽ������
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
		if(strcmp(person.name,"�����ѱ�ɾ��")){
			num++;
			agesum+=person.age;
		}
		file.read((char *)&person,sizeof(person));
	}
	
	aver=((float)agesum)/num;
	cout<<"ͨѶ¼�й���"<<num<<"��ѧ��"<<endl;
	cout<<"���ǵ�ƽ������Ϊ"<<aver<<"��"<<endl;
}




/*
ͨѶ¼�й���2��ѧ��
���ǵ�ƽ������Ϊ24��
Press any key to continue

//****
����Ϊinfo.dat�е����ݣ�

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
*/