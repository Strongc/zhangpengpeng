/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��4��20��
��    �ڣ���2��
��    �ţ�ϰ��4
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void main()
{
	ifstream infile;
	int i;
	char x;			//x������ͣ
	string data;
	char name[20];
	
	cout<<"Please input the file name :";
	cin>>name;
	
	infile.open(name);
	if(!infile)
	{
		cout<<"Fail to open the file!";
		exit(0);
	}

	for(i=1;!infile.eof();i++)
	{
		infile>>data;
		cout<<i
			<<":"
			<<data
			<<endl;
		if(i%24==0)
		{
			cout<<"Press enter to continue";
			cin.ignore();
			cin.get(x);
		}
	}
	
	infile.close();

}



/*
Please input the file name :abc.txt
1:af
2:adgfa
3:gfsd
4:e
5:adf
6:asdg
7:e
8:adefsd
9:e
10:e
11:gdsa
12:gre
13:eagae
14:ade
15:gae
16:fgr
17:agr
18:hrewr
19:aewqe
20:aetewr
21:adaer
22:aetwqa
23:aerqer
24:aetrqera4
Press enter to continue
25:qeqerq
26:3efqe
27:qer3
28:qerqarq34tq
29:qerq3gaer
30:qerq3q
31:3q5aeq3
32:over
Press any key to continue
*/