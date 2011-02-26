#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>


void fileopen(fstream &);
void main()
{
	int i=0;
	fstream file;
	try						//打开文件，并有异常处理
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
void fileopen(fstream &file)			//在子函数中，都有异常处理
{
	file.open("Info.dat",ios::out|ios::in|ios::binary);
	if(!file)
		throw "打开文件失败！";
}
