//
//  Created by Matteo Minutti on 23/10/2016
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 20

void sommaMatrice(int M[][N], int MS[][N], int nr, int nc, int R);

int main() {

    FILE *fp;

    char nomefile_in[70];

    int M[N][N], M2[N][N];
    int R;
    int nc, nr;

    printf("inserisci nome file\n");
    scanf("%s", nomefile_in);

    if ((fp=fopen(nomefile_in, "r"))==NULL)
        printf("ERRORE\n");

    fscanf(fp,"%d%d", &nr, &nc);

//creaMatrice
    for (int i = 0; i < nr ; i++) {
        for (int j = 0; j < nc ; j++) {
            fscanf(fp,"%d", &M[i][j]);
        }
    }

//creaMatriceSomma
    for (int i = 0; i < nr ; i++) {
        for (int j = 0; j < nc ; j++) {
            M2[i][j] = 0;
        }
    }

    printf("inserire il raggio:\n");
    scanf("%d", &R);

    if(R > nc || R > nr || R <= 0) {
        printf("Si scelga un raggio opportuno alle dimensioni della matrice [%d]x[%d]!\n", nr, nc);
        exit(-1);
    }

    fclose(fp);

    sommaMatrice(M,M2,nr,nc,R);

    printf("\n%d %d\n",nr,nc);
    for (int i = 0; i < nr ; i++) {
        for (int j = 0; j < nc ; j++) {
            printf("%d ", M2[i][j]);
        }printf("\n");
    }

    return 0;


}

void sommaMatrice(int M[][N], int M2[][N], int nr, int nc, int R){


int i, j, k, l, somma;

    for (i = 0; i < nr ; i++) {
        for ( j = 0; j < nc; j++) {

            somma=0;

            //per procedere al calcolo scorro la matrice come nell'esercizio 2 del lab1,
            //ovvero tramite il metodo delle cornici concentriche, intorno alla posizione [i][j]
            //in un'altra sottomatrice

            k=i-R;
            for (l=j-R; l < j+R; l++) {
                if ((k >= 0) && (l>=0) && (l<nc) )
                    somma += M[k][l];
            }

            l=j-R;
            for (k = i-R+1; k < i+R; k++) {
                if ( (l>=0) && (k>=0) && (k<nr) )
                    somma += M[k][l];
            }

            k=i+R;
            for (l = j+R; l >= j-R ; l--) {
                if ( (k>=0) && (l>=0) && (l < nc) && (k < nr) )
                    somma += M[k][l];
            }

            l=j+R;
            for (k = i+R-1; k >= i-R ; k--) {
                if ( (l>=0) && (k>=0) && (l<nc) && (k<nr) )
                    somma += M[k][l];
            }
            M2[i][j] = somma;
        }
    }

    return;

}

