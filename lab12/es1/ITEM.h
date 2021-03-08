#ifndef _HEADER1
#define _HEADER1 1

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define EXIT_DEATH -1
#define MAXC 30

typedef enum {FALSE, TRUE} bool;

#endif

#ifndef ITEM_H
#define ITEM_H 1

typedef struct item_t* ITEM;
typedef char* KEY;

KEY 	KEYget(ITEM i);
int 	KEYcompare(KEY k1, KEY k2);
int 	GOLDget(ITEM i);
int 	HEALTHget(ITEM i);
int 	MAXworth(ITEM i1, ITEM i2);

ITEM 	ITEMnew(char* n, int i, int j);
ITEM 	ITEMsetvoid();
bool 	ITEMcheckvoid(ITEM i);
void 	ITEMshow(ITEM i);

#endif
