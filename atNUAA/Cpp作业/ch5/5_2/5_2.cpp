/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��6��15��
��    �ڣ���5��
��    �ţ�ϰ��2
*/
#include "EmployeePay.h"
#include  <iostream.h>

void main()
{
	EmployeePay person("Jack");
	float pay;
	int department;

	cout<<"������"
		<<person.getName()
		<<"���¹��ʣ�";
	cin>>pay;
	cout<<"������"
		<<person.getName()
		<<"�Ĳ��źţ�";
	cin>>department;
	person.setpay(pay,department);
	cout<<"��Ա���� "
		<<person.getName()
		<<"    ��� "
		<<person.getNumber()
		<<"    �ܹ����� "
		<<person.getDate()<<endl;
	cout<<"���ź� "
		<<person.getdepartment()
		<<"    �¹��� "
		<<person.getpay()<<endl;
}


/*
������Jack�Ĺ��ţ���ʽXXX-L����123-A
������Jack���ܹ����ڣ���ʽYYYY/MM/DD����2006/12/25
������Jack���¹��ʣ�3546
������Jack�Ĳ��źţ�326356
��Ա���� Jack    ��� 123-A    �ܹ����� 2006/12/25
���ź� 326356    �¹��� 3546
Press any key to continue
*/