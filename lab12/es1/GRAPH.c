#include "GRAPH.h"

typedef struct node_t* LINK;

struct node_t
{
	char* nome;
	bool taken;
	int dst;
	LINK next;
};

struct graph_t
{
	int V;
	int E;
	LINK *adj;
	LINK z;
	ST tab;
} ;

struct edge_t
{
	int src;
	int dst;
} ;

LINK NEW(GRAPH G, int v, LINK next)
{
	LINK x = malloc(sizeof(*x));

	if (G != NULL)
		x->nome = strdup(KEYget(STretrieve(G->tab, v)));

	x->taken = FALSE;
	x->dst = v;
	x->next = next;

	return x;
}

GRAPH GRAPHinit(int N)
{
	GRAPH G = malloc(N * sizeof(*G));

	G->V = N;
	G->E = 0;

	G->z = NEW(NULL, -1, NULL);
	G->adj = malloc(G->V * sizeof(LINK));

	for (int v = 0; v < G->V; v++)
		G->adj[v] = G->z;

	G->tab = STinit(G->V);

	return G;
}

void insertEDGE(GRAPH G, EDGE e)
{
	int v = e.src, w = e.dst;

	G->adj[v] = NEW(G, w, G->adj[v]);
	G->adj[w] = NEW(G, v, G->adj[w]);
	G->E++;

	return;
}

void GRAPHread(GRAPH G)
{
	char id_r[MAXC];
	char id_src[MAXC], id_dst[MAXC];
	int id, id_g, id_h;

	FILE* fp = fopen("./tempio.txt", "r"); fscanf(fp, "%*d");

	for (int i = 0; i < G->V; i++)
	{
		fscanf(fp, "%s%d%d", id_r, &id_g, &id_h);
		id = STsearch(G->tab, id_r);

		if (id == -1)
			STinsert(G->tab, ITEMnew(id_r, id_g, id_h));
	}

	//	generazione lista adiacenze
	while (fscanf(fp, "%s%s", id_src, id_dst) == 2)
		insertEDGE(G, EDGEcreate(STsearch(G->tab, id_src), STsearch(G->tab, id_dst)));

	fclose(fp);
	return;
}

void GRAPHshow(GRAPH G)
{
	int v;
	LINK t;

	fprintf(stdout, "\n%d vertices, %d edges \n\n", G->V, G->E);
	for (v = 0; v < G->V; v++)
	{
		fprintf(stdout, "room: %s \n"
		        "gold: %d \t\t", KEYget(STretrieve(G->tab, v)), GOLDget(STretrieve(G->tab, v)));

		for (t = G->adj[v]; t != G->z; t = t->next)
			if (t->dst != -1)
				fprintf(stdout, " -> (%s)(%d)", KEYget(STretrieve(G->tab, t->dst)), t->dst);

		fprintf(stdout, "\nhealth: %d\n\n", HEALTHget(STretrieve(G->tab, v)));
	}
	printf("\n");
	return;
}

EDGE EDGEcreate(int src, int dst)
{
	EDGE e;

	e.src = src;
	e.dst = dst;

	return e;
}

void takeTheWay(GRAPH G, int n, int** sol, int** best_sol)
{
	for (int i = 0; i < n; i++) (*best_sol)[i] = (*sol)[i];
	for (int i = n; i < G->V; i++) (*best_sol)[i] = -1;
}

void pathR(GRAPH G, int v, int w, int* visited, int* life, int* l_l, bool* reachExit, int* curr_gold, int* best_gold, int* adder, int* path, int* best_path)
{
	LINK t;

	if (v == w)
	{
		if ((*curr_gold >= (*best_gold)) && (*life > 0)) {
			(*best_gold) = (*curr_gold);
			(*l_l) = (*life);

			path[(*adder)] = v;

			takeTheWay(G, (*adder) + 1, &path, &best_path);
			(*reachExit) = TRUE;
		}
		return;
	}

	if (*life <= 0)
		return;

	visited[v] = 1;

	for (t = G->adj[v]; t != G->z; t = t->next)
		if (!t->taken && !visited[t->dst])
		{
			t->taken = TRUE;
			*curr_gold += GOLDget(STretrieve(G->tab, v));
			*life -= HEALTHget(STretrieve(G->tab, v));
			path[*adder] = v;
			(*adder)++;

			pathR(G, t->dst, w, visited, life, l_l, reachExit, curr_gold, best_gold, adder, path, best_path);

			(*adder)--;
			*life += HEALTHget(STretrieve(G->tab, v));
			*curr_gold -= GOLDget(STretrieve(G->tab, v));
			t->taken = FALSE;
			visited[t->dst] = 0;
		}

	visited[v] = 0;
}

void GRAPHbestPath(GRAPH G)
{
	int id_start, id_end, adder = 0, life, l_l = 0, curr_gold = 0, best_gold = 0;
	int *visited = calloc(G->V , sizeof(int)), *path = malloc(G->V * sizeof(int)),
	     *best_path = malloc(G->V * sizeof(int));
	char src[MAXC], dst[MAXC]; bool reachExit = FALSE;

	for (int i = 0; i < G->V; i++) { path[i] = -1; best_path[i] = -1;}

	strcpy(src, "Ingresso\0");
	strcpy(dst, "Uscita\0");

	id_start = STsearch(G->tab, src);
	id_end = STsearch(G->tab, dst);

	fprintf(stdout, "\n* L\'AVVENTURIERO ORA E\' PRONTO E NON VEDE L\'ORA DI SCONFIGGERE QUELLA MERDA DI BAHAMUT *\n* INSERISCI IL VALORE DEI SUOI LIFE POINTS PER FAR INIZIARE L\'ESPLORAZIONE *\t LP = ");
	fscanf(stdin, "%d", &life);

	if (id_start != -1 || id_end != -1)
		pathR(G, id_start, id_end, visited, &life, &l_l, &reachExit,
		      &curr_gold, &best_gold, &adder, path, best_path);

	if (!reachExit)
	{
		fprintf(stderr, "\n* L\'AVVENTURIERO CI HA LASCIATO LE PENNE... TROPPO DEBOLE! *\n");
		exit(EXIT_DEATH);
	}

	for (int i = 0; i < G->V; i++)
		if (best_path[i] != -1)
			fprintf(stdout, "\n%s (Oro: %d | Vita creatura: %d)", KEYget(STretrieve(G->tab, best_path[i])), GOLDget(STretrieve(G->tab, best_path[i])), HEALTHget(STretrieve(G->tab, best_path[i])));

	fprintf(stdout, "\n\nOro raccolto: %d\nLife points residui: %d\n", best_gold, l_l);
}
