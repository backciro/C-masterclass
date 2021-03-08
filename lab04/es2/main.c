//
//	created by Matteo Minutti on 1/11/2016
//
#include <stdio.h>
#include <stdlib.h>

int **malloc2dR(int nr, int nc);

int **calloc2dR(int *dim, int maxD);

void riempiMatrice(FILE *fp, int **matr, int nr, int nc);

void creaDim(int *dim, int nr, int nc, int maxD);

void creaDiag(int **diag, int **matr, int *dim, int maxD, int nr, int nc, int i);

void creaAnti(int **anti, int **matr, int *dim, int maxD, int nr, int nc, int i);

void stampaDiag(int **diag, int *dim, int maxD);

void stampaAnti(int **anti, int *dim, int maxD);

int main()
{

	FILE *fp = fopen("./mat.txt", "r");
	
	int **matr;				//matrice
	int **diag, **anti;		//matrici delle diagonali
	int *dim;				//vettore dimensioni delle diagonali

	int nr, nc, maxD;


	fscanf(fp, "%d%d", &nr, &nc);
	maxD = (nr +nc) -1;

	matr = malloc2dR(nr, nc);
	riempiMatrice(fp, matr, nr, nc);

	dim = calloc(maxD, sizeof(int));
	creaDim(dim, nr, nc, maxD);

	diag = calloc2dR(dim, maxD);
	
	for(int i=nc-1; i >= 0; i--)
	creaDiag(diag, matr, dim, maxD, nr, nc, i);
	stampaDiag(diag, dim, maxD);

	anti = calloc2dR(dim, maxD);

	for(int i=0; i < nr; i++)
	creaAnti(anti, matr, dim, maxD, nr, nc, i);
	stampaAnti(anti, dim, maxD);

}

int **malloc2dR(int nr, int nc)
{
	int **m;

	m = malloc( nr * sizeof(*m) );

	for (int i = 0; i < nr; i++)
	{
		m[i] = malloc (nc * sizeof (*m) );
	}

	return m;
}

void riempiMatrice(FILE *fp, int **matr, int nr, int nc)
{
	for (int i = 0; i < nr; i++)
	{
		for (int j = 0; j < nc; j++)
		{
			fscanf(fp, "%d", &matr[i][j]);
		}
	}
}

void creaDim(int *dim, int nr, int nc, int maxD)
{
	int res, i, j, k;

	k=0;
	while (k<maxD)
	{
		for (i = (nc)-1; i >= 0; i--)
		{
			res = nc - i;

			if (res >= nr)
			res = nr;

		dim[k++] = res;
			
			if (i == 0)
			{
				for (j = i+1; j < (nr); j++)
				{
					res = nr - j;
						
					if (res < 1)
					res = 1;

		dim[k++] = res;

				}
			}
		}
	}
}

int **calloc2dR(int *dim, int maxD)
{
	int **d, j=0;

	d = calloc(maxD, sizeof(*d)); 

	for (int i = 0; i < maxD; i++)
	{
		d[i] = calloc(dim[j++] , sizeof(*d));
	}
	return d;
}

void creaDiag(int **diag, int **matr, int *dim, int maxD, int nr, int nc, int i)
{
	int count;
	int riga = 0;
	int pos_i = i;
	int support;
	int aux = 0;

	count = nc - i;

	for (int j = 0; j < count; j++)
	{
		if ( (riga >= nr) || (i >= nc) ) 
			continue;
			
			diag[count-1][j] = matr[riga++][i++];
	}
	
	if (pos_i == 0)
	{
		i = support = 1;
		for(int j = count; j < maxD; j++)
		{
			pos_i = 0;			
			
			for (int k = 0; k < dim[count]; k++)
			{
				
				if ( (i >= nr) || (pos_i >= nc) ) 
					continue;

				diag[j][k] = matr[i++][pos_i++];
				aux++;
			}	i = ++support;
		}
	}
}

void creaAnti(int **anti, int **matr, int *dim, int maxD, int nr, int nc, int i)
{
	int count;
	int col = 0;
	int pos_i = i;
	int support;

	count = pos_i+1;

	for (int j = 0; j < dim[count-1]; j++)
	{
		if ( (col >= nc) || (i >= nr) ) 
			continue;
			
			anti[count-1][j] = matr[i--][col++];
	}

	if (pos_i == nr-1)
	{
		i = 1;
		support = 1;
		
		for(int j = count; j < maxD; j++)
		{
			pos_i = nr-1;			

			for (int k = 0; k < dim[count]; k++)
			{	
				if ( (i > nc) || (pos_i < 0) ) 
					continue;

				anti[j][k] = matr[pos_i--][i++];

			}	i = ++support;
		}
	}
}

void stampaDiag(int **diag, int *dim, int maxD)
{
	int count=0;

	printf("\n");
	printf("DIAGONALI:\n");
	for (int i=0; i < maxD; i++)
		{
			count++;
			for (int j = 0; j < dim[i]; j++)
			{
				printf("%d ", diag[i][j]);
			} printf("\n");
		}printf("\n");
}

void stampaAnti(int **anti, int *dim, int maxD)
{
	int count=0;

	printf("ANTIDIAGONALI:\n");
	for (int i=0; i < maxD; i++)
		{
			count++;
			for (int j = 0; j < dim[i]; j++)
			{
				printf("%d ", anti[i][j]);
			} printf("\n");
		}printf("\n");
}