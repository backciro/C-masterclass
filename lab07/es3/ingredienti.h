#ifndef INGREDIENTI_H
#define INGREDIENTI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {FALSE, TRUE} bool;

typedef struct ingredienti_t* linkI;

typedef struct ingrediente_t* linki;

void menuAscelta(linkI p);

int acquisciIngredienti(linkI *p);

linki newNode(FILE *fp, int n, linki next);

void ricercaIngrediente(linkI p_ing);

void stampaLista(linkI p);

void calcolaRicetta(linkI p_ing);

#endif