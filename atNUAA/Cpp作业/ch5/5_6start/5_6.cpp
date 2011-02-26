/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年6月15日
章    节：第5章
题    号：习题6
*/
#include <iostream.h>
#include "Grades.h"

void main()
{
	Grades person[3]={"Jack","John","Joe"};
	int i;


	cout<<"请输入"
		<<person[0].getName()
		<<"的学号："<<endl;
	person[0].setNumber();
	cout<<"请输入"
		<<person[1].getName()
		<<"的学号："<<endl;
	person[1].setNumber();
	cout<<"请输入"
		<<person[2].getName()
		<<"的学号："<<endl;
	person[2].setNumber();

	cout<<"请输入"
		<<person[0].getName()
		<<"的专业："<<endl;
	person[0].setMajor();
	cout<<"请输入"
		<<person[1].getName()
		<<"的专业："<<endl;
	person[1].setMajor();
	cout<<"请输入"
		<<person[2].getName()
		<<"的专业："<<endl;
	person[2].setMajor();

	cout<<"请输入"
		<<person[0].getName()
		<<"的成绩："<<endl;
	person[0].setScore();
	cout<<"请输入"
		<<person[1].getName()
		<<"的成绩："<<endl;
	person[1].setScore();
	cout<<"请输入"
		<<person[2].getName()
		<<"的成绩："<<endl;
	person[2].setScore();

	for(i=0;i<3;i++)
	{
		cout<<person[i].getName()
			<<"的学号："
			<<person[i].getNumber()<<endl;
		cout<<" 专业："
			<<person[i].getmajor()<<endl;
		cout<<" 各门成绩："<<endl;
		person[i].getScore();
		cout<<" 平均成绩："
			<<person[i].getAver()
			<<endl;
	}

}

/*
请输入Jack的学号：
001
请输入John的学号：
002
请输入Joe的学号：
003
请输入Jack的专业：
计算机
请输入John的专业：
电子
请输入Joe的专业：
土木
请输入Jack的成绩：
请输入第1门的成绩：99
请输入第2门的成绩：998
成绩应该在0至100之间:98
请输入第3门的成绩：89
请输入第4门的成绩：87
请输入第5门的成绩：85
请输入第6门的成绩：96
请输入John的成绩：
请输入第1门的成绩：85
请输入第2门的成绩：65
请输入第3门的成绩：87
请输入第4门的成绩：54
请输入第5门的成绩：565
成绩应该在0至100之间:69
请输入第6门的成绩：58
请输入Joe的成绩：
请输入第1门的成绩：58
请输入第2门的成绩：65
请输入第3门的成绩：35
请输入第4门的成绩：25
请输入第5门的成绩：45
请输入第6门的成绩：25
Jack的学号：001
 专业：计算机
 各门成绩：
第1门的成绩为99
第2门的成绩为98
第3门的成绩为89
第4门的成绩为87
第5门的成绩为85
第6门的成绩为96
 平均成绩：92.3333
John的学号：002
 专业：电子
 各门成绩：
第1门的成绩为85
第2门的成绩为65
第3门的成绩为87
第4门的成绩为54
第5门的成绩为69
第6门的成绩为58
 平均成绩：69.6667
Joe的学号：003
 专业：土木
 各门成绩：
第1门的成绩为58
第2门的成绩为65
第3门的成绩为35
第4门的成绩为25
第5门的成绩为45
第6门的成绩为25
 平均成绩：42.1667
Press any key to continue
*/