/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��6��15��
��    �ڣ���5��
��    �ţ�ϰ��6
*/

#include "Grades.h"
#include <iostream.h>


void Grades::setScore()
{
	int i;
	for(i=0;i<6;i++)
	{
		cout<<"�������"
			<<i+1
			<<"�ŵĳɼ���";
		cin>>score[i];
		if(score[i]<0||score[i]>100)
		do{
			cout<<"�ɼ�Ӧ����0��100֮��:";
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
		cout<<"��"
			<<i+1
			<<"�ŵĳɼ�Ϊ"
			<<score[i]<<endl;
	}
}			