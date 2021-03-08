//
//	created by Matteo Minutti on 28/10/2016
//
#include <stdio.h>
#include <stdlib.h>

const int MAXR=50;

typedef enum {FALSE, TRUE} bool;

bool verificaCammino(int M[][MAXR], int nr, int nc, int *p);

void leggiMatrice(FILE *fp, int M[][MAXR], int MAXR, int *nr, int *nc);

int main()	{

	FILE *fp;

	int nc, nr, p = 0;
	int M[MAXR][MAXR];
	char nomefile[MAXR];

	printf("inserisci PATH file matrice\n");
	scanf("\n%s", nomefile);

	if ((fp=fopen(nomefile,"r"))==NULL)
	{
		printf("errore apertura file! \n");
		exit(-1);
	}

	fscanf(fp,"%d%d", &nr, &nc);
	leggiMatrice(fp,M,MAXR,&nr,&nc);

	if (verificaCammino(M,nr,nc,&p)){
		printf("\nil cammino è corretto, costa %d ed è semplice\n", p);
	}

	else{
		printf("\nil cammino NON è corretto!\n");
	}

	return 0;
	
}

void leggiMatrice(FILE *fp, int M[][MAXR], int MAXR, int *nr, int *nc){

	for (int i = 0; i < *nr; i++)
	{
		for (int j = 0; j < *nc; j++)
		{
			fscanf(fp,"%d", &M[i][j]);
		}
	}	return;
}

bool verificaCammino(int M[][MAXR], int nr, int nc, int *p){

bool ciclo = TRUE;
bool semplice = TRUE;
int c1 = 0, c2 = 0;
int c1prec, c2prec;

printf("inserisci il cammino\n");

while (ciclo){

	c1prec = c1;
	c2prec = c2;

	scanf("\n%d%d", &c1, &c2);
	if ( (c1 == -1) && (c2==-1) )
	{
		ciclo=FALSE;
		break;
	}

	if ( (c1 > nr) || (c2 > nc) )
	{
		printf("inserire dati appartenenti al cammino (compresi tra [%d]x[%d]\n", nr, nc);
		continue;
	}

	if ((c1prec+1 == c1) || (c2prec+1 == c2) || (c1prec-1 == c1) || (c2prec-1 == c2) || ((c1prec==0) && (c2prec==0)) )
	{
		*p += M[c1][c2];
	}

	if ( (c1-c1prec > 1) || (c2-c2prec > 1) || (c1-c1prec < -1) || (c2-c2prec < -1) )
	{
		semplice = FALSE;
	}
	
	if ( M[c1][c2] == 0 )
	{
		semplice = FALSE;
	} 
}

	if (semplice == TRUE)
		return TRUE;
	else return FALSE;

}