//
//	created by Matteo Minutti on 31/10/2016
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAXR=10;
const int MAXstr=25;

typedef enum {FALSE, TRUE} bool;

typedef struct {

	char cod[MAXR];
	char *obj;
	char *cat;
	float price;
	int qty;
	int dd, mm, yyyy;
} prodotto;

prodotto* allocaStruct(prodotto *V, int *num);

void scegliComando(prodotto *V, int *num);

void stampaElenco(prodotto *V, int *num);

void stampaCategorie(prodotto *V, int *num);

void ordinaPrezzo(prodotto *V, int *num);

void ordinaCodice(prodotto *V, int *num);

void ordinaNome(prodotto *V, int *num);

void aggiornaQuantita(prodotto *V, int *num);

void ricercaDicotomica(prodotto *V, int *num, bool ordinato);

void ricercaNome(prodotto *V, int *num, bool ordinato);

int main(){

    prodotto *V;
	int num;
	
	V = allocaStruct(V, &num);

	scegliComando(V, &num);

	return 0;
}

prodotto* allocaStruct(prodotto *V, int *num){
	
	FILE *fp;
	int i;
	char str1[MAXstr], str2[MAXstr];

	if((fp=fopen("./catalogo.txt", "r"))==NULL)
		printf("ERRORE APERTURA FILE!\n");

	fscanf(fp,"%d", num);

	V = (prodotto*) malloc((*num) * sizeof(*V));

	i=0;
	while (i < *num){ 

		fscanf(fp, "%s%s%s%f%d %d/%d/%4d", V[i].cod, str1, str2,
		&V[i].price, &V[i].qty, &V[i].dd, &V[i].mm, &V[i].yyyy);

		V[i].obj = (char*) malloc((int)strlen(str1) * sizeof(char));
		strcpy(V[i].obj, str1); // oppure strdup(str1);

		V[i].cat = (char*) malloc((int)strlen(str2) * sizeof(char));
		strcpy(V[i].cat, str2); // oppure strdup(str2);

		i++;
	}
		return V;
}

void scegliComando(prodotto *V, int *num){

	bool ciclo=TRUE;
	bool inizio=TRUE;
	int scelta;
	bool ordinato_nome=FALSE, ordinato_cod=FALSE, ordinato_prezzo=FALSE;


	do{
		if (inizio){
	printf("\nEffettuare una scelta tra le seguenti:\n"
		"1) Stampa l\'elenco dei prodotti disponibili\n"
		"2) Ordina l\'elenco secondo il prezzo\n"
		"3) Ordina l\'elenco secondo il codice prodotto\n"
		"4) Ordina l\'elenco secondo il nome del prodotto\n"
		"5) Stampa l\'elenco diviso per categorie\n"
		"6) Aggiorna la quantita\' di un prodotto\n"
		"7) Ricerca un prodotto per codice\n"
		"8) Ricerca un prodotto per nome\n"
		"\n... 0 per terminare il programma!\n");
		}

		if (!inizio)
			printf("\nEffettuare una scelta dal menu:\n");
		
	scanf("\n%d", &scelta);

	if (scelta==0){
		ciclo=FALSE;
		break;
	}

		switch (scelta){
			case 1:
				stampaElenco(V, num);
				inizio=TRUE;
				break;
			
			case 2:
				ordinaPrezzo(V, num);
				inizio=FALSE;
				ordinato_prezzo=TRUE;
				break;

			case 3:
				ordinaCodice(V, num);
				inizio=FALSE;
				ordinato_cod=TRUE;
				break;

			case 4:
				ordinaNome(V, num);
				inizio=FALSE;
				ordinato_nome=TRUE;
				break;

			case 5:
				stampaCategorie(V, num);
				inizio=TRUE;
				break;

			case 6:
				aggiornaQuantita(V, num);
				inizio=TRUE;
				break;

			case 7:
				ricercaDicotomica(V, num, ordinato_cod);
				inizio=FALSE;
				break;

			case 8:
				ricercaNome(V, num, ordinato_nome);
				inizio=FALSE;
				break;
		}

	}while(ciclo);
}

void stampaElenco(prodotto *V, int *num){

	FILE *fpout;
	int scelta;
	char nomefile[15];

	printf("Dove vuoi stampare? 0 -> Video || 1 -> File?\n");
	scanf("%d", &scelta);

	if (scelta==1){
		printf("Inserire nome file:\n");
		scanf("%s", nomefile);
	
		if ( (fpout=fopen(nomefile, "w")) == NULL ){
			printf("Errore file scrittura!\n");	
			exit(-1);
			}
		
		for(int i=0; i < *num; i++ )
			fprintf(fpout, "* %s %s %s %.2f %d %d\\%d\\%4d \n",
			V[i].cod, V[i].obj, V[i].cat, V[i].price, V[i].qty,
			V[i].dd, V[i].mm, V[i].yyyy);
	}

	if (scelta==0)
		for(int i=0; i < *num; i++){
			printf("\n* %s %s %s %.2f %d %d\\%d\\%4d ",
			V[i].cod, V[i].obj, V[i].cat, V[i].price, V[i].qty,
			V[i].dd, V[i].mm, V[i].yyyy);
			}printf("\n");
}

void stampaCategorie(prodotto *V, int *num){

	FILE *fpout;
	int scelta;
	char nomefile[15];
	bool check[*num];

	printf("Dove vuoi stampare? 0 -> Video || 1 -> File?\n");
	scanf("%d", &scelta);

	if (scelta==1){
		printf("Inserire nome file:\n");
		scanf("%s", nomefile);
	
			if ( (fpout=fopen(nomefile, "w")) == NULL ){
			printf("Errore file scrittura!\n");
			exit(-1);
			}
	}

	for (int i=0; i<*num; i++)
		check[i]=FALSE;

	for(int i=0; i < *num; i++){
		if ( check[i] == FALSE ){
			printf("\nCategoria %s: \n", V[i].cat);
			
			for (int j=i; j<*num; j++){
				if (strcmp(V[i].cat, V[j].cat) == 0){
					printf("* %s\n", V[j].obj);
					check[j]=TRUE;
				}
			}
		}
	}
}

void ordinaPrezzo(prodotto *V, int *num){

	int i, j, verso;
	prodotto tmp;

	printf("0 -> ascendente || 1 -> discendente\n");
	scanf("\n%d", &verso);

	if (verso == 0){
		for (i=0; i<*num-1; i++){
			for (j=i+1; j<*num; j++){
				if (V[i].price > V[j].price) {

					tmp = V[i];
					V[i] = V[j];
					V[j] = tmp;
				}
			}
		}
	}

	if (verso == 1){
		for (i=0; i<*num-1; i++){
			for (j=i+1; j<*num; j++){
				if (V[i].price < V[j].price) {

					tmp = V[i];
					V[i] = V[j];
					V[j] = tmp;
				}
			}
		}
	}
}

void ordinaCodice(prodotto *V, int *num){

	int i, j;
	prodotto tmp;

		for (i=0; i<*num-1; i++){
			for (j=i+1; j<*num; j++){
				if ((strcmp(V[i].cod, V[j].cod)) > 0) {
					tmp = V[i];
					V[i] = V[j];
					V[j] = tmp;
				}
			}
		}
}

void ordinaNome(prodotto *V, int *num){

	int i, j;
	prodotto tmp;

		for (i=0; i<*num-1; i++){
			for (j=i+1; j<*num; j++){
				if ((strcmp(V[i].obj, V[j].obj)) > 0) {
					tmp = V[i];
					V[i] = V[j];
					V[j] = tmp;
				}
			}
		}	
}

void aggiornaQuantita(prodotto *V, int *num){

	char cod[MAXR];
	int qty, ind;

	printf("\nInserire il codice del prodotto da aggiornare\n");
	scanf("\n%s", cod);

	for (int i = 0; i < *num; i++)
		if (strcmp(cod, V[i].cod)==0){
			printf("\nProdotto '%s' trovato! Q.ta attuale: %d.\n"
					"Inserire nuova quantita: \n", V[i].obj, V[i].qty);
			ind=i;
		}
		scanf("\n%d", &qty);

		V[ind].qty = qty;

		printf("Inserire data odierna: (dd/mm/yyyy)\n");
		scanf("%d/%d/%4d", &V[ind].dd, &V[ind].mm, &V[ind].yyyy);
}

void ricercaDicotomica(prodotto *V, int *num, bool ordinato){

	char str[MAXR];
	int p, u, m, trovato;
	bool found=FALSE;

   	printf("Inserisci un codice prodotto:\n");
   	scanf("\n%s",str);

    p = 0;
    u = *num -1;
   
    while(p <= u) {

	if (!ordinato){
    	printf("Prima di ricercare, effettuare un ordinamente del catalogo!");
		break;
	}
   		
   		if( strcmp(V[p].cod, str) == 0){
            trovato = p;
            found = TRUE;
            break;
        }

        m = (p + u) / 2;
        if( strcmp(V[m].cod, str) == 0){
            trovato = m;
            found = TRUE;
            break;
        }

        if(strcmp(V[m].cod, str) < 0)
            p = m + 1;
        else
            u = m - 1;
    }
    m = *num -1;
    
    if (strcmp(V[m].cod, str) == 0){
    	found = TRUE;
    	trovato = m;
	}

    if (!found && ordinato){
    	printf("Prodotto non trovato!\n"
    		"Ripetere la ricerca...\n");
    }

    else printf("* %s %s %s %.2f %d %d\\%d\\%4d \n",
			V[trovato].cod, V[trovato].obj, V[trovato].cat, V[trovato].price, V[trovato].qty,
			V[trovato].dd, V[trovato].mm, V[trovato].yyyy);
}

void ricercaNome(prodotto *V, int *num, bool ordinato){

	char stringa[MAXR+1];
	bool found=FALSE;
	int trovato[*num], j=0;

	printf("Inserire nome da ricercare (anche parziale)\n");
	scanf("\n%s", stringa);

	for (int i = 0; i < *num; i++)
	{
		
	if (!ordinato){
    	printf("Prima di ricercare, effettuare l' ordinamente del catalogo per nome!");
		break;
	}

		while(j < *num)
			{
		if (strncmp(stringa, V[i].obj, strlen(stringa))==0){
				
				found = TRUE;
				trovato[j] = i;
				j++;
		}	break;
			}
	}

	if (!found && ordinato)
		printf("Prodotto non trovato!\n");

	else if (found)
	{
		for(int i=0; i < j; i++)
			printf("\nProdotto trovato:\n"
			"* %s %s %s %.2f %d %d\\%d\\%4d \n",
			V[trovato[i]].cod, V[trovato[i]].obj, V[trovato[i]].cat, V[trovato[i]].price, V[trovato[i]].qty,
			V[trovato[i]].dd, V[trovato[i]].mm, V[trovato[i]].yyyy);
	}
}