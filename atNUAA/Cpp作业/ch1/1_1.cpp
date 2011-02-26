/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年4月6日
章    节：第1章
题    号：习题1
*/

#include <iostream.h>

void main()
{
	int num[10],i,
		max,min,
		maxNum=1,minNum=1;
	cout<<"Please enter ten numbers"<<"\n";
	for(i=0;i<10;i++)
		cin>>num[i];
	max=num[0];
	min=num[0];
	for(i=1;i<10;i++)
		{	if(max<num[i])
				{	max=num[i];
					maxNum=1;
				}
			else if(max==num[i])
					maxNum++;
			if(min>num[i])
				{	min=num[i];
					minNum=1;
			}
			else if(min==num[i])
					minNum++;
		}
	cout<<"The max number is "
		<<max
		<<"最大值共有"
		<<maxNum
		<<"个。"<<endl;
	cout<<"the min number is "
		<<min
		<<"最小值共有"
		<<minNum
		<<"个。";

}