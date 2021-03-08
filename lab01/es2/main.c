//
// Created by Matteo Minutti on 08/10/16.
//

#include <stdio.h>

#define MAXF 50
#define MAXN 20

void riempimatrice(int mat[MAXN][MAXN], int dim, FILE *fp);

void stampariga1(int mat[MAXN][MAXN], int dim, int N);
void stampacolonna1(int mat[MAXN][MAXN], int dim, int N);
void stampariga2(int mat[MAXN][MAXN], int dim, int N);
void stampacolonna2(int mat[MAXN][MAXN], int dim, int N);

typedef enum {FALSE, TRUE} bool;

int main(){

    FILE *fp;

    int matrice[MAXN][MAXN];

//int i,j;
    int dim;
    int numiter;
    int N;
    int cellacen=-1;

    char nomefile[MAXF+1];

    bool pari;

    printf("Inserisci il nome del file: \n");
    scanf("%s", nomefile);

    if ((fp=fopen(nomefile, "r"))==NULL) {
        printf("Errore apertura file!");
        return (-1);
    }

//inizio cattura dei dati! non separare fscanf dalle funzioni sottostanti;
    fscanf(fp,"%d", &dim);

//richiamo la funzione riempimatrice e memorizza la matrice come base dati e chiudo il file!
    riempimatrice(matrice, dim, fp);
    fclose(fp);

//ricordandosi sia il troncamento degli interi dispari, sia che l'indice degli array parte da 0:
    if ( (dim % 2) != 0 ) {
        pari = FALSE;
        cellacen = matrice[(dim / 2)][(dim / 2)];
    }
    else
        pari=TRUE;

//calcolo numero di iterazioni in relazione alla dimensione (dove 4 è il numero di lati di una matrice,
//quindi i passaggi per un iterazione ciclica completa
    if (pari)
        numiter = (dim*2) / 4;
    else
        numiter = ((dim*2)-2) / 4;

    N = dim; //passaggio chiave per la soluzione!

    while(numiter > 0){

        stampariga1(matrice, dim, N);
        stampacolonna1(matrice, dim, N);
        stampariga2(matrice, dim, N);
        stampacolonna2(matrice, dim, N);

        numiter--;  //decremento per usire dal ciclo sul numero di iterazioni restanti da fare in base a 'dim'.
        dim--;      //decremento per restringere pian piano la matrice.
    }

    if (!pari)
        printf("%d", cellacen);

return 0;

}

void riempimatrice (int matrice[MAXN][MAXN], int dim, FILE *fp){

    int i,j;

    for(i = 0; i < dim; i++)
        for(j = 0; j < dim; j++){
            fscanf(fp, "%d" , &matrice[i][j]);
        }
}

void stampariga1(int mat[MAXN][MAXN], int dim, int N) {

    int i, j;

        j = N - dim;
        for(i = N - dim; i < dim;i++) {
            printf("%d ", mat[j][i]);
    }
}

void stampacolonna1(int mat[MAXN][MAXN], int dim, int N) {

    int i, j;

    i = dim - 1;
    for (j = N - dim +1 ; j < dim; j++){
            printf("%d ", mat[j][i]);
    }
}

void stampariga2(int mat[MAXN][MAXN], int dim, int N) {

    int i, j;

    j = dim - 1;
    for (i = dim - 2; i >= N-dim; i--){
        printf("%d ", mat[j][i]);
    }
}

void stampacolonna2(int mat[MAXN][MAXN], int dim, int N) {

    int i, j;

    i = N - dim;
    for (j = dim-2 ;j>N-dim; j--){
        printf("%d ", mat[j][i]);
    }
}