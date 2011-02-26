/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年6月26日
章    节：第7章
题    号：习题1
*/
#include <iostream.h>
template <class T>
T min(T a,T b)
{
	if(a<b)
		return a;
	else
		return b;
}

template <class T>
T max(T a,T b)
{
	if(a>b)
		return a;
	else
		return b;
}

void main()
{
	int a,b;
	float c,d;
	cout<<"请输入两个int类型的数：";
	cin>>a;
	cin>>b;
	cout<<"其中较大的数为："<<max(a,b)<<"  ";
	cout<<"较小的数是："<<min(a,b)<<endl;

	cout<<"请输入两个float类型的数：";
	cin>>c;
	cin>>d;
	cout<<"其中较大的数为："<<max(c,d)<<"  ";
	cout<<"较小的数是："<<min(c,d)<<endl;
}


/*请输入两个int类型的数：32
23
其中较大的数为：32  较小的数是：23
请输入两个float类型的数：3.2
2.3
其中较大的数为：3.2  较小的数是：2.3
Press any key to continue
*/