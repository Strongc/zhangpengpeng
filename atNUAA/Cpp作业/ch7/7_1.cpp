/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��6��26��
��    �ڣ���7��
��    �ţ�ϰ��1
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
	cout<<"����������int���͵�����";
	cin>>a;
	cin>>b;
	cout<<"���нϴ����Ϊ��"<<max(a,b)<<"  ";
	cout<<"��С�����ǣ�"<<min(a,b)<<endl;

	cout<<"����������float���͵�����";
	cin>>c;
	cin>>d;
	cout<<"���нϴ����Ϊ��"<<max(c,d)<<"  ";
	cout<<"��С�����ǣ�"<<min(c,d)<<endl;
}


/*����������int���͵�����32
23
���нϴ����Ϊ��32  ��С�����ǣ�23
����������float���͵�����3.2
2.3
���нϴ����Ϊ��3.2  ��С�����ǣ�2.3
Press any key to continue
*/