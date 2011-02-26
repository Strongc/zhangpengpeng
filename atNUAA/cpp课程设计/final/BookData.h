/*
    C++�γ����
�������ߣ�������
ѧ    �ţ�040630416
*/


#ifndef BOOKDATA_H
#define BOOKDATA_H

#include "TitleInfo.h"
class BookData:public TitleInfo{
private:
	char dateAdded[11];				//�����������
	int qtyOnHand;					//����Ŀ����
	float wholesale;				//������
	float retail;					//���ۼ�
public:
	bool error(char *);				//����������Ч�Լ���,������ҲҪ��
	int ensurePosi(int);			//��֤int���͵�����Ϊ�Ǹ�����������ҲҪ��
	float ensurePosi(float);		//��֤float���͵�����Ϊ�Ǹ�����������ҲҪ��

	void setDateAdded(char*);
	void setQty(int qty){qtyOnHand=ensurePosi(qty);}
	void setWholesale(float sale){wholesale=ensurePosi(sale);}
	void setRetail(float re){retail=ensurePosi(re);}
	
	char *getDateAdded(){return dateAdded;}
	int getQty(){return qtyOnHand;}
	float getWholesale(){return wholesale;}
	float getRetail(){return retail;}
	
	bool isEmpty();					//�жϴ˶����Ƿ�Ϊ�գ���ɾ�ˣ�
	void removeBook();				//ɾ��ָ��Ԫ��
};
#endif