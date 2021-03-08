#include <stdio.h>
#include <stdlib.h>
#define MAXCAR 100
#define NR 5
#define NC 3

/*  Algoritmo I vers. partire da dopo la fine del commento
int main(int argc, char *argv[]){

    FILE *fp;
    
    int i,k,colonna;
    char nomef[MAXCAR+1];
    float mat[NR][NC];
    
    float xtot=0, ytot=0, ztot=0;
    float bx, by, bz;
    float xtmp, ytmp, ztmp;
    
    printf("inserisci nome file ingresso: \n");
    scanf("%s", nomef);
    
    if ((fp = fopen(nomef,"r")) == NULL)
        printf("Errore Apertura file!\n");
    
    i=0;

    // riempio la matrice dal puntatore fp
    while(fscanf(fp, "%f %f %f", &xtmp, &ytmp, &ztmp) == 3){
        mat[i][0]=xtmp;
        mat[i][1]=ytmp;
        mat[i][2]=ztmp;
i++;
    }
    
    //riempio variabili baricentro
   
    for (colonna=0 ; colonna < NC ; colonna++)
        for (k=0; (k<NR) ; k++) {
            if (colonna==0)
                xtot += mat[k][colonna];
            
            if (colonna==1)
                ytot += mat[k][colonna];

            if (colonna==2)
                ztot += mat[k][colonna];
        }
    
    // calcolo baricentro
    bx=(xtot/k);
    by=(ytot/k);
    bz=(ztot/k);
    
    printf("\n Baricentro: %.1f %.1f %.1f", bx, by, bz);
    return 0;

} */

float cb(float a, int n);
int main(){

FILE *fp;
   char nomefile[MAXCAR+1];
    float x, y, z;
    float sommax=0, sommay=0, sommaz=0;
    int count=0;

    printf("Inserisci PATH del file: \n");
    scanf("%s", nomefile);

    if ((fp=fopen(nomefile,"r"))==NULL) {
        printf("errore apertura file!\n");
        exit(1);
    }

    while (fscanf(fp,"%f %f %f", &x, &y, &z)==3){
        sommax += x;
        sommay += y;
        sommaz += z;
        count++;

    }

    fclose(fp);
    printf("Baricentro: %.2f %.2f %.2f",
           cb(sommax,count), cb(sommay,count), cb(sommaz, count));
    return 0;
}

float cb(float a, int count){

    float bar;

    bar = (a/count);
    return bar;
}
