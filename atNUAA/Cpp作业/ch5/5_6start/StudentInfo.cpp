/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��6��15��
��    �ڣ���5��
��    �ţ�ϰ��6
*/

#include "StudentInfo.h"
#include <iostream.h>
#include <string.h>
#include <stdlib.h>

StudentInfo::StudentInfo(char *ch)
{
	name=new char[strlen(ch)+1];
	if(name==NULL)
	{
		cout<<"�����ڴ�ʧ�ܣ�";
		exit(0);
	}
	strcpy(name,ch);
}

void StudentInfo::setNumber()
{
	cin.getline(number,10);					//ֻ��9λ
}

void StudentInfo::setMajor()
{
	cin.getline(major,30);	
}
