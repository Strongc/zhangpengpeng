/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��4��13��
��    �ڣ���1��
��    �ţ�ϰ��5
*/

#include<iostream.h>

void main()
{
	char stdAnswer[20]={'B','D','A','A','C','A','B','A','C','D',
						'B','C','D','A','D','C','D','B','D','A'},
			answer[20];		//answer��¼�����ش�Ĵ�
	int i,num;		//num��¼������ĸ���

	for(i=0;i<20;i++)				//����
	{	
		cout<<"�������"<<(i+1)<<"��Ĵ𰸣�\n";
		cin>>answer[i];
		if(answer[i]!='a'&&answer[i]!='A'&&answer[i]!='b'&&answer[i]!='B'
			&&answer[i]!='c'&&answer[i]!='C'&&answer[i]!='d'&&answer[i]!='D')
		{cout<<"������A��B��C��D\n";
		 i--;
		}
	}
	for(i=0,num=0;i<20;i++)			//�ж�
		if(answer[i]!=stdAnswer[i]&&
			answer[i]!=stdAnswer[i]-'A'+'a')
		{cout<<"\n��"<<(i+1)<<"������";
		 num++;
		}
	cout<<"\n�㹲��"<<num<<"��������\n";
	if(num<=8)
		cout<<"��ϲ��ͨ���˱�������";
	else
		cout<<"���ź�����û��ͨ���������ԣ������Ŭ��";

}