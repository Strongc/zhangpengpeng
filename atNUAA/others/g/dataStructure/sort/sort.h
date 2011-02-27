
/***************************************
   for my postgraduate student life
   by Zhang Pengpeng 
   rocflyhi@gmail.com
**************************************/
   
#include "preDefine.h"

#define MAXSIZE 10
typedef int KeyType;

typedef struct 
{
	KeyType key;
	//InfoType info;
}RedType;

typedef struct 
{
	RedType r[MAXSIZE+1];
	int length;
}SqList;

void intialList(SqList **L);	//intial list with random digits
void showAll(SqList *L);	//display all elements in the list L
void insertSort(SqList *L);	//sort the list L using insertSort Method
