/*
    C++课程设计
程序作者：张鹏鹏
学    号：040630416
*/


#ifndef TITLEINFO_H
#define TITLEINFO_H
#include <iostream.h>
#include <string.h>
class TitleInfo{
private:
	char isbn[14];				//ISBN号
	char title[51];				//书名
	char author[31];			//作者
	char publisher[31];			//出版单位
public:
	void setISBN(char *ch){strcpy(isbn,ch);}
	void setTitle(char *ch){strcpy(title,ch);}
	void setAuthor(char *ch){strcpy(author,ch);}
	void setPub(char *ch){strcpy(publisher,ch);}

	char *getISBN(){return isbn;}
	char *getTitle(){return title;}
	char *getAuthor(){return author;}
	char *getPub(){return publisher;}

	bool bookMatch(char *);					//根据书名进行匹配或部分比配查找
};
#endif