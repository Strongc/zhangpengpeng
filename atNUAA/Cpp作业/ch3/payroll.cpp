/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��5��18��
��    �ڣ���3��
��    �ţ�ϰ��4
*/

#include <iostream.h>
#include "Payroll.h"

void Payroll::calculate()
{
	salary=rate*time;
}
void Payroll::putsalary()
{
	cout<<salary;
}