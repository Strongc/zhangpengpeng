/*
040630416	������
��һ����ҵ����һ��
������洢�ṹʵ��P19�����Ա�Ļ�������
*/

typedef int ElemType;

#include "1_1.h"
#include <iostream.h>

void main()
{
	bool equal(ElemType,ElemType);		//��(*compare)()��ʵ��
	status print(ElemType);				//��(*visit)()��ʵ��

	LinkList L;
	ElemType e=0;

	InitList(L);
	ListInsert(L,1,1);
	ListInsert(L,1,2);
	ListInsert(L,2,3);				//2,3,1
	ListDelete(L,1,e);				//3,1
	cout<<e<<endl;
	cout<<"1�ڵ�"<<LocateElem(L,1,equal)<<"��"<<endl;
	if(ListEmpty(L))
	{
		cout<<"����"<<ListLength(L)<<endl;
		if(GetElem(L,2,e))
			cout<<"��2��������Ԫ��Ϊ:"<<e<<endl;
	}

	if(ClearList(L))
		cout<<"��ճɹ������濪ʼ�µ����Ա�"<<endl;
	ListInsert(L,1,4);
	ListInsert(L,1,5);
	ListInsert(L,2,6);				//5,6,4
	if(PriorElem(L,4,e))
		cout<<"4��ǰ����"<<e<<endl;
	if(NextElem(L,5,e))
		cout<<"5�ĺ����"<<e<<endl;
	ListTraverse(L,print);

	if(DestroyList(L))
		cout<<endl<<"�������Ա�,���������"<<endl;
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
���н��:
2
1�ڵ�2��
����2
��2��������Ԫ��Ϊ:1
��ճɹ������濪ʼ�µ����Ա�
4��ǰ����6
5�ĺ����6
5  6  4
�������Ա�,���������
Press any key to continue
*/