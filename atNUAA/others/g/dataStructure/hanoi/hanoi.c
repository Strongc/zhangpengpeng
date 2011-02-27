
/***************************************
   for my postgraduate student life
   by Zhang Pengpeng 
   rocflyhi@gmail.com
**************************************/

/*****************************************
  hanoi tower
*****************************************/

#include <stdio.h>
#include <stdlib.h>
   
#define LENGTH 5

/**** key operation ****/
int hanoi(int num, int *X, int * Y, int *Z);	 //move $num disks from X to Z throgh Y
int move(int *P, int *Q);	//move the top disk of $P to $Q

/**** assistant operation ***/
int displayAll(int num ,int *X, int *Y, int *Z);
int *x,*y,*z;

/****************************** main entry *****************************/
int main()
{
	int num=5;
	int X[10]={5,4,3,2,1,0,0,0,0,0};
	int Y[10]={0,0,0,0,0,0,0,0,0,0};
	int Z[10]={0,0,0,0,0,0,0,0,0,0};
	x=X;
	y=Y;
	z=Z;

	displayAll(LENGTH,x,y,z);	//print the tower before operation
	hanoi(num,X,Y,Z);

	return 0;
}

int hanoi(int num, int *X, int * Y, int *Z)	 //move $num disks from X to Z throgh Y
{
	if(num==1)
		move(X,Z);
	else
	{
		hanoi(num-1,X,Z,Y);
		move(X,Z);
		hanoi(num-1,Y,X,Z);
	}

	return 0;
}

int move(int *P, int *Q)	//move the top disk of $P to $Q
{
	int i,j;
	for(i=9;P[i]==0&&i>=0;i--);
	for(j=0;Q[j]!=0&&j<10;j++);
	if(i<0||j>9)
		return 0;
	else
	{
		Q[j]=P[i];
		P[i]=0;
		displayAll(LENGTH,x,y,z);
	}

	return 0;
}

int displayAll(int num,int *X, int *Y, int *Z)		//should be call at tower changes becase $movetimes counts
{
	int i;
	static movetimes=0;
	printf("%d--------------------------------\n",movetimes++);
	for(num--;num>=0;num--)
	{
		for(i=LENGTH;i>X[num];i--)
			printf(" ");
		for(;i>0;i--)
			printf("**");
		for(i=LENGTH;i>X[num];i--)
			printf(" ");

		printf("|");
		for(i=LENGTH;i>Y[num];i--)
			printf(" ");
		for(;i>0;i--)
			printf("**");
		for(i=LENGTH;i>Y[num];i--)
			printf(" ");

		printf("|");
		for(i=LENGTH;i>Z[num];i--)
			printf(" ");
		for(;i>0;i--)
			printf("**");
		for(i=LENGTH;i>Z[num];i--)
			printf(" ");

		printf("\n");
	}

	return 0;
}
