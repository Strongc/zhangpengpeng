/*
040630416	������
�ڶ�����ҵ����һ��
����˳��ṹջ�Ļ�������
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


status InitStack(SqStack &S)					//����һ����ջ
{
	S.base=(SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if(!S.base)exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
}

status DestroyStack(SqStack &S)					//����ջ
{
	free(S.base);
	return OK;
}

status ClearStack(SqStack &S)					//��Ϊ��ջ
{
	S.top=S.base;
	return OK;
}

status StackEmpty(SqStack S)					//�ж��Ƿ�Ϊ��ջ
{
	return (S.top==S.base)? 1:0;
}

int StackLength(SqStack S)						//ջ�ĳ���
{
	return S.top-S.base;
}

status GetTop(SqStack S,SElemType &e)			//����ջ��Ԫ��
{
	if(S.top==S.base) return ERROR;
	e=*(S.top-1);
	return OK;
}

status Push(SqStack &S,SElemType e)				//��ջ
{
	if(S.top-S.base>=S.stacksize)			//ջ��׷�Ӵ洢�ռ�
	{
		S.base=(SElemType *)realloc (S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!S.base)exit(OVERFLOW);
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++=e;
	return OK;
}

status Pop(SqStack &S,SElemType &e)				//����ջ��Ԫ�أ���ɾ��ջ��Ԫ��
{
	if(S.top==S.base)
		return ERROR;
	e=*--S.top;
	return OK;
}

status StackTraverse(SqStack S,status(*visit)(SElemType))				//���η���
{
	SElemType *p;
	if(S.top==S.base) return ERROR;

	for(p=S.base;p<S.top;p++)
		visit(*p);
	return OK;
}

