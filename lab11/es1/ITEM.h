#ifndef _HEADER1
#define _HEADER1 1

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXC 30

typedef enum {FALSE, TRUE} bool;

#endif

#ifndef ITEM_H
#define ITEM_H 1

typedef struct item_t* ITEM;
typedef char* KEY;

KEY 	KEYget(ITEM i);
KEY 	NETget(ITEM i);
int 	KEYcompare(KEY k1, KEY k2);

ITEM 	ITEMnew(char* id1, char* id2);
ITEM 	ITEMsetvoid();
bool 	ITEMcheckvoid(ITEM i);
void 	ITEMshow(ITEM i);

#endif
