/*
040630416	张鹏鹏
第一次作业，第二题
实现两个一元多项式的相加、相减、相乘
*/


#include "1_2.h"

void main()
{
	int num;
	LinkList A,B,C;

	cout<<"下面创建两个一元多项式，依次验证相加函数、相减函数、相乘函数。"<<endl;
	cout<<"第一个多项式，几个项式？";
	cin>>num;
	CreatPolyn(A,num);
	cout<<endl<<"第二个多项式，几个项式？";
	cin>>num;
	CreatPolyn(B,num);

	LinkList La,Lb;
	CopyPolyn(La,A);
	CopyPolyn(Lb,B);
	AddPolyn(La,Lb,C);
	PrintPolyn(C);
	DelPolyn(C);

	CopyPolyn(La,A);
	CopyPolyn(Lb,B);
	SubtractPolyn(La,Lb,C);
	PrintPolyn(C);
	DelPolyn(C);

	CopyPolyn(La,A);
	CopyPolyn(Lb,B);
	MultiplyPolyn(La,Lb,C);
	PrintPolyn(C);
	DelPolyn(C);

}

/*
运行结果
下面创建两个一元多项式，依次验证相加函数、相减函数、相乘函数。
第一个多项式，几个项式？2
请输入系数：1
   请输入指数：2

请输入系数：2
   请输入指数：3


第二个多项式，几个项式？3
请输入系数：-1
   请输入指数：1

请输入系数：4
   请输入指数：2

请输入系数：-2
   请输入指数：3


-1x1+5x2

1x1-3x2+4x3

-1x3+2x4+6x5-4x6
Press any key to continue
*/