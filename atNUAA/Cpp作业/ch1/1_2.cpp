/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��4��6��
��    �ڣ���1��
��    �ţ�ϰ��2
*/

#include <iostream.h>

void main()
{
	float rain[12],r,
		sum,ave;
	int i,
		max,min;

	cout<<"������ʮ�����µĽ�����"<<endl;
	for(i=0;i<12;i++)
	{
		cin>>r;
		if(r<0)
		{	
			cout<<"����������";
			i--;
		}
		else  rain[i]=r;
	}
	max=0;
	min=0;
	sum=rain[0];
	for(i=1;i<12;i++)
	{
		sum=sum+rain[i];
		if(rain[max]<rain[i])
			max=i;
		if(rain[min]>rain[i])
			min=i;
	}
	ave=sum/12;
	
	cout<<"һ����ܽ�������"
		<<sum<<endl;
	cout<<"ƽ��ÿ�µĽ�������"
		<<ave<<endl;
	cout<<max+1<<"�µĽ��������"<<endl;
	cout<<min+1<<"�µĽ�������С"<<endl;
}