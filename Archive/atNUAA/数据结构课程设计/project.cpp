/*
	张鹏鹏 040630416
   数据结构 课程设计
学生成绩管理系统
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
	char num[10];			//格式：**##@@@%%
	char name[20];
	int age;
	char sex[6];
	Course *first;
	int numCourse;
	bool exist;
}Student;

//下面定义两个排序用结构体
typedef struct{
	int index;			//记录该同学在student数组中的位置
	char num[10];		//按学号排序中记录学号
}Sort1;
typedef struct{
	int index;			//记录该同学在student数组中的位置
	int key;			//其他排序中记录关键字（age,score,totallScore）
}Sort2;

//下面定义一个统计各科平均成绩的结构体
typedef struct{
	char name[30];
	int num;
	int sum;
}AveCou;

Student student[totall];			//全局变量，方便修改


/**************************基本操作*******************
int Hash(char *n);
Status Insert();
Status Delete();
Status Edit();
另外,还包括按照学号查询函数int SearchNum();
再添加一个显示一个学生信息的函数Status DisplayOne(int n);
**************************基本操作*******************/

int Hash(char *n)						//hash函数
{
	int num;
	num=(n[5]-'0')*1000+(n[6]-'0')*100+(n[7]-'0')*10+(n[8]-'0');
	return num%totall;
}

Status Insert()								//插入一个学生
{
	Student *s;
	Course *c,*p;
	
	s=(Student *)malloc(sizeof(Student));
	if(!s)
	{
		cout<<"申请地址空间失败！";
		exit(0);
	}
	cout<<"请输入该学生的学号：";			//以下是基本信息
	cin>>s->num;
	cout<<"请输入该学生的姓名：";
	cin>>s->name;
	cout<<"请输入该学生的年龄：";
	cin>>s->age;
	cout<<"请输入该学生的性别：";
	cin>>s->sex;
	s->first=NULL;
	s->exist=true;

	
	int i;
	cout<<"该学生的共有几门课？";			//下面输入课程信息
	cin>>s->numCourse;
	if(s->numCourse>0)
	{
		c=(Course *)malloc(sizeof(Course));
		if(!c)
		{
			cout<<"申请地址空间失败！";
			exit(0);
		}
		cout<<"请输入第1门课程的课程名：";
		cin>>c->name;
		cout<<"请输入该课程的成绩：";
		cin>>c->score;
		cout<<"请输入该课程的授课教师：";
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
			cout<<"申请地址空间失败！";
			exit(0);
		}
		cout<<"请输入第"<<i<<"门课程的课程名：";
		cin>>c->name;
		cout<<"请输入该课程的成绩：";
		cin>>c->score;
		cout<<"请输入该课程的授课教师：";
		cin>>c->techer;
		c->next=NULL;
		p->next=c;
		p=c;
	}

	int h,h1;									//利用hash表将数据插入
	h=Hash(s->num);
	if(student[h].exist==false)
		student[h]=*s;
	else
	{
		for(h1=(h+1)%totall;student[h1].exist==true&&h1!=h;h1=(h1+1)%totall);
		if(h==h1)
		{
			cout<<"错误：插入学生信息时空间已满！";
			exit(0);
		}
		else
			student[h1]=*s;
	}
	
	free(s);
	return OK;
}


int SearchNum()				//根据学号查找，查找不到返回-1
{
	int h,h1;
	char studNum[10];
	cout<<"请输入该同学的学号：";
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

Status DisplayOne(int n)				//n 为学生信息结构数组的下标，可由查询函数获得
{
	cout<<"  学号："<<student[n].num
		<<"     姓名："<<student[n].name<<endl
		<<" \t\t年龄："<<student[n].age
		<<"   性别："<<student[n].sex<<endl;
	if(student[n].first)
	{
		Course *c;
		cout<<"\t该同学所学课程有："<<endl;
		for(c=student[n].first;c;c=c->next)
		{
			cout<<"\t 课程名："<<c->name
				<<"   成绩："<<c->score
				<<" 任课老师："<<c->techer<<endl;
		}		
	}
	else
	{
		cout<<"\t该同学没有学任何课程。"<<endl;
	}
	return OK;
}

Status Delete()					//删除同学，即将相应位置的exist标志改为false
{
	system("cls");
	int n;
	n=SearchNum();
	if(n<0)
	{
		cout<<"查找失败，请确认输入该学生的正确信息！";
		return false;
	}
	else
	{
		DisplayOne(n);
		cout<<"确认删除吗？输入Y，确认；输入其他键，取消。";
		char choice;
		cin>>choice;
		cin.clear();
		cin.ignore();
		if(choice=='y'||choice=='Y')
			student[n].exist=false;
	}
	return OK;
}

Status Edit()				//编辑同学信息
{
	system("cls");
	int n;
	n=SearchNum();
	if(n<0)
	{
		cout<<"查找失败，请确认输入该学生的正确信息！";
		return false;
	}
	else
	{
		DisplayOne(n);
		char choice;
		cout<<"  请问需要修改该同学的什么信息?"<<endl;
		cout<<"\tA.学号"<<endl
			<<"\tB.姓名"<<endl
			<<"\tC.年龄"<<endl
			<<"\tD.性别"<<endl
			<<"\tE.课程"<<endl;
		cout<<"\t\t请输入A,B,C,D或E：";
		cin>>choice;
		cin.clear();
		cin.ignore();
		while(choice!='A'&&choice!='B'&&choice!='C'&&choice!='D'&&choice!='E'&&choice!='a'&&choice!='b'&&choice!='c'&&choice!='d'&&choice!='e')
		{
			cout<<"\t\t请输入A,B,C,D或E（不分大小写）：";
			cin>>choice;
			cin.clear();
			cin.ignore();
		}
		switch(choice)
		{
			case 'a':
			case 'A':
				cout<<"\t请输入该学生的学号：";
				cin>>student[n].num;
				break;
			case 'b':
			case 'B':
				cout<<"\t请输入该学生的姓名：";
				cin>>student[n].name;
				break;
			case 'c':
			case 'C':
				cout<<"\t请输入该学生的年龄：";
				cin>>student[n].age;
				break;
			case 'd':
			case 'D':
				cout<<"\t请输入该学生的性别：";
				cin>>student[n].sex;
				break;
			case 'e':
			case 'E':
				{
					int i;
					Course *c,*p;
					cout<<"  该学生的共有几门课？";			//下面输入课程信息
					cin>>student[n].numCourse;
					if(student[n].numCourse>0)
					{
						c=(Course *)malloc(sizeof(Course));
						if(!c)
						{
							cout<<"申请地址空间失败！";
							exit(0);
						}
						cout<<"请输入第1门课程的课程名：";
						cin>>c->name;
						cout<<"\t请输入该课程的成绩：";
						cin>>c->score;
						cout<<"\t请输入该课程的授课教师：";
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
							cout<<"申请地址空间失败！";
							exit(0);
						}
						cout<<"请输入第"<<i<<"门课程的课程名：";
						cin>>c->name;
						cout<<"\t请输入该课程的成绩：";
						cin>>c->score;
						cout<<"\t请输入该课程的授课教师：";
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


/***************************查询功能中的函数************************
Status DisplayAll();
int SearchNum(); 位于基本操作中
Status SearchName();
Status SearchSex();
Status SearchGrade();
Status SearchTecher();
***************************查询功能中的函数************************/

Status DisplayAll()				//显示全部学生信息
{
	system("cls");
	cout<<"显示所有学生信息："<<endl;
	for(int i=0;i<totall;i++)
		if(student[i].exist)
		{
			DisplayOne(i);
			cout<<endl;
		}
	cout<<"\n  显示完毕！"<<endl;
	system("pause");
	return OK;
}

Status SearchName()				//按姓名查询
{
	char name[20];
	cout<<"请输入所要查找的学生的姓名：";
	cin>>name;
	for(int i=0;i<totall;i++)
		if(student[i].exist&&!strcmp(student[i].name,name))
		{
			DisplayOne(i);
			cout<<endl;
		}
	cout<<"\n  显示完毕！"<<endl;
	system("pause");
	return OK;
}

Status SearchSex()				//按性别查询
{
	system("cls");
	char sex[6];
	cout<<"\t\t按性别查询"<<endl;
	cout<<" 请输入所要查询的性别：";
	cin>>sex;
	for(int i=0;i<totall;i++)
		if(student[i].exist&&!strcmp(student[i].sex,sex))
		{
			DisplayOne(i);
			cout<<endl;
		}
	cout<<"\n  显示完毕！"<<endl;
	system("pause");
	return OK;
}

Status SearchGrade()			//按年级查询学生的所学课程
{
	system("cls");
	char grade[5];
	Course *c;
	cout<<"\t\t按年级查询学生的所学课程"<<endl;
	cout<<" 请输入该年级入学的年份：";
	cin>>grade;
	cout<<"该年级学生的课程："<<endl;
	for(int i=0;i<totall;i++)
		if(student[i].exist&&student[i].num[2]==grade[2]&&student[i].num[3]==grade[3])
		{
			cout<<"  学号："<<student[i].num
				<<"     姓名："<<student[i].name<<endl;
			if(student[i].first)
			{
				cout<<"\t该同学所学课程有："<<endl;
				for(c=student[i].first;c;c=c->next)
				{
					cout<<"\t 课程名："<<c->name
						<<"   成绩："<<c->score
						<<" 任课老师："<<c->techer<<endl;
				}		
			}
			else
			{
				cout<<"\t该同学没有学任何课程。"<<endl;
			}

		}
	cout<<"\n  显示完毕！"<<endl;
	system("pause");
	return OK;
}

Status SearchTecher()			//按教师查询听课学生信息
{
	system("cls");
	Course *c;
	char techer[20];
	cout<<"\t\t按教师查询听课学生信息"<<endl;
	cout<<" 请输入所要查询的教师名：";
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
	cout<<"\n  显示完毕！"<<endl;
	system("pause");
	return OK;
}

/***************************排序功能中的函数************************
Status SortNum()				//按学号排序
Status SortAge()				//按年龄排序
Status SortScore()				//按某一科的成绩排序
Status SortTotallScore()		//按总成绩排序
定义了两个排序用结构体,对此结构体数组进行排序
***************************排序功能中的函数************************/

//按学号排序，用希尔排序
void ShellInsert(Sort1 s[],int dk,int length)			//希尔插入排序
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
Status SortNum()				//按学号排序，用希尔排序
{
	Sort1 s[totall];
	int studNum=0;			//记录学生的个数，也是s数组中信息的个数

	for(int i=0;i<totall;i++)			//对排序数组进行赋值,s[0]只是暂存单元，不是哨兵
	if(student[i].exist)
	{
		studNum++;
		strcpy(s[studNum].num,student[i].num);
		s[studNum].index=i;
	}

	for(int k=(totall/2);k>0;k=k/2)
		ShellInsert(s,k,studNum);

	system("cls");
	cout<<"按学号排序完毕，下面输出排序结果"<<endl;
	for(i=1;i<=studNum;i++)
	{
		DisplayOne(s[i].index);
		cout<<endl;
	}
	cout<<"\n  显示完毕！"<<endl;
	system("pause");
	return OK;
}

//按年龄排序，用快速排序
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
Status SortAge()				//按年龄排序，用快速排序
{
	Sort2 s[totall];
	int studNum=0;			//记录学生的个数，也是s数组中信息的个数

	for(int i=0;i<totall;i++)			//对排序数组进行赋值,s[0]只是暂存单元，不是哨兵
	if(student[i].exist)
	{
		studNum++;
		s[studNum].key=student[i].age;
		s[studNum].index=i;
	}

	QSort(s,1,studNum);

	system("cls");
	cout<<"按年龄排序完毕，下面输出排序结果"<<endl;
	for(i=1;i<=studNum;i++)
	{
		DisplayOne(s[i].index);
		cout<<endl;
	}
	cout<<"\n  显示完毕！"<<endl;
	system("pause");
	return OK;
}

//按某一科的成绩排序，用堆排序
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
Status SortScore()				//按某一科的成绩排序，用堆排序
{
	Sort2 s[totall];
	int studNum=0;			//记录学生的个数，也是s数组中信息的个数
	char name[30];
	Course *c;
	system("cls");
	cout<<"按某一科的成绩排序，请输入课程名："<<endl;
	cin>>name;
	for(int i=0;i<totall;i++)			//对排序数组进行赋值,s[0]只是暂存单元，不是哨兵
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
		
		cout<<"按"<<name<<"的成绩排序完毕，下面输出排序结果"<<endl;
		for(i=1;i<=studNum;i++)
		{
			DisplayOne(s[i].index);
			cout<<endl;
		}
		
		cout<<"\n  显示完毕！"<<endl;
	}
	else
		cout<<"很遗憾，没有人选这门课！"<<endl;
	system("pause");
	return OK;
}

//按总成绩排序，用归并排序
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
Status SortTotallScore()		//按总成绩排序，用归并排序
{
	Sort2 s[totall];
	int studNum=0;			//记录学生的个数，也是s数组中信息的个数
	Course *c;
	for(int i=0;i<totall;i++)			//对排序数组进行赋值,s[0]只是暂存单元，不是哨兵
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
	cout<<"按总成绩排序完毕，下面输出排序结果"<<endl;
	for(i=1;i<=studNum;i++)
	{
		DisplayOne(s[i].index);
		cout<<"   总成绩为:"<<s[i].key<<endl;
	}
	cout<<"\n  显示完毕！"<<endl;
	system("pause");
	return OK;
}

/***************************统计功能中的函数************************
Status StaSex()				//统计男女生的人数
Status StaAvePerson()		//统计每个人的平均成绩
Status StaAveCou()			//统计各科的平均成绩
***************************统计功能中的函数************************/
Status StaSex()
{
	int male=0,female=0;
	system("cls");
	cout<<"\t统计男女生的人数"<<endl;
	for(int i=0;i<totall;i++)
		if(student[i].exist)
		{
			if(!strcmp(student[i].sex,"男"))
				male++;
			else
				female++;
		}
	cout<<"\n统计结果为："
		<<"男生："<<male<<"人；"
		<<"女生："<<female<<"人"<<endl;
	system("pause");
	return OK;
}

Status StaAvePerson()		//统计每个人的平均成绩
{
	int sum,n;
	Course *c;
	system("cls");
	cout<<"\t统计每个人的平均成绩"<<endl;
	for(int i=0;i<totall;i++)
		if(student[i].exist)
		{
			cout<<"  学号："<<student[i].num
				<<"     姓名："<<student[i].name<<endl;
			cout<<"\t平均成绩为：";
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
	cout<<"\n  显示完毕！"<<endl;
	system("pause");
	return OK;
}

Status StaAveCou()			//统计各科的平均成绩
{
	system("cls");
	cout<<"\t统计各科的平均成绩"<<endl;
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
		cout<<"课程名："<<AC[i].name;
		cout<<"  平均成绩："<<((float)AC[i].sum)/AC[i].num<<endl;
	}
	cout<<"\n  显示完毕！"<<endl;
	system("pause");
	return OK;
}

/***************************主菜单中的函数************************
Status GetFromFile();（包括Status WriteToFile();）
Status Construct();
Status EditMain();
Status Inquire();		查询
Status Sort();
Status Statistic();		统计
Status Exit();（包括void EndCout()）
***************************主菜单中的函数************************/

Status GetFromFile()				//从文件中读入数据
{
	fstream file;
	file.open("StudInfo",ios::in|ios::binary);
	if(!file)
	{
		cout<<"打开文件失败！"<<endl;
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
		cout<<"申请地址空间失败！";
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
			cout<<"申请地址空间失败！";
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
文件结构：
结构数组student[totall]
各个人的{int下标n，int课程数numCourse,各个课程Course
*/
Status WriteToFile()				//将数据写入文件
{
	fstream file;
	file.open("StudInfo",ios::out|ios::binary);
	if(!file)
	{
		cout<<"打开文件失败！"<<endl;
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

Status Construct()					//重新建立数据
{
	int iTotall;
	for(iTotall=0;iTotall<totall;iTotall++)			//将所有位置置空
		student[iTotall].exist=false;
	
	int num;
	system("cls");
	cout<<"请问，总共有多少名同学：";
	cin>>num;
	if(num>0)
	{
		for(int i=0;i<num;i++)
		{
			cout<<"下面输入第"<<(i+1)<<"名同学的信息："<<endl;
			Insert();
		}
		cout<<"输入结束！"<<endl;
		system("pause");
		return OK;
	}
	else
	{
		cout<<"同学数为负数或零，不进行学生信息的输入！强制从文件中读入数据！"<<endl;
		GetFromFile();
		system("pause");
		return ERROR;
	}
}

Status EditMain()					//编辑学生数据
{
	char choice;
	while(1)
	{
		system("cls");
		cout<<"\n\n\t\t学生成绩管理系统"<<endl;
		cout<<"\n\t\t    编辑学生数据";
		cout<<"\n\t\t A.插入一个学生信息"
			<<"\n\t\t B.删除一个学生信息"
			<<"\n\t\t C.修改一个学生信息"
			<<"\n\t\t D.回主菜单"<<endl;
		cout<<"\t\t请输入A,B,C或D：";
		cin>>choice;
		cin.clear();
		cin.ignore();
		while(choice!='A'&&choice!='B'&&choice!='C'&&choice!='D'&&choice!='a'&&choice!='b'&&choice!='c'&&choice!='d')
		{
			cout<<"\t\t请输入A,B,C或D（不分大小写）：";
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
		cout<<"\n\n\t\t学生成绩管理系统"<<endl;
		cout<<"\n\t\t    查询学生信息";
		cout<<"\n\t\t A.显示全部学生信息"
			<<"\n\t\t B.按学号查询"
			<<"\n\t\t C.按姓名查询"
			<<"\n\t\t D.按性别查询"
			<<"\n\t\t E.按年级查询学生的所学课程"
			<<"\n\t\t F.按教师查询听课学生信息"
			<<"\n\t\t G.回主菜单"<<endl;
		cout<<"\t\t请输入A,B,C,D,E,F或G：";
		cin>>choice;
		cin.clear();
		cin.ignore();
		while(choice!='A'&&choice!='B'&&choice!='C'&&choice!='D'&&choice!='E'&&choice!='F'&&choice!='G'&&choice!='a'&&choice!='b'&&choice!='c'&&choice!='d'&&choice!='e'&&choice!='f'&&choice!='g')
		{
			cout<<"\t\t请输入A,B,C,D,E,F或G（不分大小写）：";
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
					cout<<"\n  显示完毕！"<<endl;
				}else
					cout<<"查找失败，请确认输入该学生的正确信息！"<<endl;
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
		cout<<"\n\n\t\t学生成绩管理系统"<<endl;
		cout<<"\n\t\t 对学生信息排序";
		cout<<"\n\t\t A.按学号排序"
			<<"\n\t\t B.按年龄排序"
			<<"\n\t\t C.按某一科的成绩排序"
			<<"\n\t\t D.按总成绩排序"
			<<"\n\t\t E.回主菜单"<<endl;
		cout<<"\t\t请输入A,B,C,D或E：";
		cin>>choice;
		cin.clear();
		cin.ignore();
		while(choice!='A'&&choice!='B'&&choice!='C'&&choice!='D'&&choice!='E'&&choice!='a'&&choice!='b'&&choice!='c'&&choice!='d'&&choice!='e')
		{
			cout<<"\t\t请输入A,B,C,D或E（不分大小写）：";
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
		cout<<"\n\n\t\t学生成绩管理系统"<<endl;
		cout<<"\n\t\t  统计学生信息";
		cout<<"\n\t\t A.统计男女生的人数"
			<<"\n\t\t B.统计每个人的平均成绩"
			<<"\n\t\t C.统计各科的平均成绩"
			<<"\n\t\t D.回主菜单"<<endl;
		cout<<"\t\t请输入A,B,C或D：";
		cin>>choice;
		cin.clear();
		cin.ignore();
		while(choice!='A'&&choice!='B'&&choice!='C'&&choice!='D'&&choice!='a'&&choice!='b'&&choice!='c'&&choice!='d')
		{
			cout<<"\t\t请输入A,B,C或D（不分大小写）：";
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
	cout<<"\n\t\t学生成绩管理系统"
		<<"\n\t\t  数据结构 课程设计"
		<<"\n\t\t信息科学与技术学院"
		<<"\n\t\t       张鹏鹏"
		<<"\t学号：040630416"<<endl;
	system("pause");
	exit(0);
}

Status MExit()
{
	char choice;
	system("cls");
	cout<<"即将退出系统……\n   请问，需要将现有数据保存到文件中吗？"<<endl;
	cout<<"\tY.是的，马上保存数据"<<endl
		<<"\tN.没必要，这数据不值得保存"<<endl;
	cout<<"\t\t请输入Y或N：";
	cin>>choice;
	cin.clear();
	cin.ignore();
	while(choice!='Y'&&choice!='N'&&choice!='y'&&choice!='n')
	{
		cout<<"\t\t请输入Y或N（不分大小写）：";
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
		cout<<"你确定吗？"<<endl;
		cout<<"\tY.是的，马上退出"<<endl
			<<"\tN.慢着，还是保存一下吧"<<endl;
		cout<<"\t\t请输入Y或N：";
		cin>>choice;
		cin.clear();
		cin.ignore();
		while(choice!='Y'&&choice!='N'&&choice!='y'&&choice!='n')
		{
			cout<<"\t\t请输入Y或N（不分大小写）：";
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



/**************************主函数*******************************/

void main()
{
	char choice;

	cout<<"\n\n\t\t学 生 成 绩 管 理 系 统"<<endl;
	cout<<"\n\n请选择：现在重新建立数据吗？"<<endl;
	cout<<"\tY.是的，重新建立数据"<<endl
		<<"\tN.不，从文件中读入数据"<<endl;
	cout<<"\t\t请输入Y或N：";
	cin>>choice;
	cin.clear();
	cin.ignore();
	while(choice!='Y'&&choice!='N'&&choice!='y'&&choice!='n')
	{
		cout<<"\t\t请输入Y或N（不分大小写）：";
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
		cout<<"\n\n\t\t学生成绩管理系统"<<endl;
		cout<<"\n\t\t\t主菜单";
		cout<<"\n\t\t A.重新建立数据"
			<<"\n\t\t B.编辑学生数据"
			<<"\n\t\t C.查询学生信息"
			<<"\n\t\t D.对学生信息排序"
			<<"\n\t\t E.统计学生信息"
			<<"\n\t\t F.退出系统"<<endl;
		cout<<"\t\t    请输入A,B,C,D,E或F：";
		cin>>choice;
		cin.clear();
		cin.ignore();
		while(choice!='A'&&choice!='B'&&choice!='C'&&choice!='D'&&choice!='E'&&choice!='F'&&choice!='a'&&choice!='b'&&choice!='c'&&choice!='d'&&choice!='e'&&choice!='f')
		{
			cout<<"\t\t    请输入A,B,C,D,E或F（不分大小写）：";
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
			






