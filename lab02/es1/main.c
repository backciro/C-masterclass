//
// // created by Matteo Minutti on 12/10/16
//

#include <stdio.h>
#include <string.h>

const int N=10;
typedef enum {FALSE, TRUE} bool;

//void ruotaVettore(int V[], int dir, int N, int P);

void CopyVett(int V[], int V2[], int N);
int direzionale(char direz[N]);
char scegliVerso(char selettore[N]);

void ruotaMatrice(int M[][N], char r_o_c, int target, int dim1, int dim2, int P, int dir);
void riempiMatrice (int M[][N], int dim1, int dim2);
void stampaMatrice (int M[][N], int dim1, int dim2);

int main (){

    //int V[N]={1,2,3,4,5,6,7,8,9,10};
    int P, dir;
    int dim1, dim2, target;
    char direz[N], selettore[N], r_o_c;
    int M[N][N];
    bool ciclo=TRUE;

/*
    printf("numero spostamenti / 1 per andare a destra || 0 per andare a sinistra");
    scanf("%d %d", &P, &dir);

    ruotaVettore(V,dir,N,P);

    for (int i=0; i<N; i++)
        printf("%d ",V[i]);
*/

    printf("quanto la vuoi grande? [R]x[C] (MAX NxN)\n");
    scanf("\n%d%d", &dim1, &dim2);

    riempiMatrice(M, dim1, dim2);

    stampaMatrice(M,dim1,dim2);

    do{

    printf("inserire dati nel formato:\n"
                   "<'RIGA' / 'COLONNA' / 'BASTA COSI'> <TARGET> <NR SPOSTAMENTI> <DIREZIONE>\n");
    scanf("\n%s%d%d%s", selettore, &target, &P, direz);

    if ((strcmp(selettore,"riga\0")) && (strcmp(selettore,"colonna\0"))!= 0) {

        printf("\nP R O G R A M M A  T E R M I N A T O\n");
        ciclo = FALSE;

    }

    r_o_c = scegliVerso(selettore);

    target--;

    dir = direzionale(direz);

    ruotaMatrice(M, r_o_c, target, dim1, dim2, P, dir);

    stampaMatrice(M,dim1,dim2);

    } while (ciclo);

    return 0;
}

/*
void ruotaVettore(int V[], int dir, int N, int P) {

    int VCopy[N];
    CopyVett(V, VCopy, N);

    if (dir == 0) { //sx

        for (int i = 0, j = P; i < N - P; i++) {
            V[i] = VCopy[j];
            j++;
        }

        for (int i = N - P, j = 0; i < N; ++i) {
            V[i] = VCopy[j];
            j++;
        }
    }

        if (dir == 1) { //dx

            for (int i = 0, j=P; i < N - P; i++) {
                V[j] = VCopy[i];
                j++;
            }

            for (int i = N-P, j=0; i < N ; ++i) {
                V[j] = VCopy[i];
                j++;
            }

    }
}
*/

void CopyVett(int V[], int VCopy[], int dim){

    for (int i = 0; i < dim; i++) {
        VCopy[i]=V[i];
    }
}

int direzionale(char direz[N]){

    if ((strcmp(direz, "destra\0"))==0)
        return 1;
    if ((strcmp(direz, "sinistra\0"))==0)
        return 0;
    if ((strcmp(direz, "su\0"))==0)
        return 0;
    if ((strcmp(direz, "giu\0"))==0)
        return 1;

    else return -1;

}

char scegliVerso(char selettore[N]){

    if ((strcmp(selettore,"riga\0"))==0)
        return 'r';

    if ((strcmp(selettore,"colonna\0"))==0)
        return 'c';

    else return -1;
}

void riempiMatrice (int M[][N], int dim1, int dim2){
    int count = 0;

    for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim2; j++) {
            M[i][j] = ++count;
        }
    }
}

void ruotaMatrice(int M[][N], char r_o_c, int target, int dim1, int dim2, int P, int dir) {

    int V[N], VCopy[N];

    if (r_o_c =='r')
        for (int i = 0; i < dim2 ; i++) {
            V[i] = M[target][i];
        }

    if (r_o_c=='c')
        for (int i = 0; i < dim1 ; i++) {
            V[i] = M[i][target];
        }

    switch (r_o_c) {

            case 'r':

                while(P>dim2)
                    P -= dim2; //affinche inserendo un P maggiore della dimensione lo spostamento sia comunque adeguato

                CopyVett(V, VCopy, dim2);

                if (dir == 0) { //sx

                    for (int i = 0, j = P; i < dim2 - P; i++) {
                        V[i] = VCopy[j];
                        j++;
                    }

                    for (int i = dim2 - P, j = 0; i < dim2; i++) {
                        V[i] = VCopy[j];
                        j++;
                    }

                    for (int k = 0; k < dim2 ; k++) {
                        M[target][k] = V[k];
                    }
                }

                if (dir == 1) { //dx

                    for (int i = 0, j=P; i < dim2 - P; i++) {
                        V[j] = VCopy[i];
                        j++;
                    }

                    for (int i = dim2-P, j=0; i < dim2 ; i++) {
                        V[j] = VCopy[i];
                        j++;
                    }

                    for (int k = 0; k < dim2 ; k++) {
                        M[target][k] = V[k];
                    }

                }
                break;

            case 'c':

                while(P>dim1)
                    P -= dim1;

                CopyVett(V,VCopy,dim1);

                if (dir == 0) { //basso

                    for (int i = 0, j = P; i < dim1 - P; i++) {
                        V[i] = VCopy[j];
                        j++;
                    }

                    for (int i = dim1 - P, j = 0; i < dim1; i++) {
                        V[i] = VCopy[j];
                        j++;
                    }

                    for (int k = 0; k < dim1; k++) {
                        M[k][target] = V[k];
                    }
                }

                if (dir == 1) { //alto

                    for (int i = 0, j=P; i < dim1 - P; i++) {
                        V[j] = VCopy[i];
                        j++;
                    }

                    for (int i = dim1-P, j=0; i < dim1 ; i++) {
                        V[j] = VCopy[i];
                        j++;
                    }

                    for (int k = 0; k < dim1 ; k++) {
                        M[k][target] = V[k];
                    }
                }
                break;

            default:
                break;

        }
}

void stampaMatrice(int M[][N], int dim1, int dim2){

    printf("\n");
    for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim2; j++)
            printf("%d ", M[i][j]);
        printf("\n");
    }
    printf("\n");
}