#ifndef _HEADER1
#define _HEADER1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {FALSE, TRUE} bool;

#endif

#ifndef ESERCIZIO_H
#define ESERCIZIO_H

typedef struct esercizio_t* linkx;

struct esercizio_t
{
	char *nome_es;
	float punt;
	float diff;
};


#endif