#ifndef _HEADER1
#define _HEADER1 1

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXC 100

typedef enum {FALSE, TRUE} bool;

#endif

#ifndef ITEM_H
#define ITEM_H 1

typedef struct item_t* ITEM;
typedef int KEY;

KEY 	KEYget(ITEM i);
int 	KEYcompare(KEY k1, KEY k2);

ITEM 	ITEMnew(char* s, int p);
ITEM 	ITEMsetvoid();
void 	ITEMshow(ITEM i);

#endif
