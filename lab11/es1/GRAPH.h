#include "EDGE.h"
#include "ST.h"

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

GRAPH 	GRAPHinit(int N) ;
void 	GRAPHread(GRAPH G) ;
void 	GRAPHshow(GRAPH G) ;	
void 	GRAPHedgesM(GRAPH G, EDGE *E) ;
void 	GRAPHedgesL(GRAPH G, EDGE *E) ;

void 	ADJMatFromList(GRAPH G) ;
void 	ADJListPrint(GRAPH G) ;
void 	ADJMatPrint(GRAPH G) ;


#endif
