/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��4��13��
��    �ڣ���1��
��    �ţ�ϰ��9
*/

#include <iostream.h>
float mid(int *,int);

void main()
{
	int numbers[100],
		num=0,i;		//num����,
	cout<<"�������뼸��������\n";
	cin>>num;
	cout<<"������һ������\n";
	for(i=0;i<num;i++)
		cin>>numbers[i];
	cout<<"��ֵ��"
		<<mid(numbers,num)<<endl;
}

float mid (int *p,int n)
{
	int i,j,x;  //xΪ�н�
	for(i=0;i<n;i++)
		for(j=i;j<n;j++)
			if(*(p+i)>*(p+j))
			{x=*(p+i);
			 *(p+i)=*(p+j);
			 *(p+j)=x;
			}
	if(n%2==1)		//����
		return *(p+(n-1)/2);
	else			//ż��
		return (*(p+n/2-1)+*(p+n/2))/2.0;

}