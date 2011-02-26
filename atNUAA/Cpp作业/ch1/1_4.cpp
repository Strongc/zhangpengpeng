/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年4月13日
章    节：第1章
题    号：习题4
*/

#include<iostream.h>
void change(char *ch);

void main()
{
	char str[101];

	cout<<"请输入一句话\n";
	cin.getline(str,101);
	change(str);			//转换
	cout<<"转换后为："
		<<str<<endl;
}

void change(char *ch)
{
	char *cp;
	if('a'<=*ch&&*ch<='z')			//处理第一个字母
		*ch=*ch-'a'+'A';
	cp=ch+1;
	while(*cp!='\0')
	{
		if(*cp>='a'&&*cp<='z'&&*(cp-1)==' ')
			*cp=*cp-'a'+'A';
		cp++;
	}
}