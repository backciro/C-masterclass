#include "header.h"
#include "GRAPH.h"

struct graph_t
{
	int V;
	int E;
	int** matrix;
	EDGE* e;
	ST tab;
};

struct edge_t
{
	int src;
	int dst;
	int wt;
};

int** MATRIXinit(int N)
{
	int** m = malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
		m[i] = malloc(N * sizeof(int));

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			m[i][j] = -1;

	return m;
}

GRAPH GRAPHinit()
{
	GRAPH G = malloc(sizeof(GRAPH));
`
	G->matrix = MATRIXinit(MAXVERTEX);

	G->V = MAXVERTEX;
	G->E = 0;

	return G;
}

EDGE EDGEcreate(int v, int w, int wt)
{
	EDGE e = malloc(sizeof(*e));

	e->src = v;
	e->dst = w;
	e->wt = wt;

	return e;
}

void GRAPHread(GRAPH G)
{
	int id1, id2, wt;

	FILE* fp = fopen("./vertex.txt", "r");

	while (fscanf(fp, "%d%d%d", &id1, &id2, &wt) == 3)
		insertEDGE(G, EDGEcreate(id1, id2, wt));


	GRAPHedges(G, G->e);
}

void GRAPHedges(GRAPH G, EDGE* e)
{
	int v, w, E = 0;

	for (v = 0; v < G->V; v++)
		for (w = v + 1; w < G->V; w++)
			if (G->matrix[v][w] != -1)
				e[E++] = EDGEcreate(v, w, G->matrix[v][w]);
}

void insertEDGE(GRAPH G, EDGE e)
{
	int v, w, wt;

	v = e->src;
	w = e->dst;
	wt = e->wt;

	G->matrix[v][w] = wt;
	G->matrix[w][v] = wt;

	G->E += 1;
}

int serial (GRAPH G)
{
	int i;
	int* all = (int *) malloc(G->V * sizeof (int));

	LIST compsub = LIST_init();

	for (i = 0; i < G->V; i++)
		all[i] = i;

	bkv2(G, compsub, all, 0, G->V);

	free(all);
	return LIST_clear(compsub);
}

// recursive function version 2 of Bron-Kerbosch algorithm
void bkv2 (GRAPH G, LIST compsub, int* oldSet, int ne, int ce)
{
	int* newSet = (int *) malloc(ce * sizeof (int));
	int nod, fixp;
	int newne, newce, i, j, count, pos, p, s, sel, minnod;

	minnod = ce;
	nod = ne;

// Determine each counter value and look for minimum
	for ( i = 0 ; i < ce && minnod != 0; i++)
	{
		p = oldSet[i];
		count = 0;

// Count disconnections
		for (j = ne; j < ce && count < minnod; j++)
			if ( (G->matrix[p][oldSet[j]]) != -1 ) {
				count++;
// Save position of potential candidate
				pos = j;
			}

// Test new minimum
		if (count < minnod) {
			fixp = p;
			minnod = count;
			if (i < ne)
				s = pos;
			else {
				s = i;
				// pre-increment
				nod = 1;
			}
		}
	}
// If fixed point initially chosen from candidates then
// number of diconnections will be preincreased by one

// Backtrackcycle
	for (nod = minnod + nod; nod >= 1; nod--)
	{
// Interchange
		p = oldSet[s];
		oldSet[s] = oldSet[ne];
		sel = oldSet[ne] = p;
// Fill new set "not"
		newne = 0;
		for ( i = 0 ; i < ne ; i++)
			if (G->matrix[sel][oldSet[i]] != -1)
				newSet[newne++] = oldSet[i];

// Fill new set "cand"
		newce = newne;
		for (i = ne + 1; i < ce; i++)
			if (sel != -1 && oldSet[i] != -1)
				if (G->matrix[sel][oldSet[i]] != -1)
					newSet[newce++] = oldSet[i];

// Add to compsub
		LIST_add (compsub, sel);

		if (newce == 0) {
// found a max clique
			LIST_print(compsub);
		}

		else if (newne < newce)
			bkv2(G, compsub, newSet, newne, newce);

// Remove from compsub
		LIST_remove(compsub);

// Add to "not"
		ne++;
		if (nod > 1)
// Select a candidate disconnected to the fixed point
			for (s = ne ; G->matrix[fixp][oldSet[s]] ; s++)
				;
// nothing but finding s

	} /* Backtrackcycle */
	free (newSet);
}