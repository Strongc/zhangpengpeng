/*
    C++课程设计
程序作者：张鹏鹏
学    号：040630416
*/

#include "TitleInfo.h"

bool TitleInfo::bookMatch(char *bookname)
{
	int i,j;
	bool bo=false;
	for(i=0;i<51;i++)							//开始时bo=false
	{
		if(title[i]==*bookname)
		{
			bo=true;							//发现可能对时，令bo=true
			for(j=1;*(bookname+j)!='\0';j++)
			{
				if((i+j)>50)						//防止title越位
				{
					bo=false;						//一旦发现不符，马上设为false,并退出内循环
					break;
				}
				if(title[i+j]!=*(bookname+j))
				{
					bo=false;						//一旦发现不符，马上设为false,并退出内循环
					break;
				}
			}
			if(bo==true)							//内循环结束，bo仍为true,确定符合，退出外循环
				break;
		}											//若未进入内循环，bo仍为false
	}
	return bo;
}
		