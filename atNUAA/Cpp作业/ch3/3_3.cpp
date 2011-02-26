/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年5月10日
章    节：第3章
题    号：习题3
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
		cout<<"请输入第"<<i+1<<"个数据";
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
请输入第1个数据31.432
请输入第2个数据234.31
请输入第3个数据43
请输入第4个数据23.54
83.0705
Press any key to continue
*/
