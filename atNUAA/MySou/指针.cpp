/*
֤��C++�������ж�ָ���дָ����ͬһ��
*/

#include <fstream.h>
#include <iostream.h>
#include <stdlib.h>

void main()
{
	fstream file;
	
	file.open("DirectX",ios::in|ios::out);
	if(!file)
	{
		cout<<"Open file failes!";
		exit(0);
	}

	file.seekp(32L,ios::beg);
	cout<<file.tellp()<<endl;
	file.seekg(23L,ios::beg);
	cout<<file.tellp()<<endl;
	cout<<file.tellg()<<endl;
}

/*
32
23
23
Press any key to continue
*/