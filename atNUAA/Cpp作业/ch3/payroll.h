/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年5月18日
章    节：第3章
题    号：习题4
*/

#ifndef PAYROLL_H
#define PAYROLL_H
class Payroll{
private:
	float rate;
	int time;
	float salary;
public:
	void getrate(float rt){rate=rt;}
	void gettime(int tm){time=tm;}
	void putsalary();
	void calculate();
};
#endif
