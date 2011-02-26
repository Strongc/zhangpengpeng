/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年4月6日
章    节：第1章
题    号：习题2
*/

#include <iostream.h>

void main()
{
	float rain[12],r,
		sum,ave;
	int i,
		max,min;

	cout<<"请输入十二个月的降雨量"<<endl;
	for(i=0;i<12;i++)
	{
		cin>>r;
		if(r<0)
		{	
			cout<<"请输入正数";
			i--;
		}
		else  rain[i]=r;
	}
	max=0;
	min=0;
	sum=rain[0];
	for(i=1;i<12;i++)
	{
		sum=sum+rain[i];
		if(rain[max]<rain[i])
			max=i;
		if(rain[min]>rain[i])
			min=i;
	}
	ave=sum/12;
	
	cout<<"一年的总降雨量是"
		<<sum<<endl;
	cout<<"平均每月的降雨量是"
		<<ave<<endl;
	cout<<max+1<<"月的降雨量最大"<<endl;
	cout<<min+1<<"月的降雨量最小"<<endl;
}