/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��4��6��
��    �ڣ���1��
��    �ţ�ϰ��1
*/

#include <iostream.h>

void main()
{
	int num[10],i,
		max,min,
		maxNum=1,minNum=1;
	cout<<"Please enter ten numbers"<<"\n";
	for(i=0;i<10;i++)
		cin>>num[i];
	max=num[0];
	min=num[0];
	for(i=1;i<10;i++)
		{	if(max<num[i])
				{	max=num[i];
					maxNum=1;
				}
			else if(max==num[i])
					maxNum++;
			if(min>num[i])
				{	min=num[i];
					minNum=1;
			}
			else if(min==num[i])
					minNum++;
		}
	cout<<"The max number is "
		<<max
		<<"���ֵ����"
		<<maxNum
		<<"����"<<endl;
	cout<<"the min number is "
		<<min
		<<"��Сֵ����"
		<<minNum
		<<"����";

}