//
// // Created by Matteo Minutti on 08/10/16.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXS 5

typedef enum {FALSE, TRUE} bool;

float operando(char s[], float precedente);

int main (void) {

    char op=0;
    char str1[MAXS + 1], str2[MAXS + 1];

    float res = 0;
    float resprec;

    //boolean utilizzata come condizione del while;
    bool ciclo = TRUE;

    //inizio ciclio do-while (utilizzato per avere una prima esecuzione senza inutile check della condizione booleana);
    do {
        //salvataggio risultato precedente; 0 in caso di prima esecuzione;
        resprec = res;

        //stampa menu scelta comandi;
        printf("\nInserisci comandi formattati come '<operatore>  <operando1>  <operando2>' :"
                       "\n --- \"PREV\" per utilizzare il risultato precedente --- \n"
                       " --- \"BASTA COSI\" per terminare il programma --- \n");
        scanf("\n%c%s%s", &op, str1, str2); // il '\n' per dare una formattazione più "carina"!


        //inizio switch cases su variabile 'op';
        switch (op){
            case '+':
                res = operando(str1, resprec) + operando(str2, resprec);
                printf("Risultato: %.1f\n", res);
                break;

            case '-':
                res = operando(str1, resprec) - operando(str2, resprec);
                printf("Risultato: %.1f\n", res);
                break;

            case '*':
                res = operando(str1, resprec) * operando(str2, resprec);
                printf("Risultato: %.1f\n", res);
                break;

            case '/':
                res = operando(str1, resprec) / operando(str2, resprec);
                printf("Risultato: %.1f\n", res);
                break;

            default :
                ciclo = FALSE;
                printf("\n\nP R O G R A M M A   T E R M I N A T O ! ! !\n\n");
                break;
        }

    } while (ciclo);
}

float operando (char s[MAXS+1], float precedente){

    char strPREV[MAXS+1] = "PREV\0";

    if ( (strcmp(strPREV, s)) == 0 )
        return precedente;

    else
        return (float)atof(s);

}