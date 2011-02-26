/*
    C++课程设计
程序作者：张鹏鹏
学    号：040630416
*/


int stackmgr()
{
	int i=0;			//用来做返回值，无实际意义。下面也可能用来计数

	int showStackmenu();
	void lookUp();
	void lookUpISBN();
	void addBook();
	void editBook();
	void remove();

	while(1)
	{
		switch(showStackmenu())
			{
				case 1 :lookUp();
						break;
				case 2 :lookUpISBN();
						break;
				case 3 :addBook();
						break;
				case 4 :editBook();
						break;
				case 5 :remove();
						break;
				case 6 :return i;
						break;
			}
	}

}



int showStackmenu()
{
	int choice;
	system("cls");				//清屏

	cout<<"	 			 书店图书管理系统						\n"
		<<"	 			   书库管理菜单							\n"
		<<"	 	 1. 根据书名查找某书（模糊查找）				\n"
		<<"		 2. 根据ISBN号查找某书							\n"
		<<"	 	 3. 增加书										\n"
		<<"		 4. 修改书的信息								\n"
		<<"		 5. 删除书										\n"
		<<"		 6. 返回主菜单									\n"
		<<"														\n"
		<<"			  输入选择：								\n"
		<<"			  请输入1～6之间的数:";
	cin>>choice;
	cin.clear();
	cin.ignore();			
	while(choice<1||choice>6)
	{
		cout<<"			  请输入1～6之间的数:";
		cin>>choice;
		cin.clear();
		cin.ignore();
	}
	return choice;
}

void lookUp()
{
	BookData book;
	char title[51];
	bool bo=false;		//记录是否找到了书

	fstream file;
	try						//打开文件，并有异常处理
	{
		fileopen(file);
	}catch(char *exceptionString)
	{
		cout<<exceptionString;
		exit(0);
	}

	system("cls");				//清屏
	
	cout<<"请输入全部书名或部分书名：";
	cin.getline(title,51);
	file.read((char*)&book,sizeof(book));
	while(!file.eof())
	{
		if(book.bookMatch(title))
		{
			bo=true;
			cout<<"	 			 书店图书管理系统						\n"
				<<"	 				 书的资料		\n"
				<<"	 									\n"
				<<"	 	ISBN  号:"<<book.getISBN()<<endl
				<<"		书    名:"<<book.getTitle()<<endl
				<<"		作    者:"<<book.getAuthor()<<endl
				<<"		出 版 社:"<<book.getPub()<<endl
				<<"		进书日期:"<<book.getDateAdded()<<endl
				<<"		库 存 量:"<<book.getQty()<<endl
				<<"		批 发 价:"<<book.getWholesale()<<endl
				<<"		零 售 价:"<<book.getRetail()<<endl;
			system("pause");
		}
		file.read((char*)&book,sizeof(book));
	}
	if(bo==false)
		cout<<"无法找到你所要修改的书！";
	cout<<"\n查找结束！"<<endl;
	system("pause");
	file.close();
}

void lookUpISBN()
{
	BookData book;
	char isbn[14];
	bool bo=false;		//记录是否找到了书

	fstream file;
	try						//打开文件，并有异常处理
	{
		fileopen(file);
	}catch(char *exceptionString)
	{
		cout<<exceptionString;
		exit(0);
	}

	system("cls");				//清屏
	
	cout<<"请输入ISBN号：";
	cin.getline(isbn,14);
	file.read((char*)&book,sizeof(book));
	while(!file.eof())
	{
		if(strcmp(book.getISBN(),isbn)==0&&strcmp(book.getTitle(),"")!=0)
		{
			bo=true;
			cout<<"	 			 书店图书管理系统						\n"
				<<"	 				书的资料							\n"
				<<"	 									\n"
				<<"	 	ISBN  号:"<<book.getISBN()<<endl
				<<"		书    名:"<<book.getTitle()<<endl
				<<"		作    者:"<<book.getAuthor()<<endl
				<<"		出 版 社:"<<book.getPub()<<endl
				<<"		进书日期:"<<book.getDateAdded()<<endl
				<<"		库 存 量:"<<book.getQty()<<endl
				<<"		批 发 价:"<<book.getWholesale()<<endl
				<<"		零 售 价:"<<book.getRetail()<<endl;
			break;
		}
		file.read((char*)&book,sizeof(book));
	}
	if(bo==false)
		cout<<"无法找到你所要修改的书！";
	cout<<"\n查找结束！"<<endl;
	system("pause");
	file.close();
}

void addBook()
{
	BookData book;
	char isbn[14];				//ISBN号
	char title[51];				//书名
	char author[31];			//作者
	char publisher[31];			//出版单位
	char dateAdded[11];				//书店进书的日期
	int qtyOnHand;					//该书的库存量
	float wholesale;				//批发价
	float retail;					//零售价

	fstream file;
	try						//打开文件，并有异常处理
	{
		fileopen(file);
	}catch(char *exceptionString)
	{
		cout<<exceptionString;
		exit(0);
	}

	system("cls");				//清屏

	cout<<"请输入ISBN号:";
	cin.getline(isbn,14);
	book.setISBN(isbn);
	cout<<"请输入书名:";
	cin.getline(title,51);
	book.setTitle(title);
	cout<<"请输入作者:";
	cin.getline(author,31);
	book.setAuthor(author);
	cout<<"请输入出版单位:";
	cin.getline(publisher,31);
	book.setPub(publisher);
	cout<<"请输入进书日期（格式YYYY-MM-DD）:";
	cin.getline(dateAdded,11);
	book.setDateAdded(dateAdded);
	cout<<"请输入库存量:";
	cin>>qtyOnHand;
	book.setQty(qtyOnHand);
	cout<<"请输入批发价:";
	cin>>wholesale;
	book.setWholesale(wholesale);
	cout<<"请输入零售价:";
	cin>>retail;
	book.setRetail(retail);

	file.seekp(0L,ios::end);
	file.write((char*)&book,sizeof(book));
	file.close();


}

void editBook()
{
	BookData book;
	char isbn[14];				//ISBN号
	char title[51];				//书名
	char author[31];			//作者
	char publisher[31];			//出版单位
	char dateAdded[11];				//书店进书的日期
	int qtyOnHand;					//该书的库存量
	float wholesale;				//批发价
	float retail;					//零售价
	bool bo=false;		//记录是否找到了书

	fstream file;
	try						//打开文件，并有异常处理
	{
		fileopen(file);
	}catch(char *exceptionString)
	{
		cout<<exceptionString;
		exit(0);
	}

	system("cls");				//清屏
	
	cout<<"请输入要修改的书的ISBN号:";
	cin.getline(isbn,14);
	file.read((char*)&book,sizeof(book));
	while(!file.eof())
	{
		if(strcmp(book.getISBN(),isbn)==0&&strcmp(book.getTitle(),"")!=0)
		{
			bo=true;
			cout<<"下面开始修改书的信息:"<<endl;
			cout<<"请输入ISBN号:";
			cin.getline(isbn,14);
			book.setISBN(isbn);
			cout<<"请输入书名:";
			cin.getline(title,51);
			book.setTitle(title);
			cout<<"请输入作者:";
			cin.getline(author,31);
			book.setAuthor(author);
			cout<<"请输入出版单位:";
			cin.getline(publisher,31);
			book.setPub(publisher);
			cout<<"请输入进书日期（格式YYYY-MM-DD）:";
			cin.getline(dateAdded,11);
			book.setDateAdded(dateAdded);
			cout<<"请输入库存量:";
			cin>>qtyOnHand;
			book.setQty(qtyOnHand);
			cout<<"请输入批发价:";
			cin>>wholesale;
			book.setWholesale(wholesale);
			cout<<"请输入零售价:";
			cin>>retail;
			book.setRetail(retail);

			file.seekp((0-sizeof(BookData)),ios::cur);
			file.write((char*)&book,sizeof(BookData));

			break;
		}
		file.read((char*)&book,sizeof(book));
	}
	if(bo==false)
		cout<<"无法找到你所要修改的书！"<<endl;
	system("pause");
	file.close();
}


void remove()
{
	BookData book;
	char isbn[14];
	bool bo=false;		//记录是否找到了书
	char choice;		//确认是否删除

	fstream file;
	try						//打开文件，并有异常处理
	{
		fileopen(file);
	}catch(char *exceptionString)
	{
		cout<<exceptionString;
		exit(0);
	}

	system("cls");				//清屏
	
	cout<<"请输入ISBN号：";
	cin.getline(isbn,14);
	file.read((char*)&book,sizeof(book));
	while(!file.eof())
	{
		if(strcmp(book.getISBN(),isbn)==0&&strcmp(book.getTitle(),"")!=0)
		{
			bo=true;
			cout<<"	 			 书店图书管理系统						\n"
				<<"	 				书的资料							\n"
				<<"	 									\n"
				<<"	 	ISBN  号:"<<book.getISBN()<<endl
				<<"		书    名:"<<book.getTitle()<<endl
				<<"		作    者:"<<book.getAuthor()<<endl
				<<"		出 版 社:"<<book.getPub()<<endl
				<<"		进书日期:"<<book.getDateAdded()<<endl
				<<"		库 存 量:"<<book.getQty()<<endl
				<<"		批 发 价:"<<book.getWholesale()<<endl
				<<"		零 售 价:"<<book.getRetail()<<endl;
			cout<<"确认删除吗(Y/N)?  ";
			cin>>choice;
			while(choice!='y'&&choice!='Y'&&choice!='n'&&choice!='N')
			{
				cout<<"请输入Y或N ：";
				cin>>choice;
			}
			if(choice=='y'||choice=='Y')
			{
				book.removeBook();
				file.seekp((0-sizeof(BookData)),ios::cur);
				file.write((char*)&book,sizeof(BookData));
			}
			else
				cout<<"删除取消！"<<endl;

			break;
		}
		file.read((char*)&book,sizeof(book));
	}
	if(bo==false)
		cout<<"无法找到你所要修改的书！"<<endl;
	system("pause");
	file.close();
}

