#include "ingredienti.h"

struct ingredienti_t
{
	linki head;
	linki tail;
};

struct ingrediente_t
{
	char *nome;
	float price;
	float cal;
	linki next;
};

int acquisciIngredienti(linkI *p_ing)
{
	int n_i;

	FILE *fp = fopen("./ingredienti.txt","r");

	(*p_ing)->head = NULL; 
	(*p_ing)->tail = NULL;

	if (fp == NULL)
		exit(-1);

	fscanf(fp,"%d", &n_i);

	for (int i = 0; i < n_i; i++)
	{
		if ((*p_ing)->head == NULL){
			(*p_ing)->head = (*p_ing)->tail = newNode(fp, n_i, NULL);
		}
		else {
			(*p_ing)->tail->next = newNode(fp, n_i, NULL);
			(*p_ing)->tail = (*p_ing)->tail->next;
		}
	}

	return n_i;
}

linki newNode(FILE *fp, int n_i, linki next)
{
	char str[255+1];
	float a, b;
	
	fscanf(fp,"%s%f%f", str, &a, &b);

	linki p = malloc(sizeof *p); 
	
	if (p == NULL)
		return NULL; 

	else { 
		p->nome = strdup(str);  
		p->price = a; 
		p->cal = b;
		p->next = next;
	} 
	return p;
}

void ricercaIngrediente(linkI p_ing)
{
	char search[255+1];
	linki x;

	printf("Inserire ingrediente da ricercare: \n");
	scanf("\n%s", search);

	for (x = p_ing->head; x != NULL; x = x->next)
	{
		if (strncmp(search, x->nome, strlen(search)) == 0)
			printf("\n%s %.2f %.2f", x->nome, x->price, x->cal);
	}
		printf("\n");
}

void stampaLista(linkI p_ing)
{
	linki x;

	printf("\nINGREDIENTI: ");
	printf("\n");
	for (x = p_ing->head; x != NULL; x = x->next)
	{
		printf("%s %.2f %.2f\n", x->nome, x->price, x->cal);
	}printf("\n");
}

void calcolaRicetta(linkI p_ing)
{
	char nome[255+1];
	char search[255+1];
	int time, cnt = 1;
	float przTOT = 0, calTOT = 0, qty;
	bool ciclo = TRUE, trovato = FALSE, inizio = TRUE;

	printf("Inserire nome ricetta:\n");
	scanf("\n%s", nome);

	printf("Inserire tempo di preparazione\n");
	scanf("\n%d", &time);

	printf("Inserisci una serie di ingredienti dall'elenco:\nSpecificare come secondo parametro i GRAMMI\n('STOP' per terminare acquisizione)\n");

	do {
		if (!inizio){
			printf("\ningrediente %d:\n", ++cnt);
		}

		scanf("\n%s", search);
		
		if( (strcmp(search, "STOP\0") == 0) 
			|| (strcmp(search, "stop\0") == 0) )
		{
			ciclo = FALSE;
			break;
		}

		scanf(" %f", &qty);

		inizio = FALSE;
		trovato = FALSE;

		for (linki x = p_ing->head; x != NULL && !trovato; x = x->next){
			if (strncmp(search, x->nome, strlen(search)) == 0){
				przTOT += ((x->price)/1000) * qty;
				calTOT += (x->cal) * qty;
				trovato = TRUE;
			}
		}

	}	while(ciclo);

	printf("\nRICETTA: %s\n", nome);
	printf("PREPARAZIONE: %d minuti\n", time);
	printf("COSTO TOTALE: %.2f euro\n", przTOT);
	printf("APPORTO CALORICO: %.2f calorie\n", calTOT);
}