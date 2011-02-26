/*
    C++课程设计
程序作者：张鹏鹏
学    号：040630416
*/


#ifndef BOOKDATA_H
#define BOOKDATA_H

#include "TitleInfo.h"
class BookData:public TitleInfo{
private:
	char dateAdded[11];				//书店进书的日期
	int qtyOnHand;					//该书的库存量
	float wholesale;				//批发价
	float retail;					//零售价
public:
	bool error(char *);				//日期输入有效性检验,子类中也要用
	int ensurePosi(int);			//保证int类型的数据为非负数，子类中也要用
	float ensurePosi(float);		//保证float类型的数据为非负数，子类中也要用

	void setDateAdded(char*);
	void setQty(int qty){qtyOnHand=ensurePosi(qty);}
	void setWholesale(float sale){wholesale=ensurePosi(sale);}
	void setRetail(float re){retail=ensurePosi(re);}
	
	char *getDateAdded(){return dateAdded;}
	int getQty(){return qtyOnHand;}
	float getWholesale(){return wholesale;}
	float getRetail(){return retail;}
	
	bool isEmpty();					//判断此对象是非为空（被删了）
	void removeBook();				//删除指定元素
};
#endif