#include "INVENTARIO.h"

#ifndef _HEADER1
#define _HEADER1 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FREE -1

typedef enum {FALSE, TRUE} bool;

#endif

#ifndef POWER_H
#define POWER_H 1

void generaSpazio(ITEM* i, int** m, int dim1, int dim2);
void powerRecursive(int pos, int* sol, int k, int* bv, int *util_curr, ITEM* i, int** m, int dim1, int dim2);
bool check(int* sol, int k, int* bv, int *util_curr, ITEM* item, int** m, int dim1, int dim2);
bool GuardaSeCiEntra(int* sol, int* bv, int *util_curr, int k, int** m, ITEM* i, int dim1, int dim2, int contaInv);


#endif