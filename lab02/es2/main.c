#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIMc 200
#define DIMr 30

typedef struct
{
    int lun;
    char sim[3];
    char str[DIMr];
} parola;

void azz_vet(int v[], int s);

void verifica_testo(parola vet[], FILE *sor, FILE *com, int s);

int trova_par(char parol[], int lun, FILE *sor, int pos, char riga[]);

int cerca_max(parola v[], int n, int tro[]);

int main()
{
    int s;
    int i=0;
    parola vet[DIMr];
    
    char str[DIMr], sim[3], nomefile[80], nomefsor[80], nomefcomp[80];

    FILE *sor;
    FILE *diz;
    FILE *com;

    printf("inserire nome file diz\n");
    scanf("\n%s", nomefile);
   
    if((diz=fopen(nomefile, "r")) == NULL) 
    printf("\nERRORE IN APERTURA FILE DIZIONARIO\n");

    printf("inserire nome file sorgente\n");
    scanf("\n%s", nomefsor);

    printf("inserire nome file compresso\n");
    scanf("\n%s", nomefcomp);

    sor = fopen(nomefsor, "r");
    com = fopen(nomefcomp, "w");

    fscanf(diz, "%d", &s);
    while(i<s)
    {
        fscanf(diz, "%s%s", sim, str);
        vet[i].lun = (int)strlen(str);
        strcpy(vet[i].str, str);
        strcpy(vet[i].sim, sim);
        i++;
    }

    verifica_testo(vet, sor, com, s);

    return 0;
}

void verifica_testo(parola vet[], FILE *sor, FILE *com, int s)
{
    int i, len, pos, ind;
    char riga[DIMc];
    int tro[s];

    azz_vet(tro, s);

    while(fgets(riga, DIMc, sor)!=NULL)
    {
        len = (int)strlen(riga);
        pos=0;
        while(pos<len)
        {
            for(i=0; i<s; i++)
            {
                if(vet[i].str[0]==riga[pos])
                {
                    if(trova_par(vet[i].str, (vet[i].lun)-1, sor, pos+1, riga)==1) tro[i]=1;
                }
            }
            ind = cerca_max(vet, s, tro);
            if(ind<0)
            {
                fprintf(com, "%c", riga[pos]);
                pos++;
            }
            else
            {
                fprintf(com, "%c%c", vet[ind].sim[0], vet[ind].sim[1]);
                pos = pos + vet[ind].lun;
                azz_vet(tro, s);
            }
        }
    }
 
}

int trova_par(char parol[], int lun, FILE *sor, int pos, char riga[])
{
    int cnt=0;
    int i=pos;
    int j;

    for(j=1; j<lun+1; j++, i++)
    {
        if(parol[j]==riga[i]) 
            cnt++;
    }

    if(cnt==lun) return 1;
    else return 0;
}

void azz_vet(int v[], int n)
{
    int i;

    for(i=0; i<n; i++) 
        v[i]=0;
}

int cerca_max(parola v[], int n, int tro[])
{
    int pos, i;
    int max=0;

    for(i=0; i<n; i++)
    {
        if(tro[i]==1)
        {
            if(v[i].lun > max)
            {
                max=v[i].lun;
                pos=i;
            }
        }
    }
    if(max>0) 
        return pos;
    
    else return -1;
}
