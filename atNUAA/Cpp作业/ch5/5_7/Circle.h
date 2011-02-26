/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��6��26��
��    �ڣ���5��
��    �ţ�ϰ��7
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