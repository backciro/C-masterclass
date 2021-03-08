#include "esercizio.h"

#ifndef _HEADER1
#define _HEADER1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {FALSE, TRUE} bool;

#endif

#ifndef CATEGORIA_H
#define CATEGORIA_H

typedef struct wrapper* wr;

typedef struct categoria_t* linkc;

struct wrapper //wr
{
	linkc cat;
	int num_cat;
};

struct categoria_t //linkc
{
	char* nome;
	int num_es;
	int min, max;
	linkx esercizi; 
};

wr 		allocaWrapper();
linkc 	allocaCategorie(FILE *fp, int numcat);
linkx 	allocaEsercizi(FILE *fp, int numes);
void 	stampaS(wr w);
void 	stampaB(int **best, wr w);
void 	callRec(wr w);
void 	Rec(wr wrap, int pos, int** best, int *sol, int k, int i, int D, float* pun, float* dif);
bool 	check(wr wrap, int** best, int* sol, int k, int l, int D, float* pun, float* dif);
void 	bestCheck(int** best, int* sol, int k, int l, int D, float* pun, float* dif, float pcurr, float dcurr);
void	troppoDifficile(wr w, int** b, int* s, int i, int k, float* pun, float* dif, float d_, int DTOT, float* Tpunt, float* Tdiff);


#endif