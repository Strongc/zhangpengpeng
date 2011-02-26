/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年6月15日
章    节：第5章
题    号：习题6
*/

#include "Grades.h"
#include <iostream.h>


void Grades::setScore()
{
	int i;
	for(i=0;i<6;i++)
	{
		cout<<"请输入第"
			<<i+1
			<<"门的成绩：";
		cin>>score[i];
		if(score[i]<0||score[i]>100)
		do{
			cout<<"成绩应该在0至100之间:";
			cin>>score[i];
		}while(score[i]>100&&score[i]<0);
	}
	setAver();
}

void Grades::setAver()
{
	int i;
	float sum=0;
	for(i=0;i<6;i++)
		sum+=score[i];
	average=sum/6;
}

void Grades::getScore()
{
	int i;
	for(i=0;i<6;i++)
	{
		cout<<"第"
			<<i+1
			<<"门的成绩为"
			<<score[i]<<endl;
	}
}			