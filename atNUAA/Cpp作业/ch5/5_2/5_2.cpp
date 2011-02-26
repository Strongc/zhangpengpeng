/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年6月15日
章    节：第5章
题    号：习题2
*/
#include "EmployeePay.h"
#include  <iostream.h>

void main()
{
	EmployeePay person("Jack");
	float pay;
	int department;

	cout<<"请输入"
		<<person.getName()
		<<"的月工资：";
	cin>>pay;
	cout<<"请输入"
		<<person.getName()
		<<"的部门号：";
	cin>>department;
	person.setpay(pay,department);
	cout<<"雇员姓名 "
		<<person.getName()
		<<"    编号 "
		<<person.getNumber()
		<<"    受雇日期 "
		<<person.getDate()<<endl;
	cout<<"部门号 "
		<<person.getdepartment()
		<<"    月工资 "
		<<person.getpay()<<endl;
}


/*
请输入Jack的工号（格式XXX-L）：123-A
请输入Jack的受雇日期（格式YYYY/MM/DD）：2006/12/25
请输入Jack的月工资：3546
请输入Jack的部门号：326356
雇员姓名 Jack    编号 123-A    受雇日期 2006/12/25
部门号 326356    月工资 3546
Press any key to continue
*/