#include "ST.h"

char buf[25];

struct symboltable
{
	ITEM *A;
	int N;
};

ST STinit(int maxN)
{
	int i;
	FILE *fin2 = fopen("./nomi.txt", "r");

	ST st = malloc(sizeof(*st));

	st->N = maxN;
	st->A = malloc(st->N * sizeof(ITEM) );

	for (i = 0; i < st->N; i++) {
		fscanf(fin2, "%s", buf);
		st->A[i] = ITEMnew(buf);
	}

	return st;
}

ITEM STretrieve(ST st, int i)
{
	return st->A[i];
}