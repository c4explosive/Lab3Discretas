#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <string.h>
#include <math.h>
#define sst "H:\\BGI"
#define clrscr() system("clear")
#define TAM 20 //Se puede optimizar, TODO: cambiar por tamaño no fijo (REAL).
typedef struct cj
{
    int * X;
    int * Xc;
} conj;
////////////F(x) Principales/////////
void graphic(int *, int *,conj *,conj *);
void printj(conj * Y);
conj * cconj(conj * Z);
int ** nrel(conj *,conj *,int);
void matrel();
void pcar(conj * Y,conj * Z);
void presentacion();
//////////F(x) Auxiliares/////////////////
char * intostr(int);
void triangle(int, int, int);
void pbiarray(int **, int k);
conj * iconj();
/////////////////////////////////////////
void main()
{
    int gd = DETECT,gm,i, ch, cch;
    conj* A=iconj();
    conj* B=iconj();
A=cconj(A);
		B=A;
    clrscr();
    do
    {
    printf("1. Presentacion\n");
    printf("2. Los elementos del conjunto A o B\n");
    printf("3. El producto cartesiano\n");
    printf("4. El conjunto relación (R)\n");
    printf("5. La matriz de adyacencia de la relación\n");
    printf("6. El dígrafo de la relación\n");
    printf("7. Salir\n");
    printf("Eliga una de las opciones presentadas.\n");
    scanf("%d", &ch);
    switch(ch)
    {
	case 1: presentacion();
		break;
	case 2: 
		printf("Que conjunto desea imprimir?\n1. A\n2. B\n");
		scanf("%d", &cch);
		if(cch==1){
			printf("A=");printj(A);
		} else if(cch==2){
			printf("B=");printj(B);
		}
		break;
	case 3: printf("Producto Cartesiano\n");
		pcar(A,B);
		break;
	case 4: printf("Conjunto de Relación\n");
		nrel(A,B,1);
		break;
	case 5: printf("Matriz relacion\n");
		matrel(A, B);
		break;
	case 6: graphic(&gd,&gm,A,B);
		break;
	case 7: printf("Gracias!");
		break;
	default: printf("Eliga de las opciones predeterminadas.\n");
    }
    }while (ch!=7);
    //printf("N: %d\n",A->X[0]);
    getch();
}
////////////////////////////GRAPHIC MODE////////////////////////////////////////
void graphic(int *gd, int *gm,conj * A,conj * B)
{
    int left=100,top=100,right=200,bottom=200;
    //x= 300,y=150,radius=50;
    int i,j,k=0,l=0,p1,p2;
    int Xpos[2][8]={{3,45,135,90,178,152,255,300},
		    {45,140,97,38,17,142,105,200}};
    int** Pos=malloc(sizeof(int*));
    int ** rel=nrel(A,B,0);
    char cont='y';
    for(i=0;i<2;i++)
	Pos[i]=malloc(7*sizeof(int));
    for(k=0;k<TAM;k++)
    {
	if(A->Xc[k])
	{
	    Pos[0][l]=k;
	    Pos[1][l]=l;
	    l++;
	}
    }
    //pbiarray(rel,rel[0][0]);
    //pbiarray(Pos,l);
    k=0;
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
	l=k=0;
	l++;
	for (i=1;i<rel[0][0];i++)
	{
	    for (j=0;j<8;j++)
	    {
		if( rel[0][i] == Pos[0][j])
		{
		    p1=Pos[1][j];
		}
		if( rel[1][i] == Pos[0][j])
		{
		    p2=Pos[1][j];
		}

	    }
	    //printf("n: %d->%d\n",Xpos[0][p1],Xpos[0][p2]);
	    if (!(rel[0][i]==rel[1][i]))
	    {
		setcolor(l);
		line(left+Xpos[0][p1]-5,top+ Xpos[1][p1]+2,left+Xpos[0][p2]-5,top+ Xpos[1][p2]+2);
		if(l!=10)
		    l++;
		else
		    l=1;
		setcolor(0xE);
		triangle(left+Xpos[0][p2]-5,top+ Xpos[1][p2],0);
	    }
	    else
	    {
		setcolor(l);
		circle(left+Xpos[0][p1]+5,top+Xpos[1][p1]+5,20);
		if(l!=10)
		    l++;
		else
		    l=1;
	    }

	}
	for (i=0;i<TAM;i++)
	{
	    if(A->Xc[i])
	    {
		outtextxy(left + Xpos[0][k], top + Xpos[1][k], intostr(A->X[i]));
		k++;
	    }

	}
	cont=getch();
	closegraph();
    } while(cont == 'y');
    //printf("DETECT: 0x%x\n",&gd);
}

void triangle(int xalpha, int yalpha,int mode)
{
    int i,j=0;
    moveto(xalpha-=5,yalpha+=2);
    for(i=0;i<5;i++)
    {
	moveto(xalpha+0,yalpha+0);
	linerel(i/0.577,i); //Para ángulo de 30º se divide entre 0.577 para  la pendiente.
	linerel(-i/0.577,i);
	linerel(0,-i*2);
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
    printf("AxB={");
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
int ** nrel(conj *Y,conj *Z,int s)
{
    int i,j,k=0;
    int **pares=malloc(sizeof(int*));
    for(k=0;k<2;k++)
	pares[k]=malloc(49*sizeof(int));
    k=1;
    if(s)
	printf("R={");
    for(i=0;i<TAM;i++)
    {
	if (Y->Xc[i])
	{
	    for(j=0;j<TAM;j++)
	    {
		if(Z->Xc[j])
		{
		    //if((Y->X[i]*Z->X[j])<(pow(Y->X[i],2)))
		    if(Y->X[i]%Z->X[j]==0)
		    //if(Y->X[i]==Z->X[j]-2)
		    {
			if(s)
			    printf("(%d,%d),",Y->X[i],Z->X[j]); //TODO: ¿puede ser independiente o depende del producto cartesiano?
			pares[0][k]=i;
			pares[1][k]=j;
			k++;
		    }
		}
	    }
	}
    }
    if(s)
	printf("\b}\n");
    /*k++;
    k--;*/
    pares[0][0]=k;
    pares[1][0]=k;
    k--;
    //pares[0][k]=1000;
    //pares[1][k]=1000;
    return pares;
}

void pbiarray(int ** biarray, int k)
{
    int j,i;
    printf("ARRAY: \n");
    for(i=0;i<2;i++)
    {
	for(j=0;j<k;j++)
	{
	    printf("%d\t",biarray[i][j]);
	}
	printf("\n");
    }
}
///////////////////////////////Cargar Conjunto/////////////////////////////
conj * cconj(conj * Z) //¿Se puede cargar directamente?
{
    int i=0,k=1;
    for (k=0;k<TAM;k++)
    {
	if (k == 16)
	    break;
	if (k == 0)
	    continue;
	if(k%2==0)
	{
	    Z->X[i]=k;
	    Z->Xc[i]=1;
	    i++;
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
void matrel()
{
	int i, j, a=0, b=0;
	int mat[8][8]={{0,2,4,6,8,10,12,14},{2,1,0,0,0,0,0,0},{4,1,1,0,0,0,0,0},{6,1,0,1,0,0,0,0}
			,{8,1,1,0,1,0,0,0},{10,1,0,0,0,1,0,0},{12,1,1,1,0,0,1,1},{14,1,0,0,0,0,0,1}};


for(i=0; i<8; i++)
  {
      for(j=0; j<8; j++)
      {
	 printf("%4d", mat[i][j]);
      }
      printf("\n");
  }
  }
/////////////////////////////////////////////////////////////////////////////
void presentacion ()
{
    printf("\t\t\tUNIVERSIDAD TECNOLOGICA DE PANAMA\n");
    printf("\t\tFACULTAD DE INGENIERÍA DE SISTEMAS COMPUTACIONALES\n");
      printf("\t\tDEPARTAMENTO DE COMPUTACIÓN Y SIMULACIÓN DE SISTEMAS\n\n");
    printf("\t\t\t\t  LABORATORIO N_3\n");
	  printf("\t\t\t\tRELACIONES Y DIGRAFO\n\n");
    printf("\t\t\t\tMaria T. Rodriguez\n");
      printf("\t\t\t\t Angel Espinosa\n\n");
    printf("\t\t\tPROFESORA: Ing. Jacqueline S. de Ching\n\n");
      printf("\t\t\t\t GRUPO: 1-IL-121\n\n");
    printf("\t\t\t\t       2015\n");
}
