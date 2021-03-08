#ifndef _HEADER1
#define _HEADER1 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DAY 1440

typedef enum {FALSE, TRUE} bool;

#endif

#ifndef ITEM_H
#define ITEM_H 1

typedef struct item_t* ITEM;
typedef int KEY;

typedef struct list_skilift* LIST;

struct item_t
{
	KEY cardID;
	LIST skiUsed;
};

struct list_skilift
{
	char* skiliftID;
	int last_use;
	LIST next;
};

KEY KEYget(ITEM i);
int KEYcompare(KEY k1, KEY k2);

ITEM ITEMsetvoid();
ITEM ITEMscan();
ITEM ITEMnew();

LIST LISTnew();
void LISTupdate(ITEM i);


#endif
