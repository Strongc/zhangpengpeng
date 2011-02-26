/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��6��1��
��    �ڣ���4��
��    �ţ�ϰ��2
*/

#include "numdays.h"
#ifndef TIMEOFF
#define TIMEOFF
class TimeOff{
private:
	NumDays maxSickDays;
	NumDays sickTaken;
	NumDays maxVacation;
	NumDays vacTaken;
	NumDays maxUnpaid;
	NumDays unpaidTaken;
	char *name;
	char *workNum;
public:
	TimeOff(char *,char *);
	~TimeOff(){ delete []name;delete[]workNum;}
	char *getname(){return name;}
	void getmaxSi(int d){ maxSickDays.getday(d);}
	void getmaxVa(int d);			//�˴�����
	void getmaxUn(int d){ maxUnpaid.getday(d);}
	float putmaxSi(){ return maxSickDays.putday();}
	float putmaxVa(){ return maxVacation.putday();}
	float putmaxUn(){ return maxUnpaid.putday();}
	void getsi(int d){ sickTaken.getday(d);}
	void getva(int d){ vacTaken.getday(d);}
	void getun(int d){ unpaidTaken.getday(d);}
	float putsic(){ return sickTaken.putday();}
	float putvac(){ return vacTaken.putday();}
	float putunp(){ return unpaidTaken.putday();}
};
#endif
