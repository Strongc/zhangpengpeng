/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��4��13��
��    �ڣ���1��
��    �ţ�ϰ��3
*/

#include <iostream.h>
 
void main()
{
	char ch[101];
	int i;		//i��������

	cout<<"������һ���ַ�\n";
	cin>>ch;
	for(i=0;i<101;i++)
	{	if(ch[i]=='\0')
			break;
		else
			if('a'<=ch[i]&&ch[i]<='z')
				ch[i]=ch[i]-'a'+'A';
	}
	cout<<"���ǣ�"
		<<ch<<endl;

}