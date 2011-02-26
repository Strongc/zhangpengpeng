/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年6月8日
章    节：第4章
题    号：习题3
*/

#include "timeoff.h"
#include <iostream.h>

void main()
{
	TimeOff person("ZhangSan","0406304");
	int months,i,day;			//i is used for counting,day用来输入天数的中间变量

	cout<<"请输入已经工作的月数：";
	cin>>months;
	cout<<"请输入雇员每个月生病可以不工作的最多天数：";
	cin>>day;
	person.getmaxSi(day*months);
	cout<<"请输入雇员每个月可以带薪休假的最多天数：";
	cin>>day;
	if(day*months<=3)
		person.getmaxVa(day*months);
	else 
	{
		person.getmaxVa(3);
		cout<<"许多公司规定，雇员带薪休假累计不得超过24小时，系统已自动将其设为3天。"<<endl;
	}
	cout<<"请输入每个月在不支付薪水的情况下，雇员可以休假的最多天数：";
	cin>>day;
	person.getmaxUn(day*months);
	person.getsi(0);
	person.getva(0);
	person.getun(0);

	for(i=0;i<months;i++)
	{
		cout<<"请输入第"
			<<i+1
			<<"月"
			<<person.getname()
			<<"因生病已经不工作的天数：";
		cin>>day;
		person.getsi(person.putsic()+day);

		cout<<"请输入第"
			<<i+1
			<<"月"
			<<person.getname()
			<<"已经带薪休假的天数：";
		cin>>day;
		person.getva(person.putvac()+day);

		cout<<"请输入第"
			<<i+1
			<<"月"
			<<person.getname()
			<<"在不支付薪水的情况下，已经休假的天数：";
		cin>>day;
		person.getun(person.putunp()+day);
	}

	cout<<"这"
		<<months
		<<"个月来"
		<<person.getname()
		<<"因生病已经不工作的天数为："
		<<person.putsic()
		<<"天，还剩"
		<<person.putmaxSi()-person.putsic()
		<<"天"<<endl;
	cout<<"这"
		<<months
		<<"个月来"
		<<person.getname()
		<<"正常休假的天数为："
		<<person.putvac()+person.putunp()
		<<"天，还剩"
		<<person.putmaxVa()+person.putmaxUn()-person.putvac()-person.putunp()
		<<"天"<<endl;
}

/*
请输入已经工作的月数：3
请输入雇员每个月生病可以不工作的最多天数：3
请输入雇员每个月可以带薪休假的最多天数：2
许多公司规定，雇员带薪休假累计不得超过24小时，系统已自动将其设为3天。
请输入每个月在不支付薪水的情况下，雇员可以休假的最多天数：2
请输入第1月ZhangSan因生病已经不工作的天数：2
请输入第1月ZhangSan已经带薪休假的天数：0
请输入第1月ZhangSan在不支付薪水的情况下，已经休假的天数：4
请输入第2月ZhangSan因生病已经不工作的天数：2
请输入第2月ZhangSan已经带薪休假的天数：1
请输入第2月ZhangSan在不支付薪水的情况下，已经休假的天数：0
请输入第3月ZhangSan因生病已经不工作的天数：2
请输入第3月ZhangSan已经带薪休假的天数：0
请输入第3月ZhangSan在不支付薪水的情况下，已经休假的天数：0
这3个月来ZhangSan因生病已经不工作的天数为：6天，还剩3天
这3个月来ZhangSan正常休假的天数为：5天，还剩4天
Press any key to continue
*/