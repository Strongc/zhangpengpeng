/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年5月18日
章    节：第3章
题    号：习题4
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