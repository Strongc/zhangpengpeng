/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��6��15��
��    �ڣ���5��
��    �ţ�ϰ��2
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