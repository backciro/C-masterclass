#include "ingredienti.h"

#ifndef _HEADER1
#define _HEADER1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC 255

typedef enum {FALSE, TRUE} bool;

#endif

#ifndef _RICETTE_H
#define _RICETTE_H

typedef struct ricette_t* LINKR;
typedef struct ricetta_t* linkr;
typedef struct elenchi_t* LINKE;
typedef struct elenco_t* linke;

LINKR 	LINKR_fill(LINKI i);
linkr 	linkr_fill(FILE* f, linkr nx, LINKI i);
LINKE 	LINKE_fill(FILE* f, int n, LINKI i);
linke 	linke_fill(FILE* f, linke x,  LINKI i);
void 	LINKR_show(LINKR p, LINKI i, int s);
void 	LINKR_eval(LINKR p, LINKI i, int s);
void 	linkr_add(LINKR* p, LINKI i);
void 	menu(LINKI i, LINKR* p);


#endif