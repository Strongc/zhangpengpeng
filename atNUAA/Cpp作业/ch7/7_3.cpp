/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��6��26��
��    �ڣ���7��
��    �ţ�ϰ��3
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
		cout<<"�������"
			<<i+1
			<<"��int���͵���";
		cin>>in[i];
	}

	for(i=0;i<3;i++)
	{
		cout<<"�������"
			<<i+1
			<<"��float���͵���";
		cin>>fl[i];
	}

	cout<<"int���͵����ĺ�Ϊ��"
		<<sum(in,5)<<endl;
	cout<<"float���͵����ĺ�Ϊ��"
		<<sum(fl,3)<<endl;
}


/*
�������1��int���͵���1
�������2��int���͵���2
�������3��int���͵���3
�������4��int���͵���4
�������5��int���͵���5
�������1��float���͵���1.0
�������2��float���͵���2.1
�������3��float���͵���3.2
int���͵����ĺ�Ϊ��15
float���͵����ĺ�Ϊ��6.3
Press any key to continue
*/