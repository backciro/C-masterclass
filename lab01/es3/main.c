//
// // created by Matteo Minutti on 10/10/2016
//
#include <stdio.h>

float valutaHorner(float P[11], float x);
void copyVett(float P[11], float COPY[11]);

int main(){

    int n, a, b, m, k=0, i;
    float h, x, horner=0.0;
    float P[11], COPY[11];

    printf("inserisci il grado N del polinomio: \n");
    scanf("%d", &n);

    printf("inserisci gli N+1 coefficienti reali: \n");
    for (k=n;k>=0;k--)
        scanf("%f", &P[k]);

    printf("si inseriscano gli estremi di integrazione: \n");
    scanf("%d %d", &a, &b);

    printf("si inserisca il numero di sottointervalli M, dunque la precisione di calcolo: \n");
    scanf("%d", &m);

    h = (float)(b-a)/(float)m; //passo
    x = ((a + h) / 2 ); //pto medio

    for(i=0; i < m; i++){

        copyVett(P, COPY);
        horner += valutaHorner(COPY, x);
        x = (x + h);
    }
        printf("\nArea Totale sottesa dalla funzione pari: %.2f\n", h * horner);
    return 0;
}

float valutaHorner(float P[11], float x){

    float res;
    int nmax=10, i;

    for (i = nmax; i >= 0 ; i--) {
        P[i-1] += (P[i] * x);
    }
        res = P[0];
return res;
}

void copyVett(float P[11], float COPY[11])
{
    for (int i = 0; i <=11 ; i++) {
        COPY[i]=P[i];
    }
}