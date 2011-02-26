/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��5��25��
��    �ڣ���4��
��    �ţ�ϰ��1
*/

#include <iostream.h>
#include "numdays.h"

NumDays::NumDays(int h)
{
	hour=h;
	transform();
}

void NumDays::gethour(int h)
{
	hour=h;
	transform();
}

void NumDays::transform()
{
	day=hour/8.000f;
}

NumDays NumDays::operator+(const NumDays &right)
{
	NumDays temp(0);
	temp.hour=hour+right.hour;
	temp.transform();
	return temp;
}

NumDays NumDays::operator-(const NumDays &right)
{
	NumDays temp(0);
	temp.hour=hour-right.hour;
	temp.transform();
	return temp;
}

NumDays NumDays::operator++()
{
	hour++;
	transform();
	return *this;
}

NumDays NumDays::operator++(int)
{
	NumDays temp(hour);
	hour++;
	transform();
	return temp;
}

NumDays NumDays::operator--()
{
	hour--;
	transform();
	return *this;
}

NumDays NumDays::operator--(int)
{
	NumDays temp(hour);
	hour--;
	transform();
	return temp;
}

