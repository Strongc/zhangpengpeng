/*
    C++�γ����
�������ߣ�������
ѧ    �ţ�040630416
*/
#include "Sale.h"
#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#include <fstream.h>
#include <iomanip.h>

int showMainmenu();					//��������
void showmsg();
int ensurePosi(int );		//��֤�Ǹ���
float ensurePosi(float );	//��֤�Ǹ���
void fileopen(fstream &);
Sale *newSale();
BookData *newBookData();

#include "cash.h"					//�Ӻ���
#include "stackmgr.h"
#include "reports.h"


void main()	
{
	cout.precision(2);		//���þ���
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


//����������ʵ��

int showMainmenu()
{
	int choice;
	system("cls");				//����

	cout<<"	 			 ���ͼ�����ϵͳ						\n"
		<<"	 				 ���˵�								\n"
		<<"	 	 1. ����ģ��									\n"
		<<"	 	 2. ������ģ��								\n"
		<<"		 3. ����ģ��									\n"
		<<"		 4. �˳�ϵͳ									\n"
		<<"														\n"
		<<"			  ����ѡ��								\n"
		<<"			  ������1��4֮�����:";
	cin>>choice;		//Bug:����������ĸ��������ѭ����why?
	cin.clear();		//�����������bug
	cin.ignore();
	while(choice<1||choice>4)
	{
		cout<<"			  ������1��4֮�����:";
		cin>>choice;
		cin.clear();
		cin.ignore();
	}
	return choice;
}

void showmsg()
{
	system("cls");
	cout<<"	 			 ���ͼ�����ϵͳ						\n"
		<<"	 													\n"
		<<"	 			�Ͼ����պ����ѧ						\n"
		<<"	 			��Ϣ��ѧ�뼼��ѧԺ						\n"
		<<"		 		   ѧ�ţ�040630416						\n"
		<<"				   ������������							\n"
		<<"				   ָ����ʦ��Ƥ�³�						\n"
		<<"														\n"<<endl;
	system("pause");

}

int ensurePosi(int in)
{
	int temp=in;
	while(temp<0)
	{
		cout<<"������һ���Ǹ�����";
		cin>>temp;
	}
	return temp;
}
float ensurePosi(float fl)
{
	float temp=fl;
	while(temp<0)
	{
		cout<<"������һ���Ǹ�����";
		cin>>temp;

	}
	return temp;
}



void fileopen(fstream &file)			//���Ӻ����У������쳣����
{
	file.open("Info.dat",ios::out|ios::in|ios::binary);
	if(!file)
		throw "���ļ�ʧ�ܣ�";
}

Sale *newSale()					//���Ӻ����У������쳣����
{
	Sale *pr;
	pr=new Sale;
	if(pr==NULL)
		throw "�����ڴ�ʧ�ܣ�";
	return pr;
}
BookData *newBookData()			//���Ӻ����У������쳣����
{
	BookData *pr;
	pr=new BookData;
	if(pr==NULL)
		throw "�����ڴ�ʧ�ܣ�";
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