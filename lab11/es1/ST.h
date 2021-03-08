#include "ITEM.h"

#ifndef _HEADER1
#define _HEADER1 1

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXC 30

typedef enum {FALSE, TRUE} bool;

#endif

#ifndef _ST
#define _ST 1

typedef struct symboltable *ST;

ST 		STinit(int n);
ITEM 	STretrieve(ST t, int i) ;
int 	STsearch(ST t, KEY k) ;
int 	STcount(ST t) ;
void 	STinsert(ST t, ITEM i);
void 	STdelete(ST t, KEY k) ; 
void 	STdisplay(ST t) ;
bool 	STempty(ST t) ;


#endif
