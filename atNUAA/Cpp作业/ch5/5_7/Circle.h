/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年6月26日
章    节：第5章
题    号：习题7
*/

#ifndef CIRCLE_H
#define CIRCLE_H
#include "BasicShape.h"

class Circle:public BasicShape{
private:
	int centerX;
	int centerY;
	double radius;
public:
	Circle(int x,int y,double r)
	{
		centerX=x;
		centerY=y;
		radius=r;
		CalcArea();
	}
	int getCenterX(){return centerX;}
	int getCenterY(){return centerY;}
	void CalcArea(){area=3.14*radius*radius;}
};
#endif