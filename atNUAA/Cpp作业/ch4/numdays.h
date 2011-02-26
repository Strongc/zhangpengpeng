/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��5��25��
��    �ڣ���4��
��    �ţ�ϰ��1
*/

#ifndef NUMDAYS_H
#define NUMDAYS_H
class NumDays{
private:
	int hour;
	float day;
	void transform();
public:
	NumDays(){day=0;hour=0;}
	NumDays(int);
	NumDays(float d){ day=d;hour=(int)8*d;}
	void gethour(int);
	void getday(int d){ day=(float)d;hour=8*d;};
	int puthour(){	return hour;}
	float putday(){	return day;}
	NumDays operator+(const NumDays &);
	NumDays operator-(const NumDays &);
	NumDays operator++();
	NumDays operator++(int);
	NumDays operator--();
	NumDays operator--(int);
};
#endif