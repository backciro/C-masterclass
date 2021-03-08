#ifndef _HEADER1
#define _HEADER1 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {FALSE, TRUE} bool ;

#endif

#ifndef QUICK_H
#define QUICK_H 1

void quickSort(int** A, int N);
void quickSortR(int** A, int l, int r);
int partition(int** A, int l, int r);


#endif
