#include "ingredienti.h"

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

LINKI LINKI_fill()
{
	LINKI p_ing = malloc(sizeof(*p_ing));

	int n_i, i = 0;
	float ac, prz;

	FILE *fp = fopen("./ingredienti.txt", "r");
	fscanf(fp, "%d", &n_i);

	p_ing->V = malloc( n_i * sizeof(*(p_ing->V)) );
	p_ing->num_ing = n_i;

	while(fscanf(fp, "%s%f%f", buf, &prz, &ac) == 3 ){
		p_ing->V[i] = malloc(sizeof(*(p_ing->V[i])));
			p_ing->V[i]->nome = strdup(buf);
			p_ing->V[i]->price = prz;
			p_ing->V[i]->cal = ac;
		i++;
	}
	fclose(fp);

	return p_ing;
}

int iFind(LINKI p_ing, char* buf)
{
	for (int i = 0; i < p_ing->num_ing; i++)
		if (!strcmp(buf, p_ing->V[i]->nome))
			return i;

	return -1;
}

void LINKI_show(LINKI p, int s)
{
	linki x;

	if (s == 1){
		printf("Inserisci il nome dell'ingrediente da visualizzare\n");
		scanf("\n%s", buf);

		for(int i = 0; i < p->num_ing; i++){
			if (!strncmp(buf, p->V[i]->nome, strlen(buf))) {
				printf("\ningrediente: %s\n"
				"prezzo al kg: %.2f euro\n"
				"apporto calorico al gr: %.2f cal\n", 
				p->V[i]->nome, p->V[i]->price, p->V[i]->cal);
			}
		}
	}

	if (!s){
		for(int i = 0; i < p->num_ing; i++){
			printf("\ningrediente: %s\n"
				"prezzo al kg: %.2f euro\n"
				"apporto calorico al gr: %.2f cal\n", 
				p->V[i]->nome, p->V[i]->price, p->V[i]->cal);
		}
	}

	return;
}

