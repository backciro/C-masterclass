#include "GRAPH.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXVERTEX 21

int 	serial (GRAPH G) ;
void 	bkv2 (GRAPH G, LIST compsub, int* oldSet, int ne, int ce) ; 