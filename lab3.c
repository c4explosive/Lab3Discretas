#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <string.h>
#include <math.h>
#define sst "H:\\BGI"
#define TAM 20 //Se puede optimizar, TODO: cambiar por tamaño no fijo (REAL).
typedef struct cj {
    int * X;
    int * Xc;
} conj;
////////////F(x) Principales/////////  
void graphic(int *, int *,conj * A);
void printj(conj * Y);
conj * cconj(conj * Z);
int ** nrel(conj *,conj *);
void matrel();
void pcar(conj * Y,conj * Z);
//////////F(x) Auxiliares/////////////////
char * intostr(int);
void triangle(int, int);
conj * iconj();
/////////////////////////////////////////
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
    nrel(A,B);
    getch();
    graphic(&gd,&gm,A);
}
////////////////////////////GRAPHIC MODE////////////////////////////////////////
void graphic(int *gd, int *gm,conj * A)
{
    int left=100,top=100,right=200,bottom=200,x= 300,y=150,radius=50;
    int i,k=0;
    int Xpos[2][7]={{23,45,67,90,178,152,255},
		    {45,140,89,38,17,142,105}};
    char cont='y';
    do
    {
    	initgraph(gd,gm,sst);
    	setcolor(0x1);
	for (i=0;i<TAM;i++)
	{
	    if(A->Xc[i])
	    {
    	    	outtextxy(left + Xpos[0][k], top + Xpos[1][k], intostr(A->X[i]));
	    	k++;
	    }
		
	}
	for (i=0;i<7;i++)
	{
	    if(i==6)
	    	break;
	    else
	    {
    		setcolor(0x1);
	    	line(left+Xpos[0][i]-5,top+ Xpos[1][i]+2,left+Xpos[0][i+1]-5,top+ Xpos[1][i+1]+2);
    		setcolor(0x4);
		triangle(left+Xpos[0][i+1],top+ Xpos[1][i+1]);
	    }	
	}
        cont=getch();
        closegraph();
    } while(cont == 'y');
    //printf("DETECT: 0x%x\n",&gd);
}

void triangle(int xalpha, int yalpha)
{
    int i,j=0;
    moveto(xalpha-=5,yalpha+=2);
    for(i=0;i<5;i++)
    {
    	moveto(xalpha+0,yalpha+0);
    	linerel(i,i/0.577); //Para ángulo de 30º se divide entre 0.577 la pendiente.
    	linerel(i,-i/0.577);
    	linerel(-i*2,0);
    }
}
//////////////////Un intento de itoa//////////////////////////
char * intostr(int x)
{
    char * buffer=malloc(sizeof(char));
    sprintf(buffer,"%d",x);
    return buffer;
}
///////////////////Imprimir Conjuntos//////////////////////////////
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
/////////////////////Producto Cartesiano//////////////////////////////////
void pcar(conj * Y,conj * Z)
{
    int i, j;
    printf("{");
    for(i=0;i<TAM;i++)
    {
	//printf("DEBUG: (%d) -> POS: %d\n",Y->X[i],i);
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
/////////////////////////Condición para Relación//////////////////////////
int ** nrel(conj *Y,conj *Z)
{
    int i,j,k=0;
    int **pares=malloc(sizeof(int*));
    for(k=0;k<2;k++)
	pares[k]=malloc(49*sizeof(int));
    for(i=0;i<2;i++)
    {
	for(j=0;j<k;j++)
	{
	    printf("%d ",pares[i][j]);
	}
	printf("\n");
    }

}
///////////////////////////////Cargar Conjunto/////////////////////////////
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
//////////////////////////////Crear Conjuntos////////////////////////////////
conj * iconj()
{
    conj * ccj=malloc(sizeof(conj));
    ccj->X=malloc(TAM*sizeof(int));
    ccj->Xc=malloc(TAM*sizeof(int));
    return ccj;
}
/////////////////////////////////////////////////////////////////////////////
