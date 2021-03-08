#include "ST.h"

struct symboltable
{
	ITEM *A;
	int N;
	int M;
};

ST STinit(int maxN)
{
	int i;

	ST st = malloc(sizeof(*st));

	st->N = 0;
	st->M = maxN;
	st->A = malloc(st->M * sizeof(ITEM) );

	for (i = 0; i < st->M; i++)
		st->A[i] = ITEMsetvoid();

	return st;
}

int hash(KEY k, int M)
{
	int h, a = 0, b = 127;

	for ( h = 0; *k != '\0'; k++, a = a * b % (M - 1))
		h = (a * h + *k) % M;

	return h;
}

int full(ST st, int i)
{
	if (ITEMcheckvoid(st->A[i]))
		return 0;

	else
		return 1;
}

void STinsert(ST st, ITEM item)
{
	ITEM tmp;
	int i = hash(KEYget(item), st->M);
	int first = 0, last = st->M - 1;
	
	while (full(st, i))
		i = (i + 1) % st->M;

	if (KEYcompare(KEYget(item), "Ingresso\0") == 0) {
		if (full(st, first)) {
			tmp = st->A[first];
			st->A[i] = tmp;
			i = first;
		}
		else 
			i = first;
	}

	if (KEYcompare(KEYget(item), "Uscita\0") == 0) {
		if (full(st, last)) {
			tmp = st->A[last];
			st->A[i] = tmp;
			i = last;
		}
		else
			i = last;
	}

	st->A[i] = item;
	st->N++;
}

int STsearch(ST st, KEY k)
{
	int i = hash(k, st->M);

	while (full(st, i))
		if (KEYcompare(k, KEYget(st->A[i])) == 0)
			return i;
		else
			i = (i + 1) % st->M;

	return -1;
}

ITEM STretrieve(ST st, int i)
{
	return st->A[i];
}

void STdisplay(ST st)
{
	int i;

	for (i = 0; i < st->M; i++) {
		printf("st->A[%d] = ", i);
		ITEMshow(st->A[i]);
		printf("\n");
	}
}

int STcount(ST tab)
{
	return tab->N;
}

bool STempty(ST tab)
{
	if (STcount(tab) == 0)
		return TRUE;
	else
		return FALSE;
}
