/*
�������ߣ�������
ѧ    �ţ�040630416
������ڣ�2007��4��13��
��    �ڣ���1��
��    �ţ�ϰ��4
*/

#include<iostream.h>
void change(char *ch);

void main()
{
	char str[101];

	cout<<"������һ�仰\n";
	cin.getline(str,101);
	change(str);			//ת��
	cout<<"ת����Ϊ��"
		<<str<<endl;
}

void change(char *ch)
{
	char *cp;
	if('a'<=*ch&&*ch<='z')			//�����һ����ĸ
		*ch=*ch-'a'+'A';
	cp=ch+1;
	while(*cp!='\0')
	{
		if(*cp>='a'&&*cp<='z'&&*(cp-1)==' ')
			*cp=*cp-'a'+'A';
		cp++;
	}
}