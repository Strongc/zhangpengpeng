/*
 ������   040630416
�ڶ�����ҵ���ڶ���
���ʵ�ֱ��ʽ��ֵ�㷨
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



Status InitStack(Opnd &S)					//����һ����ջ
{
	S.base=(int *)malloc(STACK_INIT_SIZE * sizeof(int));
	if(!S.base)exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
}

Status InitStack(Optr &S)					//����һ����ջ
{
	S.base=(char *)malloc(STACK_INIT_SIZE * sizeof(char));
	if(!S.base)exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
}

char GetTop(Optr S)			//����ջ��Ԫ��
{
	if(S.top==S.base) return ERROR;
	return *(S.top-1);
}

int GetTop(Opnd S)			//����ջ��Ԫ��
{
	if(S.top==S.base) return ERROR;
	return *(S.top-1);
}

Status Push(Optr &S,char e)				//��ջ
{
	if(S.top-S.base>=S.stacksize)			//ջ��׷�Ӵ洢�ռ�
	{
		S.base=(char *)realloc (S.base,(S.stacksize+STACKINCREMENT)*sizeof(char));
		if(!S.base)exit(OVERFLOW);
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++=e;
	return OK;
}

Status Push(Opnd &S,int e)				//��ջ
{
	if(S.top-S.base>=S.stacksize)			//ջ��׷�Ӵ洢�ռ�
	{
		S.base=(int *)realloc (S.base,(S.stacksize+STACKINCREMENT)*sizeof(int));
		if(!S.base)exit(OVERFLOW);
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++=e;
	return OK;
}

Status Pop(Optr &S,char &e)				//����ջ��Ԫ�أ���ɾ��ջ��Ԫ��
{
	if(S.top==S.base)
		return ERROR;
	e=*--S.top;
	return OK;
}

Status Pop(Opnd &S,int &e)				//����ջ��Ԫ�أ���ɾ��ջ��Ԫ��
{
	if(S.top==S.base)
		return ERROR;
	e=*--S.top;
	return OK;
}

  
char Precede(char x,char y)								//�Ƚ����ȹ�ϵ
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

int Operate(int a,char theta,int b)					//��Ԫ����
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



Status EvaluateBds(char * bd)					//������ʽ
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
				case '<':			//ջ��Ԫ������Ȩ��
					Push(OPTR,*p);
					p++;
					break;
				case '=':			//�����Ų�������һ�ַ�
					Pop(OPTR,x);
					p++;
					break;
				case '>':			//��ջ������������ջ
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
	cout<<"��������ʽ����#�Ž���:"<<endl;
	cin>>b;
	cout<<EvaluateBds(b)<<endl;
}


/*
���н��

��������ʽ����#�Ž���:
10+23*45/15-7#
72
Press any key to continue
*/