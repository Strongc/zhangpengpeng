
/***************************************
   for my postgraduate student life
   by Zhang Pengpeng 
   rocflyhi@gmail.com
**************************************/
   

/*****************************************
 Abstract Data Type : linear_list
 ADT List implemented using sequence address memory
*****************************************/

#include <stdlib.h>
#include "./SqList.h"

Status InitList_Sq(SqList *L)
{	//create a new sequence list called L
	L->elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L->elem)		//if failed to allocate memory
		exit(OVERFLOW);
	L->length = 0;			//set length to 0
	L->listsize = LIST_INIT_SIZE;	// initial size is given
	return OK;
}// InitList_Sq

int main()
{
	SqList *L;
	InitList_Sq(L);
	return 0;
}
