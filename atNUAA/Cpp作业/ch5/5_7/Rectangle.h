/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��6��26��
��    �ڣ���5��
��    �ţ�ϰ��7
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