/*
 张鹏鹏   040630416
第二次作业，第二题
编程实现表达式求值算法
*/


#include <iostream.h>
#include <stdlib.h>
#include <string.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

#define TRUE	1
#define FALSE	0
#define OK		1
#define ERROR	0
#define INFEASIBLE	-1
#define OVERFLOW	-2

typedef int Status;

typedef struct{
	int *base;
	int *top;
	int stacksize;
}Opnd;
typedef struct{
	char *base;
	char *top;
	int stacksize;
}Optr;



Status InitStack(Opnd &S)					//构造一个空栈
{
	S.base=(int *)malloc(STACK_INIT_SIZE * sizeof(int));
	if(!S.base)exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
}

Status InitStack(Optr &S)					//构造一个空栈
{
	S.base=(char *)malloc(STACK_INIT_SIZE * sizeof(char));
	if(!S.base)exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
}

char GetTop(Optr S)			//返回栈顶元素
{
	if(S.top==S.base) return ERROR;
	return *(S.top-1);
}

int GetTop(Opnd S)			//返回栈顶元素
{
	if(S.top==S.base) return ERROR;
	return *(S.top-1);
}

Status Push(Optr &S,char e)				//入栈
{
	if(S.top-S.base>=S.stacksize)			//栈满追加存储空间
	{
		S.base=(char *)realloc (S.base,(S.stacksize+STACKINCREMENT)*sizeof(char));
		if(!S.base)exit(OVERFLOW);
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++=e;
	return OK;
}

Status Push(Opnd &S,int e)				//入栈
{
	if(S.top-S.base>=S.stacksize)			//栈满追加存储空间
	{
		S.base=(int *)realloc (S.base,(S.stacksize+STACKINCREMENT)*sizeof(int));
		if(!S.base)exit(OVERFLOW);
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++=e;
	return OK;
}

Status Pop(Optr &S,char &e)				//返回栈顶元素，并删除栈顶元素
{
	if(S.top==S.base)
		return ERROR;
	e=*--S.top;
	return OK;
}

Status Pop(Opnd &S,int &e)				//返回栈顶元素，并删除栈顶元素
{
	if(S.top==S.base)
		return ERROR;
	e=*--S.top;
	return OK;
}

  
char Precede(char x,char y)								//比较优先关系
{
	int a,b;
	char f[7][7]={		{ '>','>','<','<','<','>','>'},
						{ '>','>','<','<','<','>','>'},
						{ '>','>','>','>','<','>','>'},
						{ '>','>','>','>','<','>','>'},
						{ '<','<','<','<','<','=',' '},
						{ '>','>','>','>',' ','>','>'},
						{ '<','<','<','<','<',' ','='}
					};
	switch(x)
	{
		case '+': a=0; break;
		case '-': a=1; break;
		case '*': a=2; break;
		case '/': a=3; break;
		case '(': a=4; break;
		case ')': a=5; break;
		case '#': a=6; break;
	}
	switch(y)
	{
		case '+': b=0; break;
		case '-': b=1; break;
		case '*': b=2; break;
		case '/': b=3; break;
		case '(': b=4; break;
		case ')': b=5; break;
		case '#': b=6; break;
	}
	return f[a][b];
}

int Operate(int a,char theta,int b)					//二元运算
{
	switch(theta)
	{
		case '+': return a+b;
		case '-': return a-b;
		case '*': return a*b;
		case '/': return a/b;
		case '(': break;
		case ')': break;
		case '#': break;
	}
}



Status EvaluateBds(char * bd)					//运算表达式
{
	char *p,x,y;
	char theta;
	int a,b;
	Optr OPTR;
	Opnd OPND;
	InitStack(OPTR);
	Push(OPTR,'#');
	InitStack(OPND);
	p=bd;
	while(*p!='#'||GetTop(OPTR)!='#')
	{
		if(*p<='9'&&*p>='0')
		{
			y=*p-'0';
			while(*(p+1)<='9'&&*(p+1)>='0')
			{
				p++;
				y=y*10+(*p-'0');
			}
			Push(OPND,y);
			p++;
		}
		else
			switch(Precede(GetTop(OPTR),*p))
			{	
				case '<':			//栈顶元素优先权低
					Push(OPTR,*p);
					p++;
					break;
				case '=':			//脱括号并接受下一字符
					Pop(OPTR,x);
					p++;
					break;
				case '>':			//退栈并将运算结果入栈
					Pop(OPTR,theta);
					Pop(OPND,b);
					Pop(OPND,a);
					Push(OPND,Operate(a,theta,b));
					break;
			}
	}
	return GetTop(OPND);
}


	
void main()
{
	char b[100];
	cout<<"请输入算式并以#号结束:"<<endl;
	cin>>b;
	cout<<EvaluateBds(b)<<endl;
}


/*
运行结果

请输入算式并以#号结束:
10+23*45/15-7#
72
Press any key to continue
*/