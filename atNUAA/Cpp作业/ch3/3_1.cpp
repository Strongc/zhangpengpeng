/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年5月10日
章    节：第3章
题    号：习题1
*/

#include <iostream.h>
#include <string.h>

class Date{
private:
	int year;
	int month;
	int day;
	char mon[10];				//记录月的英文名
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
	do{
		cout<<"Please input the month:";
		cin>>month;
	}while(month>=12||month<=1);
	do{
		cout<<"Please input the day:";
		cin>>day;
	}while(day>=31||day<=1);

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
Please input the year:2007
Please input the month:5
Please input the day:10
5-10-7
May   10,2007
10  May  2007
Press any key to continue

Please input the year:2008
Please input the month:23
Please input the month:4
Please input the day:43
Please input the day:29
4-29-8
April   29,2008
29  April  2008
Press any key to continue
*/