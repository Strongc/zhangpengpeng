/*
040630416	张鹏鹏
第一次作业，第二题
实现两个一元多项式的相加、相减、相乘
*/

#define TRUE	1
#define FALSE	0
#define OK		1
#define ERROR	0
#define INFEASIBLE	-1
#define OVERFLOW	-2
typedef int status;

#include <stdlib.h>
#include <iostream.h>

typedef struct LNode{
	float coef;			//系数
	int expn;			//指数
	struct LNode *next;
}LNode,*LinkList;

status CreatPolyn(LinkList &P,int m)						//创建一个多项式，支持无序输入
{
	P=(LinkList)malloc(sizeof(LNode));
	if(!P)exit(OVERFLOW);
	P->next=NULL;
	LinkList q,r;
	for(int i=0;i<m;i++)
	{
		q=(LinkList)malloc(sizeof(LNode));
		if(!q) exit(OVERFLOW);
		cout<<"请输入系数：";
		cin>>q->coef;
		cout<<"   请输入指数：";
		cin>>q->expn;
		cout<<endl;
		r=P;
		while(r->next)
			if(r->next->expn<q->expn)
				r=r->next;
			else
				break;
		q->next=r->next;
		r->next=q;
	}
	return OK;
}

void AddPolyn(LinkList &A,LinkList &B,LinkList &C)			//相加
{
	LinkList pa=A->next;
	LinkList pb=B->next;
	C=(LinkList)malloc(sizeof(LNode));
	if(!C) exit(OVERFLOW);
	C->next=NULL;
	LinkList pc=C;
	float c;
	while(pa&&pb)
	{
		if(pa->expn<pb->expn)
		{
			A->next=pa->next;
			pa->next=NULL;
			pc->next=pa;
			pc=pc->next;
			pa=A->next;
		}
		else
		{
			if(pb->expn<pa->expn)
			{
				B->next=pb->next;
				pb->next=NULL;
				pc->next=pb;
				pc=pc->next;
				pb=B->next;
			}
			else				//指数相等时
			{
				c=pa->coef+pb->coef;
				if(!c)							//系数和为0
				{
					A->next=pa->next;
					free(pa);
					pa=A->next;
					B->next=pb->next;
					free(pb);
					pb=B->next;
				}
				else							//系数和不为0，用A的节点
				{
					pa->coef=c;
					A->next=pa->next;
					pa->next=NULL;
					pc->next=pa;
					pc=pc->next;
					pa=A->next;
					B->next=pb->next;
					free(pb);
					pb=B->next;
				}
			}
		}
	}
	if(pa)									//处理剩下的一个链表
		pc->next=pa;
	if(pb)
		pc->next=pb;
		
	free(A);
	free(B);
}

void SubtractPolyn(LinkList &A,LinkList &B,LinkList &C)			//相减
{
	LinkList pa=A->next;
	LinkList pb=B->next;
	C=(LinkList)malloc(sizeof(LNode));
	if(!C) exit(OVERFLOW);
	C->next=NULL;
	LinkList pc=C;
	float c;
	while(pa&&pb)
	{
		if(pa->expn<pb->expn)
		{
			A->next=pa->next;
			pa->next=NULL;
			pc->next=pa;
			pc=pc->next;
			pa=A->next;
		}
		else 
		{
			if(pb->expn<pa->expn)
			{
				pb->coef=(-1)*pb->coef;
				B->next=pb->next;
				pb->next=NULL;
				pc->next=pb;
				pc=pc->next;
				pb=B->next;
			}
			else						//指数相等时
			{
				c=pa->coef-pb->coef;
				if(!c)							//系数和为0
				{
					A->next=pa->next;
					free(pa);
					pa=A->next;
					B->next=pb->next;
					free(pb);
					pb=B->next;
				}
				else							//系数和不为0，用A的节点
				{
					pa->coef=c;
					A->next=pa->next;
					pa->next=NULL;
					pc->next=pa;
					pc=pc->next;
					pa=A->next;
					B->next=pb->next;
					free(pb);
					pb=B->next;

				}
			}
		}
	}
	if(pa)									//处理剩下的一个链表
		pc->next=pa;
	if(pb)
	{
		LinkList pd=pb;
		while(pd)
		{
			pd->coef=(-1)*pd->coef;
			pd=pd->next;
		}
		pc->next=pb;
	}

	free(A);
	free(B);
}


status CopyPolyn(LinkList &A,LinkList B)				//拷贝多项式，相乘时要重复调用
{
	A=(LinkList)malloc(sizeof(LNode));
	if(!A) exit(OVERFLOW);
	A->next=NULL;
	LinkList pa=A;
	LinkList pb=B->next;
	LinkList pc;
	while(pb)
	{
		pc=(LinkList)malloc(sizeof(LNode));
		if(!pc) exit(OVERFLOW);
		pc->coef=pb->coef;
		pc->expn=pb->expn;
		pc->next=pa->next;
		pa->next=pc;
		pa=pa->next;
		pb=pb->next;
	}
	return OK;
}

status DelPolyn(LinkList &C)					//删除链表,多处用到
{
	LinkList pc;
	pc=C->next;	
	while(pc)
	{
		C->next=pc->next;
		free(pc);
		pc=C->next;
	}
	free(C);
	return OK;
}

void MultiplyPolyn(LinkList &A,LinkList &B,LinkList &C)			//相乘
{
	C=(LinkList)malloc(sizeof(LNode));
	if(!C) exit(OVERFLOW);
	C->next=NULL;
	LinkList pa=A->next,pb,Lb,Lc;
	while(pa)
	{
		CopyPolyn(Lb,B);				//调用复制函数
		pb=Lb->next;
		while(pb)
		{
			pb->coef=pb->coef*pa->coef;
			pb->expn=pb->expn+pa->expn;
			pb=pb->next;
		}
		AddPolyn(C,Lb,Lc);
		C=Lc;
		pa=pa->next;
	}
												//处理完毕,释放A,B空间
 
	DelPolyn(A);
	DelPolyn(B);
}


void PrintPolyn(LinkList P)
{
	LinkList q=P->next;
	if(!q)
		cout<<0;
	else
	{
		cout<<endl<<q->coef<<'x'<<q->expn;
		q=q->next;
	}
	while(q)
	{
		if(q->coef>0)
			cout<<'+'<<q->coef<<'x'<<q->expn;
		else
			cout<<q->coef<<'x'<<q->expn;
		q=q->next;
	}
	cout<<endl;
}