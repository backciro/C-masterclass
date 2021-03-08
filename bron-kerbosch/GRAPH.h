#include "LIST.h"
#include "ST.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXVERTEX 21

typedef struct graph_t* GRAPH;
typedef struct edge_t* EDGE;

GRAPH 	GRAPHinit();
EDGE 	EDGEcreate(int v, int w, int wt);

void 	GRAPHread(GRAPH G) ;
void	GRAPHedges(GRAPH G, EDGE* e) ;
void	insertEDGE(GRAPH G, EDGE e) ;
void	removeEDGE(GRAPH G, EDGE e) ;