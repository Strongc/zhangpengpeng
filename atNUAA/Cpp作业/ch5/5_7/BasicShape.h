/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��6��26��
��    �ڣ���5��
��    �ţ�ϰ��7
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