#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#define sst "H:\\BGI"
#define TAM 10
typedef struct cj {
    int * X;
    int * Xc;
} conj;
void graphic(int *, int *);
void printj(conj * Y);
conj * cconj(conj * Z);
void pcar(int * cj1, int * cjc1, int * cj2, int * cjc2 );
void nrel();
void matrel();
conj * iconj();
void main()
{
    int gd = DETECT,gm,i;
    conj* A=iconj();
    conj* B=iconj();
    A=cconj(A);
    printf("N: %d\n",A->X[0]);
    //printj(A);
    //graphic(&gd,&gm);
}

void graphic(int * gd, int * gm)
{
    int left=100,top=100,right=200,bottom=200,x= 300,y=150,radius=50;
    int i;
    char cont='y';
    do
    {
    	initgraph(gd,gm,sst);
    	setcolor(0x1);
    	outtextxy(left + 2, top + 34, "C SDL");
    	outtextxy(left + 2, top + 99, "Salir?");
        cont=getch();
        closegraph();
    } while(cont == 'y');
    printf("DETECT: 0x%x\n",&gd);
}

void printj(conj * Y)
{
    int i; int vac=1;
    printf("{");
    for (i=0;i<TAM;i++)
    {
	if(Y->Xc[i])
	{
	    printf("%d,",Y->X[i]);
	    vac=0;
	}
    }
    if (vac)	
	printf("}\n");
    else
    	printf("\b}\n");
}
void pcar(int * cj1, int * cjc1, int * cj2, int * cjc2 )
{
    int i, j;
    
}
conj * cconj(conj * Z)
{
    int i;
    for (i=0;i<16;i++)
    {
	/*if(i%2==0)
	{*/
	    Z->X[i]=i+2;
	    Z->Xc[i]=1;
	//}
    }
    return Z;
}
conj * iconj()
{
    conj * ccj=malloc(sizeof(conj));
    ccj->X=malloc(TAM*sizeof(int));
    ccj->Xc=malloc(TAM*sizeof(int));
    *ccj->Xc=0;
    return ccj;
}

