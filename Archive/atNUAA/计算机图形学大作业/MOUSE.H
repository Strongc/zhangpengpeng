#include "graphics.h"
#include "dos.h"

void mouse(int *m1,int *m2,int *m3,int *m4)
{
    union REGS inregs,outregs;
    inregs.x.ax=*m1;
    inregs.x.bx=*m2;
    inregs.x.cx=*m3;
    inregs.x.dx=*m4;
    int86(0x33,&inregs,&outregs);
    *m1=outregs.x.ax;
    *m2=outregs.x.bx;
    *m3=outregs.x.cx;
    *m4=outregs.x.dx;
}

void resetmouse(void)
{
    int m1,m2,m3,m4;
    m1=0;
    mouse(&m1,&m2,&m3,&m4);
}

void showmouse(void)
{
    int m1,m2,m3,m4;
    m1=1;
    mouse(&m1,&m2,&m3,&m4);
}

void hidemouse(void)
{
    int m1,m2,m3,m4;
    m1=2;
    mouse(&m1,&m2,&m3,&m4);
}

void set_mouse_limit(int x1,int x2,int xy)
{
    int m1,m2,m3,m4;
    if (xy==0) m1=7; else m1=8;
    m3=x1;m4=x2;
    mouse(&m1,&m2,&m3,&m4);
}

void getmousexy(int *x,int *y)
{
    int m1,m2;
    m1=3;
    mouse(&m1,&m2,x,y);
    if(getmaxx()==319) (*x)/=2;
}

void getmousebutton(int *button)
{
    int m1,m3,m4;
    m1=3;
    *button=0;
    mouse(&m1,button,&m3,&m4);
}

void movemouse(int x,int y)
{
    int m1,m2,m3,m4;
    m1=4;m3=x;m4=y;
    if(getmaxx()==319) x*=2;
    mouse(&m1,&m2,&m3,&m4);
}




