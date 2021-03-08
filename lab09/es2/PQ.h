#include "ITEM.h"

#ifndef _HEADER1
#define _HEADER1 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {FALSE, TRUE} bool;

int s;
char str[50];

#endif

#ifndef PQ_H
#define PQ_H 1

typedef struct PQnode* link;

struct PQnode
{
	Item player;
	link next;
};

void 	PQinit();
bool 	PQempty();
Item 	PQextractLess();
Item 	PQextract2Less(Item data);
void 	PQinsert(FILE* fp);
void 	PQdisplay(FILE *fp, int s);
void 	PQchange(Item data);
void 	PQdelete(Item data);

link 	newNode(link next, FILE *fp);

#endif