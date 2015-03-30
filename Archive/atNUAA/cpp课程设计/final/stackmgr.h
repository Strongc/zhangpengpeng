/*
    C++�γ����
�������ߣ�������
ѧ    �ţ�040630416
*/


int stackmgr()
{
	int i=0;			//����������ֵ����ʵ�����塣����Ҳ������������

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
	system("cls");				//����

	cout<<"	 			 ���ͼ�����ϵͳ						\n"
		<<"	 			   ������˵�							\n"
		<<"	 	 1. ������������ĳ�飨ģ�����ң�				\n"
		<<"		 2. ����ISBN�Ų���ĳ��							\n"
		<<"	 	 3. ������										\n"
		<<"		 4. �޸������Ϣ								\n"
		<<"		 5. ɾ����										\n"
		<<"		 6. �������˵�									\n"
		<<"														\n"
		<<"			  ����ѡ��								\n"
		<<"			  ������1��6֮�����:";
	cin>>choice;
	cin.clear();
	cin.ignore();			
	while(choice<1||choice>6)
	{
		cout<<"			  ������1��6֮�����:";
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
	bool bo=false;		//��¼�Ƿ��ҵ�����

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
	
	cout<<"������ȫ�������򲿷�������";
	cin.getline(title,51);
	file.read((char*)&book,sizeof(book));
	while(!file.eof())
	{
		if(book.bookMatch(title))
		{
			bo=true;
			cout<<"	 			 ���ͼ�����ϵͳ						\n"
				<<"	 				 �������		\n"
				<<"	 									\n"
				<<"	 	ISBN  ��:"<<book.getISBN()<<endl
				<<"		��    ��:"<<book.getTitle()<<endl
				<<"		��    ��:"<<book.getAuthor()<<endl
				<<"		�� �� ��:"<<book.getPub()<<endl
				<<"		��������:"<<book.getDateAdded()<<endl
				<<"		�� �� ��:"<<book.getQty()<<endl
				<<"		�� �� ��:"<<book.getWholesale()<<endl
				<<"		�� �� ��:"<<book.getRetail()<<endl;
			system("pause");
		}
		file.read((char*)&book,sizeof(book));
	}
	if(bo==false)
		cout<<"�޷��ҵ�����Ҫ�޸ĵ��飡";
	cout<<"\n���ҽ�����"<<endl;
	system("pause");
	file.close();
}

void lookUpISBN()
{
	BookData book;
	char isbn[14];
	bool bo=false;		//��¼�Ƿ��ҵ�����

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
	
	cout<<"������ISBN�ţ�";
	cin.getline(isbn,14);
	file.read((char*)&book,sizeof(book));
	while(!file.eof())
	{
		if(strcmp(book.getISBN(),isbn)==0&&strcmp(book.getTitle(),"")!=0)
		{
			bo=true;
			cout<<"	 			 ���ͼ�����ϵͳ						\n"
				<<"	 				�������							\n"
				<<"	 									\n"
				<<"	 	ISBN  ��:"<<book.getISBN()<<endl
				<<"		��    ��:"<<book.getTitle()<<endl
				<<"		��    ��:"<<book.getAuthor()<<endl
				<<"		�� �� ��:"<<book.getPub()<<endl
				<<"		��������:"<<book.getDateAdded()<<endl
				<<"		�� �� ��:"<<book.getQty()<<endl
				<<"		�� �� ��:"<<book.getWholesale()<<endl
				<<"		�� �� ��:"<<book.getRetail()<<endl;
			break;
		}
		file.read((char*)&book,sizeof(book));
	}
	if(bo==false)
		cout<<"�޷��ҵ�����Ҫ�޸ĵ��飡";
	cout<<"\n���ҽ�����"<<endl;
	system("pause");
	file.close();
}

void addBook()
{
	BookData book;
	char isbn[14];				//ISBN��
	char title[51];				//����
	char author[31];			//����
	char publisher[31];			//���浥λ
	char dateAdded[11];				//�����������
	int qtyOnHand;					//����Ŀ����
	float wholesale;				//������
	float retail;					//���ۼ�

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

	cout<<"������ISBN��:";
	cin.getline(isbn,14);
	book.setISBN(isbn);
	cout<<"����������:";
	cin.getline(title,51);
	book.setTitle(title);
	cout<<"����������:";
	cin.getline(author,31);
	book.setAuthor(author);
	cout<<"��������浥λ:";
	cin.getline(publisher,31);
	book.setPub(publisher);
	cout<<"������������ڣ���ʽYYYY-MM-DD��:";
	cin.getline(dateAdded,11);
	book.setDateAdded(dateAdded);
	cout<<"����������:";
	cin>>qtyOnHand;
	book.setQty(qtyOnHand);
	cout<<"������������:";
	cin>>wholesale;
	book.setWholesale(wholesale);
	cout<<"���������ۼ�:";
	cin>>retail;
	book.setRetail(retail);

	file.seekp(0L,ios::end);
	file.write((char*)&book,sizeof(book));
	file.close();


}

void editBook()
{
	BookData book;
	char isbn[14];				//ISBN��
	char title[51];				//����
	char author[31];			//����
	char publisher[31];			//���浥λ
	char dateAdded[11];				//�����������
	int qtyOnHand;					//����Ŀ����
	float wholesale;				//������
	float retail;					//���ۼ�
	bool bo=false;		//��¼�Ƿ��ҵ�����

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
	
	cout<<"������Ҫ�޸ĵ����ISBN��:";
	cin.getline(isbn,14);
	file.read((char*)&book,sizeof(book));
	while(!file.eof())
	{
		if(strcmp(book.getISBN(),isbn)==0&&strcmp(book.getTitle(),"")!=0)
		{
			bo=true;
			cout<<"���濪ʼ�޸������Ϣ:"<<endl;
			cout<<"������ISBN��:";
			cin.getline(isbn,14);
			book.setISBN(isbn);
			cout<<"����������:";
			cin.getline(title,51);
			book.setTitle(title);
			cout<<"����������:";
			cin.getline(author,31);
			book.setAuthor(author);
			cout<<"��������浥λ:";
			cin.getline(publisher,31);
			book.setPub(publisher);
			cout<<"������������ڣ���ʽYYYY-MM-DD��:";
			cin.getline(dateAdded,11);
			book.setDateAdded(dateAdded);
			cout<<"����������:";
			cin>>qtyOnHand;
			book.setQty(qtyOnHand);
			cout<<"������������:";
			cin>>wholesale;
			book.setWholesale(wholesale);
			cout<<"���������ۼ�:";
			cin>>retail;
			book.setRetail(retail);

			file.seekp((0-sizeof(BookData)),ios::cur);
			file.write((char*)&book,sizeof(BookData));

			break;
		}
		file.read((char*)&book,sizeof(book));
	}
	if(bo==false)
		cout<<"�޷��ҵ�����Ҫ�޸ĵ��飡"<<endl;
	system("pause");
	file.close();
}


void remove()
{
	BookData book;
	char isbn[14];
	bool bo=false;		//��¼�Ƿ��ҵ�����
	char choice;		//ȷ���Ƿ�ɾ��

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
	
	cout<<"������ISBN�ţ�";
	cin.getline(isbn,14);
	file.read((char*)&book,sizeof(book));
	while(!file.eof())
	{
		if(strcmp(book.getISBN(),isbn)==0&&strcmp(book.getTitle(),"")!=0)
		{
			bo=true;
			cout<<"	 			 ���ͼ�����ϵͳ						\n"
				<<"	 				�������							\n"
				<<"	 									\n"
				<<"	 	ISBN  ��:"<<book.getISBN()<<endl
				<<"		��    ��:"<<book.getTitle()<<endl
				<<"		��    ��:"<<book.getAuthor()<<endl
				<<"		�� �� ��:"<<book.getPub()<<endl
				<<"		��������:"<<book.getDateAdded()<<endl
				<<"		�� �� ��:"<<book.getQty()<<endl
				<<"		�� �� ��:"<<book.getWholesale()<<endl
				<<"		�� �� ��:"<<book.getRetail()<<endl;
			cout<<"ȷ��ɾ����(Y/N)?  ";
			cin>>choice;
			while(choice!='y'&&choice!='Y'&&choice!='n'&&choice!='N')
			{
				cout<<"������Y��N ��";
				cin>>choice;
			}
			if(choice=='y'||choice=='Y')
			{
				book.removeBook();
				file.seekp((0-sizeof(BookData)),ios::cur);
				file.write((char*)&book,sizeof(BookData));
			}
			else
				cout<<"ɾ��ȡ����"<<endl;

			break;
		}
		file.read((char*)&book,sizeof(book));
	}
	if(bo==false)
		cout<<"�޷��ҵ�����Ҫ�޸ĵ��飡"<<endl;
	system("pause");
	file.close();
}

