#include "ITEM.h"

#ifndef _HEADER1
#define _HEADER1 1

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXC 10+1

typedef enum {FALSE, TRUE} bool;

#endif

#ifndef PQ_H
#define PQ_H 1

typedef struct pqueue *PQ, *HEAP;

PQ 		PQinit(int n);
ITEM 	PQget(PQ pq);
void 	PQinsert(PQ pq, ITEM i);
void 	PQdisplay(PQ pq);
bool 	PQempty(PQ pq); 
int 	PQsize(PQ pq); 

void 	HEAPify(HEAP h, int i);


#endif