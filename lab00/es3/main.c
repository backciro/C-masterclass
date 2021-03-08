#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXCAR 100
#define N 10

float trovapotenza(float base);

int main() {

    FILE *fpin;
    FILE *fpout;
    char nomefilein[MAXCAR];
    char nomefileout[MAXCAR];
    int dim, i, j;
    float ncurr;

    float mat[N][N];

    printf("\n Inserisci il nome del file input cazzo: ");
    scanf("%s", nomefilein);

    if ((fpin=fopen(nomefilein, "r"))==NULL)
        printf("Errore apertura file input!\n");

    printf("\n Inserisci il nome del file output 1: ");
    scanf("%s", nomefileout);


    if ((fpin = fopen(nomefilein, "r" )) == NULL)
        printf("Errore apertura file matrice!\n");

    if ((fpout = fopen(nomefileout, "w" )) == NULL)
        printf("Errore apertura file matrice finale!\n");

    if ((fscanf(fpin, "%d", &dim))!=1)
        printf("Errore lettura dimensione file!/n");

    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            while(fscanf(fpin, "%f", &ncurr)){
                if (ncurr<=0)
                    mat[i][j] = 0;

                else {
                    mat[i][j] = powf(10, trovapotenza(ncurr));
                }
            }

    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)

            printf("%f", mat[i][j]);

        fclose(fpin);
        fclose(fpout);

}


float trovapotenza(float base){

    float i=base, count=-1;

    while(i > 1) {
        i = base / 10;
        count++;
    }

    return count;
}
