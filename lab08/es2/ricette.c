#include "ingredienti.h"
#include "ricette.h"

LINKR acquisciRicette(LINKI p_ing)
{
	int n_r;
	int n_ing, time;

	LINKR wrap = malloc(sizeof(*wrap));

	FILE *fp = fopen("./ricette.txt","r");

	wrap->head = wrap->tail = NULL;

	fscanf(fp,"%d", &n_r);
	for (int i = 0; i < n_r; i++)
	{
		fscanf(fp,"%s%d%d",str, &time, &n_ing);

		if(wrap->head == NULL){
			wrap->head = nuovaRicetta(fp, NULL, str, time, n_ing, p_ing);
			wrap->tail = wrap->head;
		}
		else{
			wrap->tail->next = nuovaRicetta(fp, NULL, str, time, n_ing, p_ing); 
			wrap->tail = wrap->tail->next;
		}
	}
	fclose(fp);
	return wrap;
}

linkr nuovaRicetta(FILE *fp, linkr next, char* nome, int time, int n_ing, LINKI p_ing)
{
	linkr ric = malloc(sizeof(*ric));

	ric->nome = strdup(nome);
	ric->tempo = time;
	ric->next = next;

	ric->elenco = nuovoElenco(fp, n_ing, p_ing);

	return ric;
}

LINKE nuovoElenco(FILE *fp, int n_ing, LINKI p_ing)
{
	int gr;
	int index;
	LINKE wrapper = malloc(sizeof(*wrapper));

	wrapper->head = wrapper->tail = NULL;

	for (int i = 0; i < n_ing; i++)
	{
		if (fp == NULL){
			printf("\nInserisci INGREDIENTE e PESO in grammi\n"
				"(Gli ingredienti devono essere presenti nell\'elenco)\n");
			scanf("\n%s%d", str, &gr);
		}

		else fscanf(fp, "%s%d", str, &gr);
		
		index = cercaIndice(str, p_ing);

		if (index >= 0){
			if(wrapper->head == NULL){
				wrapper->head = nuovoNodo(index, gr, NULL);
				wrapper->tail = wrapper->head;
			}		
			else{
				wrapper->tail->next = nuovoNodo(index, gr, NULL); 
				wrapper->tail = wrapper->tail->next;
			}
		}
	}

	return wrapper;
}

linke nuovoNodo(int ind, int gr, linke next)
{
	linke n = malloc(sizeof(*n));

	n->indice = ind;
	n->grammi = gr;
	n->next = next;

	return n;
}

void stampaRicette(LINKR p_ric, LINKI p_ing, int scelta)
{
	linkr x;
	linke e;

	if (scelta == 1){
		printf("Inserisci il nome (anche parziale) della ricetta da cercare:\n");
		scanf("\n%s", str);
		printf("\n");

		for (x = p_ric->head; x != NULL; x = x->next){
			if (strncmp(str, x->nome, strlen(str)) == 0){
				printf("\n** %s / tempo: %d minuti **\n", x->nome, x->tempo);
				printf("ingredienti:\n");
				
				for(e = x->elenco->head; e != NULL; e = e->next){
					if(strlen(p_ing->V[e->indice]->nome) > 4 && strlen(p_ing->V[e->indice]->nome) < 12)
					printf("  %s \t\t gr: %d\n", p_ing->V[e->indice]->nome, e->grammi);
					if(strlen(p_ing->V[e->indice]->nome) <= 4)
					printf("  %s \t\t\t gr: %d\n", p_ing->V[e->indice]->nome, e->grammi);
					if(strlen(p_ing->V[e->indice]->nome) > 12)
					printf("  %s \t gr: %d\n", p_ing->V[e->indice]->nome, e->grammi);
				}
			}
		}
	}

	if (scelta == 2){
		printf("Inserisci un ingrediente come filtro: \n");
		scanf("\n%s", str);

		for (x = p_ric->head; x != NULL; x = x->next){
			for (e = x->elenco->head; e != NULL; e = e->next){
				if (strncmp(str, p_ing->V[e->indice]->nome, strlen(str)) == 0){
					printf("\n** %s / tempo: %d minuti **\n", x->nome, x->tempo);
					printf("ingredienti:\n");
			
					for(linke ed = x->elenco->head; ed != NULL; ed = ed->next){
						if(strlen(p_ing->V[ed->indice]->nome) > 4 && strlen(p_ing->V[ed->indice]->nome) < 12)
						printf("  %s \t\t gr: %d\n", p_ing->V[ed->indice]->nome, ed->grammi);
						if(strlen(p_ing->V[ed->indice]->nome) <= 4)
						printf("  %s \t\t\t gr: %d\n", p_ing->V[ed->indice]->nome, ed->grammi);
						if(strlen(p_ing->V[ed->indice]->nome) > 12)
						printf("  %s \t gr: %d\n", p_ing->V[ed->indice]->nome, ed->grammi);
					}
				}
			}
		}
	}

	if (!scelta){
		for (x = p_ric->head; x != NULL; x = x->next){

			printf("\n** %s / tempo: %d minuti **\n", x->nome, x->tempo);
			printf("ingredienti:\n");
			
			for(e = x->elenco->head; e != NULL; e = e->next){
				if(strlen(p_ing->V[e->indice]->nome) > 4 && strlen(p_ing->V[e->indice]->nome) < 12)
				printf("  %s \t\t gr: %d\n", p_ing->V[e->indice]->nome, e->grammi);
				if(strlen(p_ing->V[e->indice]->nome) <= 4)
				printf("  %s \t\t\t gr: %d\n", p_ing->V[e->indice]->nome, e->grammi);
				if(strlen(p_ing->V[e->indice]->nome) > 12)
				printf("  %s \t gr: %d\n", p_ing->V[e->indice]->nome, e->grammi);
			}
		}
	}
	return;
}

void calcolaRicetta(LINKR p_ric, LINKI p_ing, int scelta)
{
	float tot;
	int i;

	linkr r;
	linke e;

	if (scelta){
		printf("Inserisci il nome di una ricetta per conoscere il prezzo:\n");
		scanf("\n%s", str);
		tot = 0.0;

		for (r = p_ric->head; r != NULL; r = r->next){
			if (strncmp(str, r->nome, strlen(str)) == 0){
				tot = 0.0;
				for(e = r->elenco->head; e != NULL; e = e->next){
					tot += (((p_ing->V[e->indice]->price) / 1000) * e->grammi);
				}

				printf("\n La ricetta '%s' ha un costo totale di: %.2f euro\n", r->nome, tot);
			}	
		}
	}


	if (!scelta){
		printf("Inserisci il nome di una ricetta per conoscere l'apporto calorico:\n");
		scanf("\n%s", str);
		tot = 0.0;

		for (r = p_ric->head; r != NULL; r = r->next){
			if (strncmp(str, r->nome, strlen(str)) == 0){
				tot = 0.0;
				for(e = r->elenco->head; e != NULL; e = e->next){
					tot += ((p_ing->V[e->indice]->cal) * e->grammi);
				}

				printf("\n La ricetta '%s' ha un apporto calorico totale di: %.2f cal\n", r->nome, tot);
			}	
		}
	}

	return;
}

void newRicetta(LINKR* p_ric, LINKI p_ing)
{
	linkr newR = malloc(sizeof(*newR));
	int time, n_ing;

	printf("Inserisci nome, tempo e numero ingredienti della ricetta: \n");
	scanf("\n%s%d%d", str, &time, &n_ing);

	newR = nuovaRicetta(NULL, NULL, str, time, n_ing, p_ing);

	(*p_ric)->tail->next =  newR;
	(*p_ric)->tail = (*p_ric)->tail->next;

	return;
}