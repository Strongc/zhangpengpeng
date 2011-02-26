/*
040630416	张鹏鹏
第一次作业，第一题
用链表存储结构实现P19的线性表的基本操作
*/

typedef int ElemType;

#include "1_1.h"
#include <iostream.h>

void main()
{
	bool equal(ElemType,ElemType);		//给(*compare)()赋实参
	status print(ElemType);				//给(*visit)()赋实参

	LinkList L;
	ElemType e=0;

	InitList(L);
	ListInsert(L,1,1);
	ListInsert(L,1,2);
	ListInsert(L,2,3);				//2,3,1
	ListDelete(L,1,e);				//3,1
	cout<<e<<endl;
	cout<<"1在第"<<LocateElem(L,1,equal)<<"个"<<endl;
	if(ListEmpty(L))
	{
		cout<<"长度"<<ListLength(L)<<endl;
		if(GetElem(L,2,e))
			cout<<"第2二个数据元素为:"<<e<<endl;
	}

	if(ClearList(L))
		cout<<"清空成功，下面开始新的线性表"<<endl;
	ListInsert(L,1,4);
	ListInsert(L,1,5);
	ListInsert(L,2,6);				//5,6,4
	if(PriorElem(L,4,e))
		cout<<"4的前驱是"<<e<<endl;
	if(NextElem(L,5,e))
		cout<<"5的后继是"<<e<<endl;
	ListTraverse(L,print);

	if(DestroyList(L))
		cout<<endl<<"销毁线性表,程序结束。"<<endl;
}

bool equal(ElemType e1,ElemType e2)
{
	return (e1==e2)? true:false;
}

status print(ElemType e )
{
	cout<<e<<"  ";
	return OK;
}


/*
运行结果:
2
1在第2个
长度2
第2二个数据元素为:1
清空成功，下面开始新的线性表
4的前驱是6
5的后继是6
5  6  4
销毁线性表,程序结束。
Press any key to continue
*/