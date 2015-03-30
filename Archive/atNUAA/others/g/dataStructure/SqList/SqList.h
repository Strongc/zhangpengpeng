
/***************************************
   for my postgraduate student life
   by Zhang Pengpeng 
   rocflyhi@gmail.com
**************************************/
   

/*****************************************
 Abstract Data Type : linear_list
 ADT List implemented using sequence address memory
*****************************************/

#include "../preDefine.h"
typedef int ElemType;

#define LIST_INIT_SIZE 100	//initial memory size allocated
#define LISTINCREMENT 10	//increment memory size each time

typedef struct 
{
	ElemType * elem;	//base address 
	int length;		//current length used
	int listsize;		//current size of the memory allocated
} SqList;

