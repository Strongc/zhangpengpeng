/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��6��15��
��    �ڣ���5��
��    �ţ�ϰ��2
*/

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee{
private:
	char *name;
	char *number;
	char *date;
	void memError(char *);			//�����ڴ�����ж�
	bool error1(char *);					//���������Ч�Լ���
	bool error2(char *);					//����������Ч�Լ���
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
