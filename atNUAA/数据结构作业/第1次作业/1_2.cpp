/*
040630416	������
��һ����ҵ���ڶ���
ʵ������һԪ����ʽ����ӡ���������
*/


#include "1_2.h"

void main()
{
	int num;
	LinkList A,B,C;

	cout<<"���洴������һԪ����ʽ��������֤��Ӻ����������������˺�����"<<endl;
	cout<<"��һ������ʽ��������ʽ��";
	cin>>num;
	CreatPolyn(A,num);
	cout<<endl<<"�ڶ�������ʽ��������ʽ��";
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
���н��
���洴������һԪ����ʽ��������֤��Ӻ����������������˺�����
��һ������ʽ��������ʽ��2
������ϵ����1
   ������ָ����2

������ϵ����2
   ������ָ����3


�ڶ�������ʽ��������ʽ��3
������ϵ����-1
   ������ָ����1

������ϵ����4
   ������ָ����2

������ϵ����-2
   ������ָ����3


-1x1+5x2

1x1-3x2+4x3

-1x3+2x4+6x5-4x6
Press any key to continue
*/