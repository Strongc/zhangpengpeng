/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年6月15日
章    节：第5章
题    号：习题6
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
		cout<<"分配内存失败！";
		exit(0);
	}
	strcpy(name,ch);
}

void StudentInfo::setNumber()
{
	cin.getline(number,10);					//只有9位
}

void StudentInfo::setMajor()
{
	cin.getline(major,30);	
}
