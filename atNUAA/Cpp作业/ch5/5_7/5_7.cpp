/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年6月26日
章    节：第5章
题    号：习题7
*/

#include <iostream.h>
#include "Circle.h"
#include "Rectangle.h"

void main()
{
	Circle cir(1,2,3.1);
	Rectangle rec(2,3);
	
	cout<<"圆："<<"圆心("<<cir.getCenterX()<<","<<cir.getCenterY()<<")"
		<<"面积为"<<cir.getArea()<<endl;
	cout<<"矩形："<<"宽"<<rec.getWidth()<<","<<"长"<<rec.getLength()
		<<"面积为"<<rec.getArea()<<endl;
}
/*
圆：圆心(1,2)面积为30.1754
矩形：宽2,长3面积为6
Press any key to continue
*/