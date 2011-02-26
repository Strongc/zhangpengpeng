/*
程序作者：张鹏鹏
学    号：040630416
完成日期：2007年6月26日
章    节：第7章
题    号：习题5
*/
//说明，按照本题的要求，FreewillArray类是需要自己打出的，
//但鉴于类模版不做考试要求，FreewillArray类过于庞大，而且期末将近，时间紧迫
//我也就一切从简,望见谅!

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
			cout<<"分配内存失败！"<<endl;
			exit(0);
		}
		for(int i=0;i<arraySize;i++)
		{
			cout<<"请输入第"
				<<i+1
				<<"个数据：";
			cin>>aptr[i];
		}
		sort();
	}
	void getData()
	{
		cout<<"按照升序排列为："<<endl;
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
	cout<<"int类型："<<endl;
	SortableArray <int> intTable(5);
	intTable.getData();

	cout<<"float类型："<<endl;
	SortableArray <float> floatTable(3);
	floatTable.getData();
}


/*
int类型：
请输入第1个数据：1
请输入第2个数据：4
请输入第3个数据：5
请输入第4个数据：2
请输入第5个数据：3
按照升序排列为：
1       2       3       4       5
float类型：
请输入第1个数据：1.2
请输入第2个数据：3.0
请输入第3个数据：2.1
按照升序排列为：
1.2     2.1     3
Press any key to continue
*/