#include "ingredienti.h"
#include "ricette.h"

static char buf[MAXC+1];

struct ingredienti_t // LINKI
{
	linki *V;
	int num_ing;
};

struct ingrediente_t // linki
{
	char *nome;
	float price;
	float cal;
};

struct ricette_t //LINKR
{
	linkr head;
	linkr tail;
};

struct ricetta_t //linkr
{
	char *nome;
	int tempo;
	LINKE elenco;
	linkr next;
};

struct elenchi_t //LINKE
{
	linke head;
	linke tail;
};

struct elenco_t //linke
{
	int indice;
	int grammi;
	linke next;
};

LINKR LINKR_fill(LINKI p_ing)
{
	int n_r;

	LINKR wrap = malloc(sizeof(*wrap));

	FILE *fp = fopen("./ricette.txt","r");

	wrap->head = wrap->tail = NULL;

	fscanf(fp,"%d", &n_r);
	for (int i = 0; i < n_r; i++)
	{
		if(wrap->head == NULL){
			wrap->head = linkr_fill(fp, NULL, p_ing);
			wrap->tail = wrap->head;
		}
		else{
			wrap->tail->next = linkr_fill(fp, NULL, p_ing); 
			wrap->tail = wrap->tail->next;
		}
	}
	fclose(fp);
	return wrap;
}

linkr linkr_fill(FILE *fp, linkr next, LINKI p_ing)
{
	int n_ing, time;

	if(fp != NULL){
		fscanf(fp,"%s%d%d", buf, &time, &n_ing);
	}

	else {
		printf("Inserisci nome, tempo e numero ingredienti della ricetta: \n");
		scanf("\n%s%d%d", buf, &time, &n_ing);
	}

	linkr ric = malloc(sizeof(*ric));

	ric->nome = strdup(buf);
	ric->tempo = time;
	ric->next = next;

	ric->elenco = LINKE_fill(fp, n_ing, p_ing);

	return ric;
}

LINKE LINKE_fill(FILE *fp, int n_ing, LINKI p_ing)
{
	LINKE wrapper = malloc(sizeof(*wrapper));

	wrapper->head = wrapper->tail = NULL;

	for (int i = 0; i < n_ing; i++)
	{
		if(wrapper->head == NULL){
			wrapper->head = linke_fill(fp, NULL, p_ing);
			wrapper->tail = wrapper->head;
		}		
		else{
			wrapper->tail->next = linke_fill(fp, NULL, p_ing); 
			wrapper->tail = wrapper->tail->next;
		}
	}

	return wrapper;
}

linke linke_fill(FILE *fp, linke next, LINKI p_ing)
{
	int gr;
	int index;

	if (fp == NULL){
		printf("\nInserisci INGREDIENTE e PESO in grammi\n"
		"(Gli ingredienti devono essere presenti nell\'elenco)\n");
		scanf("\n%s%d", buf, &gr);
		}

	else fscanf(fp, "%s%d", buf, &gr);
		
	index = iFind(p_ing, buf);

	linke n = malloc(sizeof(*n));

	n->indice = index;
	n->grammi = gr;
	n->next = next;

	return n;
}

void LINKR_show(LINKR p_ric, LINKI p_ing, int scelta)
{
	linkr x;
	linke e;

	if (scelta == 1){
		printf("Inserisci il nome (anche parziale) della ricetta da cercare:\n");
		scanf("\n%s", buf);
		printf("\n");

		for (x = p_ric->head; x != NULL; x = x->next){
			if (strncmp(buf, x->nome, strlen(buf)) == 0){
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
		scanf("\n%s", buf);

		for (x = p_ric->head; x != NULL; x = x->next){
			for (e = x->elenco->head; e != NULL; e = e->next){
				if (strncmp(buf, p_ing->V[e->indice]->nome, strlen(buf)) == 0){
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

void LINKR_eval(LINKR p_ric, LINKI p_ing, int scelta)
{
	float tot;
	int i;

	linkr r;
	linke e;

	if (scelta){
		printf("Inserisci il nome di una ricetta per conoscere il prezzo:\n");
		scanf("\n%s", buf);
		tot = 0.0;

		for (r = p_ric->head; r != NULL; r = r->next){
			if (strncmp(buf, r->nome, strlen(buf)) == 0){
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
		scanf("\n%s", buf);
		tot = 0.0;

		for (r = p_ric->head; r != NULL; r = r->next){
			if (strncmp(buf, r->nome, strlen(buf)) == 0){
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

void linkr_add(LINKR* p_ric, LINKI p_ing)
{
	linkr newR = malloc(sizeof(*newR));

	newR = linkr_fill(NULL, NULL, p_ing);

	(*p_ric)->tail->next =  newR;
	(*p_ric)->tail = (*p_ric)->tail->next;

	return;
}
