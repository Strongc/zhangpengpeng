/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年4月13日
章    节：第1章
题    号：习题9
*/

#include <iostream.h>
float mid(int *,int);

void main()
{
	int numbers[100],
		num=0,i;		//num个数,
	cout<<"你想输入几个整数？\n";
	cin>>num;
	cout<<"请输入一组整数\n";
	for(i=0;i<num;i++)
		cin>>numbers[i];
	cout<<"中值是"
		<<mid(numbers,num)<<endl;
}

float mid (int *p,int n)
{
	int i,j,x;  //x为中介
	for(i=0;i<n;i++)
		for(j=i;j<n;j++)
			if(*(p+i)>*(p+j))
			{x=*(p+i);
			 *(p+i)=*(p+j);
			 *(p+j)=x;
			}
	if(n%2==1)		//奇数
		return *(p+(n-1)/2);
	else			//偶数
		return (*(p+n/2-1)+*(p+n/2))/2.0;

}