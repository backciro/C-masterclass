/* Si noti che l'esempio presente nel pdf 'lab03' fatto per il comando "rifiuto"
È errato poichè figura un user (user1 n.d.r.) che non dovrebbe essere presente
in quanto accede in un intervallo di tempo non compreso tra le date proposte! occhio!
*/

//
//  created by Matteo Minutti on 27/10/2016
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

const int MAXS = 30;
const int MAXN = 1000;

typedef enum {FALSE, TRUE} bool;

typedef enum {r_nome, r_IP, r_rifiuto, r_risorse, r_fine} comando_e;

typedef struct
{
    char ip[MAXS];
    char user[MAXS];
    int giorno, mese, anno;
    char tipo_r[MAXS];
    char risorsa[MAXS];
    int risposta;
} Tabella;

comando_e leggiComando (char str[], bool *ciclo);

void selezionaDati(Tabella tab[], int nDati, comando_e cmd);

int leggiTabella(FILE *fp, Tabella tab[MAXN], int MAXN);

double trasformaNumero(int anno, int mese, int giorno);

int main (){

    FILE *fp;
    Tabella tab[MAXN];
    int nDati;
    char nomefile[MAXS+1], selettore[MAXS];
    comando_e cmd;
    bool ciclo=TRUE;

    printf("inserisci PATH file accessi: \n");
    scanf("\n%s", nomefile);

    if ((fp=fopen(nomefile,"r"))==NULL){
        printf("errore aperura file\n");
        exit(EXIT_FAILURE);
    }

    nDati = leggiTabella(fp, tab, MAXN);
    
    do{    
    printf("\ninserisci comando \n <nome / IP / rifiuto / risorsa / fine> :  \n");
    scanf("\n%s", selettore);

    cmd = leggiComando(selettore, &ciclo);

    selezionaDati(tab, nDati, cmd);

    } while (ciclo);

    return 0;
}

int leggiTabella(FILE *fp, Tabella tab[MAXN], int MAXN){

    int nd, i=0;

    fscanf(fp,"%d",&nd);

    while((fscanf(fp,"%s%s %d/%d/%4d:%*s %s%s%d",tab[i].ip, tab[i].user, &tab[i].giorno,
                  &tab[i].mese, &tab[i].anno, tab[i].tipo_r, tab[i].risorsa, &tab[i].risposta))==8){
        i++;
    }
    return nd;
}

comando_e leggiComando (char str[], bool *ciclo){

    if ((strcmp(str,"nome\0")) == 0)
        return r_nome;

    if ((strcmp(str,"IP\0")) == 0)
        return r_IP;

    if ((strcmp(str,"rifiuto\0")) == 0)
        return r_rifiuto;

    if ((strcmp(str,"risorsa\0")) == 0)
        return r_risorse;

    if ((strcmp(str,"fine\0")) == 0)
    {
        *ciclo = FALSE;
        return r_fine;
    }
    
    else {
        *ciclo = FALSE;
        return r_fine;
        }
}

void selezionaDati(Tabella tab[], int nDati, comando_e cmd){

    int giorno_i, mese_i, anno_i;
    int giorno_e, mese_e, anno_e;
    int i;

    switch (cmd){

        case r_nome :

            printf("\ninserisci intervallo di date <DATA START> - <DATA END> \n");
            scanf("%d/%d/%4d - %d/%d/%4d", &giorno_i, &mese_i, &anno_i,
            &giorno_e, &mese_e, &anno_e);

            i = 0;
            while(i<nDati){

                if  ( ( trasformaNumero(tab[i].anno, tab[i].mese, tab[i].giorno)
                        >= trasformaNumero(anno_i, mese_i, giorno_i) ) &&
                      (trasformaNumero(tab[i].anno, tab[i].mese, tab[i].giorno)
                       <= trasformaNumero(anno_e, mese_e, giorno_e)) )
                {
                    printf("%s\n", tab[i].user);
                }	i++;
            }
            break;

        case r_IP:

            printf("\ninserisci intervallo di date <DATA START> - <DATA END> \n");
            scanf("%d/%d/%4d - %d/%d/%4d", &giorno_i, &mese_i, &anno_i,
            &giorno_e, &mese_e, &anno_e);

            i = 0;
            while(i<nDati){
                if  ( ( trasformaNumero(tab[i].anno, tab[i].mese, tab[i].giorno)
                        >= trasformaNumero(anno_i, mese_i, giorno_i) ) &&
                      (trasformaNumero(tab[i].anno, tab[i].mese, tab[i].giorno)
                       <= trasformaNumero(anno_e, mese_e, giorno_e)) )
                {
                    printf("%s\n", tab[i].ip);
                }
                i++;
            }
            break;

        case r_rifiuto:

            printf("\ninserisci intervallo di date <DATA START> - <DATA END> \n");
            scanf("%d/%d/%4d - %d/%d/%4d", &giorno_i, &mese_i, &anno_i,
            &giorno_e, &mese_e, &anno_e);        

            i = 0;
            while(i<nDati){
                if  ( ( trasformaNumero(tab[i].anno, tab[i].mese, tab[i].giorno)
                        >= trasformaNumero(anno_i, mese_i, giorno_i) ) &&
                      (trasformaNumero(tab[i].anno, tab[i].mese, tab[i].giorno)
                       <= trasformaNumero(anno_e, mese_e, giorno_e)))
                    if (tab[i].risposta == 401)
                {
                    printf("%s\n", tab[i].user);
                }
                i++;
            } break;

        case r_risorse:

            printf("\ninserisci intervallo di date <DATA START> - <DATA END> \n");
            scanf("%d/%d/%4d - %d/%d/%4d", &giorno_i, &mese_i, &anno_i,
            &giorno_e, &mese_e, &anno_e); 

            i = 0;
            while(i<nDati){
                if  ( ( trasformaNumero(tab[i].anno, tab[i].mese, tab[i].giorno)
                        >= trasformaNumero(anno_i, mese_i, giorno_i) ) &&
                      (trasformaNumero(tab[i].anno, tab[i].mese, tab[i].giorno)
                       <= trasformaNumero(anno_e, mese_e, giorno_e)) )
                {
                    printf("`%s\n", tab[i].risorsa);
                }
                i++;
            } break;

        default :
            printf("\nProgramma Terminato! \n");
            break;
    }
}

double trasformaNumero(int anno, int mese, int giorno){

    double result=0;

    result = ( (anno * pow(10,4)) + (mese*pow(10,2)) + (giorno*pow(10,0)) );

    return result;
}