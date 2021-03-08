#ifndef _HEADER1
#define _HEADER1 1

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXC 30

typedef enum {FALSE, TRUE} bool;

#endif

#ifndef H_GRAPH
#define H_GRAPH 1

typedef struct graph_t* GRAPH;
typedef struct edge_t* EDGE;

GRAPH 	GRAPHinit(int N) ;
EDGE	EDGEcreate(int a, int b, int c) ;

void 	GRAPHread(GRAPH G) ;
void 	GRAPHshow(GRAPH G) ;	
void 	GRAPHmstPrim(GRAPH G) ;
int 	GRAPHedges(GRAPH G, EDGE *E) ;

int 	GETv(EDGE e) ;
int 	GETw(EDGE e) ;
int 	GETwt(EDGE e) ;

void 	quadsort(EDGE* A, int l, int r) ;

#endif
