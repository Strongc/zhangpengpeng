/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年4月13日
章    节：第1章
题    号：习题3
*/

#include <iostream.h>
 
void main()
{
	char ch[101];
	int i;		//i用来记数

	cout<<"请输入一串字符\n";
	cin>>ch;
	for(i=0;i<101;i++)
	{	if(ch[i]=='\0')
			break;
		else
			if('a'<=ch[i]&&ch[i]<='z')
				ch[i]=ch[i]-'a'+'A';
	}
	cout<<"答案是："
		<<ch<<endl;

}