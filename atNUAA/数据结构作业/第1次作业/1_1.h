/*
040630416	张鹏鹏
第一次作业，第一题
用链表存储结构实现P19的线性表的基本操作
*/

#define TRUE	1
#define FALSE	0
#define OK		1
#define ERROR	0
#define INFEASIBLE	-1
#define OVERFLOW	-2

#include <stdlib.h>

typedef int status;

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;

status InitList(LinkList &L)	//初始化一个线性表
{
	L=(LinkList)malloc(sizeof(LNode));
	if(!L)exit(OVERFLOW);
	L->next=NULL;
	return OK;
}

status DestroyList(LinkList &L)		//销毁线性表
{
	LinkList p;
	p=L->next;
	while(p)
	{
		L->next=p->next;
		free(p);
		p=L->next;
	}
	free(L);
	return OK;
}

status ClearList(LinkList &L)		//将线性表重置为空表
{
	 LinkList p;
	 p=L->next;
	 while(p)
	 {
		 L->next=p->next;
		 free(p);
		 p=L->next;
	 }
	 return OK;
}

bool ListEmpty(LinkList L)			//检查线性表是否为空表，空true,否false
{
	if(L->next)
		return true;
	else
		return false;
}

int ListLength(LinkList L)			//返回数据元素的个数
{
	int i=0;
	LinkList p;
	p=L->next;
	while(p)
	{
		i++;
		p=p->next;
	}
	return i;
}

status GetElem(LinkList L,int i,ElemType &e)	//返回第i个数据元素
{
	int j=0;
	LinkList p=L->next;
	while(p)
	{
		j++;
		if(i==j)
		{
			e=p->data;
			break;
		}
		p=p->next;
	}
	if(i==j)
		return OK;
	else
		return ERROR;
}

int LocateElem(LinkList L,ElemType e,bool (*compare)(ElemType,ElemType))	//返回满足关系的数据元素的位序
{
	int i=1;
	LinkList p=L->next;
	while(p)
	{
		if((*compare)(p->data,e))
			return i;
		else
		{
			p=p->next;
			i++;
		}
	}
	return 0;
}



status PriorElem(LinkList L,ElemType cur_e,ElemType &pre_e)		//返回前驱
{
	LinkList p=L->next;
	while(p->next)
	{
		if(p->next->data==cur_e)
		{
			pre_e=p->data;
			break;
		}
		else
			p=p->next;
	}
	if(p->next->data==cur_e)
		return OK;
	else
		return ERROR;
}
		
status NextElem(LinkList L,ElemType cur_e,ElemType &next_e)		//返回后继
{
	LinkList p=L->next;
	while(p->next)
	{
		if(p->data==cur_e)
		{
			next_e=p->next->data;
			return OK;
		}
		else
			p=p->next;
	}
	return ERROR;
}

status ListInsert(LinkList &L,int i,ElemType e)			//插入
{
	int j=1;
	LinkList q,p=L;
	while(p)
	{
		if(i==j)
		{
			q=(LinkList)malloc(sizeof(LNode));
			if(!L)exit(OVERFLOW);
			q->data=e;
			q->next=p->next;
			p->next=q;
			return OK;
		}
		else
		{
			p=p->next;
			j++;
		}
	}
	return ERROR;
}


status ListDelete(LinkList &L,int i ,ElemType &e)		//删除
{
	int j=1;
	LinkList q,p=L;
	while(p->next)
	{
		if(i==j)
		{
			q=p->next;
			e=q->data;
			p->next=q->next;
			free(q);
			return OK;
		}
		p=p->next;
		j++;
	}
	return ERROR;
}
	

status ListTraverse(LinkList &L, status(*visit)(ElemType))		//依次访问
{
	LinkList p=L->next;
	while(p)
	{
		if(!(*visit)(p->data))
		{
			break;
			return ERROR;
		}
		p=p->next;
	}

	return OK;
}

