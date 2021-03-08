#include "ST.h"

struct symboltable
{
	int *A;
	int N;
};

ST STinit(int maxN)
{
	int i;

	ST st = malloc(sizeof(*st));

	st->N = maxN;
	st->A = malloc(st->N * sizeof(int) );

	for (i = 0; i < st->N; i++)
		st->A[i] = -1;

	return st;
}

void STinsert(ST st, int k)
{
	for (int i = 0; i < st->N; i++)
		if (st->A[i] == -1)
			st->A[i] = k;
}

int STsearch(ST st, int k)
{
	for (int i = 0; i < st->N; i++)
		if (k == st->A[i])
			return i;

	return -1;
}

int STretrieve(ST st, int i)
{
	return st->A[i];
}