#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#define sst "H:\\BGI"
void main()
{
    int gd = DETECT,gm,left=100,top=100,right=200,bottom=200,x= 300,y=150,radius=50;
    int i;
    char cont='y';
    do
    {
    	initgraph(&gd,&gm,sst);
    	setcolor(0x1);
    	/*rectangle(left,top,right,bottom);
    	circle(left+45,top+34,90);*/
    	arc(left,top,270,180,90);
    	outtextxy(left + 2, top + 34, "C SDL");
    	outtextxy(left + 2, top + 99, "Salir?");
        cont=getch();
        closegraph();
	//printf("%c",cont);
    } while(cont == 'y');
    printf("DETECT: 0x%x\n",&gd);
}
