#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>


void fileopen(fstream &);
void main()
{
	int i=0;
	fstream file;
	try						//���ļ��������쳣����
	{
		fileopen(file);
	}catch(char *exceptionString)
	{
		cout<<exceptionString;
		exit(0);
	}
	file<<i;
	i=1;
	cout<<i<<endl;
	file.clear();
	file.seekg(0L,ios::beg);
	file>>i;
	cout<<i<<endl;
}
void fileopen(fstream &file)			//���Ӻ����У������쳣����
{
	file.open("Info.dat",ios::out|ios::in|ios::binary);
	if(!file)
		throw "���ļ�ʧ�ܣ�";
}
