#include "ingredienti.h"

#ifndef _HEADER1
#define _HEADER1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {FALSE, TRUE} bool;

char str[255+1];

#endif

#ifndef _RICETTE_H
#define _RICETTE_H

typedef struct ricette_t* LINKR;

typedef struct ricetta_t* linkr;

typedef struct elenchi_t* LINKE;

typedef struct elenco_t* linke;

struct ricette_t //LINKR
{
	linkr head;
	linkr tail;
};

struct ricetta_t //linkr
{
	char *nome;
	int tempo;
	LINKE elenco;
	linkr next;
};

struct elenchi_t //LINKE
{
	linke head;
	linke tail;
};

struct elenco_t //linke
{
	int indice;
	int grammi;
	linke next;
};

void menuAscelta(LINKI i, LINKR* r);

LINKR acquisciRicette(LINKI p);

linkr nuovaRicetta(FILE *fp, linkr nx, char* s, int t, int n, LINKI i);

LINKE nuovoElenco(FILE *fp, int n, LINKI p);

linke nuovoNodo(int i, int g, linke nx);

void stampaRicette(LINKR p, LINKI i, int s);

void calcolaRicetta(LINKR p, LINKI i, int s);

void newRicetta(LINKR* p, LINKI i);

#endif