//
//  Created by Matteo Minutti on 25/10/2016
//
#include <stdio.h>
#include <stdlib.h>

#define NERO 1

const int MAXR=50;

typedef enum {FALSE, TRUE} bool;

void leggiMatrice(FILE *fp, int M[][MAXR], int MAXR, int *nr, int *nc);
bool riconosciRegione(int M[][MAXR], int nr, int nc, int r, int c, int *b, int *h);

int main(){

    FILE *fp;

    int nr, nc, r, c, b, h, count=0;
    int M[MAXR][MAXR];
    char nomefile[MAXR];
    
    printf("inserire PATH file regioni: \n");
    scanf("\n%s", nomefile);

    if ((fp=fopen(nomefile, "r"))==NULL){
        printf("ERRORE APERTURA FILE!\n");
        return EXIT_FAILURE;
    }
    
//lettura matrice tramite leggiMatrice a cui passo il puntatore a file
    fscanf(fp, "%d%d", &nr, &nc);
    leggiMatrice(fp,M,MAXR,&nr,&nc);
    fclose(fp);

    for (r = 0; r < nr ; r++) {
        for (c = 0; c < nc; c++) {

            if (riconosciRegione(M, nr, nc, r, c, &b, &h) ){
                count++;
                printf("Regione %d: estr. sup. SX = <%d,%d> b = %d, h = %d, Area = %d \n", count, r, c, b, h, (b)*(h) );
            }
        }
    }

    return EXIT_SUCCESS;
}

void leggiMatrice(FILE *fp, int M[][MAXR], int MAXR, int *nr , int *nc){

    for (int i = 0; i < *nr; i++) {
        for (int j = 0; j < *nc ; j++) {
            fscanf(fp,"%d",&M[i][j]);
        }
    }
    return;
}

bool riconosciRegione(int M[][MAXR], int nr, int nc, int r, int c, int *b, int *h) {

    int flagc = 0, flagr = 0, flagq = 0, flagp=0;
    int counter = 0, contacolonne = 0, contarighe = 0;

    if (((M[r - 1][c]) != NERO) && (M[r][c - 1] != NERO) && (M[r][c] == NERO)) {

                //imposto i flag a seconda della situazione per il calcolo area
                if ((M[r + 1][c] == NERO) && (M[r][c + 1] != NERO))
                    flagc = 1;

                if ((M[r][c + 1] == NERO) && (M[r + 1][c] != NERO))
                    flagr = 1;

                if ((M[r + 1][c]) && (M[r][c + 1]) == NERO)
                    flagq = 1;

                if ((M[r][c] == NERO) && 
                    (M[r + 1][c] != NERO) && (M[r][c + 1] != NERO) && 
                    (M[r - 1][c] != NERO) && (M[r][c - 1] != NERO))
                    flagp = 1;

                //caso 1 verticale
                if (flagc == 1) {
                    for (int i = r; i <= nr; i++) {
                        if (M[i][c] == NERO)
                            counter++;
                    }
                    *h = counter;
                    *b = 1;
                }

                //caso 2 orizzontale
                if (flagr == 1) {
                    for (int i = c; i <= nc; i++) {
                        if (M[r][i] == NERO)
                            counter++;
                    }
                    *b = counter;
                    *h = 1;
                }

                //caso 3 quadrato
                if (flagq == 1) {
                    for (int i = r; i < nr; i++) {
                        for (int j = c; j < nc; j++) {
                            if (M[i][j] == NERO)
                                contarighe++;
                        }
                        contacolonne++;
                    }
                    
                    contarighe /= contacolonne;
                    contacolonne /= contarighe;
                    *b = contacolonne;
                    *h = contarighe;
                }

                //caso 4 puntuale
                if (flagp==1){
                    *b=1;
                    *h=1;
                }

        return TRUE;
        }
    else return FALSE;
}