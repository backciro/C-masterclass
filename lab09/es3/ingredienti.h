#ifndef _HEADER1
#define _HEADER1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC 255

typedef enum {FALSE, TRUE} bool;

#endif

#ifndef _INGREDIENTI_H
#define _INGREDIENTI_H

typedef struct ingredienti_t* LINKI;
typedef struct ingrediente_t* linki;

LINKI 	LINKI_fill(void);
void 	LINKI_show(LINKI i, int s);
int 	iFind(LINKI i, char* buf);


#endif