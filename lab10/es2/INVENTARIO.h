#ifndef _HEADER1
#define _HEADER1 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FREE -1

typedef enum {FALSE, TRUE} bool;
int O;

#endif

#ifndef INV_H
#define INV_H 1

typedef struct inventario_t* ITEM;

struct inventario_t
{
	char* nome_obj;
	char* cat;
	int dim1;
	int dim2;
	int util;
};

int** loadInventario(int* O, char* s1, char* s2, ITEM** i);
int estraiGreater(ITEM* item, int* sol, int** mark, int k);
bool provaAMettere(ITEM* item, int*** m, int* sol, int k, int dim1, int dim2);
void stampaInventario(ITEM* item, int** matr_inv, int dim1, int dim2);
void aggiornaBest(int* sol, int k);
void aggiornaBestMat(int** m, int dim1, int dim2);

#endif