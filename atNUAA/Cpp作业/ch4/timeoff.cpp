/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��6��1��
��    �ڣ���4��
��    �ţ�ϰ��2
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
			cout<<"������һ��������3������";
			cin>>temp;
		}while(temp<=3);
	 	maxVacation.getday(temp);
	}
}
