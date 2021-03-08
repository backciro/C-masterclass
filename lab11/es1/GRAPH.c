#include "GRAPH.h"

typedef struct GRAPHnode* LINK;

struct GRAPHnode
{
	int v;
	int wt;
	LINK next;
};

struct graph_t
{
	int V;
	int E;
	int **adjM;
	LINK *adjL;
	LINK z;
	ST tab;
};

LINK NEW(int v, int wt, LINK next)
{
	LINK x = malloc(sizeof (*x));
	x->v = v;
	x->wt = wt;
	x->next = next;

	return x;
}

int** MATRIXint(int r, int c, int val)
{
	int i, j;
	int **t = malloc(r * sizeof(int *));

	for (i = 0; i < r; i++)
		t[i] = malloc(c * sizeof(int));

	for (i = 0; i < r; i++)
		for (j = 0; j < c; j++)
			t[i][j] = val;

	return t;
}

GRAPH GRAPHinit(int V)
{
	int v;
	GRAPH G = malloc(sizeof(*G));

	if (G == NULL)
		return NULL;

	G->V = V;
	G->E = 0;

	G->adjM = MATRIXint(V, V, 0);
	G->tab = STinit(V);

	G->z = NEW(-1, -1, NULL);
	G->adjL = malloc(G->V * sizeof(LINK));

	for (v = 0; v < G->V; v++)
		G->adjL[v] = G->z;

	if (G->tab == NULL)
		return NULL;

	return G;
}

void insertEL(GRAPH G, EDGE e)
{
	int v = e.v, w = e.w, wt = e.wt;
	G->adjL[v] = NEW(w, wt, G->adjL[v]);
	G->adjL[w] = NEW(v, wt, G->adjL[w]);
	G->E++;

	return;
}

void removeEL(GRAPH G, EDGE e)
{
	int v = e.v, w = e.w;

	LINK x;

	if (G->adjL[v]->v == w) {
		G->adjL[v] = G->adjL[v]->next;
		G->E--;
	}
	else
		for (x = G->adjL[v]; x != G->z; x = x->next)
			if (x->next->v == w) {
				x->next = x->next->next;
				G->E--;
			}

	if (G->adjL[w]->v == v)
		G->adjL[w] = G->adjL[w]->next;
	else
		for (x = G->adjL[w]; x != G->z; x = x->next)
			if (x->next->v == v) x->next = x->next->next;

	return;
}

void insertEM(GRAPH G, EDGE e)
{
	int v = e.v, w = e.w, wt = e.wt;

	if (G->adjM[v][w] == 0)
		G->E++;

	G->adjM[v][w] = wt; G->adjM[w][v] = wt;
}

void removeEM(GRAPH G, EDGE e)
{
	int v = e.v, w = e.w;

	if (G->adjM[v][w] != 0)
		G->E--;

	G->adjM[v][w] = 0; G->adjM[w][v] = 0;
	return;
}

void GRAPHread(GRAPH G)
{
	char id_e[MAXC], id_n[MAXC];
	char id_e1[MAXC], id_e2[MAXC];
	int id, V;
	FILE* fp = fopen("./grafo.txt", "r");
	if (fp == NULL) exit(-1);
	fscanf(fp, "%d", &V);

	for (int i = 0; i < G->V; i++)
	{
		fscanf(fp, "%s%s", id_e, id_n);
		id = STsearch(G->tab, id_e);

		if (id == -1)
			STinsert(G->tab, ITEMnew(id_e, id_n));
	}

//	generazione lista adiacenze
	while (fscanf(fp, "%s%s%d", id_e1, id_e2, &id) == 3)
		insertEL(G, EDGEcreate(STsearch(G->tab, id_e1), STsearch(G->tab, id_e2), id));

	fclose(fp);
	return;
}

void ADJMatFromList(GRAPH G)
{
	for (int v = 0; v < G->V; v++) {
		for (LINK j = G->adjL[v]; j != G->z; j = j->next) {
			insertEM(G, EDGEcreate(v, j->v, j->wt));
		}
	}
	return;
}

void GRAPHedgesL(GRAPH G, EDGE *e)
{
	int v, E = 0;
	LINK t;

	for (v = 0; v < G->V; v++)
		for (t = G->adjL[v]; t != G->z; t = t->next)
			if (v < t->v)
				e[E++] = EDGEcreate(v, t->v, G->adjL[t->v]->wt);
	return;
}

void GRAPHedgesM(GRAPH G, EDGE *e)
{
	int v, w, E = 0;
	for (v = 0; v < G->V; v++)
		for (w = v + 1; w < G->V; w++)
			if (G->adjM[v][w] != 0)
				e[E++] = EDGEcreate(v, w, G->adjM[v][w]);
	return;
}

void GRAPHshow(GRAPH G)
{
	int v;
	LINK t;

	fprintf(stdout, "\n%d vertices, %d edges \n\n", G->V, G->E);

	for (v = 0; v < G->V; v++)
	{
		fprintf(stdout, "node: %s\nnetw: %s\t", KEYget(STretrieve(G->tab, v)), NETget(STretrieve(G->tab, v)));

		for (t = G->adjL[v]; t != G->z; t = t->next)
			fprintf(stdout, " -> (%s %d)", KEYget(STretrieve(G->tab, t->v)), t->wt);
		fprintf(stdout, "\nid: n%d\n", v + 1);
		fprintf(stdout, "\n");
	}
	printf("\n");
	return;
}

void ADJListPrint(GRAPH G)
{
	fprintf(stdout, "\nLISTA ADIACENZE: \n");
	for (int i = 0; i < G->V; i++) {
		fprintf(stdout, "(node: %4s)\t\t->\t", KEYget(STretrieve(G->tab, i)));
		for (LINK j = G->adjL[i]; j != G->z; j = j->next)
			printf("%d (id: n%d)\t", j->wt, j->v + 1);
		fprintf(stdout, "\n\n");
	}
}

void ADJMatPrint(GRAPH G)
{
	fprintf(stdout, "\nMATRICE ADIACENZE: ");

	for (int i = 0; i < G->V; i++)
		fprintf(stdout, "\t%c", KEYget(STretrieve(G->tab, i))[0]);

	fprintf(stdout, "\n\n\n");

	for (int i = 0; i < G->V; i++) {
		fprintf(stdout, "(node: %s)\t\t", KEYget(STretrieve(G->tab, i)));
		for (int j = 0; j != G->V; j++)
			printf("%d\t", G->adjM[i][j]);
		fprintf(stdout, "\n\n");
	}
	return;
}