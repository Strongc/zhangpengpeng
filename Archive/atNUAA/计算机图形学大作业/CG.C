/****************************************
	《计算机图形学》大作业   
	信息科学与技术学院     张鹏鹏  040630416 
	几点注意：
	1，除了启动时的欢迎界面，本程序完全由鼠标控制；
	2，操作时不要点住鼠标不放（除了B样条下拖动点），这种动作已经被程序屏蔽了；
	3，画折线、多变形时，以鼠标右击结束；
	4，B样条不是同一时期写的，所以与其他部分没多太多关联；
	5，驱动程序为 EGAVGA.BGI，放在源文件或程序的相同目录下；（驱动程序我是用二分查找的方法找到的）
	6，选择图形时，请尽可能靠近顶点（或圆心）；
****************************************/

#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "mouse.h"
#include "math.h"

#define PI 3.14159265

typedef struct dot			/*点*/
{
	int x;
	int y;
}DOT;
typedef struct multiline	/*图形均采用结构体记载，以后可以方便的扩展其属性，需要时再申请存储空间*/
{
	struct dot dots[50];	/*点的最多个数；圆时[0]处放圆点，[1]处放圆周上一点；矩形时[0]处放一角的点，[1]处放另一角的点*/
	int color;			/*图形的颜色*/
	int type;			/*图形的类型，折线为1，多边形为2，圆为3，矩形为4 ；*/
	int count;			/*numbers of dots,also point to the next blank dot.no used when circle and rectangle*/
} MLINE;

typedef struct matrix	/*矩阵，行列数为1～3*/
{
	int col;	/*行数*/
	int row;	/*列数*/
	float m[3][3]; 
}MATRIX;

/*函数声明*/
int cgMain();
void chgBorderClr(int);
void displayXY(int ,int );
void showmsg(char *);
void myMouse(int ,int );
int freeline(MLINE *);
int mycircle(MLINE *);
void subcircle(int,int,int,int);
int myrectangle(MLINE *);
void cut(MLINE *);
MLINE * subcut(MLINE *,int *,int ,int ,int );
DOT getcrosp(DOT ,DOT ,int ,int ,int);
void mMultiply(MATRIX *,MATRIX *,MATRIX *);
void move(MLINE *);
void subtrans(MLINE *,float ,float ,float ,float ,float ,float );
void whirl(MLINE *);
void setCer(MLINE *);
void zoom(MLINE *);
void BLine();


void main()
{
	int isEnd;
	void preMian();

	preMian();
	do
	{
		isEnd=cgMain();
	}while(isEnd==1);
}

void preMian()
{
	system("cls");
	printf("\n\n\n\t  Hello ,welcome!\n\n\n\t\tComputer Graphics\n\t\t\tby ZhangPengpeng\n\n\n\t\t\t\t\t");
	system("pause");
}

int cgMain()				/*返回值 ，1 reset ,2 close*/
{
	int gdrive,gmode;
	int isEnd=0; 			/*returned value:go to end or continue*/
	int x=0,y=0;
	int oldx=x,oldy=y;
	int mousebutton;
	MLINE *mln[20];		/*图形的最多数*/
	int mlnCount=0;		/*现在图形的个数*/
	int drawmode=0;		/*what to do now*/
	int x_gd,y_gd;			/*using when get drawmode*/
	int temp;				/*temporary variable,used once or in nearly context*/
	int color=15;	/*color using now*/
	void showUI();
	int setDMC(int ,int );
	int selectG(MLINE **,int ,int );

	gdrive=DETECT;
	initgraph(&gdrive,&gmode,"");
	setwritemode(XOR_PUT);

	showUI();
	setcolor(15);
	showmsg("Please make your choice!");
	myMouse(x,y);
	while(!isEnd)
	{
		mousebutton=0;
		getmousexy(&x,&y);
		getmousebutton(&mousebutton);
		if(x!=oldx||y!=oldy)
		{
			myMouse(oldx,oldy);
			myMouse(x,y);
			displayXY(x,y);
		}
		
		if(mousebutton==1) 		/*set drawmode*/
		{
			getmousexy(&x_gd,&y_gd);
			if(x_gd<85)
				drawmode=setDMC(x_gd,y_gd);
			while(mousebutton==1)				/*按下鼠标会持续一段时间，造成多次错误循环，用此屏蔽*/
				getmousebutton(&mousebutton);
		}		
		if(drawmode>100)	/*change current color ,the black color are forbidden*/
		{
			color=drawmode-100;
			myMouse(x,y);
			setcolor(color);
			myMouse(x,y);
			drawmode=0;
		}
		
		if(drawmode<=11&&drawmode>0)	/*处理子函数的前期处理*/
		{
			myMouse(x,y);		
			chgBorderClr(drawmode);
			setcolor(color);		/*color are set to 15 in function chgBorder()*/
		}	
		switch(drawmode)		/*进入处理子函数*/
		{
			case 1 :	/*画折线*/
				showmsg("Now drawing a fold line");
				mln[mlnCount]=(MLINE *)malloc(sizeof(MLINE));
				mln[mlnCount]->color=color;
				mln[mlnCount]->type=1;
				temp=freeline(mln[mlnCount]);
				if(temp==1)	/*judging the effectiveness*/
					mlnCount++;
				break;
			case 2 :	/*画多边形*/
				showmsg("Now drawing a ploygon");
				mln[mlnCount]=(MLINE *)malloc(sizeof(MLINE));
				mln[mlnCount]->color=color;
				mln[mlnCount]->type=2;
				temp=freeline(mln[mlnCount]);
				line(mln[mlnCount]->dots[0].x,mln[mlnCount]->dots[0].y,mln[mlnCount]->dots[mln[mlnCount]->count-1].x,mln[mlnCount]->dots[mln[mlnCount]->count-1].y);
				if(temp==1&&mln[mlnCount]->count>2)	/*judging the effectiveness*/
					mlnCount++;
				break;
			case 3 :	/*画圆*/
				showmsg("Now drawing a circle");
				mln[mlnCount]=(MLINE *)malloc(sizeof(MLINE));
				mln[mlnCount]->color=color;
				mln[mlnCount]->type=3;
				temp=mycircle(mln[mlnCount]);
				if(temp==1)	/*judging the effectiveness*/
					mlnCount++;
				break;
			case 4 :	/*画矩形*/
				showmsg("Now drawing a rectangle");
				mln[mlnCount]=(MLINE *)malloc(sizeof(MLINE));
				mln[mlnCount]->color=color;
				mln[mlnCount]->type=4;
				temp=myrectangle(mln[mlnCount]);
				if(temp==1)	/*judging the effectiveness*/
					mlnCount++;
				break;
			case 5 :	/*裁剪*/
				temp=selectG(mln,mlnCount ,2);
				if(temp>=0)
					cut(mln[temp]);
				if(temp==-1)
				{
					showmsg("No ploygon selected,select or draw one  .Press to continue.");
					do
					{
						getmousebutton(&mousebutton);
					}while(mousebutton==0);
				}
				break;
			case 6 :	/*平移*/
				temp=selectG(mln,mlnCount ,0);
				if(temp>=0)
					move(mln[temp]);
				if(temp==-1)
				{
					showmsg("No graph selected,select or draw one  .Press to continue.");
					do
					{
						getmousebutton(&mousebutton);
					}while(mousebutton==0);
				}
				break;
			case 7 :	/*旋转*/
				temp=selectG(mln,mlnCount ,0);
				if(temp>=0)
					whirl(mln[temp]);
				if(temp==-1)
				{
					showmsg("No graph selected,select or draw one  .Press to continue.");
					do
					{
						getmousebutton(&mousebutton);
					}while(mousebutton==0);
				}
				break;
			case 8 :	/*缩放*/
				temp=selectG(mln,mlnCount ,0);
				if(temp>=0)
					zoom(mln[temp]);
				if(temp==-1)
				{
					showmsg("No graph selected,select or draw one  .Press to continue.");
					do
					{
						getmousebutton(&mousebutton);
					}while(mousebutton==0);
				}
				break;
			case 9 :	/*B样条*/
				BLine();
				break;
			case 10:
				isEnd=1;
				break;
			case 11:
				isEnd=2;
				break;
			case 0 :
			default :;
				;
		}
		if(drawmode<11&&drawmode>0)	/*处理子函数的后期处理*/
		{
			chgBorderClr(drawmode);
			setcolor(color);		/*color are set to 15 in function chgBorder() and even sub-processing function*/
			showmsg("Please make your choice!");
			drawmode=0;
			myMouse(x,y);
		}
		
		oldx=x;
		oldy=y;
	}

	closegraph();
	return isEnd;
}

void showUI()		/*display the user interface*/
{
	int y;  /*use for offset per choice*/
	int i;
	setcolor(9);
	line(0,20,640,20);		/*follows:main frame*/
	line(87,20,87,460);
	line(0,460,640,460);
	line(637,20,637,460);
	for(i=0;i<=4;i++)		/*follows:color zone*/
		line(3,330+20*i,83,330+20*i);
	for(i=0;i<=4;i++)
		line(3+20*i,330,3+20*i,410);
	setfillstyle(1,8);
	floodfill(80,25,9);			/*fill main-frame color*/
	floodfill(1,1,9);
	floodfill(0,461,9);
	floodfill(638,22,9);
	for(i=0;i<16;i++)	/*fill color-zone color*/
	{
		setfillstyle(1,i);
		floodfill(5+i%4*20,332+i/4*20,9);
	}
	setcolor(10);
	outtextxy(50,7,"Computer Graphics Homework   by ZhangPengpeng 040630416 from NUAA");

	y=25;	/*方便调整按钮高度*/
	for(i=0;i<11;i++) /*give initial button border*/
	{
		setcolor(7);
		line(1,22+i*y,84,22+i*y);
		line(2,23+i*y,83,23+i*y);
		line(1,23+i*y,1,20+y-3+i*y);
		line(2,24+i*y,2,20+y-4+i*y);
		setcolor(8);
		line(1,20+y-2+i*y,84,20+y-2+i*y);
		line(2,20+y-3+i*y,83,20+y-3+i*y);
		line(84,23+i*y,84,20+y-3+i*y);
		line(83,24+i*y,83,20+y-4+i*y);
	}
	setcolor(1);
	i=0;
	outtextxy(3,27+(i++)*y,"  line");
	outtextxy(3,27+(i++)*y," ploygon");
	outtextxy(3,27+(i++)*y,"  circle");
	outtextxy(3,27+(i++)*y," rectangle");
	outtextxy(3,27+(i++)*y,"   cut");
	outtextxy(3,27+(i++)*y,"  move");
	outtextxy(3,27+(i++)*y,"  whirl");
	outtextxy(3,27+(i++)*y,"  zoom");
	outtextxy(3,27+(i++)*y,"  B");
	outtextxy(3,27+(i++)*y,"  reset");
	outtextxy(3,27+(i++)*y,"  close");
	setcolor(15);
}

int setDMC(int x_gd,int y_gd)	 /*设置控制信息，drawmode和颜色(原有值+100做为返回值)*/
{
	int drawmode=0;
	if(y_gd<20)			/*set drawmode*/
		drawmode=0;
	else
	{
		drawmode=(y_gd-20)/25;		/*调整按钮高度时，此处也要改*/
		drawmode++;
	}

	if(y_gd>330)		/*choose color */
	{
		drawmode=(x_gd-3)/20+(y_gd-330)/20*4;
		drawmode+=100;
	}

	return drawmode;
}

int selectG(MLINE *mln[], int mlnCount, int type)			/*select a graph that you want to deal with*/
{	/*type为需查找图形的类型，其为0时代表查找所有的类型；左击选择，右击退出；返回值-1表示查找失败，-2表示右击退出，0开始表示选择的图形*/
	/*选择图形时，折线和多边形以及矩形必须在顶点附近点击才能被选中，而圆则要在圆心附近点击，这样做是为了减少计算的复杂度，提高运行速度*/
	int x=0,y=0;
	int oldx=x,oldy=y;
	int mousebutton;
	int isreturn=-3;
	int isfind=0;
	int bound=10;	/*选择范围为2×bound-2的正方形*/
	int i,j;	/*just for counting*/

	showmsg("Please select a graphic");
	while(isreturn==-3)
	{
		mousebutton=0;
		getmousexy(&x,&y);
		getmousebutton(&mousebutton);
		if(x!=oldx||y!=oldy)
		{
			myMouse(oldx,oldy);
			myMouse(x,y);
			displayXY(x,y);
		}
		
		if(mousebutton==1)
		{
			while(mousebutton==1)		/*按下鼠标会持续一段时间，造成多次错误循环，用此屏蔽*/
				getmousebutton(&mousebutton);
				
			for(i=0;i<mlnCount&&!isfind;i++)
			{
				if(mln[i]->type==type||!type)
				{
					if(mln[i]->type==1||mln[i]->type==2)
					{
						for(j=0;j<mln[i]->count;j++)
						{	
							if(x-mln[i]->dots[j].x<bound&&x-mln[i]->dots[j].x>(-bound)&&y-mln[i]->dots[j].y<bound&&y-mln[i]->dots[j].y>(-bound))
							{
								isreturn=i;
								isfind=1;
								break;
							}
						}
					}
					if(mln[i]->type==3)
					{
						if(x-mln[i]->dots[0].x<bound&&x-mln[i]->dots[0].x>(-bound)&&y-mln[i]->dots[0].y<bound&&y-mln[i]->dots[0].y>(-bound))
						{
							isreturn=i;
							isfind=1;
							break;
						}
					}
					if(mln[i]->type==4)
					{
						if(((x-mln[i]->dots[0].x<bound&&x-mln[i]->dots[0].x>(-bound))||(x-mln[i]->dots[1].x<bound&&x-mln[i]->dots[1].x>(-bound)))\
						&&((y-mln[i]->dots[0].y<bound&&y-mln[i]->dots[0].y>(-bound))||(y-mln[i]->dots[1].y<bound&&y-mln[i]->dots[1].y>(-bound))))
						{
							isreturn=i;
							isfind=1;
							break;
						}
					}
				}
			}
			if(!isfind)
				isreturn=-1;
		}
		if(mousebutton==2)
			isreturn=-2;
		oldx=x;
		oldy=y;
	}

	myMouse(oldx,oldy);
	return isreturn;
}

void chgBorderClr(int num)		/*第几个按钮，从第二次开始，由1开始记*/
{
	int y;
	y=25;	/*方便调整按钮高度*/
	num--;
	setcolor(15);
	line(1,22+num*y,84,22+num*y);
	line(2,23+num*y,83,23+num*y);
	line(1,23+num*y,1,20+y-3+num*y);
	line(2,24+num*y,2,20+y-4+num*y);
	line(1,20+y-2+num*y,84,20+y-2+num*y);
	line(2,20+y-3+num*y,83,20+y-3+num*y);
	line(84,23+num*y,84,20+y-3+num*y);
	line(83,24+num*y,83,20+y-4+num*y);
}

void displayXY(int x ,int y)
{
	char buffer[20];
	setfillstyle(0,0);
	bar(540,463,637,475);
	sprintf(buffer,"X=%d,Y=%d",x,y);
	outtextxy(543,466,buffer);
}

void showmsg(char msg[50])
{
	setfillstyle(0,0);
	bar(5,463,500,475);
	outtextxy(8,466,msg);
}
void myMouse(int x,int y)
{
	line(x-10,y,x+10,y);
	line(x,y-10,x,y+10);
}

int freeline(MLINE *mln)		/*返回值1为有效图形，2为无效图形*/
{
	int x=0,y=0;
	int oldx=x,oldy=y;
	int mousebutton;
	int bgline=0;				/*begin to line,value 0 is ready,else when lining*/
	int isreturn=0;
	int temp;

	mln->count=0;
	while(!isreturn)
	{
		mousebutton=0;
		getmousexy(&x,&y);
		getmousebutton(&mousebutton);
		if(x!=oldx||y!=oldy)
		{
			myMouse(oldx,oldy);
			myMouse(x,y);
			displayXY(x,y);
		}

		switch(mousebutton)
		{
			case 0 :
				if(bgline&&(x!=oldx||y!=oldy))
				{
					line(mln->dots[mln->count-1].x,mln->dots[mln->count-1].y,oldx,oldy);
					line(mln->dots[mln->count-1].x,mln->dots[mln->count-1].y,x,y);
				}
				break;
			case 1 :
				if(bgline==0)
					bgline=1;
				mln->dots[mln->count].x=x;
				mln->dots[mln->count].y=y;
				mln->count++;
				while(mousebutton==1)		/*按下鼠标会持续一段时间，造成多次错误循环，用此屏蔽*/
					getmousebutton(&mousebutton);
				break;
			case 2 :
				if(bgline)
				{
					line(mln->dots[mln->count-1].x,mln->dots[mln->count-1].y,oldx,oldy);
					isreturn=1;
				}
				else
					isreturn=2;
				break;
		}
		oldx=x;
		oldy=y;
	}
	myMouse(oldx,oldy);

	for(temp=0;temp<mln->count;temp++)		/*对顶点处优化*/
		line(mln->dots[temp].x,mln->dots[temp].y,mln->dots[temp].x,mln->dots[temp].y);

	return isreturn;
}

int mycircle(MLINE *mln)				/*返回值1为有效图形，2为无效图形，再次点击左键或直接点击右键均可结束画圆*/
{
	int x=0,y=0;
	int oldx=x,oldy=y;
	int mousebutton;
	int bgline=0;				/*begin to creat circle,value 0 is ready,else when processing*/
	int isreturn=0;

	while(!isreturn)
	{
		mousebutton=0;
		getmousexy(&x,&y);
		getmousebutton(&mousebutton);
		if(x!=oldx||y!=oldy)
		{
			myMouse(oldx,oldy);
			myMouse(x,y);
			displayXY(x,y);
		}

		switch(mousebutton)
		{
			case 0 :
				if(bgline&&(x!=oldx||y!=oldy))
				{
					subcircle(mln->dots[0].x,mln->dots[0].y,oldx,oldy);
					subcircle(mln->dots[0].x,mln->dots[0].y,x,y);
				}
				break;
			case 1 :
				if(bgline==0)
				{
					bgline=1;
					mln->dots[0].x=x;
					mln->dots[0].y=y;
				}
				else
				{
					subcircle(mln->dots[0].x,mln->dots[0].y,oldx,oldy);
					subcircle(mln->dots[0].x,mln->dots[0].y,x,y);
					mln->dots[1].x=x;
					mln->dots[1].y=y;
					if(mln->dots[0].x!=x&&mln->dots[0].y!=y)
						isreturn=1;
					else
						isreturn=2;
				}
				while(mousebutton==1)		/*按下鼠标会持续一段时间，造成多次错误循环，用此屏蔽*/
					getmousebutton(&mousebutton);
				break;
			case 2 :
				if(bgline)
				{
					subcircle(mln->dots[0].x,mln->dots[0].y,oldx,oldy);
					subcircle(mln->dots[0].x,mln->dots[0].y,x,y);
					mln->dots[1].x=x;
					mln->dots[1].y=y;
					if(mln->dots[0].x!=x&&mln->dots[0].y!=y)
						isreturn=1;
					else
						isreturn=2;
				}
				else
					isreturn=2;
				break;
		}
		oldx=x;
		oldy=y;
	}
	myMouse(oldx,oldy);
	return isreturn;
}

void subcircle(int initx,int inity,int x,int y)  /*create a circle, clr means color */
{
	double xd,yd,x1,y1,r;	/*x1,y1辅助计算*/
	int x2,y2,i;   	/*x2,y2表示圆上的点*/
	if(initx!=x || inity!=y)
	{
		xd=(double)initx;
		yd=(double)inity;
		x1=(double)(x-initx);
		y1=(double)(y-inity);
		x1=pow(x1,2);
		y1=pow(y1,2);
		r=sqrt(x1+y1);
		for(i=0;i<46;i++)
		{
			x2=(int)(xd+r*cos(i*PI/180));
			y2=(int)(yd+r*sin(i*PI/180));
			line(x2,y2,x2,y2);
			line(y2+initx-inity,x2+inity-initx,y2+initx-inity,x2+inity-initx);
			line(initx+inity-y2,x2+inity-initx,initx+inity-y2,x2+inity-initx);
			line(2*initx-x2,y2,2*initx-x2,y2);
			line(2*initx-x2,2*inity-y2,2*initx-x2,2*inity-y2);
			line(initx+inity-y2,initx+inity-x2,initx+inity-y2,initx+inity-x2);
			line(y2+initx-inity,initx+inity-x2,y2+initx-inity,initx+inity-x2);
			line(x2,2*inity-y2,x2,2*inity-y2);
		}
	}
}

int myrectangle(MLINE *mln)	/* create a rectangle*/
{
	int x=0,y=0;
	int oldx=x,oldy=y;
	int mousebutton;
	int bgline=0;				/*begin to line,value 0 is ready,else when processing*/
	int isreturn=0;

	while(!isreturn)
	{
		mousebutton=0;
		getmousexy(&x,&y);
		getmousebutton(&mousebutton);
		if(x!=oldx||y!=oldy)
		{
			myMouse(oldx,oldy);
			myMouse(x,y);
			displayXY(x,y);
		}

		switch(mousebutton)
		{
			case 0 :
				if(bgline&&(x!=oldx||y!=oldy))
				{
					rectangle(mln->dots[0].x,mln->dots[0].y,oldx,oldy);
					rectangle(mln->dots[0].x,mln->dots[0].y,x,y);
				}
				break;
			case 1 :
				if(bgline==0)
				{
					bgline=1;
					mln->dots[0].x=x;
					mln->dots[0].y=y;
				}
				else
				{
					rectangle(mln->dots[0].x,mln->dots[0].y,oldx,oldy);
					rectangle(mln->dots[0].x,mln->dots[0].y,x,y);
					mln->dots[1].x=x;
					mln->dots[1].y=y;
					if(mln->dots[0].x!=x&&mln->dots[0].y!=y)
						isreturn=1;
					else
						isreturn=2;
				}
				while(mousebutton==1)		/*按下鼠标会持续一段时间，造成多次错误循环，用此屏蔽*/
					getmousebutton(&mousebutton);
				break;
			case 2 :
				if(bgline)
				{
					rectangle(mln->dots[0].x,mln->dots[0].y,oldx,oldy);
					rectangle(mln->dots[0].x,mln->dots[0].y,x,y);
					mln->dots[1].x=x;
					mln->dots[1].y=y;
					if(mln->dots[0].x!=x&&mln->dots[0].y!=y)
						isreturn=1;
					else
						isreturn=2;
				}
				break;
		}
		oldx=x;
		oldy=y;
	}
	myMouse(oldx,oldy);
	return isreturn;
}

void cut(MLINE *mln)		/*多边形剪裁*/
{
	MLINE *rec;
	int temp;
	DOT recd[2];	/*two dots of the new rectangle*/
	int seat[50];	/*点的位置*/

	showmsg("Now cuting");
	setcolor(mln->color);		/*change to the former color*/
	rec=(MLINE *)malloc(sizeof(MLINE));	/*draw a rectangle first */
	temp=myrectangle(rec);
	if(temp==1)	/*judging the effectiveness*/
	{
		rectangle(rec->dots[0].x,rec->dots[0].y,rec->dots[1].x,rec->dots[1].y); 	/*erase the new rectangle*/
		for(temp=0;temp+1<mln->count;temp++)			 /*erase the old ploygon*/
			line(mln->dots[temp].x,mln->dots[temp].y,mln->dots[temp+1].x,mln->dots[temp+1].y);
		line(mln->dots[0].x,mln->dots[0].y,mln->dots[mln->count-1].x,mln->dots[mln->count-1].y);

		if(rec->dots[0].x<rec->dots[1].x)
		{
			recd[0].x=rec->dots[0].x;
			recd[1].x=rec->dots[1].x;
		}
		else
		{
			recd[0].x=rec->dots[1].x;
			recd[1].x=rec->dots[0].y;
		}
		if(rec->dots[0].y>rec->dots[1].y)
		{
			recd[0].y=rec->dots[0].y;
			recd[1].y=rec->dots[1].y;
		}
		else
		{
			recd[0].y=rec->dots[1].y;
			recd[1].y=rec->dots[0].y;
		}

		free(rec);		/*now we can free the block to save memory*/

		for(temp=0;temp<mln->count;temp++)		/*先得出位置，在调用子处理函数*/
		{
			if(mln->dots[temp].x<recd[0].x )
				seat[temp]=0;
			if(mln->dots[temp].x>=recd[0].x)
				seat[temp]=1;
		}
		mln=subcut(mln,seat,1,0,recd[0].x);
		for(temp=0;temp<mln->count;temp++)
		{
			if(mln->dots[temp].y>recd[0].y )
				seat[temp]=0;
			if(mln->dots[temp].y<=recd[0].y)
				seat[temp]=1;
		}
		mln=subcut(mln,seat,0,1,recd[0].y);
		for(temp=0;temp<mln->count;temp++)
		{
			if(mln->dots[temp].x>recd[1].x )
				seat[temp]=0;
			if(mln->dots[temp].x<=recd[1].x)
				seat[temp]=1;
		}
		mln=subcut(mln,seat,1,0,recd[1].x);
		for(temp=0;temp<mln->count;temp++)
		{
			if(mln->dots[temp].y<recd[1].y )
				seat[temp]=0;
			if(mln->dots[temp].y>=recd[1].y)
				seat[temp]=1;
		}
		mln=subcut(mln,seat,0,1,recd[1].y);
	}

	for(temp=0;temp+1<mln->count;temp++) /*draw the new ploygon*/
		line(mln->dots[temp].x,mln->dots[temp].y,mln->dots[temp+1].x,mln->dots[temp+1].y);
	line(mln->dots[0].x,mln->dots[0].y,mln->dots[mln->count-1].x,mln->dots[mln->count-1].y);

}
MLINE * subcut(MLINE *mln,int seat[50],int a,int b,int c)	/*根据书上的那四种情况进行处理,*/
{	/*参数解释：mln为原数据，也是处理后记录数据的地方；seat记录各对应点的位置，1内侧，0外侧；边界aX+bY=c*/
	int i;
	MLINE *rec ;
	rec=(MLINE *)malloc(sizeof(MLINE));	/*draw a rectangle first ,then use the block to recond the new ploygon*/

	rec->count=0;
	rec->color=mln->color;
	rec->type=2;
	mln->dots[mln->count]=mln->dots[0]; /*方便下面统一处理*/
	seat[mln->count]=seat[0];
	
	for(i=0;i<mln->count;i++)
	{
		if(seat[i]==0 && seat[i+1]==1)
		{
			rec->dots[rec->count]=getcrosp(mln->dots[i],mln->dots[i+1],a,b,c);
			rec->count++;
			rec->dots[rec->count]=mln->dots[i+1];
			rec->count++;
		}
		if(seat[i]==1 && seat[i+1]==1)
		{
			rec->dots[rec->count]=mln->dots[i+1];
			rec->count++;
		}
		if(seat[i]==1 &&seat[i+1]==0)
		{
			rec->dots[rec->count]=getcrosp(mln->dots[i],mln->dots[i+1],a,b,c);
			rec->count++;
		}
	}

	free(mln);
	return rec;

}

DOT getcrosp(DOT A,DOT B,int a21,int a22,int b2)	/*获得交点 直线AB 与a21X+a22Y=b2的交点*/
{
	DOT cp;
	float a11,a12,b1,t1,t2;
	a11=(float)A.y-(float)B.y;		/*TC太垃圾了，VC下全用int都能正确算对，tc下非得用float，还得手动强制转换*/
	a12=(float)B.x-(float)A.x;
	b1=((float)B.x*(float)A.y)-((float)A.x*(float)B.y);
	t1=(b1*a22-b2*a12)/(a11*a22-a12*a21);
	t2=(b2*a11-b1*a21)/(a11*a22-a12*a21);
	cp.x=(int)t1;
	cp.y=(int)t2;
	return cp;
}

void mMultiply(MATRIX *A,MATRIX *B,MATRIX * M)  /*矩阵相乘，成功则返回结果，失败返回空矩阵*/
{	
	int i,j,k;	/*used for counting */
	M->row=0;
	M->col=0;

	if(A->row==B->col&&A->row!=0)
	{
		M->col=A->col;
		M->row=B->row;
		for(i=0;i<A->col;i++)
			for(j=0;j<B->row;j++)
				for(k=0,M->m[i][j]=0;k<A->row;k++)
					M->m[i][j]+=A->m[i][k]*B->m[k][j];
	}				
}

void move(MLINE *mln)		/*图形的平移*/
{
	int x=0,y=0;
	int oldx=x,oldy=y;
	int mousebutton;
	int bgline=0;				/*begin to move,value 0 is ready,else when processing*/
	int isreturn=0;

	showmsg("Now moving");
	setcolor(mln->color);		/*change to the former color*/
	while(!isreturn)
	{
		mousebutton=0;
		getmousexy(&x,&y);
		getmousebutton(&mousebutton);
		if(x!=oldx||y!=oldy)
		{
			myMouse(oldx,oldy);
			myMouse(x,y);
			displayXY(x,y);
		}

		switch(mousebutton)
		{
			case 0 :
				if(bgline&&(x!=oldx||y!=oldy))
				{
					subtrans(mln,1,0,0,0,1,0);
					subtrans(mln,1,0,(float)(x-oldx),0,1,(float)(y-oldy));
				}
				break;
			case 1 :
				if(bgline==0)
					bgline=1;
				else
				{
					subtrans(mln,1,0,0,0,1,0);
					subtrans(mln,1,0,(float)(x-oldx),0,1,(float)(y-oldy));
					isreturn=1;
				}
				while(mousebutton==1)		/*按下鼠标会持续一段时间，造成多次错误循环，用此屏蔽*/
					getmousebutton(&mousebutton);
				break;
		}
		oldx=x;
		oldy=y;
	}
	myMouse(oldx,oldy);
}

void subtrans(MLINE *mln ,float a,float b,float c,float d,float e,float f)		/*变换的子函数，计算出新的图形，并画出新图形,对应于书上的那个变换矩阵，余下的为0、0、1*/
{
	MATRIX *D,*T,*M;
	int i;

	D=(MATRIX *)malloc(sizeof(MATRIX));
	T=(MATRIX *)malloc(sizeof(MATRIX));
	M=(MATRIX *)malloc(sizeof(MATRIX));
	D->col=1;
	D->row=3;
	D->m[0][2]=1;
	T->col=3;
	T->row=3;
	T->m[0][0]=a;
	T->m[1][0]=b;
	T->m[2][0]=c;
	T->m[0][1]=d;
	T->m[1][1]=e;
	T->m[2][1]=f;

	if(mln->type==1||mln->type==2)
	{
		for(i=0;i<mln->count;i++)
		{
			D->m[0][0]=(float)mln->dots[i].x;
			D->m[0][1]=(float)mln->dots[i].y;
			mMultiply(D,T,M);
			mln->dots[i].x=(int)M->m[0][0];
			mln->dots[i].y=(int)M->m[0][1];
		}
		for(i=0;i+1<mln->count;i++)
			line(mln->dots[i].x,mln->dots[i].y,mln->dots[i+1].x,mln->dots[i+1].y);
		if(mln->type==2)
			line(mln->dots[0].x,mln->dots[0].y,mln->dots[mln->count-1].x,mln->dots[mln->count-1].y);
		for(i=0;i<mln->count;i++)		/*对顶点处优化*/
			line(mln->dots[i].x,mln->dots[i].y,mln->dots[i].x,mln->dots[i].y);
	}
	if(mln->type==3 || mln->type==4)
	{
		for(i=0;i<2;i++)
		{
			D->m[0][0]=(float)mln->dots[i].x;
			D->m[0][1]=(float)mln->dots[i].y;
			mMultiply(D,T,M);
			mln->dots[i].x=(int)M->m[0][0];
			mln->dots[i].y=(int)M->m[0][1];
		}
		if(mln->type==3)
			subcircle(mln->dots[0].x,mln->dots[0].y,mln->dots[1].x,mln->dots[1].y);
		else
			rectangle(mln->dots[0].x,mln->dots[0].y,mln->dots[1].x,mln->dots[1].y);
	}

	free(D);
	free(T);
	free(M);
}

void whirl(MLINE *mln)		/*图形的旋转*/
{
	int x=0,y=0;
	int oldx=x,oldy=y;
	int mousebutton;
	int bgline=0;				/*begin to move,value 0 is ready,else when processing*/
	int isreturn=0;
	double theta1,theta2;

	showmsg("Now whirling");
	setcolor(mln->color);		/*change to the former color*/
	if(mln->type==4)		/*考虑到矩形旋转后就不是用rectangle所能画的了，也就不是类型4了，修改成类型2*/
	{
		mln->type=2;
		mln->count=4;
		mln->dots[2]=mln->dots[1];
		mln->dots[1].x=mln->dots[2].x;
		mln->dots[1].y=mln->dots[0].y;
		mln->dots[3].x=mln->dots[0].x;
		mln->dots[3].y=mln->dots[2].y;
	}

	setCer(mln);
	while(!isreturn)
	{
		mousebutton=0;
		getmousexy(&x,&y);
		getmousebutton(&mousebutton);
		if(x!=oldx||y!=oldy)
		{
			myMouse(oldx,oldy);
			myMouse(x,y);
			displayXY(x,y);
		}

		switch(mousebutton)
		{
			case 0 :
				if(bgline&&(x!=oldx||y!=oldy))
				{
					theta1=atan2((double)(oldy - mln->dots[mln->count].y),(double)(oldx - mln->dots[mln->count].x));
					theta2=atan2((double)(y - mln->dots[mln->count].y),(double)(x - mln->dots[mln->count].x));
					theta2-=theta1;
					subtrans(mln,1,0,0,0,1,0);
					subtrans(mln , (float)cos(theta2) , -(float)sin(theta2) , \
					-(float)mln->dots[mln->count].x * (float)cos(theta2) + (float)mln->dots[mln->count].y * (float)sin(theta2) + (float)mln->dots[mln->count].x , (float)sin(theta2) , \
					(float)cos(theta2) , -(float)mln->dots[mln->count].y * (float)cos(theta2) + -(float)mln->dots[mln->count].x * (float)sin(theta2) + (float)mln->dots[mln->count].y );
				}
				break;
			case 1 :
				if(bgline==0)
					bgline=1;
				else
				{
					theta1=atan2((double)(oldy - mln->dots[mln->count].y),(double)(oldx - mln->dots[mln->count].x));
					theta2=atan2((double)(y - mln->dots[mln->count].y),(double)(x - mln->dots[mln->count].x));
					theta2-=theta1;
					subtrans(mln,1,0,0,0,1,0);
					subtrans(mln , (float)cos(theta2) , -(float)sin(theta2) , \
					-(float)mln->dots[mln->count].x * (float)cos(theta2) + (float)mln->dots[mln->count].y * (float)sin(theta2) + (float)mln->dots[mln->count].x , (float)sin(theta2) , \
					(float)cos(theta2) , -(float)mln->dots[mln->count].y * (float)cos(theta2) + -(float)mln->dots[mln->count].x * (float)sin(theta2) + (float)mln->dots[mln->count].y );
					isreturn=1;
				}
				while(mousebutton==1)		/*按下鼠标会持续一段时间，造成多次错误循环，用此屏蔽*/
					getmousebutton(&mousebutton);
				break;
		}
		oldx=x;
		oldy=y;
	}
	myMouse(oldx,oldy);
}

void setCer(MLINE *mln) 		/*获得图形的中心点，记录在dots[count]，圆和矩形的count=2*/
{
	int temp,sumx,sumy;

	if(mln->type==4 || mln->type==3)	/*求中心时，统一进来处理*/
		mln->count=2;
	if(mln->type==3)
		mln->dots[2]=mln->dots[0];
	else
	{
		for(temp=0,sumx=0,sumy=0;temp<mln->count;temp++)
		{
			sumx+=mln->dots[temp].x;
			sumy+=mln->dots[temp].y;
		}
		mln->dots[temp].x=sumx/temp;
		mln->dots[temp].y=sumy/temp;
	}
}

void zoom(MLINE *mln)
{
	int x=0,y=0;
	int oldx=x,oldy=y;
	int mousebutton;
	int bgline=0;				/*begin to move,value 0 is ready,else when processing*/
	int isreturn=0;
	float sx,sy;

	showmsg("Now zooming");
	setcolor(mln->color);		/*change to the former color*/
	setCer(mln);
	while(!isreturn)
	{
		mousebutton=0;
		getmousexy(&x,&y);
		getmousebutton(&mousebutton);
		if(x!=oldx||y!=oldy)
		{
			myMouse(oldx,oldy);
			myMouse(x,y);
			displayXY(x,y);
		}

		switch(mousebutton)
		{
			case 0 :
				if(bgline&&(x!=oldx||y!=oldy))
				{
					if(x-mln->dots[mln->count].x!=0&&oldx-mln->dots[mln->count].x!=0&&y-mln->dots[mln->count].y!=0&&oldy-mln->dots[mln->count].y!=0)
					{
						sx=(float)fabs(((double)x-(double)mln->dots[mln->count].x)/((double)oldx-(double)mln->dots[mln->count].x));
						sy=(float)fabs(((double)y-(double)mln->dots[mln->count].y)/((double)oldy-(double)mln->dots[mln->count].y));
						if(mln->type!=3 || fabs((double)mln->dots[0].x-(double)mln->dots[1].x)>5 || fabs((double)mln->dots[0].y-(double)mln->dots[1].y)>5 || (sx>1 && sy>1) ) 	/*放缩时，如果这两个点靠得太近之后无法还原*/
						{
							subtrans(mln,1,0,0,0,1,0);
							subtrans(mln,sx,0,(float)mln->dots[mln->count].x *(1- sx) ,0,sy,(float)mln->dots[mln->count].y *(1-sy));
						}
					}
				}
				break;
			case 1 :
				if(bgline==0)
					bgline=1;
				else
				{
					if(x-mln->dots[mln->count].x!=0&&oldx-mln->dots[mln->count].x!=0&&y-mln->dots[mln->count].y!=0&&oldy-mln->dots[mln->count].y!=0)
					{
						sx=(float)fabs(((double)x-(double)mln->dots[mln->count].x)/((double)oldx-(double)mln->dots[mln->count].x));
						sy=(float)fabs(((double)y-(double)mln->dots[mln->count].y)/((double)oldy-(double)mln->dots[mln->count].y));
						if(mln->type!=3 || fabs((double)mln->dots[0].x-(double)mln->dots[1].x)>5 || fabs((double)mln->dots[0].y-(double)mln->dots[1].y)>5 || (sx>1 && sy>1) ) 	/*放缩时，如果这两个点靠得太近之后无法还原*/
						{
							subtrans(mln,1,0,0,0,1,0);
							subtrans(mln,sx,0,(float)mln->dots[mln->count].x *(1- sx) ,0,sy,(float)mln->dots[mln->count].y *(1-sy));
						}
					}
					isreturn=1;
				}
				while(mousebutton==1)		/*按下鼠标会持续一段时间，造成多次错误循环，用此屏蔽*/
					getmousebutton(&mousebutton);
				break;
		}
		oldx=x;
		oldy=y;
	}
	myMouse(oldx,oldy);
}


void MakeLine(int a[][2],int N)    /*画三次B样条曲线*/
{
	float a0,a1,a2,a3,b0,b1,b2,b3;
	int  fx,fy,k;
	float  i,t,dt,dis=0,diy=0;
	int preColor;
	dt=1/(float)N;
	   
	preColor=getcolor();
	if(((preColor+1)%16)!=0)		/*avoid to choose black that is my background*/
		setcolor(preColor+1); 		/*change to another color*/
	else
		setcolor(preColor-1);

	for(k=0;k<N-3;k++)                   /*画三次B样条曲线*/
	{
		 a0=(a[k][0]+4*a[k+1][0]+a[k+2][0])/6;
		 a1=(a[k+2][0]-a[k][0])/2;
		 a2=(a[k][0]-2*a[k+1][0]+a[k+2][0])/2;
		 a3=-(a[k][0]-3*a[k+1][0]+3*a[k+2][0]-a[k+3][0])/6;
		
		b0=(a[k][1]+4*a[k+1][1]+a[k+2][1])/6;
		b1=(a[k+2][1]-a[k][1])/2;
		b2=(a[k][1]-2*a[k+1][1]+a[k+2][1])/2;
		b3=-(a[k][1]-3*a[k+1][1]+3*a[k+2][1]-a[k+3][1])/6;
		for(i=0;i<N;i+=0.1)                 /*逐点画出B样条曲线*/
		{
			t=i*dt;
			fx=a0+a1*t+a2*t*t+a3*t*t*t;
			fy=b0+b1*t+b2*t*t+b3*t*t*t;
			if(i==0.0) 
			{  
				moveto(fx,fy);
				dis=fx;
				diy=fy;
				line(fx,fy,fx,fy);
			} 
			if(fx!=dis&&fy!=diy)
			{
			line(fx,fy,fx,fy);
			dis=fx;
			}
		}
	}
	setcolor(preColor);
}

void DisplayArray(int a[][2],int n)    /*将数组里的元素用直线显示出来*/
{
	int i;
	for(i=1;i<n;i++)
	line(a[i-1][0],a[i-1][1],a[i][0],a[i][1]);
}

void BLine()                             /*画三次B样条曲线并实现拉拽功能*/
{
	MLINE *mln;
	int inch=0;
	int n=0,N,j,number;
	int distance=1000,dis=0,diy=0;
	int oldx=320,x=320,oldy=240,y=240;

	int a[20][2]={0};
	int b[20][2]={0};

	showmsg("Now creating B-spline");
	mln=(MLINE *)malloc(sizeof(MLINE ));
	freeline(mln);
	N=mln->count-1;
	for(n=0;n<mln->count;n++)
	{
		a[n][0]=mln->dots[n].x;
		a[n][1]=mln->dots[n].y;
	}
	
	N=n;
	getmousebutton(&inch);
	while(inch==2) /*防止连续按右键而退出程序*/
	{
		delay(50);
		getmousebutton(&inch);
	}

	MakeLine(a,N);   /*画上三次B样条曲线*/
	
	myMouse(x,y);
	while(1)         /*实现拉拽功能*/
	{
		getmousebutton(&inch);
		if(inch==2)   break;   /*按右键退出*/
		while(inch==0)     /*不按键*/
		{
			oldx=x;
			oldy=y;
			getmousexy(&x,&y);
			if(oldx!=x||oldy!=y)
			{
				displayXY(x,y);
				myMouse(oldx,oldy);
				myMouse(x,y);
			}
			getmousebutton(&inch);
		}
		if(inch==1)
		{
			oldx=x;
		        oldy=y;
			getmousexy(&x,&y);
			displayXY(x,y);
			myMouse(oldx,oldy);
			myMouse(x,y);
		        distance=1000;
			for(j=0;j<N;j++)
			{
	                         dis=diy=0;
	                         dis=a[j][0]-x;
	                         diy=a[j][1]-y;
	                         if(dis<0)  dis=0-dis;
	                         if(diy<0)  diy=0-diy;
	                         dis+=diy;
	                         if(dis<distance)   /*判断选中的点*/
	                         {
					distance=dis;
					number=j;
				}
			}
			getmousebutton(&inch);
			while(inch==1)     /*连续按左键*/
			{  
				oldx=x;
				oldy=y;
				getmousexy(&x,&y);
				displayXY(x,y);
				myMouse(oldx,oldy);
				myMouse(x,y);
				
		                for(j=0;j<N+1;j++)   /*将a保存在b中*/
				{
					b[j][0]=a[j][0];
					b[j][1]=a[j][1];
				}
				a[number][0]=x;      /*修改a中相应点的坐标*/
				a[number][1]=y;
		
				DisplayArray(b,N); 
				DisplayArray(a,N); 
				MakeLine(b,N); 
				MakeLine(a,N);
				getmousebutton(&inch);
			}
		}   
	}
	myMouse(x,y);
} 





