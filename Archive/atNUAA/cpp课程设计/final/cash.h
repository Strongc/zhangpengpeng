/*
    C++课程设计
程序作者：张鹏鹏
学    号：040630416
*/

void cash()
{
	int i=0;			//用来计数
	float taxRate;
	int number;			//用来记录一个人要买书的种数
	char isbn[14];
	int bookNum;		//此种书的本数
	Sale *Spr[51];			//指针数组，指向类
	BookData *BDpr[51];
	Sale temp;	//temp用来修改销售税率

	char ch;				//用于问是非还有顾客买书

	float total=0;			//用来记录此次使用此程序时的总收入
	float cost=0;				//用来记录此次使用此程序时的总成本

	fstream file;
	try						//打开文件，并有异常处理
	{
		fileopen(file);
	}catch(char *exceptionString)
	{
		cout<<exceptionString;
		exit(0);
	}
	
	bool search(fstream &,char *);			//函数申明
	void BDtoSa(BookData *,Sale *);

	cout<<"请输入销售税率:";
	cin>>taxRate;
	temp.setTaxRate(taxRate);

	while(1)
	{
		system("cls");
		cout<<"这名顾客需要买几种书？";
		cin>>number;
		cin.ignore();
		number=ensurePosi(number);
		
		for(i=0;i<number;i++)				//输入处理
		{
			cout<<"请输入第"
				<<i+1
				<<"种书的ISBN号：";
			cin.getline(isbn,14);
			if(search(file,isbn))
			{	
				try
				{
					Spr[i]=newSale();
					BDpr[i]=newBookData();
				}catch(char *String)
				{
					cout<<String;
					exit(0);
				}
				file.seekg((0-sizeof(BookData)),ios::cur);
				file.read((char*)BDpr[i],sizeof(BookData));
				BDtoSa(BDpr[i],Spr[i]);
				cout<<"请输入要买的本数：";
				cin>>bookNum;
				cin.ignore();
				bookNum=ensurePosi(bookNum);
				while((Spr[i]->getQty()-bookNum)<0)
				{
					cout<<"库存量不足，请重新输入："<<endl;
					cin>>bookNum;
					cin.ignore();
				}
				Spr[i]->setQtySold(bookNum);			//处理交易
				
				BDpr[i]->setQty(BDpr[i]->getQty()-bookNum);			//处理库存量
				file.seekp((0-sizeof(BookData)),ios::cur);
				file.write((char*)BDpr[i],sizeof(BookData));
				
			}
			else
			{
				cout<<"输入ISBN号错误"<<endl;
				i=i-1;			
			}
		}
			
		//输出处理
		cout<<"	 			 前台销售模块						\n"
			<<"数量	 ISBN号		书名			单价	   金额 \n"
			<<endl;
		for(i=0;i<number;i++)							//位置对齐最后调整
		{
			cout<<setw(7)
				<<Spr[i]->getQtySold()
				<<setw(14)
				<<Spr[i]->getISBN()
				<<setw(24)
				<<Spr[i]->getTitle()
				<<"RMB"
				<<setw(10)
				<<Spr[i]->getRetail()
				<<"RMB"
				<<Spr[i]->getSales()<<endl;
		}
		cout<<endl;
		cout<<"		销售合计:	RMB"
			<<Spr[0]->getTotal()
			<<endl;		//安照常理，零售税哪有让消费者承当的道理，在此删了
		cout<<"				谢谢光临";

		total=total+Spr[0]->getTotal();
		cost=cost+Spr[0]->getTotalCost();
		Spr[0]->setTotal(0);			
		Spr[0]->setTotalCost(0);

		cout<<"\n\n\n\t还有顾客要买书吗？(Y/N) ";
		cin>>ch;
		while(ch!='y'&&ch!='Y'&&ch!='n'&&ch!='N')
		{
			cout<<"请输入Y或N ：";
			cin>>ch;
		}
			
		if(ch=='n'||ch=='N')
			break;
	}
	system("cls");
	cout<<"\n\n"
		<<"		此次经营共收入RMB "
		<<total
		<<"\n		其中总成本为RMB "
		<<cost
		<<"\n		总利润为RMB "
		<<total-cost<<endl;
	file.close();
	cout<<"回主菜单。"<<endl;
	system("pause");
	system("cls");
}


bool search(fstream &file,char *isbn)		//实现查找
{
	file.clear();
	file.seekg(0L,ios::beg);
	BookData bd;
	file.read((char*)&bd,sizeof(bd));
	while(!file.eof())
	{
		if(strcmp(bd.getISBN(),isbn)==0&&strcmp(bd.getTitle(),"")!=0)
			return true;
		file.read((char*)&bd,sizeof(bd));
	}
	return false;
}

void BDtoSa(BookData *bd,Sale *s)			//对Sale类进行赋值
{
	s->setISBN(bd->getISBN());
	s->setTitle(bd->getTitle());
	s->setAuthor(bd->getAuthor());
	s->setPub(bd->getPub());

	s->setDateAdded(bd->getDateAdded());
	s->setQty(bd->getQty());
	s->setWholesale(bd->getWholesale());
	s->setRetail(bd->getRetail());
}