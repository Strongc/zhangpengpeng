/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年6月15日
章    节：第5章
题    号：习题2
*/

#ifndef EMPLOYEEPAY_H
#define EMPLOYEEPAY_H
#include <iostream.h>
#include "Employee.h"

class EmployeePay : public Employee{
private:
	float pay;
	int department;
public:
	EmployeePay(char *ch):Employee(ch){}
	void setpay(float p,int d){pay=p;department=d;}
	float getpay(){return pay;}
	int getdepartment(){return department;}
};
#endif

//EmployeePay::EmployeePay(char *ch):Employee(char *ch){}