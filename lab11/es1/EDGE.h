#ifndef _HEADER1
#define _HEADER1 1

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXC 30

typedef enum {FALSE, TRUE} bool;

#endif

#ifndef H_EDGE
#define H_EDGE 1

typedef struct 
{ 
	int v; 
	int w; 
	int wt; 
} EDGE;

EDGE EDGEcreate(int v, int w, int wt);


#endif
