/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年6月1日
章    节：第4章
题    号：习题2
*/

#include "timeoff.h"
#include <string.h>
#include <iostream.h>
TimeOff::TimeOff(char *na,char *wn)
{
	name=new char[strlen(na)+1];
	strcpy(name,na);
	workNum=new char[strlen(wn)+1];
	strcpy(workNum,wn);
}

void TimeOff::getmaxVa(int d)
{
	int temp;
	if(d<=3)
	 	maxVacation.getday(d);
	else 
	{
		do
		{
			cout<<"请输入一个不大于3的数：";
			cin>>temp;
		}while(temp<=3);
	 	maxVacation.getday(temp);
	}
}
