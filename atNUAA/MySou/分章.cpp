#include <iostream.h>
#include <fstream>
#include <string>
using namespace std;

void main()
{
	ifstream infile;
	ofstream outfile;
	int i=0,j,num1,num2,num3;
	char name[]="000.txt";
	string data;

	infile.open("x.txt");		//打开源文件
	if(!infile)
	{
		cout<<"Open failed!";
		exit(0);
	}
	outfile.open("000.txt");			//打开生成文件
	if(!outfile)
	{
		cout<<"Open failed!";
		exit(0);
	}

	while(!infile.eof())		//开始处理
	{		
		infile>>data;
		num1=data.find("第");
		num3=data.find("完");
		num2=data.find("章");
		if(num1!=0||num2<0||num3>0||(num2-num1)>15||(num2-num1)<0)
			outfile<<data;
		else
		{
			i++;
			j=i;						//处理生成文件的命名
			if(j<10)					
				name[2]='0'+j;
			else
				if(j<100)
				{	
					name[2]='0'+j%10;
					name[1]='0'+j/10;
				}
				else
				{
					name[2]='0'+j%10;
					j=j/10;
					name[1]='0'+j%10;
					name[0]='0'+j/10;
				}
			
			outfile.close();
			outfile.open(name);			//生成下一个文件
			if(!outfile)
			{
				cout<<"Open failed!";
				exit(0);
			}
			cout<<name<<"\t";
			outfile<<data<<endl;
		}
	}
	outfile.close();			//关闭最后一个文件
	infile.close();

	cout<<endl;				//输出缓存里的东西
	system("pause");
}