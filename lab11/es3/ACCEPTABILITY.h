#include "HEADER1.h"
#include "QUICKSORT.h"

#ifndef _HEADER1
#define _HEADER1 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {FALSE, TRUE} bool ;

#endif

#ifndef ACCEPT_H
#define ACCEPT_H 1

// diposizioni ripetute
void isAcceptable(char* str, int* lungh, int N);
void powerRecursive(int pos, int start, int* sol, char* str, int N, int* lungh, int card, bool* isAcc);
bool check(int* sol, int card, int n);

// permutazioni semplici / ripetute
void permuta(int* val, int* mark, int card, char* str, int k);
void permRecursive(int pos, int card, int *val, int *sol, int *mark, int n, int n_dist, char* str);
int checkDoppi(int** sol, int** mark, int card);


#endif
