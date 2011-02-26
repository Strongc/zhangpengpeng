/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年6月26日
章    节：第5章
题    号：习题7
*/

#ifndef BASICSHAPE_H
#define BASICSHAPE_H

class BasicShape{
protected:
	double area;
public:
	double getArea(){return area;}
	virtual void CalcArea()=0;
};
#endif