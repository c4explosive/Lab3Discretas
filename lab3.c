#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <graphics.h>
#define sst "H:\\BGI"
#define TAM 100
typedef struct cj {
    int * X;
    int * Xc;
} conj;  
void graphic(int *, int *);
void printj(conj * Y);
conj * cconj(conj * Z);
void pcar(conj * Y,conj * Z);
void nrel();
void matrel();
conj * iconj();
void main()
{
    int gd = DETECT,gm,i;
    conj* A=iconj();
    conj* B=iconj();
    A=cconj(A);
    B=A;
    //printf("N: %d\n",A->X[0]);
    printj(A);
    printj(B);
    pcar(A,B);
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
    //printf("DETECT: 0x%x\n",&gd);
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
void pcar(conj * Y,conj * Z)
{
    int i, j;
    printf("{");
    for(i=0;i<TAM;i++)
    {
	
	if(Y->Xc[i])
	{
	    //printf("%d\n",Y->X[i]);
	    for(j=0;j<TAM;j++)
	     {
		if(Z->Xc[j])
		{
		    printf("(%d,%d),",Y->X[i],Z->X[j]);
		}
	     }
	}
    } 
    printf("\b}\n");
}
conj * cconj(conj * Z)
{
    int i;
    for (i=0;i<TAM;i++)
    {
	if (i == 16)
	    break;
	if (i == 0)
	    continue;
	if(i%2==0)
	{
	    Z->X[i]=i;
	    Z->Xc[i]=1;
	}
    }
    return Z;
}
conj * iconj()
{
    conj * ccj=malloc(sizeof(conj));
    ccj->X=malloc(TAM*sizeof(int));
    ccj->Xc=malloc(TAM*sizeof(int));
    return ccj;
}

