/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��4��20��
��    �ڣ���2��
��    �ţ�ϰ��5
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void main()
{
	ifstream infile;
	string data1,data2;
	char name[20];
	int i;

	cout<<"Please input the file name:";
	cin>>name;
	cout<<"\nPlease input the string:";
	cin>>data1;

	infile.open(name);
	if(!infile)
	{
		cout<<"Fail to open the file!";
		exit(0);
	}

	for(i=0;!infile.eof();)
	{
		infile>>data2;
		if(data1==data2)
		{
			i++;
			cout<<data2<<endl;
		}
	}

	cout<<"\n"
		<<data1
		<<" appear for "
		<<i
		<<" times."
		<<endl;
	
}



/*
Please input the file name:abc.txt

Please input the string:e
e
e
e
e

e appear for 4 times.
Press any key to continue
*/