/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年4月19日
章    节：第1章
题    号：习题11
*/


#include <iostream>
#include <string>
using namespace std;

void main()
{
	string date,name,money;
	int i,dot;

	cout<<"请输入日期(YYYY/MM/DD):";			//收集信息
	cin>>date;
	cout<<"请输入你的姓名:";
	cin>>name;
	cout<<"请输入金额(nnnn.nn):";
	cin>>money;

	date.replace(4,1,"年");			//处理日期和姓名及RMB
	date.replace(8,1,"月");
	date.append("日");
	cout<<"日期"<<date<<endl;
	cout<<"姓名"<<name<<"   ";
	cout<<"RMB"<<money<<endl;

	cout<<"人民币:";				//处理大写的输出
	dot=money.find('.');
	for(i=0;money[i]!='\0';i++)
	{
		switch(money[i])
		{	
			case '0':	cout<<"零";
						break;
			case '1':	cout<<"壹";
						break;
			case '2':	cout<<"贰";
						break;
			case '3':	cout<<"叁";
						break;
			case '4':	cout<<"肆";
						break;
			case '5':	cout<<"伍";
						break;		
			case '6':	cout<<"陆";
						break;		
			case '7':	cout<<"柒";
						break;		
			case '8':	cout<<"捌";
						break;
			case '9':	cout<<"玖";
						break;		
		}

		switch(dot-i)
		{
			case 4:	cout<<"仟";
					break;
			case 3:	cout<<"佰";
					break;
			case 2:	cout<<"拾";
					break;
			case 1:	cout<<"元";
					break;
			case 0:	;
					break;
			case -1:	cout<<"角";
					break;
			case -2:	cout<<"分";
					break;
		}
	}
		
}




/*
第一次运行：
请输入日期(YYYY/MM/DD):2007/04/19
请输入你的姓名:Roc
请输入金额(nnnn.nn):123.45
日期2007年04月19日
姓名Roc   RMB123.45
人民币:壹佰贰拾叁元肆角伍分Press any key to continue

第二次运行：
请输入日期(YYYY/MM/DD):2007/04/20
请输入你的姓名:Rocflyhi
请输入金额(nnnn.nn):9876.54
日期2007年04月20日
姓名Rocflyhi   RMB9876.54
人民币:玖仟捌佰柒拾陆元伍角肆分Press any key to continue
*/