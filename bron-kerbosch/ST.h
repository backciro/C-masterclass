#ifndef _HEADER1
#define _HEADER1 1

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXVERTEX 21

typedef enum {FALSE, TRUE} bool;

#endif

#ifndef _ST
#define _ST 1

typedef struct symboltable *ST;

ST 		STinit(int n);
int 	STretrieve(ST t, int i) ;
int 	STsearch(ST t, int k) ;
void 	STinsert(ST t, int i);


#endif