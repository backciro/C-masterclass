#ifndef _HEADER1
#define _HEADER1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {FALSE, TRUE} bool;

char str[255+1];

#endif

#ifndef _INGREDIENTI_H
#define _INGREDIENTI_H

typedef struct ingredienti_t* LINKI;

typedef struct ingrediente_t* linki;

struct ingredienti_t // LINKI
{
	linki *V;
	int num_ing;
};

struct ingrediente_t // linki
{
	char *nome;
	float price;
	float cal;
};

LINKI acquisciIngredienti();

linki newNode(FILE *fp, int n, linki next);

int cercaIndice(char *str, LINKI p_ing);

void stampaIngredienti(LINKI p, int s);


#endif