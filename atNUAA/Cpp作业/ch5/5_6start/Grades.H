/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年6月15日
章    节：第5章
题    号：习题6
*/

#ifndef GRADES_H
#define GRADES_H
#include "StudentInfo.h"
#include <iostream.h>

class Grades:public StudentInfo{
private:
	float score[6];
	float average;
	void setAver();
public:
	Grades(char *na):StudentInfo(na){}
	void setScore();
	void getScore();
	float getAver(){return average;}
};
#endif