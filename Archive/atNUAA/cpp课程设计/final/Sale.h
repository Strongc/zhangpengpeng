/*
    C++�γ����
�������ߣ�������
ѧ    �ţ�040630416
*/

#ifndef SALE_H
#define SALE_H
#include "BookData.h"
class Sale:public BookData{
private:
	static float taxRate;				//����˰��
	static float total;					//�������۵Ķ�,������Ϊһ�ν��ף��ܵ������������ж���
	static float totalCost;				//�Ҷ����Ϊ�ܳɱ���������Ϊһ�ν��ף��ܵ������������ж���
	int qtySold;						//һ�ι���ĳ���������
	float sales;						//�ҵĶ���Ϊ����������۶�
	float tax;							//�ôι��������˰��һ����
	float subtotal;						//�Ҷ����Ϊ�ɱ�,һ����

	void setSales(){sales=getRetail()*qtySold;}	
	void setTotal(){total+=sales;}			
	void setTax(){tax=sales*taxRate;}
	void setSubtotal(){subtotal=getWholesale()*qtySold+tax;}
	void setTotalCost(){totalCost+=subtotal;}
public:
	void setTaxRate(float f){taxRate=ensurePosi(f);}			//ensurePosi()���Ը���
	void setTotal(float f){total=ensurePosi(f);}				//����
	void setTotalCost(float f){totalCost=ensurePosi(f);}		//����
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
���࣬���ϵĶ���ģ�����壬��δ��������
*/