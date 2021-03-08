#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXPAR 20
#define MAXFILE 100

int contavocali (char stringa[], char vocali[]);

int main(){

    FILE *fpin;
    FILE *fpout1, *fpout2;

    int righe, i;
    char parolacorrente[MAXPAR];
    char parolatmp[MAXPAR];

    char vocali[5] = {'a','e','i','o','u'};

    char nomefilein[MAXFILE];
    char nomefileout1[MAXFILE];
    char nomefileout2[MAXFILE];

    printf("\n Inserisci il nome del file input: ");
    scanf("%s", nomefilein);

    if ((fpin=fopen(nomefilein, "r"))==NULL)
        printf("Errore apertura file input!\n");

    printf("\n Inserisci il nome del file output 1: ");
    scanf("%s", nomefileout1);

    if ((fpout1=fopen(nomefileout1, "w"))==NULL)
        printf("Errore apertura file output 1!\n");

    printf("\n Inserisci il nome del file output 2: ");
    scanf("%s", nomefileout2);

    if ((fpout2=fopen(nomefileout2, "w"))==NULL)
        printf("Errore apertura file output2 !\n");


    fscanf(fpin, "%d %s", &righe, parolacorrente);

    i=1;

    while(i < righe+1){

        fscanf(fpin, "%s", parolatmp);

        if (strcmp(parolacorrente, parolatmp) <= 0)
            fprintf(fpout1, "%s\n" , parolatmp);

        if ((contavocali(parolatmp, vocali)) >= (contavocali(parolacorrente, vocali)) )
            fprintf(fpout2, "%s\n", parolatmp);

        i++;


    }   fclose(fpin);
        fclose(fpout1);
        fclose(fpout2);
    }



int contavocali (char stringa[], char vocali[]) {

    int i, j;
    int contatore = 0;

    stringa[0] = tolower(stringa[0]);
    for (j = 0; j < 5; j++)
        for (i = 0; i < strlen(stringa); i++)
            if (vocali[j] == stringa[i])
                contatore++;

    return contatore;

}




