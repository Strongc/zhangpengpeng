/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��4��19��
��    �ڣ���1��
��    �ţ�ϰ��11
*/


#include <iostream>
#include <string>
using namespace std;

void main()
{
	string date,name,money;
	int i,dot;

	cout<<"����������(YYYY/MM/DD):";			//�ռ���Ϣ
	cin>>date;
	cout<<"�������������:";
	cin>>name;
	cout<<"��������(nnnn.nn):";
	cin>>money;

	date.replace(4,1,"��");			//�������ں�������RMB
	date.replace(8,1,"��");
	date.append("��");
	cout<<"����"<<date<<endl;
	cout<<"����"<<name<<"   ";
	cout<<"RMB"<<money<<endl;

	cout<<"�����:";				//�����д�����
	dot=money.find('.');
	for(i=0;money[i]!='\0';i++)
	{
		switch(money[i])
		{	
			case '0':	cout<<"��";
						break;
			case '1':	cout<<"Ҽ";
						break;
			case '2':	cout<<"��";
						break;
			case '3':	cout<<"��";
						break;
			case '4':	cout<<"��";
						break;
			case '5':	cout<<"��";
						break;		
			case '6':	cout<<"½";
						break;		
			case '7':	cout<<"��";
						break;		
			case '8':	cout<<"��";
						break;
			case '9':	cout<<"��";
						break;		
		}

		switch(dot-i)
		{
			case 4:	cout<<"Ǫ";
					break;
			case 3:	cout<<"��";
					break;
			case 2:	cout<<"ʰ";
					break;
			case 1:	cout<<"Ԫ";
					break;
			case 0:	;
					break;
			case -1:	cout<<"��";
					break;
			case -2:	cout<<"��";
					break;
		}
	}
		
}




/*
��һ�����У�
����������(YYYY/MM/DD):2007/04/19
�������������:Roc
��������(nnnn.nn):123.45
����2007��04��19��
����Roc   RMB123.45
�����:Ҽ�۷�ʰ��Ԫ�������Press any key to continue

�ڶ������У�
����������(YYYY/MM/DD):2007/04/20
�������������:Rocflyhi
��������(nnnn.nn):9876.54
����2007��04��20��
����Rocflyhi   RMB9876.54
�����:��Ǫ�ư���ʰ½Ԫ�������Press any key to continue
*/