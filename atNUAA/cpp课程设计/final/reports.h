/*
    C++课程设计
程序作者：张鹏鹏
学    号：040630416
*/


int reports()
{
	int i=0;			//用来做返回值，无实际意义。下面也可能用来计数

	int showReportsmenu();
	void showAll();				//函数申明
	void showWholesale();
	void showRetail();
	void showQty();
	void showWh();
	void showDate();

	while(1)
	{
		switch(showReportsmenu())
			{
				case 1 :showAll();
						break;
				case 2 :showWholesale();
						break;
				case 3 :showRetail();
						break;
				case 4 :showQty();
						break;
				case 5 :showWh();
						break;
				case 6 :showDate();
						break;
				case 7 :return i;
						break;
			}
	}

}



int showReportsmenu()
{
	int choice;
	system("cls");				//清屏

	cout<<"	 			 书店图书管理系统						\n"
		<<"	 			    报表模块							\n"
		<<"	 	 1. 书库列表		\n"
		<<"		 2. 批发价列表		\n"
		<<"	 	 3. 零售价列表		\n"
		<<"		 4. 按书的数量列表	\n"
		<<"		 5. 按书的价值额列表\n"
		<<"		 6. 按进书日期列表	\n"
		<<"		 7. 返回主菜单		\n"
		<<"											\n"
		<<"			  输入选择：					\n"
		<<"			  请输入1～7之间的数:";
	cin>>choice;
	cin.clear();
	cin.ignore();
	while(choice<1||choice>7)
	{
		cout<<"			  请输入1～7之间的数:";
		cin>>choice;
		cin.clear();
		cin.ignore();
	}
	return choice;
}

void showAll()
{
	BookData book;
	int i=0;			//用于分屏显示时计数

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
	file.read((char*)&book,sizeof(book));
	while(!file.eof())
	{
		if(!book.isEmpty())
		{
			i++;
			cout<<"ISBN 号:"<<book.getISBN()
				<<"	书名:"<<book.getTitle()<<endl
				<<"	作者:"<<book.getAuthor()
				<<"	进书日期:"<<book.getDateAdded()
				<<"	出版社:"<<book.getPub()<<endl
				<<"	库存量:"<<book.getQty()
				<<"	批发价:"<<book.getWholesale()
				<<"	零售价:"<<book.getRetail()<<endl;
			if(i%10==0&&i>0)
				system("pause");
		}
		file.read((char*)&book,sizeof(book));
	}
	system("pause");
	file.close();
}

void showWholesale()
{
	BookData book;
	int i=0;			//用于分屏显示时计数
	float total=0;		//记录批发价总额

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
	cout<<setw(14)<<"ISBN号"<<setw(7)<<"批发价"<<setw(7)<<"库存量"<<"书  名"<<endl;
	file.read((char*)&book,sizeof(book));
	while(!file.eof())
	{
		if(!book.isEmpty())
		{
			i++;
			cout<<setw(14)<<book.getISBN()
				<<setw(7)<<book.getWholesale()
				<<setw(7)<<book.getQty()
				<<book.getTitle()<<endl;
			if(i%10==0&&i>0)
				system("pause");
			total+=book.getQty()*book.getWholesale();
		}
		file.read((char*)&book,sizeof(book));
	}
	cout<<"所有图书的批发价总和为：RMB"
		<<total<<endl;
//	cout.flush();
	system("pause");
	file.close();
}

void showRetail()
{
	BookData book;
	int i=0;			//用于分屏显示时计数
	float total=0;		//记录零售价总额

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
	cout<<setw(14)<<"ISBN号"<<setw(7)<<"零售价"<<setw(7)<<"库存量"<<"书  名"<<endl;
	file.read((char*)&book,sizeof(book));
	while(!file.eof())
	{
		if(!book.isEmpty())
		{
			i++;
			cout<<setw(14)<<book.getISBN()
				<<setw(7)<<book.getRetail()
				<<setw(7)<<book.getQty()
				<<book.getTitle()<<endl;
			if(i%10==0&&i>0)
				system("pause");
			total+=book.getQty()*book.getRetail();
		}
		file.read((char*)&book,sizeof(book));
	}
	cout<<"	所有图书的零售价总和为：RMB"
		<<total<<endl;
	system("pause");
	file.close();
}

void showQty()
{
	BookData *pr[1000];
	BookData *p;	//通过指针数组排序,p为交换时的中间变量
	int i,j,k;		//j记录书的总数，为i的最大值;i,k参与排序

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
	i=0;
	try
	{
		pr[i]=newBookData();
		file.read((char*)pr[i],sizeof(BookData));
	}catch(char *String)
	{
		cout<<String;
		exit(0);
	}
	while(!file.eof())
	{
		if(!pr[i]->isEmpty())		//分配内存
			i++;
		try
		{
			pr[i]=newBookData();
			file.read((char*)pr[i],sizeof(BookData));
		}catch(char *String)
		{
			cout<<String;
			exit(0);
		}
	}
	j=i;
	for(i=0;i<j;i++)
	{
		for(k=i+1;k<j;k++)
			if(pr[k]->getQty()>pr[i]->getQty())		//交换指针来完成排序
			{
				p=pr[i];
				pr[i]=pr[k];
				pr[k]=p;
			}
	}

	cout<<setw(14)<<"ISBN号"<<setw(7)<<"库存量"<<"书  名"<<endl;
	for(i=0;i<j;i++)
	{
		cout<<setw(14)<<pr[i]->getISBN()
			<<setw(7)<<pr[i]->getQty()
			<<pr[i]->getTitle()<<endl;
			if(i%10==0&&i>0)
				system("pause");
	}
	cout<<"输出结束!"<<endl;
	system("pause");
	file.close();
}

void showWh()
{
	BookData *pr[1000];
	BookData *p;	//通过指针数组排序,p为交换时的中间变量
	int i,j,k;		//j记录书的总数，为i的最大值;i,k参与排序

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
	i=0;
	try
	{
		pr[i]=newBookData();
		file.read((char*)pr[i],sizeof(BookData));
	}catch(char *String)
	{
		cout<<String;
		exit(0);
	}
	while(!file.eof())
	{
		if(!pr[i]->isEmpty())	
			i++;
		try
		{
			pr[i]=newBookData();
			file.read((char*)pr[i],sizeof(BookData));
		}catch(char *String)
		{
			cout<<String;
			exit(0);
		}
	}
	j=i;
	for(i=0;i<j;i++)
	{
		for(k=i+1;k<j;k++)
			if((pr[k]->getQty()*pr[k]->getWholesale())>(pr[i]->getQty()*pr[i]->getWholesale()))		//交换指针来完成排序
			{
				p=pr[i];
				pr[i]=pr[k];
				pr[k]=p;
			}
	}

	cout<<setw(14)<<"ISBN号"<<setw(9)<<"价值额"<<"书  名"<<endl;
	for(i=0;i<j;i++)
	{
		cout<<setw(14)<<pr[i]->getISBN()
			<<setw(9)<<(pr[i]->getQty()*pr[i]->getWholesale())
			<<pr[i]->getTitle()<<endl;
			if(i%10==0&&i>0)
				system("pause");
	}
	cout<<"输出结束!"<<endl;
	system("pause");
	file.close();
}

void showDate()
{
	BookData *pr[1000];
	BookData *p;	//通过指针数组排序,p为交换时的中间变量
	int i,j,k;		//j记录书的总数，为i的最大值;i,k参与排序

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
	i=0;
	try
	{
		pr[i]=newBookData();
		file.read((char*)pr[i],sizeof(BookData));
	}catch(char *String)
	{
		cout<<String;
		exit(0);
	}
	while(!file.eof())
	{
		if(!pr[i]->isEmpty())
			i++;
		try
		{
			pr[i]=newBookData();
			file.read((char*)pr[i],sizeof(BookData));
		}catch(char *String)
		{
			cout<<String;
			exit(0);
		}
	}
	j=i;
	for(i=0;i<j;i++)
	{
		for(k=i+1;k<j;k++)
			if(strcmp(pr[k]->getDateAdded(),pr[i]->getDateAdded())<0)		//交换指针来完成排序
			{
				p=pr[i];
				pr[i]=pr[k];
				pr[k]=p;
			}
	}

	cout<<setw(14)<<"ISBN号"<<setw(11)<<"进书日期"<<"书  名"<<endl;
	for(i=0;i<j;i++)
	{
		cout<<setw(14)<<pr[i]->getISBN()
			<<setw(11)<<pr[i]->getDateAdded()
			<<pr[i]->getTitle()<<endl;
			if(i%10==0&&i>0)
				system("pause");
	}
	cout<<"输出结束!"<<endl;
	system("pause");
	file.close();
}

