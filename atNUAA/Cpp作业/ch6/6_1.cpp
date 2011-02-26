/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��6��26��
��    �ڣ���6��
��    �ţ�ϰ��1
*/

#include <iostream.h>
#include <string.h>
#include <stdlib.h>

class Date{
private:
	int year;
	int month;
	int day;
	char mon[10];				//��¼�µ�Ӣ����
public:
	void getdate();
	void format1();
	void format2();
	void format3();
};

void Date::getdate()
{
	//get the date
	cout<<"Please input the year:";
	cin>>year;
	try{													//�쳣����
		cout<<"Please input the month:";
		cin>>month;
		if(month>12||month<1)
			throw "�·���Ч��";
		cout<<"Please input the day:";
		cin>>day;
		if(day>31||day<1)
			throw "������Ч��";
	}catch(char *string)
	{
		cout<<string;
		exit(0);
	}

	//cope with the English name of every month
	switch(month){
		case 1:strcpy(mon,"January");
			break;
		case 2:strcpy(mon,"February");
			break;
		case 3:strcpy(mon,"March");
			break;
		case 4:strcpy(mon,"April");
			break;
		case 5:strcpy(mon,"May");
			break;
		case 6:strcpy(mon,"June");
			break;
		case 7:strcpy(mon,"July");
			break;
		case 8:strcpy(mon,"August");
			break;
		case 9:strcpy(mon,"September");
			break;
		case 10:strcpy(mon,"October");
			break;
		case 11:strcpy(mon,"November");
			break;
		case 12:strcpy(mon,"December");
			break;
	}
}

void Date::format1()
{
	cout<<month
		<<'-'
		<<day
		<<'-'
		<<(year%100)<<endl;
}
void Date::format2()
{
	cout<<mon
		<<"   "
		<<day
		<<','
		<<year<<endl;
}
void Date::format3()
{
	cout<<day
		<<"  "
		<<mon
		<<"  "
		<<year<<endl;
}

void main()
{
	Date dat;

	dat.getdate();
	dat.format1();
	dat.format2();
	dat.format3();
}

/*
Please input the year:2006
Please input the month:13
�·���Ч��Press any key to continue
*/
/*
Please input the year:2007
Please input the month:12
Please input the day:32
������Ч��Press any key to continue
*/