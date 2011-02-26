/*
    C++课程设计
程序作者：张鹏鹏
学    号：040630416
*/

#ifndef SALE_H
#define SALE_H
#include "BookData.h"
class Sale:public BookData{
private:
	static float taxRate;				//销售税率
	static float total;					//所有销售的额,我限制为一次交易，总的再在主函数中定义
	static float totalCost;				//我定义此为总成本，我限制为一次交易，总的再在主函数中定义
	int qtySold;						//一次购买某种书的数量
	float sales;						//我的定义为这种书的销售额
	float tax;							//该次购买的销售税，一种书
	float subtotal;						//我定义此为成本,一种书

	void setSales(){sales=getRetail()*qtySold;}	
	void setTotal(){total+=sales;}			
	void setTax(){tax=sales*taxRate;}
	void setSubtotal(){subtotal=getWholesale()*qtySold+tax;}
	void setTotalCost(){totalCost+=subtotal;}
public:
	void setTaxRate(float f){taxRate=ensurePosi(f);}			//ensurePosi()来自父类
	void setTotal(float f){total=ensurePosi(f);}				//重载
	void setTotalCost(float f){totalCost=ensurePosi(f);}		//重载
	void setQtySold(int);
	
	float getTaxRate(){return taxRate;}
	float getTotal(){return total;}
	float getTotalCost(){return totalCost;}
	int getQtySold(){return qtySold;}
	float getSales(){return sales;}
	float getTax(){return tax;}
	float getSubTotal(){return subtotal;}
};
#endif

float Sale::taxRate=0;
float Sale::total=0;
float Sale::totalCost=0;

void Sale::setQtySold(int i)
{
	qtySold=ensurePosi(i);
	setSales();
	setTotal();
	setTax();
	setSubtotal();
	setTotalCost();
	setQty(getQty()-qtySold);
}


/*
此类，书上的定义模糊不清，我未按照书来
*/