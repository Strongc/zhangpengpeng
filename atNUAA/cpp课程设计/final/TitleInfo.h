/*
    C++�γ����
�������ߣ�������
ѧ    �ţ�040630416
*/


#ifndef TITLEINFO_H
#define TITLEINFO_H
#include <iostream.h>
#include <string.h>
class TitleInfo{
private:
	char isbn[14];				//ISBN��
	char title[51];				//����
	char author[31];			//����
	char publisher[31];			//���浥λ
public:
	void setISBN(char *ch){strcpy(isbn,ch);}
	void setTitle(char *ch){strcpy(title,ch);}
	void setAuthor(char *ch){strcpy(author,ch);}
	void setPub(char *ch){strcpy(publisher,ch);}

	char *getISBN(){return isbn;}
	char *getTitle(){return title;}
	char *getAuthor(){return author;}
	char *getPub(){return publisher;}

	bool bookMatch(char *);					//������������ƥ��򲿷ֱ������
};
#endif