/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��6��26��
��    �ڣ���5��
��    �ţ�ϰ��7
*/

#include <iostream.h>
#include "Circle.h"
#include "Rectangle.h"

void main()
{
	Circle cir(1,2,3.1);
	Rectangle rec(2,3);
	
	cout<<"Բ��"<<"Բ��("<<cir.getCenterX()<<","<<cir.getCenterY()<<")"
		<<"���Ϊ"<<cir.getArea()<<endl;
	cout<<"���Σ�"<<"��"<<rec.getWidth()<<","<<"��"<<rec.getLength()
		<<"���Ϊ"<<rec.getArea()<<endl;
}
/*
Բ��Բ��(1,2)���Ϊ30.1754
���Σ���2,��3���Ϊ6
Press any key to continue
*/