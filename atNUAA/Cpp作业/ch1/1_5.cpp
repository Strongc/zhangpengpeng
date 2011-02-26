/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年4月13日
章    节：第1章
题    号：习题5
*/

#include<iostream.h>

void main()
{
	char stdAnswer[20]={'B','D','A','A','C','A','B','A','C','D',
						'B','C','D','A','D','C','D','B','D','A'},
			answer[20];		//answer记录考生回答的答案
	int i,num;		//num记录作错题的个数

	for(i=0;i<20;i++)				//作答
	{	
		cout<<"请输入第"<<(i+1)<<"题的答案：\n";
		cin>>answer[i];
		if(answer[i]!='a'&&answer[i]!='A'&&answer[i]!='b'&&answer[i]!='B'
			&&answer[i]!='c'&&answer[i]!='C'&&answer[i]!='d'&&answer[i]!='D')
		{cout<<"请输入A，B，C或D\n";
		 i--;
		}
	}
	for(i=0,num=0;i<20;i++)			//判断
		if(answer[i]!=stdAnswer[i]&&
			answer[i]!=stdAnswer[i]-'A'+'a')
		{cout<<"\n第"<<(i+1)<<"题答错了";
		 num++;
		}
	cout<<"\n你共有"<<num<<"道题答错了\n";
	if(num<=8)
		cout<<"恭喜你通过了本场考试";
	else
		cout<<"很遗憾，你没有通过本场考试，请继续努力";

}