/*
040630416	张鹏鹏
第二次作业，第一题
调试顺序结构栈的基本操作
*/


#include <stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

#define TRUE	1
#define FALSE	0
#define OK		1
#define ERROR	0
#define INFEASIBLE	-1
#define OVERFLOW	-2

typedef int status;

typedef struct{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;


status InitStack(SqStack &S)					//构造一个空栈
{
	S.base=(SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if(!S.base)exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
}

status DestroyStack(SqStack &S)					//销毁栈
{
	free(S.base);
	return OK;
}

status ClearStack(SqStack &S)					//置为空栈
{
	S.top=S.base;
	return OK;
}

status StackEmpty(SqStack S)					//判断是否为空栈
{
	return (S.top==S.base)? 1:0;
}

int StackLength(SqStack S)						//栈的长度
{
	return S.top-S.base;
}

status GetTop(SqStack S,SElemType &e)			//返回栈顶元素
{
	if(S.top==S.base) return ERROR;
	e=*(S.top-1);
	return OK;
}

status Push(SqStack &S,SElemType e)				//入栈
{
	if(S.top-S.base>=S.stacksize)			//栈满追加存储空间
	{
		S.base=(SElemType *)realloc (S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!S.base)exit(OVERFLOW);
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++=e;
	return OK;
}

status Pop(SqStack &S,SElemType &e)				//返回栈顶元素，并删除栈顶元素
{
	if(S.top==S.base)
		return ERROR;
	e=*--S.top;
	return OK;
}

status StackTraverse(SqStack S,status(*visit)(SElemType))				//依次访问
{
	SElemType *p;
	if(S.top==S.base) return ERROR;

	for(p=S.base;p<S.top;p++)
		visit(*p);
	return OK;
}

