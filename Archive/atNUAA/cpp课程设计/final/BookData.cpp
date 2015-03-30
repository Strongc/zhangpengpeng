/*
    C++课程设计
程序作者：张鹏鹏
学    号：040630416
*/

#include "BookData.h"
#include <iostream.h>

bool BookData::error(char *da)
{
	int i;
	bool b=true;

	if(da[4]!='-'||da[7]!='-')
		b=false;
	else
		for(i=0;i<10;i++)
			if(i!=4&&i!=7)
				if(da[i]<'0'||da[i]>'9')
				{
					b=false;
					break;
				}
	return b;
}

int BookData::ensurePosi(int in)
{
	int temp=in;
	while(temp<0)
	{
		cout<<"请输入一个正数：";
		cin>>temp;
	}
	return temp;
}
float BookData::ensurePosi(float fl)
{
	float temp=fl;
	while(temp<0)
	{
		cout<<"请输入一个正数：";
		cin>>temp;
	}
	return temp;
}

void BookData::setDateAdded(char *date)
{
	strcpy(dateAdded,date);
	while(!error(dateAdded))
	{
		cout<<"请注意日期格式（YYYY-MM-DD）：";
		cin.getline(dateAdded,11);
	}
}

bool BookData::isEmpty()
{
	char *tit=getTitle();
	if(*tit=='\0')
		return true;
	else 
		return false;
}
void BookData::removeBook()
{
	setTitle("");
}