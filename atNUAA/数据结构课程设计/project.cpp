/*
	������ 040630416
   ���ݽṹ �γ����
ѧ���ɼ�����ϵͳ
*/


#include <stdlib.h>
#include <iostream.h>
#include <string.h>
#include <fstream.h>


#define totall 11

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

typedef struct course{
	char name[30];
	int score;
	char techer[20];
	struct course *next;
}Course;

typedef struct{
	char num[10];			//��ʽ��**##@@@%%
	char name[20];
	int age;
	char sex[6];
	Course *first;
	int numCourse;
	bool exist;
}Student;

//���涨�����������ýṹ��
typedef struct{
	int index;			//��¼��ͬѧ��student�����е�λ��
	char num[10];		//��ѧ�������м�¼ѧ��
}Sort1;
typedef struct{
	int index;			//��¼��ͬѧ��student�����е�λ��
	int key;			//���������м�¼�ؼ��֣�age,score,totallScore��
}Sort2;

//���涨��һ��ͳ�Ƹ���ƽ���ɼ��Ľṹ��
typedef struct{
	char name[30];
	int num;
	int sum;
}AveCou;

Student student[totall];			//ȫ�ֱ����������޸�


/**************************��������*******************
int Hash(char *n);
Status Insert();
Status Delete();
Status Edit();
����,����������ѧ�Ų�ѯ����int SearchNum();
�����һ����ʾһ��ѧ����Ϣ�ĺ���Status DisplayOne(int n);
**************************��������*******************/

int Hash(char *n)						//hash����
{
	int num;
	num=(n[5]-'0')*1000+(n[6]-'0')*100+(n[7]-'0')*10+(n[8]-'0');
	return num%totall;
}

Status Insert()								//����һ��ѧ��
{
	Student *s;
	Course *c,*p;
	
	s=(Student *)malloc(sizeof(Student));
	if(!s)
	{
		cout<<"�����ַ�ռ�ʧ�ܣ�";
		exit(0);
	}
	cout<<"�������ѧ����ѧ�ţ�";			//�����ǻ�����Ϣ
	cin>>s->num;
	cout<<"�������ѧ����������";
	cin>>s->name;
	cout<<"�������ѧ�������䣺";
	cin>>s->age;
	cout<<"�������ѧ�����Ա�";
	cin>>s->sex;
	s->first=NULL;
	s->exist=true;

	
	int i;
	cout<<"��ѧ���Ĺ��м��ſΣ�";			//��������γ���Ϣ
	cin>>s->numCourse;
	if(s->numCourse>0)
	{
		c=(Course *)malloc(sizeof(Course));
		if(!c)
		{
			cout<<"�����ַ�ռ�ʧ�ܣ�";
			exit(0);
		}
		cout<<"�������1�ſγ̵Ŀγ�����";
		cin>>c->name;
		cout<<"������ÿγ̵ĳɼ���";
		cin>>c->score;
		cout<<"������ÿγ̵��ڿν�ʦ��";
		cin>>c->techer;
		c->next=NULL;
		s->first=c;
		p=c;
	}
	for(i=2;i<=s->numCourse;i++)
	{
		c=(Course *)malloc(sizeof(Course));
		if(!c)
		{
			cout<<"�����ַ�ռ�ʧ�ܣ�";
			exit(0);
		}
		cout<<"�������"<<i<<"�ſγ̵Ŀγ�����";
		cin>>c->name;
		cout<<"������ÿγ̵ĳɼ���";
		cin>>c->score;
		cout<<"������ÿγ̵��ڿν�ʦ��";
		cin>>c->techer;
		c->next=NULL;
		p->next=c;
		p=c;
	}

	int h,h1;									//����hash�����ݲ���
	h=Hash(s->num);
	if(student[h].exist==false)
		student[h]=*s;
	else
	{
		for(h1=(h+1)%totall;student[h1].exist==true&&h1!=h;h1=(h1+1)%totall);
		if(h==h1)
		{
			cout<<"���󣺲���ѧ����Ϣʱ�ռ�������";
			exit(0);
		}
		else
			student[h1]=*s;
	}
	
	free(s);
	return OK;
}


int SearchNum()				//����ѧ�Ų��ң����Ҳ�������-1
{
	int h,h1;
	char studNum[10];
	cout<<"�������ͬѧ��ѧ�ţ�";
	cin>>studNum;
	h=Hash(studNum);
	if(student[h].exist==true&&!strcmp(student[h].num,studNum))
		return h;
	else
	{
		for(h1=(h+1)%totall;strcmp(student[h1].num,studNum)!=0&&h1!=h;h1=(h1+1)%totall);
		if(h!=h1)
			return h1;
	}
	return -1;
}

Status DisplayOne(int n)				//n Ϊѧ����Ϣ�ṹ������±꣬���ɲ�ѯ�������
{
	cout<<"  ѧ�ţ�"<<student[n].num
		<<"     ������"<<student[n].name<<endl
		<<" \t\t���䣺"<<student[n].age
		<<"   �Ա�"<<student[n].sex<<endl;
	if(student[n].first)
	{
		Course *c;
		cout<<"\t��ͬѧ��ѧ�γ��У�"<<endl;
		for(c=student[n].first;c;c=c->next)
		{
			cout<<"\t �γ�����"<<c->name
				<<"   �ɼ���"<<c->score
				<<" �ο���ʦ��"<<c->techer<<endl;
		}		
	}
	else
	{
		cout<<"\t��ͬѧû��ѧ�κογ̡�"<<endl;
	}
	return OK;
}

Status Delete()					//ɾ��ͬѧ��������Ӧλ�õ�exist��־��Ϊfalse
{
	system("cls");
	int n;
	n=SearchNum();
	if(n<0)
	{
		cout<<"����ʧ�ܣ���ȷ�������ѧ������ȷ��Ϣ��";
		return false;
	}
	else
	{
		DisplayOne(n);
		cout<<"ȷ��ɾ��������Y��ȷ�ϣ�������������ȡ����";
		char choice;
		cin>>choice;
		cin.clear();
		cin.ignore();
		if(choice=='y'||choice=='Y')
			student[n].exist=false;
	}
	return OK;
}

Status Edit()				//�༭ͬѧ��Ϣ
{
	system("cls");
	int n;
	n=SearchNum();
	if(n<0)
	{
		cout<<"����ʧ�ܣ���ȷ�������ѧ������ȷ��Ϣ��";
		return false;
	}
	else
	{
		DisplayOne(n);
		char choice;
		cout<<"  ������Ҫ�޸ĸ�ͬѧ��ʲô��Ϣ?"<<endl;
		cout<<"\tA.ѧ��"<<endl
			<<"\tB.����"<<endl
			<<"\tC.����"<<endl
			<<"\tD.�Ա�"<<endl
			<<"\tE.�γ�"<<endl;
		cout<<"\t\t������A,B,C,D��E��";
		cin>>choice;
		cin.clear();
		cin.ignore();
		while(choice!='A'&&choice!='B'&&choice!='C'&&choice!='D'&&choice!='E'&&choice!='a'&&choice!='b'&&choice!='c'&&choice!='d'&&choice!='e')
		{
			cout<<"\t\t������A,B,C,D��E�����ִ�Сд����";
			cin>>choice;
			cin.clear();
			cin.ignore();
		}
		switch(choice)
		{
			case 'a':
			case 'A':
				cout<<"\t�������ѧ����ѧ�ţ�";
				cin>>student[n].num;
				break;
			case 'b':
			case 'B':
				cout<<"\t�������ѧ����������";
				cin>>student[n].name;
				break;
			case 'c':
			case 'C':
				cout<<"\t�������ѧ�������䣺";
				cin>>student[n].age;
				break;
			case 'd':
			case 'D':
				cout<<"\t�������ѧ�����Ա�";
				cin>>student[n].sex;
				break;
			case 'e':
			case 'E':
				{
					int i;
					Course *c,*p;
					cout<<"  ��ѧ���Ĺ��м��ſΣ�";			//��������γ���Ϣ
					cin>>student[n].numCourse;
					if(student[n].numCourse>0)
					{
						c=(Course *)malloc(sizeof(Course));
						if(!c)
						{
							cout<<"�����ַ�ռ�ʧ�ܣ�";
							exit(0);
						}
						cout<<"�������1�ſγ̵Ŀγ�����";
						cin>>c->name;
						cout<<"\t������ÿγ̵ĳɼ���";
						cin>>c->score;
						cout<<"\t������ÿγ̵��ڿν�ʦ��";
						cin>>c->techer;
						c->next=NULL;
						student[n].first=c;
						p=c;
					}
					else
						student[n].first=NULL;
					for(i=2;i<=student[n].numCourse;i++)
					{
						c=(Course *)malloc(sizeof(Course));
						if(!c)
						{
							cout<<"�����ַ�ռ�ʧ�ܣ�";
							exit(0);
						}
						cout<<"�������"<<i<<"�ſγ̵Ŀγ�����";
						cin>>c->name;
						cout<<"\t������ÿγ̵ĳɼ���";
						cin>>c->score;
						cout<<"\t������ÿγ̵��ڿν�ʦ��";
						cin>>c->techer;
						c->next=NULL;
						p->next=c;
						p=c;
					}
				}//case 'e'
				break;
		}//switch()
	}//else
	return OK;
}


/***************************��ѯ�����еĺ���************************
Status DisplayAll();
int SearchNum(); λ�ڻ���������
Status SearchName();
Status SearchSex();
Status SearchGrade();
Status SearchTecher();
***************************��ѯ�����еĺ���************************/

Status DisplayAll()				//��ʾȫ��ѧ����Ϣ
{
	system("cls");
	cout<<"��ʾ����ѧ����Ϣ��"<<endl;
	for(int i=0;i<totall;i++)
		if(student[i].exist)
		{
			DisplayOne(i);
			cout<<endl;
		}
	cout<<"\n  ��ʾ��ϣ�"<<endl;
	system("pause");
	return OK;
}

Status SearchName()				//��������ѯ
{
	char name[20];
	cout<<"��������Ҫ���ҵ�ѧ����������";
	cin>>name;
	for(int i=0;i<totall;i++)
		if(student[i].exist&&!strcmp(student[i].name,name))
		{
			DisplayOne(i);
			cout<<endl;
		}
	cout<<"\n  ��ʾ��ϣ�"<<endl;
	system("pause");
	return OK;
}

Status SearchSex()				//���Ա��ѯ
{
	system("cls");
	char sex[6];
	cout<<"\t\t���Ա��ѯ"<<endl;
	cout<<" ��������Ҫ��ѯ���Ա�";
	cin>>sex;
	for(int i=0;i<totall;i++)
		if(student[i].exist&&!strcmp(student[i].sex,sex))
		{
			DisplayOne(i);
			cout<<endl;
		}
	cout<<"\n  ��ʾ��ϣ�"<<endl;
	system("pause");
	return OK;
}

Status SearchGrade()			//���꼶��ѯѧ������ѧ�γ�
{
	system("cls");
	char grade[5];
	Course *c;
	cout<<"\t\t���꼶��ѯѧ������ѧ�γ�"<<endl;
	cout<<" ��������꼶��ѧ����ݣ�";
	cin>>grade;
	cout<<"���꼶ѧ���Ŀγ̣�"<<endl;
	for(int i=0;i<totall;i++)
		if(student[i].exist&&student[i].num[2]==grade[2]&&student[i].num[3]==grade[3])
		{
			cout<<"  ѧ�ţ�"<<student[i].num
				<<"     ������"<<student[i].name<<endl;
			if(student[i].first)
			{
				cout<<"\t��ͬѧ��ѧ�γ��У�"<<endl;
				for(c=student[i].first;c;c=c->next)
				{
					cout<<"\t �γ�����"<<c->name
						<<"   �ɼ���"<<c->score
						<<" �ο���ʦ��"<<c->techer<<endl;
				}		
			}
			else
			{
				cout<<"\t��ͬѧû��ѧ�κογ̡�"<<endl;
			}

		}
	cout<<"\n  ��ʾ��ϣ�"<<endl;
	system("pause");
	return OK;
}

Status SearchTecher()			//����ʦ��ѯ����ѧ����Ϣ
{
	system("cls");
	Course *c;
	char techer[20];
	cout<<"\t\t����ʦ��ѯ����ѧ����Ϣ"<<endl;
	cout<<" ��������Ҫ��ѯ�Ľ�ʦ����";
	cin>>techer;
	for(int i=0;i<totall;i++)
		if(student[i].exist)
		{
			if(student[i].first)
				for(c=student[i].first;c;c=c->next)
				{
					if(!strcmp(c->techer,techer))
					{			
						DisplayOne(i);
						cout<<endl;
						break;
					}
				}
		}
	cout<<"\n  ��ʾ��ϣ�"<<endl;
	system("pause");
	return OK;
}

/***************************�������еĺ���************************
Status SortNum()				//��ѧ������
Status SortAge()				//����������
Status SortScore()				//��ĳһ�Ƶĳɼ�����
Status SortTotallScore()		//���ܳɼ�����
���������������ýṹ��,�Դ˽ṹ�������������
***************************�������еĺ���************************/

//��ѧ��������ϣ������
void ShellInsert(Sort1 s[],int dk,int length)			//ϣ����������
{
	int i,j;
	for(i=dk+1;i<=length;++i)
		if(strcmp(s[i].num,s[i-dk].num)<0)
		{
			s[0]=s[i];
			for(j=i-dk;j>0&&strcmp(s[0].num,s[j].num)<0;j-=dk)
				s[j+dk]=s[j];
			s[j+dk]=s[0];
		}
}
Status SortNum()				//��ѧ��������ϣ������
{
	Sort1 s[totall];
	int studNum=0;			//��¼ѧ���ĸ�����Ҳ��s��������Ϣ�ĸ���

	for(int i=0;i<totall;i++)			//������������и�ֵ,s[0]ֻ���ݴ浥Ԫ�������ڱ�
	if(student[i].exist)
	{
		studNum++;
		strcpy(s[studNum].num,student[i].num);
		s[studNum].index=i;
	}

	for(int k=(totall/2);k>0;k=k/2)
		ShellInsert(s,k,studNum);

	system("cls");
	cout<<"��ѧ��������ϣ��������������"<<endl;
	for(i=1;i<=studNum;i++)
	{
		DisplayOne(s[i].index);
		cout<<endl;
	}
	cout<<"\n  ��ʾ��ϣ�"<<endl;
	system("pause");
	return OK;
}

//�����������ÿ�������
int Partition(Sort2 s[],int low,int high)
{
	s[0]=s[low];
	int pivotkey=s[low].key;
	while(low<high)
	{
		while(low<high&&s[high].key>=pivotkey)
			--high;
		s[low]=s[high];
		while(low<high&&s[low].key<=pivotkey)
			++low;
		s[high]=s[low];
	}
	s[low]=s[0];
	return low;
}
void QSort(Sort2 s[],int low,int high)
{
	int pivotloc;
	if(low<high)
	{
		pivotloc=Partition(s,low,high);
		QSort(s,low,pivotloc-1);
		QSort(s,pivotloc+1,high);
	}
}
Status SortAge()				//�����������ÿ�������
{
	Sort2 s[totall];
	int studNum=0;			//��¼ѧ���ĸ�����Ҳ��s��������Ϣ�ĸ���

	for(int i=0;i<totall;i++)			//������������и�ֵ,s[0]ֻ���ݴ浥Ԫ�������ڱ�
	if(student[i].exist)
	{
		studNum++;
		s[studNum].key=student[i].age;
		s[studNum].index=i;
	}

	QSort(s,1,studNum);

	system("cls");
	cout<<"������������ϣ��������������"<<endl;
	for(i=1;i<=studNum;i++)
	{
		DisplayOne(s[i].index);
		cout<<endl;
	}
	cout<<"\n  ��ʾ��ϣ�"<<endl;
	system("pause");
	return OK;
}

//��ĳһ�Ƶĳɼ������ö�����
void HeapAdjust(Sort2 s[],int k,int m)
{
	Sort2 rc;
	rc=s[k];
	int j;
	for(j=2*k;j<=m;j*=2)
	{
		if(j<m&&s[j].key<s[j+1].key)
			++j;
		if(!(rc.key<s[j].key))
			break;
		s[k]=s[j];
		k=j;
	}
	s[k]=rc;
}
Status SortScore()				//��ĳһ�Ƶĳɼ������ö�����
{
	Sort2 s[totall];
	int studNum=0;			//��¼ѧ���ĸ�����Ҳ��s��������Ϣ�ĸ���
	char name[30];
	Course *c;
	system("cls");
	cout<<"��ĳһ�Ƶĳɼ�����������γ�����"<<endl;
	cin>>name;
	for(int i=0;i<totall;i++)			//������������и�ֵ,s[0]ֻ���ݴ浥Ԫ�������ڱ�
	if(student[i].exist)
	{
		if(student[i].first)
			for(c=student[i].first;c;c=c->next)
			{
				if(!strcmp(c->name,name))
				{			
					studNum++;
					s[studNum].key=c->score;
					s[studNum].index=i;
				}
			}
	}
	
	if(studNum)
	{
		for(i=studNum/2;i>0;--i)
			HeapAdjust(s,i,studNum);
		for(i=studNum;i>1;--i)
		{
			s[0]=s[1];
			s[1]=s[i];
			s[i]=s[0];
			HeapAdjust(s,1,i-1);
		}
		
		cout<<"��"<<name<<"�ĳɼ�������ϣ��������������"<<endl;
		for(i=1;i<=studNum;i++)
		{
			DisplayOne(s[i].index);
			cout<<endl;
		}
		
		cout<<"\n  ��ʾ��ϣ�"<<endl;
	}
	else
		cout<<"���ź���û����ѡ���ſΣ�"<<endl;
	system("pause");
	return OK;
}

//���ܳɼ������ù鲢����
void Merge(Sort2 SR[],Sort2 TR[],int i,int m,int n)
{
	int j,k;
	for(j=m+1,k=i;i<=m&&j<=n;++k)
	{
		if(SR[i].key<SR[j].key)
			TR[k]=SR[i++];
		else
			TR[k]=SR[j++];
	}
	while(i<=m)
	{
		TR[k]=SR[i];
		k++;
		i++;
	}
	while(j<=n)
	{
		TR[k]=SR[j];
		k++;
		j++;
	}
}
void MSort(Sort2 SR[],Sort2 TR1[],int s,int t)
{
	int m;
	if(s==t)
		TR1[s]=SR[s];
	else
	{
		Sort2 TR2[totall];
		m=(s+t)/2;
		MSort(SR,TR2,s,m);
		MSort(SR,TR2,m+1,t);
		Merge(TR2,TR1,s,m,t);
	}
}
Status SortTotallScore()		//���ܳɼ������ù鲢����
{
	Sort2 s[totall];
	int studNum=0;			//��¼ѧ���ĸ�����Ҳ��s��������Ϣ�ĸ���
	Course *c;
	for(int i=0;i<totall;i++)			//������������и�ֵ,s[0]ֻ���ݴ浥Ԫ�������ڱ�
	if(student[i].exist)
	{
		studNum++;
		s[studNum].key=0;
		s[studNum].index=i;
		if(student[i].first)
			for(c=student[i].first;c;c=c->next)
					s[studNum].key+=c->score;
	}

	MSort(s,s,1,studNum);

	system("cls");
	cout<<"���ܳɼ�������ϣ��������������"<<endl;
	for(i=1;i<=studNum;i++)
	{
		DisplayOne(s[i].index);
		cout<<"   �ܳɼ�Ϊ:"<<s[i].key<<endl;
	}
	cout<<"\n  ��ʾ��ϣ�"<<endl;
	system("pause");
	return OK;
}

/***************************ͳ�ƹ����еĺ���************************
Status StaSex()				//ͳ����Ů��������
Status StaAvePerson()		//ͳ��ÿ���˵�ƽ���ɼ�
Status StaAveCou()			//ͳ�Ƹ��Ƶ�ƽ���ɼ�
***************************ͳ�ƹ����еĺ���************************/
Status StaSex()
{
	int male=0,female=0;
	system("cls");
	cout<<"\tͳ����Ů��������"<<endl;
	for(int i=0;i<totall;i++)
		if(student[i].exist)
		{
			if(!strcmp(student[i].sex,"��"))
				male++;
			else
				female++;
		}
	cout<<"\nͳ�ƽ��Ϊ��"
		<<"������"<<male<<"�ˣ�"
		<<"Ů����"<<female<<"��"<<endl;
	system("pause");
	return OK;
}

Status StaAvePerson()		//ͳ��ÿ���˵�ƽ���ɼ�
{
	int sum,n;
	Course *c;
	system("cls");
	cout<<"\tͳ��ÿ���˵�ƽ���ɼ�"<<endl;
	for(int i=0;i<totall;i++)
		if(student[i].exist)
		{
			cout<<"  ѧ�ţ�"<<student[i].num
				<<"     ������"<<student[i].name<<endl;
			cout<<"\tƽ���ɼ�Ϊ��";
			sum=0;
			n=0;
			if(student[i].first)
				for(c=student[i].first;c;c=c->next)
				{
					sum+=c->score;
					n++;
				}
			if(n>0)
				cout<<((float)sum)/n<<endl;
			else
				cout<<0<<endl;
		}
	cout<<"\n  ��ʾ��ϣ�"<<endl;
	system("pause");
	return OK;
}

Status StaAveCou()			//ͳ�Ƹ��Ƶ�ƽ���ɼ�
{
	system("cls");
	cout<<"\tͳ�Ƹ��Ƶ�ƽ���ɼ�"<<endl;
	AveCou AC[100];
	Course *c;
	int j=0,CourseNum=0;
	for(int i=0;i<totall;i++)
	if(student[i].exist)
	{
		if(student[i].first)
			for(c=student[i].first;c;c=c->next)
			{
				j=0;
				while(j<CourseNum)
				{
					if(!strcmp(c->name,AC[j].name))
						break;
					j++;
				}
				if(!strcmp(c->name,AC[j].name)&&CourseNum!=0)
				{
					AC[j].num++;
					AC[j].sum+=c->score;
				}
				else
				{
					strcpy(AC[j].name,c->name);
					CourseNum++;
					AC[j].num=1;
					AC[j].sum=c->score;
				}
			}
	}

	for(i=0;i<CourseNum;i++)
	{
		cout<<"�γ�����"<<AC[i].name;
		cout<<"  ƽ���ɼ���"<<((float)AC[i].sum)/AC[i].num<<endl;
	}
	cout<<"\n  ��ʾ��ϣ�"<<endl;
	system("pause");
	return OK;
}

/***************************���˵��еĺ���************************
Status GetFromFile();������Status WriteToFile();��
Status Construct();
Status EditMain();
Status Inquire();		��ѯ
Status Sort();
Status Statistic();		ͳ��
Status Exit();������void EndCout()��
***************************���˵��еĺ���************************/

Status GetFromFile()				//���ļ��ж�������
{
	fstream file;
	file.open("StudInfo",ios::in|ios::binary);
	if(!file)
	{
		cout<<"���ļ�ʧ�ܣ�"<<endl;
		system("pause");
		exit(0);
	}
	file.read((char*)student,sizeof(student));
	int n,numCourse;
	int i;
	Course *c,*p;
	file.read((char*)&n,sizeof(n));
	while(!file.eof())
	{
		file.read((char*)&numCourse,sizeof(numCourse));

		c=(Course *)malloc(sizeof(Course));
		if(!c)
		{
		cout<<"�����ַ�ռ�ʧ�ܣ�";
		exit(0);
		}
		c->next=NULL;
		file.read((char*)c,sizeof(Course));
		p=c;
		student[n].first=c;
		for(i=1;i<numCourse;i++)
		{
			c=(Course *)malloc(sizeof(Course));
			if(!c)
			{
			cout<<"�����ַ�ռ�ʧ�ܣ�";
			exit(0);
			}
			c->next=NULL;
			file.read((char*)c,sizeof(Course));
			p->next=c;
			p=c;
		}
		file.read((char*)&n,sizeof(n));
	}
	file.close();
	return OK;
}
/*
�ļ��ṹ��
�ṹ����student[totall]
�����˵�{int�±�n��int�γ���numCourse,�����γ�Course
*/
Status WriteToFile()				//������д���ļ�
{
	fstream file;
	file.open("StudInfo",ios::out|ios::binary);
	if(!file)
	{
		cout<<"���ļ�ʧ�ܣ�"<<endl;
		system("pause");
		exit(0);
	}
	file.write((char*)student,sizeof(student));
	Course *c;
	for(int i=0;i<totall;i++)
		if(student[i].exist&&student[i].numCourse>0)
		{
			file.write((char*)&i,sizeof(i));
			file.write((char*)&student[i].numCourse,sizeof(int));
			c=student[i].first;
			while(c)
			{
				file.write((char*)c,sizeof(Course));
				c=c->next;
			}
		}
	file.close();
	return OK;
}

Status Construct()					//���½�������
{
	int iTotall;
	for(iTotall=0;iTotall<totall;iTotall++)			//������λ���ÿ�
		student[iTotall].exist=false;
	
	int num;
	system("cls");
	cout<<"���ʣ��ܹ��ж�����ͬѧ��";
	cin>>num;
	if(num>0)
	{
		for(int i=0;i<num;i++)
		{
			cout<<"���������"<<(i+1)<<"��ͬѧ����Ϣ��"<<endl;
			Insert();
		}
		cout<<"���������"<<endl;
		system("pause");
		return OK;
	}
	else
	{
		cout<<"ͬѧ��Ϊ�������㣬������ѧ����Ϣ�����룡ǿ�ƴ��ļ��ж������ݣ�"<<endl;
		GetFromFile();
		system("pause");
		return ERROR;
	}
}

Status EditMain()					//�༭ѧ������
{
	char choice;
	while(1)
	{
		system("cls");
		cout<<"\n\n\t\tѧ���ɼ�����ϵͳ"<<endl;
		cout<<"\n\t\t    �༭ѧ������";
		cout<<"\n\t\t A.����һ��ѧ����Ϣ"
			<<"\n\t\t B.ɾ��һ��ѧ����Ϣ"
			<<"\n\t\t C.�޸�һ��ѧ����Ϣ"
			<<"\n\t\t D.�����˵�"<<endl;
		cout<<"\t\t������A,B,C��D��";
		cin>>choice;
		cin.clear();
		cin.ignore();
		while(choice!='A'&&choice!='B'&&choice!='C'&&choice!='D'&&choice!='a'&&choice!='b'&&choice!='c'&&choice!='d')
		{
			cout<<"\t\t������A,B,C��D�����ִ�Сд����";
			cin>>choice;
			cin.clear();
			cin.ignore();
		}
		switch(choice)
		{
			case 'a':
			case 'A':
				system("cls");
				Insert();
				break;
			case 'b':
			case 'B':
				Delete();
 				break;
			case 'c':
			case 'C':
				Edit();
				break;
			case 'd':
			case 'D':
				return OK;
		}
	}

}

Status Inquire()
{
	char choice;
	while(1)
	{	
		system("cls");
		cout<<"\n\n\t\tѧ���ɼ�����ϵͳ"<<endl;
		cout<<"\n\t\t    ��ѯѧ����Ϣ";
		cout<<"\n\t\t A.��ʾȫ��ѧ����Ϣ"
			<<"\n\t\t B.��ѧ�Ų�ѯ"
			<<"\n\t\t C.��������ѯ"
			<<"\n\t\t D.���Ա��ѯ"
			<<"\n\t\t E.���꼶��ѯѧ������ѧ�γ�"
			<<"\n\t\t F.����ʦ��ѯ����ѧ����Ϣ"
			<<"\n\t\t G.�����˵�"<<endl;
		cout<<"\t\t������A,B,C,D,E,F��G��";
		cin>>choice;
		cin.clear();
		cin.ignore();
		while(choice!='A'&&choice!='B'&&choice!='C'&&choice!='D'&&choice!='E'&&choice!='F'&&choice!='G'&&choice!='a'&&choice!='b'&&choice!='c'&&choice!='d'&&choice!='e'&&choice!='f'&&choice!='g')
		{
			cout<<"\t\t������A,B,C,D,E,F��G�����ִ�Сд����";
			cin>>choice;
			cin.clear();
			cin.ignore();
		}
		switch(choice)
		{
			case 'a':
			case 'A':
				DisplayAll();
				break;
			case 'b':
			case 'B':
				int n;
				n=SearchNum();
				if(n>0)
				{
					DisplayOne(n);
					cout<<"\n  ��ʾ��ϣ�"<<endl;
				}else
					cout<<"����ʧ�ܣ���ȷ�������ѧ������ȷ��Ϣ��"<<endl;
				system("pause");
 				break;
			case 'c':
			case 'C':
				SearchName();
				break;
			case 'd':
			case 'D':
				SearchSex();
				break;
			case 'e':
			case 'E':
				SearchGrade();
				break;
			case 'f':
			case 'F':
				SearchTecher();
				break;
			case 'g':
			case 'G':
				return OK;
		}
	}
}

Status Sort()
{
	char choice;
	while(1)
	{	
		system("cls");
		cout<<"\n\n\t\tѧ���ɼ�����ϵͳ"<<endl;
		cout<<"\n\t\t ��ѧ����Ϣ����";
		cout<<"\n\t\t A.��ѧ������"
			<<"\n\t\t B.����������"
			<<"\n\t\t C.��ĳһ�Ƶĳɼ�����"
			<<"\n\t\t D.���ܳɼ�����"
			<<"\n\t\t E.�����˵�"<<endl;
		cout<<"\t\t������A,B,C,D��E��";
		cin>>choice;
		cin.clear();
		cin.ignore();
		while(choice!='A'&&choice!='B'&&choice!='C'&&choice!='D'&&choice!='E'&&choice!='a'&&choice!='b'&&choice!='c'&&choice!='d'&&choice!='e')
		{
			cout<<"\t\t������A,B,C,D��E�����ִ�Сд����";
			cin>>choice;
			cin.clear();
			cin.ignore();
		}
		switch(choice)
		{
			case 'a':
			case 'A':
				SortNum();
				break;
			case 'b':
			case 'B':
				SortAge();
				break;
			case 'c':
			case 'C':
				SortScore();
				break;
			case 'd':
			case 'D':
				SortTotallScore();
				break;
			case 'e':
			case 'E':
				return OK;
		}
	}
}

Status Statistic()
{
	char choice;
	while(1)
	{	
		system("cls");
		cout<<"\n\n\t\tѧ���ɼ�����ϵͳ"<<endl;
		cout<<"\n\t\t  ͳ��ѧ����Ϣ";
		cout<<"\n\t\t A.ͳ����Ů��������"
			<<"\n\t\t B.ͳ��ÿ���˵�ƽ���ɼ�"
			<<"\n\t\t C.ͳ�Ƹ��Ƶ�ƽ���ɼ�"
			<<"\n\t\t D.�����˵�"<<endl;
		cout<<"\t\t������A,B,C��D��";
		cin>>choice;
		cin.clear();
		cin.ignore();
		while(choice!='A'&&choice!='B'&&choice!='C'&&choice!='D'&&choice!='a'&&choice!='b'&&choice!='c'&&choice!='d')
		{
			cout<<"\t\t������A,B,C��D�����ִ�Сд����";
			cin>>choice;
			cin.clear();
			cin.ignore();
		}
		switch(choice)
		{
			case 'a':
			case 'A':
				StaSex();
				break;
			case 'b':
			case 'B':
				StaAvePerson();
				break;
			case 'c':
			case 'C':
				StaAveCou();
				break;
			case 'd':
			case 'D':
				return OK;
		}
	}
}


void EndCout()
{
	system("cls");
	cout<<"\n\t\tѧ���ɼ�����ϵͳ"
		<<"\n\t\t  ���ݽṹ �γ����"
		<<"\n\t\t��Ϣ��ѧ�뼼��ѧԺ"
		<<"\n\t\t       ������"
		<<"\tѧ�ţ�040630416"<<endl;
	system("pause");
	exit(0);
}

Status MExit()
{
	char choice;
	system("cls");
	cout<<"�����˳�ϵͳ����\n   ���ʣ���Ҫ���������ݱ��浽�ļ�����"<<endl;
	cout<<"\tY.�ǵģ����ϱ�������"<<endl
		<<"\tN.û��Ҫ�������ݲ�ֵ�ñ���"<<endl;
	cout<<"\t\t������Y��N��";
	cin>>choice;
	cin.clear();
	cin.ignore();
	while(choice!='Y'&&choice!='N'&&choice!='y'&&choice!='n')
	{
		cout<<"\t\t������Y��N�����ִ�Сд����";
		cin>>choice;
		cin.clear();
		cin.ignore();
	}
	if(choice=='Y'||choice=='y')
	{
		WriteToFile();
		EndCout();
	}
	else
	{
		cout<<"��ȷ����"<<endl;
		cout<<"\tY.�ǵģ������˳�"<<endl
			<<"\tN.���ţ����Ǳ���һ�°�"<<endl;
		cout<<"\t\t������Y��N��";
		cin>>choice;
		cin.clear();
		cin.ignore();
		while(choice!='Y'&&choice!='N'&&choice!='y'&&choice!='n')
		{
			cout<<"\t\t������Y��N�����ִ�Сд����";
			cin>>choice;
			cin.clear();
			cin.ignore();
		}
		if(choice=='N'||choice=='n')
			WriteToFile();
		EndCout();
	}
	return OK;

}



/**************************������*******************************/

void main()
{
	char choice;

	cout<<"\n\n\t\tѧ �� �� �� �� �� ϵ ͳ"<<endl;
	cout<<"\n\n��ѡ���������½���������"<<endl;
	cout<<"\tY.�ǵģ����½�������"<<endl
		<<"\tN.�������ļ��ж�������"<<endl;
	cout<<"\t\t������Y��N��";
	cin>>choice;
	cin.clear();
	cin.ignore();
	while(choice!='Y'&&choice!='N'&&choice!='y'&&choice!='n')
	{
		cout<<"\t\t������Y��N�����ִ�Сд����";
		cin>>choice;
		cin.clear();
		cin.ignore();
	}
	if(choice=='Y'||choice=='y')
		Construct();
	else
		GetFromFile();

	while(1)
	{	
		system("cls");
		cout<<"\n\n\t\tѧ���ɼ�����ϵͳ"<<endl;
		cout<<"\n\t\t\t���˵�";
		cout<<"\n\t\t A.���½�������"
			<<"\n\t\t B.�༭ѧ������"
			<<"\n\t\t C.��ѯѧ����Ϣ"
			<<"\n\t\t D.��ѧ����Ϣ����"
			<<"\n\t\t E.ͳ��ѧ����Ϣ"
			<<"\n\t\t F.�˳�ϵͳ"<<endl;
		cout<<"\t\t    ������A,B,C,D,E��F��";
		cin>>choice;
		cin.clear();
		cin.ignore();
		while(choice!='A'&&choice!='B'&&choice!='C'&&choice!='D'&&choice!='E'&&choice!='F'&&choice!='a'&&choice!='b'&&choice!='c'&&choice!='d'&&choice!='e'&&choice!='f')
		{
			cout<<"\t\t    ������A,B,C,D,E��F�����ִ�Сд����";
			cin>>choice;
			cin.clear();
			cin.ignore();
		}
		switch(choice)
		{
			case 'a':
			case 'A':
				Construct();
				break;
			case 'b':
			case 'B':
				EditMain();
 				break;
			case 'c':
			case 'C':
				Inquire();
				break;
			case 'd':
			case 'D':
				Sort();
				break;
			case 'e':
			case 'E':
				Statistic();
				break;
			case 'f':
			case 'F':
				MExit();
				break;
		}//switch
	}//while
}
			






