/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年6月26日
章    节：第5章
题    号：习题7
*/

#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "BasicShape.h"

class Rectangle:public BasicShape{
private:
	long width;
	long length;
public:
	Rectangle(long w,long l)
	{
		width=w;
		length=l;
		CalcArea();
	}
	long getWidth(){return width;}
	long getLength(){return length;}
	void CalcArea(){area=width*length;}
};
#endif