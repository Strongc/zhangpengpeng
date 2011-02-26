/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年5月25日
章    节：第4章
题    号：习题1
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

