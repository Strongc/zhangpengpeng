/*
    C++�γ����
�������ߣ�������
ѧ    �ţ�040630416
*/


int reports()
{
	int i=0;			//����������ֵ����ʵ�����塣����Ҳ������������

	int showReportsmenu();
	void showAll();				//��������
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
	system("cls");				//����

	cout<<"	 			 ���ͼ�����ϵͳ						\n"
		<<"	 			    ����ģ��							\n"
		<<"	 	 1. ����б�		\n"
		<<"		 2. �������б�		\n"
		<<"	 	 3. ���ۼ��б�		\n"
		<<"		 4. ����������б�	\n"
		<<"		 5. ����ļ�ֵ���б�\n"
		<<"		 6. �����������б�	\n"
		<<"		 7. �������˵�		\n"
		<<"											\n"
		<<"			  ����ѡ��					\n"
		<<"			  ������1��7֮�����:";
	cin>>choice;
	cin.clear();
	cin.ignore();
	while(choice<1||choice>7)
	{
		cout<<"			  ������1��7֮�����:";
		cin>>choice;
		cin.clear();
		cin.ignore();
	}
	return choice;
}

void showAll()
{
	BookData book;
	int i=0;			//���ڷ�����ʾʱ����

	fstream file;
	try						//���ļ��������쳣����
	{
		fileopen(file);
	}catch(char *exceptionString)
	{
		cout<<exceptionString;
		exit(0);
	}

	system("cls");				//����
	file.read((char*)&book,sizeof(book));
	while(!file.eof())
	{
		if(!book.isEmpty())
		{
			i++;
			cout<<"ISBN ��:"<<book.getISBN()
				<<"	����:"<<book.getTitle()<<endl
				<<"	����:"<<book.getAuthor()
				<<"	��������:"<<book.getDateAdded()
				<<"	������:"<<book.getPub()<<endl
				<<"	�����:"<<book.getQty()
				<<"	������:"<<book.getWholesale()
				<<"	���ۼ�:"<<book.getRetail()<<endl;
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
	int i=0;			//���ڷ�����ʾʱ����
	float total=0;		//��¼�������ܶ�

	fstream file;
	try						//���ļ��������쳣����
	{
		fileopen(file);
	}catch(char *exceptionString)
	{
		cout<<exceptionString;
		exit(0);
	}

	system("cls");				//����
	cout<<setw(14)<<"ISBN��"<<setw(7)<<"������"<<setw(7)<<"�����"<<"��  ��"<<endl;
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
	cout<<"����ͼ����������ܺ�Ϊ��RMB"
		<<total<<endl;
//	cout.flush();
	system("pause");
	file.close();
}

void showRetail()
{
	BookData book;
	int i=0;			//���ڷ�����ʾʱ����
	float total=0;		//��¼���ۼ��ܶ�

	fstream file;
	try						//���ļ��������쳣����
	{
		fileopen(file);
	}catch(char *exceptionString)
	{
		cout<<exceptionString;
		exit(0);
	}

	system("cls");				//����
	cout<<setw(14)<<"ISBN��"<<setw(7)<<"���ۼ�"<<setw(7)<<"�����"<<"��  ��"<<endl;
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
	cout<<"	����ͼ������ۼ��ܺ�Ϊ��RMB"
		<<total<<endl;
	system("pause");
	file.close();
}

void showQty()
{
	BookData *pr[1000];
	BookData *p;	//ͨ��ָ����������,pΪ����ʱ���м����
	int i,j,k;		//j��¼���������Ϊi�����ֵ;i,k��������

	fstream file;
	try						//���ļ��������쳣����
	{
		fileopen(file);
	}catch(char *exceptionString)
	{
		cout<<exceptionString;
		exit(0);
	}

	system("cls");				//����
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
		if(!pr[i]->isEmpty())		//�����ڴ�
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
			if(pr[k]->getQty()>pr[i]->getQty())		//����ָ�����������
			{
				p=pr[i];
				pr[i]=pr[k];
				pr[k]=p;
			}
	}

	cout<<setw(14)<<"ISBN��"<<setw(7)<<"�����"<<"��  ��"<<endl;
	for(i=0;i<j;i++)
	{
		cout<<setw(14)<<pr[i]->getISBN()
			<<setw(7)<<pr[i]->getQty()
			<<pr[i]->getTitle()<<endl;
			if(i%10==0&&i>0)
				system("pause");
	}
	cout<<"�������!"<<endl;
	system("pause");
	file.close();
}

void showWh()
{
	BookData *pr[1000];
	BookData *p;	//ͨ��ָ����������,pΪ����ʱ���м����
	int i,j,k;		//j��¼���������Ϊi�����ֵ;i,k��������

	fstream file;
	try						//���ļ��������쳣����
	{
		fileopen(file);
	}catch(char *exceptionString)
	{
		cout<<exceptionString;
		exit(0);
	}

	system("cls");				//����
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
			if((pr[k]->getQty()*pr[k]->getWholesale())>(pr[i]->getQty()*pr[i]->getWholesale()))		//����ָ�����������
			{
				p=pr[i];
				pr[i]=pr[k];
				pr[k]=p;
			}
	}

	cout<<setw(14)<<"ISBN��"<<setw(9)<<"��ֵ��"<<"��  ��"<<endl;
	for(i=0;i<j;i++)
	{
		cout<<setw(14)<<pr[i]->getISBN()
			<<setw(9)<<(pr[i]->getQty()*pr[i]->getWholesale())
			<<pr[i]->getTitle()<<endl;
			if(i%10==0&&i>0)
				system("pause");
	}
	cout<<"�������!"<<endl;
	system("pause");
	file.close();
}

void showDate()
{
	BookData *pr[1000];
	BookData *p;	//ͨ��ָ����������,pΪ����ʱ���м����
	int i,j,k;		//j��¼���������Ϊi�����ֵ;i,k��������

	fstream file;
	try						//���ļ��������쳣����
	{
		fileopen(file);
	}catch(char *exceptionString)
	{
		cout<<exceptionString;
		exit(0);
	}

	system("cls");				//����
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
			if(strcmp(pr[k]->getDateAdded(),pr[i]->getDateAdded())<0)		//����ָ�����������
			{
				p=pr[i];
				pr[i]=pr[k];
				pr[k]=p;
			}
	}

	cout<<setw(14)<<"ISBN��"<<setw(11)<<"��������"<<"��  ��"<<endl;
	for(i=0;i<j;i++)
	{
		cout<<setw(14)<<pr[i]->getISBN()
			<<setw(11)<<pr[i]->getDateAdded()
			<<pr[i]->getTitle()<<endl;
			if(i%10==0&&i>0)
				system("pause");
	}
	cout<<"�������!"<<endl;
	system("pause");
	file.close();
}

