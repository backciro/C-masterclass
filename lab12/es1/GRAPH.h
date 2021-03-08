#include "ST.h"

#ifndef _HEADER1
#define _HEADER1 1

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define EXIT_DEATH -1
#define MAXC 30

typedef enum {FALSE, TRUE} bool;

#endif

#ifndef H_GRAPH
#define H_GRAPH 1

typedef struct graph_t* GRAPH;
typedef struct edge_t EDGE;

GRAPH 	GRAPHinit(int N) ;
EDGE 	EDGEcreate(int src, int dst);

void 	GRAPHread(GRAPH G) ;
void 	GRAPHshow(GRAPH G) ;	
void 	GRAPHedges(GRAPH G, EDGE *E) ;
void	GRAPHbestPath(GRAPH G) ;

//int 	checkWTpath(ST st, int* path) ;

#endif
