/*
040630416	张鹏鹏
第二次作业，第一题
调试顺序结构栈的基本操作
*/

typedef int SElemType;
#include <iostream.h>

#include "2_1.h"



void main()
{	
	SqStack S;
	SElemType e;
	status print(SElemType);

	InitStack(S);
	Push(S,1);
	Push(S,2);
	Push(S,3);
	if(!StackEmpty(S))
		cout<<StackLength(S)<<endl;				//3
	Pop(S,e);
	cout<<e<<endl;								//3
	Push(S,4);
	Push(S,5);
	Pop(S,e);
	cout<<e<<endl;								//5

	StackTraverse(S,print);						//1 2 4 
	cout<<endl;
	ClearStack(S);
	cout<<StackLength(S)<<endl;					//0
	DestroyStack(S);

}

status print(SElemType e)
{
	cout<<e<<" ";
	return OK;
}


/*
3
3
5
1 2 4
0
Press any key to continue
*/