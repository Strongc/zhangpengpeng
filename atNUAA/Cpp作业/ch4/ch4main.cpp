/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��6��8��
��    �ڣ���4��
��    �ţ�ϰ��3
*/

#include "timeoff.h"
#include <iostream.h>

void main()
{
	TimeOff person("ZhangSan","0406304");
	int months,i,day;			//i is used for counting,day���������������м����

	cout<<"�������Ѿ�������������";
	cin>>months;
	cout<<"�������Աÿ�����������Բ����������������";
	cin>>day;
	person.getmaxSi(day*months);
	cout<<"�������Աÿ���¿��Դ�н�ݼٵ����������";
	cin>>day;
	if(day*months<=3)
		person.getmaxVa(day*months);
	else 
	{
		person.getmaxVa(3);
		cout<<"��๫˾�涨����Ա��н�ݼ��ۼƲ��ó���24Сʱ��ϵͳ���Զ�������Ϊ3�졣"<<endl;
	}
	cout<<"������ÿ�����ڲ�֧��нˮ������£���Ա�����ݼٵ����������";
	cin>>day;
	person.getmaxUn(day*months);
	person.getsi(0);
	person.getva(0);
	person.getun(0);

	for(i=0;i<months;i++)
	{
		cout<<"�������"
			<<i+1
			<<"��"
			<<person.getname()
			<<"�������Ѿ���������������";
		cin>>day;
		person.getsi(person.putsic()+day);

		cout<<"�������"
			<<i+1
			<<"��"
			<<person.getname()
			<<"�Ѿ���н�ݼٵ�������";
		cin>>day;
		person.getva(person.putvac()+day);

		cout<<"�������"
			<<i+1
			<<"��"
			<<person.getname()
			<<"�ڲ�֧��нˮ������£��Ѿ��ݼٵ�������";
		cin>>day;
		person.getun(person.putunp()+day);
	}

	cout<<"��"
		<<months
		<<"������"
		<<person.getname()
		<<"�������Ѿ�������������Ϊ��"
		<<person.putsic()
		<<"�죬��ʣ"
		<<person.putmaxSi()-person.putsic()
		<<"��"<<endl;
	cout<<"��"
		<<months
		<<"������"
		<<person.getname()
		<<"�����ݼٵ�����Ϊ��"
		<<person.putvac()+person.putunp()
		<<"�죬��ʣ"
		<<person.putmaxVa()+person.putmaxUn()-person.putvac()-person.putunp()
		<<"��"<<endl;
}

/*
�������Ѿ�������������3
�������Աÿ�����������Բ����������������3
�������Աÿ���¿��Դ�н�ݼٵ����������2
��๫˾�涨����Ա��н�ݼ��ۼƲ��ó���24Сʱ��ϵͳ���Զ�������Ϊ3�졣
������ÿ�����ڲ�֧��нˮ������£���Ա�����ݼٵ����������2
�������1��ZhangSan�������Ѿ���������������2
�������1��ZhangSan�Ѿ���н�ݼٵ�������0
�������1��ZhangSan�ڲ�֧��нˮ������£��Ѿ��ݼٵ�������4
�������2��ZhangSan�������Ѿ���������������2
�������2��ZhangSan�Ѿ���н�ݼٵ�������1
�������2��ZhangSan�ڲ�֧��нˮ������£��Ѿ��ݼٵ�������0
�������3��ZhangSan�������Ѿ���������������2
�������3��ZhangSan�Ѿ���н�ݼٵ�������0
�������3��ZhangSan�ڲ�֧��нˮ������£��Ѿ��ݼٵ�������0
��3������ZhangSan�������Ѿ�������������Ϊ��6�죬��ʣ3��
��3������ZhangSan�����ݼٵ�����Ϊ��5�죬��ʣ4��
Press any key to continue
*/