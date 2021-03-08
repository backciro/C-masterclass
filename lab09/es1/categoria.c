//*
// l'idea era quella di trovare la migliore soluzione per ogni categoria e
// di inserirla in una matrice best contenente solo le migliori soluzioni. 
// Ho trovato problemi a "smarcare" la difficoltà quando invoco 'troppoDifficile()'.
// Infatti il programma solo per alcuni valori di difficoltà, e non in maniera ottimale.
//*
#include "categoria.h"

wr allocaWrapper()
{
	int numcat;

	wr w = malloc(sizeof(*w));

	FILE *fp = fopen("/Users/Mattew/github/labapa_C/lab9/es1/elementi.txt", "r");
	fscanf(fp, "%d", &numcat);

	w->num_cat = numcat;
	w->cat = allocaCategorie(fp, numcat);

	return w;
}

linkc allocaCategorie(FILE *fp, int numcat)
{
	int min, max, numes;
	char str[100];

	linkc cat = malloc(numcat * sizeof(*cat));

	for (int i = 0; i < numcat; i++)
	{
		fscanf(fp, "%s%d%d%d", str, &numes, &min, &max);

		(cat[i]).nome = strdup(str);
		(cat[i]).num_es = numes;
		(cat[i]).min = min;
		(cat[i]).max = max;
		(cat[i]).esercizi = allocaEsercizi(fp, numes);
	}

	return cat;
}

linkx allocaEsercizi(FILE *fp, int numes)
{
	char str[100];
	float p, d;

	linkx ex = malloc(numes * sizeof(*ex));

	for (int i = 0; i < numes; i++) {
		fscanf(fp, "%s%f%f", str, &p, &d);

		(ex[i]).nome_es = strdup(str);
		(ex[i]).punt = p;
		(ex[i]).diff = d;
	}

	return ex;
}

void stampaS(wr wrap)
{
	printf("\n");
	for (int i = 0; i < wrap->num_cat; i++) {
		printf("%s %d %d %d\n", wrap->cat[i].nome, wrap->cat[i].num_es, wrap->cat[i].min, wrap->cat[i].max);

		for (int j = 0; j < wrap->cat[i].num_es; j++)
		{
			printf("\t%s %.2f %.2f\n", wrap->cat[i].esercizi[j].nome_es, wrap->cat[i].esercizi[j].punt, wrap->cat[i].esercizi[j].diff);
		}
		printf("\n");
	}
}

void stampaB(int **best, wr w)
{
	printf("\n");

	for (int i = 0; i < w->num_cat; i++) {
		for (int j = 0; j < w->cat[i].num_es; j++) {
			if (best[i][j] == 1)
				printf("%s \n", w->cat[i].esercizi[j].nome_es);
			if (best[i][j] > 1)
				printf("%d X %s \n", best[i][j], w->cat[i].esercizi[j].nome_es);
		} printf("\n");
	}
}

void callRec(wr wrap)
{
	int **best;
	int *sol;
	float punt = 0.0, diff = 0.0;
	float Tpunt = 0.0, Tdiff = 0.0;
	int i, D;
	float h;

	printf("scegli un GRADO di difficolta\':\n");
	scanf("\n%d", &D);

	sol = malloc((wrap->num_cat) * sizeof(*sol));

	best = malloc((wrap->num_cat) * sizeof(*best));
	for (int i = 0; i < (wrap->num_cat); i++)
		best[i] = malloc((wrap->cat[i].num_es) * sizeof(*best[i]));

	while(Tdiff <= D && i < wrap->num_cat) {
		punt = 0.0, diff = 0.0;
		Rec(wrap, 0, best, sol, wrap->cat[i].num_es, i, D, &punt, &diff);
		Tpunt += punt; Tdiff += diff;

		if (Tdiff > D) {
			h = punt;
			Tpunt -= punt; Tdiff -= diff;

			//azzera best
			for (int j = 0; j < wrap->cat[i].num_es; j++) {
				best[i][j] = 0;
			}

			troppoDifficile(wrap, best, sol, wrap->cat[i].num_es, i, &punt, &diff, h, D, Tdiff);
			Tpunt += punt; Tdiff += diff;
			i = wrap->num_cat;
			break;
		}
		i++;
	}

	stampaB(best, wrap);

	printf("Totale punti: %.2f \n", Tpunt);
	printf("Totale difficolta\': %.2f \n", Tdiff);
}

void troppoDifficile(wr wrap, int** best, int* sol, int i, int k, float* punt, float* diff, float dq, int DT, float Tdiff)
{
	(*punt) = (*diff) = 0;
	Rec(wrap, 0, best, sol, k, i, (Tdiff - dq), punt, diff);
}

void Rec(wr wrap, int pos, int** best, int *sol, int k, int l, int D, float* pun, float* dif)
{
	int i;

	if (pos >= k) {
		if (check(wrap, best, sol, k, l, D, pun, dif))
		{}
		return;
	}

	for (i = 0; i < k; i++) {
		sol[pos] = i;
		Rec(wrap, pos + 1, best, sol, k, l, D, pun, dif);
	}

	return;
}

bool check(wr wrap, int** best, int* sol, int k, int l, int D, float* punt, float* diff)
{
	int contatore;

	int min = wrap->cat[l].min;
	int max = wrap->cat[l].max;

	float p_curr, d_curr;

	contatore = 0;

	p_curr = 0.0, d_curr = 0.0;

	for (int i = 0; i < k; i++)
		contatore += sol[i];

	if ( (contatore < min) || (contatore > max) )
		return FALSE;

	if(l >= 5)
		return FALSE;

	for (int i = 0; i < k; i++)
		if (sol[i] > 0)
			d_curr += ((sol[i]) * (wrap->cat[l].esercizi[i].diff));

	if ((d_curr) > D/3.4)
		return FALSE;

	for (int i = 0; i < k; i++)
	{
		if (sol[i] > 0)
		{
			if (sol[i] == 1)
				p_curr += (wrap->cat[l].esercizi[i].punt);

			if (sol[i] >= 2)
				p_curr += (wrap->cat[l].esercizi[i].punt) + ((wrap->cat[l].esercizi[i].punt) / 2);
		}
	}

	if (p_curr > (*punt)) {
		bestCheck(best, sol, k, l, D, punt, diff, p_curr, d_curr);
		return TRUE;
	}

	return FALSE;
}

void bestCheck(int** best, int* sol, int k, int l, int D, float* punt, float* diff, float p_curr, float d_curr)
{
	for (int i = 0; i < k; i++)
		(best[l][i]) = sol[i];

	(*diff) = d_curr;
	(*punt) = p_curr;
}
