/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年6月15日
章    节：第5章
题    号：习题6
*/

#ifndef STUDENTINFO_H
#define STUDENTINFO_H

class StudentInfo{
private:
	char *name;
	char number[10];
	char major[30];
public:
	StudentInfo(char *);
	~StudentInfo(){delete []name;}
	void setNumber();
	void setMajor();
	char *getName(){return name;}
	char *getNumber(){return number;}
	char *getmajor(){return major;}
};
#endif