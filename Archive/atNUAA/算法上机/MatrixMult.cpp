//������  040630416@nuaa  ��Ϣ��ѧ�뼼��ѧԺ

#include <iostream.h>
#include <time.h>
#include <stdlib.h>

/************************ȫ�ֱ���*********************/
int ArT[10000][10000]			//�������飬�Դ˽��д�ͳ�㷨
int ArS[10000][10000];			//��ArTһ�����Դ˽���STRASSEN�㷨
int numArr;						//����Ԫ�ظ������ֶ�����,��100��10000��
double countMul;				//�㷨ִ�г˷��Ĵ���
double countAdd;				//�㷨ִ�мӷ��Ĵ���
double notes[4][10000];			//��¼numArr�αȽϵĴ���
double countAver[4];			//��¼ÿ���㷨sortMode������ģ��ƽ���Ƚϴ���
								//0��1ʱ��¼��ͳ�㷨�ĳ˷��ͼӷ���2��3���ƣ���ΪoperMode

/**************************׼������**********************
void getArr()					//�����������
void statistics(int sortMode)	//ͳ��ƽ������
void output()					//������
*********************************************************/

void getArr()					//�����������
{
	srand (time(NULL));
	for(int i=0;i<numArr;i++)
		for(int j=0;j<numArr;j++)
		{
			ArT[i]=rand();
			ArS[i]=ArT[i];
		}
}

void statistics()				//ͳ��ƽ������
{
	double sum;
	int compCount,operMode;
	for(operMode=0;operMode<4;operMode++)
	{
		sum=0;
		for(compCount=0;compCount<numArr;compCount++)
			sum+=notes[operMode][compCount];
		countAver[operMode]=sum/numArr;
	}
}
void output()					//������
{
	cout<<endl;
	cout<<"\n\n\t �����������"<<numArr<<"�����ݹ�ģ��"<<endl;
	cout<<"��ͳ�㷨�ĳ˷��������ӷ�������STRASSEN�㷨�ĳ˷��������ӷ�������"<<endl;
	for(int operMode;operMode<4;operMode++)
		cout<<countAver[operMode]<<",    ";
	cout<<endl;
	cout<<"************End************"<<endl;
}


/**********************************������*****************************/
void main ()
{
	cout<<"������n��n����ĵ���Ԫ�ظ���n��500��5000����";
	cin>>numArr;
	if(numArr==0)	exit(0);	//�����˳�
	int compCount;
	for(compCount=0;compCount<numArr;compCount++)			//ִ�бȽ�
	{
		if((compCount+1)%100==0)
			cout<<compCount+1<<endl;
		getArr();



	statistics();
	output();
}