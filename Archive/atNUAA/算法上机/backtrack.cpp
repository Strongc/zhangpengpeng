//������  040630416
//���ݷ�ʵ���Ӽ�������

#include <iostream.h>
#include <stdlib.h>

int X[10]={10,20,30,40,50,60,70,80,90,100};//XΪ�������Ӽ�
int Y;//YΪ���ĺ�
int v[10]={0};//vΪ������,�������ѳ�ʼ����һ��ֻ�ܴ���һ��Y�������ѭ�����������³�ʼ��
bool flag;

void output()			//����������
{
	cout<<" v :";
	for(int i=0;i<10;i++)
		cout<<"  "<<v[i]<<",";
	cout<<endl;
	flag=true;
}

int getSum()			//����ͣ��ж��Ƿ�Ϊ���ս�
{
	int sum=0;
	int x=10;
	for(int i=0;i<10;i++)
		sum+=x*(i+1)*v[i];
	return sum;
}

void advance(int k)			//�ݹ�
{
	if(k<0) return;//kΪ-1ʱ��ȷ�����޽��ˣ�����-1�˳��ݹ�

	v[k]=1;
	if(getSum()==Y)
	{
		output();
		v[k]=0;
	}
	if(getSum()<Y)			//�������
	{
		if(k<9)
			advance(k+1);
	}
	else					//����
	{
		v[k]=0;
		for(;k>=0;k--)
			if(v[k]==1)
			{
				v[k]=0;
				advance(k+1);
			}
		if(k<0) advance(k);//kΪ-1ʱ��ȷ�����޽��ˣ�����-1�˳��ݹ�
	}
}

void main()
{
	cout<<"Please input a number(30~100):";
	cin>>Y;
	if(Y<30||Y>100)
	{
		cout<<"Input False!";
		system("pause");
		exit(0);
	}
	flag=false;
	cout<<" X : 10, 20, 30, 40, 50, 60, 70, 80, 90, 100"<<endl
		<<endl;
	advance(0);
	if(flag==false)
		cout<<"\n No Solution!";
	cout<<"\n----------END-----------"<<endl;
	system("pause");

}
