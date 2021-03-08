//
//	created by Matteo Minutti on 12/11/2016
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAXR = 10;
const int MAXstr = 25;

typedef enum {FALSE, TRUE} bool;

typedef struct {

	char cod[MAXR];
	char *obj;
	char *cat;
	float price;
	int qty;
	int dd, mm, yyyy;
	bool available;

}prodotto;

prodotto* allocaStruct(prodotto *V, int *num);

prodotto** allocaVett(int num);

prodotto* aggiungiObj(prodotto **V, int *num);

void scegliComando(prodotto *V, prodotto **V_price, prodotto **V_cod, prodotto **V_obj, int *num);

void stampaElenco(prodotto *V, int *num);

void stampaCategorie(prodotto *V, int *num);

void ordinaPrezzo(prodotto *V, prodotto **V_price, int *num);

void priceRicorsivo(prodotto *V, prodotto **V_price, int *num, int *mark, int pos, int verso);

void ordinaCodice(prodotto *V, prodotto **V_cod, int *num);

void codRicorsivo(prodotto *V, prodotto **V_cod, int *num, int *mark, int pos);

void ordinaNome(prodotto *V, prodotto **V_obj, int *num);

void objRicorsivo(prodotto *V, prodotto **V_obj, int *num, int *mark, int pos);

void aggiornaQuantita(prodotto *V, int *num);

void ricercaDicotomica(prodotto **V, int *num, bool ordinato);

void ricercaNome(prodotto *V, int *num, bool ordinato);

void distruggiTutto(prodotto **V_price, prodotto **V_cod, prodotto **V_obj, int num);

int main(){

    prodotto *V;

    prodotto **V_price;
    prodotto **V_cod;
    prodotto **V_obj;

	int num;
	
	V = allocaStruct(V, &num);

	V_price = allocaVett(num);
	V_cod = allocaVett(num);
	V_obj = allocaVett(num);

	scegliComando(V, V_price, V_cod, V_obj, &num);

	distruggiTutto(V_price, V_cod, V_obj, num);
	free(V);
	
	return 0;
}

prodotto* allocaStruct(prodotto *V, int *num){
	
	FILE *fp;
	int i;
	char str1[MAXstr], str2[MAXstr];

	if((fp=fopen("./catalogo.txt","r"))==NULL)
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

			V[i].available = TRUE;

			i++;
	}
		return V;
}

prodotto** allocaVett(int num){

	prodotto **V;

	V = malloc((num) * sizeof(prodotto));
		for (int i=0; i <= num; i++)
			(V)[i] = malloc(sizeof(*V[i]));
		return V;
}

void distruggiTutto(prodotto **V_price, prodotto **V_cod, prodotto **V_obj, int num){

	if(V_price!=NULL){
		for (int i = 0; i < num; i++)
		{
			free(V_price[i]);
		}
		free(V_price);
	}
	
	if(V_cod!=NULL){	
		for (int i = 0; i < num; i++)
		{
			free(V_cod[i]);
		}
		free(V_cod);
	}
	
	if(V_obj!=NULL){
		for (int i = 0; i < num; i++)
		{
			free(V_obj[i]);
		}
		free(V_obj);
	}
}

void scegliComando(prodotto *V, prodotto **V_price, prodotto **V_cod, prodotto **V_obj, int *num){

	bool ciclo=TRUE;
	bool inizio=TRUE;
	bool ordinato_nome=FALSE, ordinato_cod=FALSE, ordinato_prezzo=FALSE;
	int scelta;

	do{
		if (inizio){
	printf("\nEffettuare una scelta tra le seguenti:\n"
		"1 -> Stampa l\'elenco dei prodotti disponibili\n"
		"2 -> Ordina l\'elenco secondo il prezzo\n"
		"3 -> Ordina l\'elenco secondo il codice prodotto\n"
		"4 -> Ordina l\'elenco secondo il nome del prodotto\n"
		"5 -> Stampa l\'elenco diviso per categorie\n"
		"6 -> Aggiorna la quantita\' di un prodotto\n"
		"7 -> Ricerca un prodotto per codice\n"
		"8 -> Ricerca un prodotto per nome\n"
		"9 -> Inserisci un prodotto nel catalogo\n"
		"... 0 per terminare il programma!\n\n");
		}

		if (!inizio)
			printf("\nEffettuare una scelta dal menu principale <1...9>\n");
		
	scanf("\n%d", &scelta);
	
	if (!scelta)
	{
		ciclo=FALSE;
		break;
	}

		switch (scelta){

			case 1:
				stampaElenco(V, num);
				inizio=TRUE;
				break;
			
			case 2:
				ordinaPrezzo(V, V_price, num);
				inizio=FALSE;
				ordinato_prezzo=TRUE;
				break;

			case 3:
				ordinaCodice(V, V_cod, num);
				inizio=FALSE;
				ordinato_cod=TRUE;
				break;

			case 4:
				ordinaNome(V, V_obj, num);
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
				ricercaDicotomica(V_cod, num, ordinato_cod);
				inizio=FALSE;
				break;

			case 8:
				ricercaNome(V, num, ordinato_nome);
				inizio=FALSE;
				break;

			case 9:
				(*num) += 1; //realloc di +1 perchè non è necessario raddoppiare
				V = realloc(V, (size_t)((*num) * sizeof(*V)) );

				V = aggiungiObj(&V, num);
				
				V_price = allocaVett(*num);
				V_cod =	allocaVett(*num);
				V_obj = allocaVett(*num);
				
				inizio=FALSE;
				break;
			
			default:
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
	
	if (!scelta){
			for(int i=0; i < *num; i++){
				if (V[i].available)
					printf("\n* %s %s %s %.2f %d %d\\%d\\%4d ",
					V[i].cod, V[i].obj, V[i].cat, V[i].price, V[i].qty,
					V[i].dd, V[i].mm, V[i].yyyy);
			}printf("\n");
	}

	if (scelta){
		printf("Inserire nome file:\n");
		scanf("%s", nomefile);
	
		if ( (fpout=fopen(nomefile, "w")) == NULL ){
			printf("Errore file scrittura!\n");	
			exit(-1);
			}
		
		for(int i=0; i < *num; i++ )
			if (V[i].available)
				fprintf(fpout, "* %s %s %s %.2f %d %d\\%d\\%4d \n",
				V[i].cod, V[i].obj, V[i].cat, V[i].price, V[i].qty,
				V[i].dd, V[i].mm, V[i].yyyy);
		fclose(fpout);
	}		
}

void stampaCategorie(prodotto *V, int *num){

	FILE *fpout;
	int scelta;
	char nomefile[15];
	bool check[*num];

	printf("Dove vuoi stampare? 0 -> Video || 1 -> File?\n");
	scanf("%d", &scelta);

	if (scelta){
		printf("Inserire nome file:\n");
		scanf("\n%s", nomefile);
	
			if ((fpout = fopen(nomefile, "w")) == NULL){
			printf("Errore file scrittura!\n");
			exit(-1);
			}
		

		for (int i=0; i<*num; i++)
			check[i]=FALSE;

		for(int i=0; i < *num; i++){
			if (check[i] == FALSE ){
				fprintf(fpout, "\nCategoria %s: \n", V[i].cat);
				
				for (int j=i; j<*num; j++){
					if (strcmp(V[i].cat, V[j].cat) == 0){
						if (V[j].available)
						fprintf(fpout, "* %s\n", V[j].obj);
						check[j]=TRUE;
					}
				}
			}
		}
		fclose(fpout);	
	}

	if (!scelta){
		for (int i=0; i<*num; i++)
			check[i]=FALSE;

		for(int i=0; i < *num; i++){
			if ( check[i] == FALSE ){
				printf("\nCategoria %s: \n", V[i].cat);
				
				for (int j=i; j<*num; j++){
					if (strcmp(V[i].cat, V[j].cat) == 0){
						if (V[j].available)
						printf("* %s\n", V[j].obj);
						check[j]=TRUE;
					}
				}
			}
		}
	}
}

void ordinaPrezzo(prodotto *V, prodotto **V_price, int *num){

	int pos=0, verso, *mark;

	printf("0 -> ascendente || 1 -> discendente\n");
	scanf("\n%d", &verso);

	mark = malloc((*num) * sizeof(int));
	for(int k=0; k<*num; k++)
		mark[k] = 0;

	priceRicorsivo(V, V_price, num, mark, pos, verso);
	printf("\n");
}

void priceRicorsivo(prodotto *V, prodotto **V_price, int *num, int *mark, int pos, int verso){

	int j, ind;
    float min = INT_MAX;
    float max = 0;

    if (pos >= (*num))
    	return;

    if (!verso){

    	for(j=0; j<(*num); j++){
            if(V[j].price < min){
                if(mark[j]==0){
                    min = V[j].price;
                    ind = j;
                }
            }
    	}
    	mark[ind] = 1;
    	*V_price[pos] = V[ind];
	}

	if (verso){

    	for(j=0; j<(*num); j++){
            if(V[j].price > max){
                if(mark[j]==0){
                    max = V[j].price;
                    ind = j;
                }
            }
    	}
    	mark[ind] = 1;
    	*V_price[pos] = V[ind];
	}

	if (V_price[pos]->available)
	printf("\n* %s %s %s %.2f %d %d\\%d\\%4d ",
		V_price[pos]->cod, V_price[pos]->obj, V_price[pos]->cat, 
		V_price[pos]->price, V_price[pos]->qty,
		V_price[pos]->dd, V_price[pos]->mm, V_price[pos]->yyyy);

	priceRicorsivo(V, V_price, num, mark, pos+1, verso);
}

void ordinaCodice(prodotto *V, prodotto **V_cod, int *num){

	int pos=0, *mark;

	mark = malloc((*num) * sizeof(int));
	for(int k=0; k<*num; k++)
		mark[k] = 0;

	codRicorsivo(V, V_cod, num, mark, pos);

	printf("\n");
}

void codRicorsivo(prodotto *V, prodotto **V_cod, int *num, int *mark, int pos){

	int j, ind;
	char *temp = strdup("cod999999");

	if (pos >= (*num))
		return;

	for(j=0; j<(*num); j++){
            if(strcmp(temp, V[j].cod) > 0) {
                if(mark[j]==0){
                    ind = j;
                    strcpy(temp, V[j].cod);
                }
            }
    	}
    	mark[ind] = 1;
    	*V_cod[pos] = V[ind];

    if (V_cod[pos]->available)
		printf("\n* %s %s %s %.2f %d %d\\%d\\%4d",
		V_cod[pos]->cod, V_cod[pos]->obj, V_cod[pos]->cat, 
		V_cod[pos]->price, V_cod[pos]->qty,
		V_cod[pos]->dd, V_cod[pos]->mm, V_cod[pos]->yyyy);

    codRicorsivo(V, V_cod, num, mark, pos+1);
}

void ordinaNome(prodotto *V, prodotto **V_obj, int *num){

	int *mark, pos=0;

	mark = malloc((*num) * sizeof(int));
	for (int i = 0; i < *num; i++)
		mark[i] = 0;

	objRicorsivo(V, V_obj, num, mark, pos);

	for(int i = *num-1; i >= 0; i--){
		if (V_obj[i]->available)
			printf("\n* %s %s %s %.2f %d %d\\%d\\%4d",
			V_obj[i]->cod, V_obj[i]->obj, V_obj[i]->cat, 
			V_obj[i]->price, V_obj[i]->qty,
			V_obj[i]->dd, V_obj[i]->mm, V_obj[i]->yyyy);
	}printf("\n");
}

void objRicorsivo(prodotto *V, prodotto **V_obj, int *num, int *mark, int pos){

	char *temp = strdup("ZZZZ");
	int j, ind;

	if(pos > *num)
		return;

	for (j = 0; j < *num; j++){
		if (strcmp(V[j].obj, temp) > 0)
		{
			if (mark[j] == 0){
				ind = j;
				temp = strdup(V[j].obj);
			}
		}
	}
	mark[ind] = 1;
	*V_obj[pos] = V[ind];

	objRicorsivo(V, V_obj, num, mark, pos+1);
}

void aggiornaQuantita(prodotto *V, int *num){

	char cod[MAXR];
	int qty, ind;

	printf("\nPer cancellare un prodotto impostare a ZERO la sua quantita\'\n"
		"(sara\' visibile poi solo tramite ricerca per NOME)\n"
		"Inserire il codice del prodotto da aggiornare:\n");
	scanf("\n%s", cod);

	for (int i = 0; i < *num; i++)
		if (strcmp(cod, V[i].cod)==0){
			printf("\nProdotto '%s' trovato! Q.ta attuale: %d.\n"
					"Inserire nuova quantita: \n", V[i].obj, V[i].qty);
			ind=i;
		}
		scanf("\n%d", &qty);

		V[ind].qty = qty;

		if (!qty)	
			V[ind].available = FALSE; 
		
		if (qty)
			V[ind].available = TRUE;
		
		printf("Inserire data odierna: (dd/mm/yyyy)\n");
		scanf("%d/%d/%4d", &V[ind].dd, &V[ind].mm, &V[ind].yyyy);
}

void ricercaDicotomica(prodotto **V, int *num, bool ordinato){

	char str[MAXR];
	int p, u, m, trovato;
	bool found=FALSE;

	if (!ordinato){
    	printf("ATTENZIONE!\n"
    		"Prima di ricercare, effettuare l\'ordinamente per codice!\n");
	}

	if (ordinato){
   		printf("Inserisci un codice prodotto:\n");
   		scanf("\n%s",str);

    	p = 0;
    	u = *num -1;
   
	    while(p <= u) {

	   		if( strcmp(V[p]->cod, str) == 0){
	            trovato = p;
	            found = TRUE;
	            break;
	        }

	        m = (p + u) / 2;
	        if( strcmp(V[m]->cod, str) == 0){
	            trovato = m;
	            found = TRUE;
	            break;
	        }

	        if(strcmp(V[m]->cod, str) < 0)
	            p = m + 1;
	        else
	            u = m - 1;
	    }
	}
    m = *num -1;
    
    if (strcmp(V[m]->cod, str) == 0){
    	found = TRUE;
    	trovato = m;
	}

    if (!found && ordinato){
    	printf("Prodotto non trovato!\n"
    		"Ripetere la ricerca...\n");
    }

    if (found && ordinato)
    	printf("* %s %s %s %.2f %d %d\\%d\\%4d \n",
			V[trovato]->cod, V[trovato]->obj, V[trovato]->cat, V[trovato]->price, V[trovato]->qty,
			V[trovato]->dd, V[trovato]->mm, V[trovato]->yyyy);
}

void ricercaNome(prodotto *V, int *num, bool ordinato){

	char stringa[MAXR+1];
	bool found=FALSE;
	int trovato[*num], j=0;

	if (!ordinato){
    	printf("ATTENZIONE!\n"
    		"Prima di ricercare, effettuare l' ordinamento per nome!\n");
	}
	
	if (ordinato){
		printf("Inserire nome da ricercare (anche parziale)\n");
		scanf("\n%s", stringa);

		for (int i = 0; i < *num; i++)
		{
			while(j < *num)
			{
				if (strncmp(stringa, V[i].obj, strlen(stringa))==0)
				{
					found = TRUE;
					trovato[j] = i;
					j++;
				}break;
			}
		}
	}
	if (!found && ordinato)
		printf("Prodotto non trovato!\n");

	else if (found)
	{
		printf("\nProdotto/i trovato/i:\n");
		for(int i=0; i < j; i++)
			printf("* %s %s %s %.2f %d %d\\%d\\%4d \n",
			V[trovato[i]].cod, V[trovato[i]].obj, V[trovato[i]].cat, V[trovato[i]].price, V[trovato[i]].qty,
			V[trovato[i]].dd, V[trovato[i]].mm, V[trovato[i]].yyyy);
	}
}

prodotto* aggiungiObj(prodotto **V, int *num){

	char str1[MAXstr], str2[MAXstr];

	prodotto *P = *V;

	int i = (*num) - 1;

	printf("Inserisci codice prodotto \n< codXXXXXX - nome - categoria - prezzo - quantita\' - data di inserimento >\n");
	scanf("%s %s %s %f %d %d/%d/%4d", P[i].cod, str1, str2, &P[i].price, &P[i].qty, &P[i].dd, &P[i].mm, &P[i].yyyy);
	
	P[i].obj = malloc(strlen(str1) * sizeof(char));
		strcpy(P[i].obj, str1);
	P[i].cat = malloc(strlen(str2) * sizeof(char));
		strcpy(P[i].cat, str2);
	P[i].available = TRUE;

		return P;
}