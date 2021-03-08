#include "GRAPH.h"
#include "ST.h"

int N, M, K, U, minWT = -5;

typedef struct GRAPHnode* LINK;

typedef struct data_t* DATA;

struct GRAPHnode
{
	int v;
	int wt;
	LINK next;
};

struct data_t
{
	int N;
	int M;
	int K;
	int U;
	int E;
};

struct graph_t
{
	int **adj;
	EDGE *e;
	DATA D;
	ST tab;
};

struct edge_t
{
	int v;
	int w;
	int wt;
} ;

int GETv(EDGE e) { return e->v; }
int GETw(EDGE e) { return e->w; }
int GETwt(EDGE e) { return e->wt; }

int contaArchi(GRAPH G)
{
	int res = 0;

	for (int i = G->D->N - 1; i >= 0; i--)
		res += i;

	return res;
}

EDGE EDGEcreate(int v, int w, int wt)
{
	EDGE e = malloc(sizeof(*e));

	e->v = v;
	e->w = w;
	e->wt = wt;

	return e;
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
	GRAPH G = malloc(sizeof(*G));

	if (G == NULL)
		return NULL;

	G->D = malloc(sizeof(*G->D));
	G->D->N = V;

	G->e = malloc(contaArchi(G) * sizeof(EDGE));

	G->D->M = 0;
	G->D->K = 0;
	G->D->U = 0;
	G->D->E = 0;

	G->adj = MATRIXint(V, V, 0);
	G->tab = STinit(V);

	if (G->tab == NULL)
		return NULL;

	return G;
}

void GRAPHread(GRAPH G)
{
	FILE *fin = fopen("./amici.txt", "r");

	if (fin == NULL)
		exit(-1);

	fscanf(fin, "%d%d%d%d", &N, &M, &K, &U);

	G->D->M = M;
	G->D->K = K;
	G->D->U = U;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			fscanf(fin, "%d", &G->adj[i][j]);

	G->D->E = GRAPHedges(G, G->e);

	fclose(fin);
	return;
}

int GRAPHedges(GRAPH G, EDGE *a)
{
	int v, w, E = 0;

	for (v = 0; v < G->D->N; v++)
		for (w = v + 1; w < G->D->N; w++)
			if (G->adj[v][w] != 0)
				a[E++] = EDGEcreate(v, w, G->adj[v][w]);

	return E;
}

int siParte(GRAPH G, EDGE* final)
{
	int numMacc = G->D->M, numPosti = G->D->K, handler = 0, cntM = 0, cntP = 0;
	float cntHumor = 0, humorTot = 0;
	int* mark = calloc(G->D->N , sizeof(int));

	while (cntM < numMacc)
	{
		fprintf(stdout, "Smart #%d:\n", cntM + 1); cntP = 0;
		cntHumor = 0;

		while (cntP < numPosti)
		{
			if (mark[final[handler]->v] == 0 && mark[final[handler]->w] == 0)
			{

				fprintf(stdout, "%s  %s\n", KEYget(STretrieve(G->tab, final[handler]->v)), KEYget(STretrieve(G->tab, final[handler]->w)));
				cntHumor += final[handler]->wt;

				mark[final[handler]->v] = 1;
				mark[final[handler]->w] = 1;
				cntP += 2;
			}
			handler += 1;
		}

		humorTot += cntHumor;
		fprintf(stdout, "(umore della Smart: %.1f)\n\n", cntHumor);
		cntM += 1;
	}

	return humorTot;
}

void mstV(GRAPH G, int* st, int* wt)
{
	int v, w, add, max, start, *fr = malloc(G->D->N * sizeof(int));

	for ( v = 0; v < G->D->N; v++)
	{ st[v] = -1; fr[v] = v; st[0] = 0; wt[0] = 0; }

	wt[v] = minWT;
	wt[G->D->N] = minWT;
	start = 0;

	for ( add = 0, max = 0; max != G->D->N; add++) {
		v = max;
		st[max] = fr[max];

		for (w = 0, max = G->D->N ; w < G->D->N; w++) {
			if (st[w] == -1) {
				if (G->adj[v][w] > wt[w])
				{ wt[w] = G->adj[v][w]; fr[w] = v; }

				if (wt[w] > wt[max])
					max = w;
			}
		}
	}
}

void GRAPHmstPrim(GRAPH G)
{
	int v, *st, *wt, adder = 0;
	float humor;
	EDGE* final = malloc(G->D->N * sizeof(EDGE));

	st = malloc(G->D->N * sizeof(int));
	wt = malloc((G->D->N + 1) * sizeof(int));

	mstV(G, st, wt);

	for (v = 0; v < G->D->N; v++)
	{ if (st[v] != v) final[adder++] = EDGEcreate(st[v], v, G->adj[st[v]][v]); }

	humor = siParte(G, final);

	fprintf(stdout, "umore medio totale delle Smart ForTwo in comitiva: %.1f\n\n", humor / (G->D->N / 2));

}

void quadsort(EDGE* A, int l, int r)
{
	int i, j, flag;
	EDGE temp = malloc(sizeof(*temp));

	flag = 1;

	for (i = l; i <= r && flag == 1; i++) {
		flag = 0;
		for (j = l; j < (r - i) - 1; j++)
			if (A[j]->wt < A[j + 1]->wt)
			{
				flag = 1;
				temp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = temp;
			}
	}

	return;
}