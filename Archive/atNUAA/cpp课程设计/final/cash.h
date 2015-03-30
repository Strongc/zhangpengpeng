/*
    C++�γ����
�������ߣ�������
ѧ    �ţ�040630416
*/

void cash()
{
	int i=0;			//��������
	float taxRate;
	int number;			//������¼һ����Ҫ���������
	char isbn[14];
	int bookNum;		//������ı���
	Sale *Spr[51];			//ָ�����飬ָ����
	BookData *BDpr[51];
	Sale temp;	//temp�����޸�����˰��

	char ch;				//�������Ƿǻ��й˿�����

	float total=0;			//������¼�˴�ʹ�ô˳���ʱ��������
	float cost=0;				//������¼�˴�ʹ�ô˳���ʱ���ܳɱ�

	fstream file;
	try						//���ļ��������쳣����
	{
		fileopen(file);
	}catch(char *exceptionString)
	{
		cout<<exceptionString;
		exit(0);
	}
	
	bool search(fstream &,char *);			//��������
	void BDtoSa(BookData *,Sale *);

	cout<<"����������˰��:";
	cin>>taxRate;
	temp.setTaxRate(taxRate);

	while(1)
	{
		system("cls");
		cout<<"�����˿���Ҫ�����飿";
		cin>>number;
		cin.ignore();
		number=ensurePosi(number);
		
		for(i=0;i<number;i++)				//���봦��
		{
			cout<<"�������"
				<<i+1
				<<"�����ISBN�ţ�";
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
				cout<<"������Ҫ��ı�����";
				cin>>bookNum;
				cin.ignore();
				bookNum=ensurePosi(bookNum);
				while((Spr[i]->getQty()-bookNum)<0)
				{
					cout<<"��������㣬���������룺"<<endl;
					cin>>bookNum;
					cin.ignore();
				}
				Spr[i]->setQtySold(bookNum);			//������
				
				BDpr[i]->setQty(BDpr[i]->getQty()-bookNum);			//��������
				file.seekp((0-sizeof(BookData)),ios::cur);
				file.write((char*)BDpr[i],sizeof(BookData));
				
			}
			else
			{
				cout<<"����ISBN�Ŵ���"<<endl;
				i=i-1;			
			}
		}
			
		//�������
		cout<<"	 			 ǰ̨����ģ��						\n"
			<<"����	 ISBN��		����			����	   ��� \n"
			<<endl;
		for(i=0;i<number;i++)							//λ�ö���������
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
		cout<<"		���ۺϼ�:	RMB"
			<<Spr[0]->getTotal()
			<<endl;		//���ճ�������˰�����������߳е��ĵ����ڴ�ɾ��
		cout<<"				лл����";

		total=total+Spr[0]->getTotal();
		cost=cost+Spr[0]->getTotalCost();
		Spr[0]->setTotal(0);			
		Spr[0]->setTotalCost(0);

		cout<<"\n\n\n\t���й˿�Ҫ������(Y/N) ";
		cin>>ch;
		while(ch!='y'&&ch!='Y'&&ch!='n'&&ch!='N')
		{
			cout<<"������Y��N ��";
			cin>>ch;
		}
			
		if(ch=='n'||ch=='N')
			break;
	}
	system("cls");
	cout<<"\n\n"
		<<"		�˴ξ�Ӫ������RMB "
		<<total
		<<"\n		�����ܳɱ�ΪRMB "
		<<cost
		<<"\n		������ΪRMB "
		<<total-cost<<endl;
	file.close();
	cout<<"�����˵���"<<endl;
	system("pause");
	system("cls");
}


bool search(fstream &file,char *isbn)		//ʵ�ֲ���
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

void BDtoSa(BookData *bd,Sale *s)			//��Sale����и�ֵ
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