/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年6月26日
章    节：第7章
题    号：习题3
*/

#include <iostream.h>

template <class T>
T sum(T t[],int n)
{
	T sum;
	int i;

	for(i=0,sum=0;i<n;i++)
		sum+=t[i];
	return sum;
}
void main()
{
	int in[5];
	float fl[3];
	int i;

	for(i=0;i<5;i++)
	{
		cout<<"请输入第"
			<<i+1
			<<"个int类型的数";
		cin>>in[i];
	}

	for(i=0;i<3;i++)
	{
		cout<<"请输入第"
			<<i+1
			<<"个float类型的数";
		cin>>fl[i];
	}

	cout<<"int类型的数的和为："
		<<sum(in,5)<<endl;
	cout<<"float类型的数的和为："
		<<sum(fl,3)<<endl;
}


/*
请输入第1个int类型的数1
请输入第2个int类型的数2
请输入第3个int类型的数3
请输入第4个int类型的数4
请输入第5个int类型的数5
请输入第1个float类型的数1.0
请输入第2个float类型的数2.1
请输入第3个float类型的数3.2
int类型的数的和为：15
float类型的数的和为：6.3
Press any key to continue
*/