/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��6��26��
��    �ڣ���7��
��    �ţ�ϰ��5
*/
//˵�������ձ����Ҫ��FreewillArray������Ҫ�Լ�����ģ�
//��������ģ�治������Ҫ��FreewillArray������Ӵ󣬶�����ĩ������ʱ�����
//��Ҳ��һ�дӼ�,������!

#include <iostream.h>
#include <stdlib.h>

template <class T>
class SortableArray{
private:
	T *aptr;
	int arraySize;
	void sort();
public:
	SortableArray(int n)
	{
		arraySize=n;
		aptr=new T[n];
		if(aptr==0)
		{
			cout<<"�����ڴ�ʧ�ܣ�"<<endl;
			exit(0);
		}
		for(int i=0;i<arraySize;i++)
		{
			cout<<"�������"
				<<i+1
				<<"�����ݣ�";
			cin>>aptr[i];
		}
		sort();
	}
	void getData()
	{
		cout<<"������������Ϊ��"<<endl;
		for(int i=0;i<arraySize;i++)
			cout<<aptr[i]<<"\t";
		cout<<endl;
	}
};

template <class T>
void SortableArray<T>::sort()
{
	T temp;
	for(int i=0;i<arraySize;i++)
		for(int j=i+1;j<arraySize;j++)
			if(aptr[i]>aptr[j])
			{
				temp=aptr[i];
				aptr[i]=aptr[j];
				aptr[j]=temp;
			}
}
void main()
{
	cout<<"int���ͣ�"<<endl;
	SortableArray <int> intTable(5);
	intTable.getData();

	cout<<"float���ͣ�"<<endl;
	SortableArray <float> floatTable(3);
	floatTable.getData();
}


/*
int���ͣ�
�������1�����ݣ�1
�������2�����ݣ�4
�������3�����ݣ�5
�������4�����ݣ�2
�������5�����ݣ�3
������������Ϊ��
1       2       3       4       5
float���ͣ�
�������1�����ݣ�1.2
�������2�����ݣ�3.0
�������3�����ݣ�2.1
������������Ϊ��
1.2     2.1     3
Press any key to continue
*/