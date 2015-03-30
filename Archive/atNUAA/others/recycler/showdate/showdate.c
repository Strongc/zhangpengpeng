#include<stdio.h> 
#include<stdlib.h>

int p=0; 

void da(int xing1,int day1,int xing2,int day2) 
{
	int ding1,i1,ding2,i2; 
	
	printf(" SUN MON TUE WED THR FRI SAT   "); 
	printf("  SUN MON TUE WED THR FRI SAT\n"); 

	for(ding1=0;ding1<xing1;ding1++) 
		printf("%4c",' '); 
	for(i1=1;xing1<7;xing1++,i1++)
		printf("%4d",i1);
	printf("    ");

	for(ding2=0;ding2<xing2;ding2++) 
		printf("%4c",' '); 
	for(i2=1;xing2<7;xing2++,i2++)
		printf("%4d",i2);
	printf("\n");

	while(i1<=day1||i2<=day2) 
	{
		while(i1<=day1||i2<=day2) 
		{
			if(i1<=day1)
				printf("%4d",i1); 
			else
				printf("    ");
			xing1=(xing1+1)%7; 
			i1++;
			if(xing1==0)
			{
				printf("    "); 
				break;
			}
		}

		while(i1<=day1||i2<=day2) 
		{
			if(i2<=day2)
				printf("%4d",i2); 
			else
				printf("    ");
			xing2=(xing2+1)%7; 
			i2++;
			if(xing2==0)
			{
				printf("\n"); 
				break;
			}
		}
	} 
} 



int rui(int year) 
{ 
	if(year%4==0&&year%100!=0||year%400==0) 
		return 1; 
	else 
		return 0; 
} 

int day(int y,int year) 
{ 
	if(y==1||y==3||y==5||y==7||y==8||y==10||y==12) 
		return 31; 
	if(y==4||y==6||y==9||y==11) 
		return 30; 
	if(y==2&&rui(year)==1)
		return 29; 
	else 
		return 28; 
} 

int xing1(int year,int e,int k) 
{
	int i,w=0; 
	static int l; 
	for(i=2001;i<year;i++) 
	{
		if(rui(i)==1)
			w++;
	} 
	if(k==0) 
	{
		p=1; 
		l=(year-2001+1+w)%7; 
	} 
	else 
		l+=e%7; 
	return l%7; 
} 
 
int b;
int xing2(int year,int m) 
{ 
	int i,w=0;

	for(i=2001;i<year;i++) 
		if(rui(i)==1)
			w++; 

	if(m==1)
	{
		b=(b+(year-2001+1+w))%7; 
		if(rui(i)!=1) 
			b=(181+b)%7;
		else 
			b=(182+b)%7;

	}
	else
		b=(b+day(m+6-1, year))%7; 
	return b%7; 
}  


int main() 
{
	int i,year; 
	printf("Please input the year whose calendar you want to know(later than 2000):"); 
	scanf("%4d",&year); 
	printf("\n==================The Calendar of Year %4d=====================\n",year);
	for(i=1;i<=6;i++) 
	{ 
		printf("\n=============%2d月=============||===========%2d月==============\n",i,i+6); 
		da((xing1(year,day(i-1, year),p)),day(i, year),\
				(xing2(year,i)),day(i+6, year)); 
	} 
	printf("\n");
	return 0;
}
