/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��5��18��
��    �ڣ���3��
��    �ţ�ϰ��4
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
