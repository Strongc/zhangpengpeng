/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��5��10��
��    �ڣ���3��
��    �ţ�ϰ��3
*/

#include <iostream.h>
#include <stdlib.h>

class Aver{
private:
	float *prf;
	int num;
	float sum;
public:
	Aver(const int count){
		prf=new float[count];
		num=count;
	}
	~Aver(){
		delete []prf;
	}
	void getdata();
	float averange();
};

void Aver::getdata()
{
	int i;
	for(i=0;i<num;i++){
		cout<<"�������"<<i+1<<"������";
		cin>>prf[i];
	}
}
float Aver::averange()
{
	int i;
	for(sum=0,i=0;i<num;i++)
		sum=sum+*(prf+i);
	return sum/num;
}

void main()
{
	Aver date(4);
	date.getdata();
	cout<<date.averange()<<endl;
}


/*
�������1������31.432
�������2������234.31
�������3������43
�������4������23.54
83.0705
Press any key to continue
*/
