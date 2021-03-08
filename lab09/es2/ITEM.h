#ifndef _HEADER1
#define _HEADER1 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {FALSE, TRUE} bool;

int s;

#endif

#ifndef ITEM_H
#define ITEM_H 1

typedef char* Key;
typedef struct item_t* Item;

struct item_t
{
	char* nomeP;
	float punteggio;
};

Key 	KEYget(Item data);
int 	KEYcompare(Key k1, Key k2);

Item 	ITEMnew();
Item 	ITEMscan();
Item 	ITEMbufferScan(FILE* f);
Item 	ITEMsetvoid();
void 	ITEMdisplay(Item data, int s, FILE *f);
void 	ITEMfree(Item data);

void 	PlayerInsert();
void 	PlayerDelete();
void 	BufferInsert();
void 	saveRanking();
void 	MATCH();


#endif