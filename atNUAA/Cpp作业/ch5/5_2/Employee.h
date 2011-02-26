/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年6月15日
章    节：第5章
题    号：习题2
*/

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee{
private:
	char *name;
	char *number;
	char *date;
	void memError(char *);			//分配内存错误判断
	bool error1(char *);					//编号输入有效性检验
	bool error2(char *);					//日期输入有效性检验
public:
	Employee(char *);
	~Employee()
	{
		delete []name;
		delete []number;
		delete []date;
	}

	char *getName(){return name;}
	char *getNumber(){return number;}
	char *getDate(){return date;}
};
#endif
