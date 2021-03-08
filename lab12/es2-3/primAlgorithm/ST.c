#include "ST.h"

char buf[15];

struct symboltable
{
	ITEM *A;
	int N;
	int M;
};

ST STinit(int maxN)
{
	int i;
	FILE *fin2 = fopen("./nomi.txt", "r");

	ST st = malloc(sizeof(*st));

	st->N = 0;
	st->M = maxN;
	st->A = malloc(st->M * sizeof(ITEM) );

	for (i = 0; i < st->M; i++) {
		fscanf(fin2, "%s", buf);
		st->A[i] = ITEMnew(buf);
	}

	return st;
}

int STsearch(ST st, KEY k)
{
	int i = 0;

	while (i < st->M) {
		if (KEYcompare(k, KEYget(st->A[i])) == 0)
			return i;
		i++;
	}

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

int STcount(ST st)
{
	return st->N;
}

bool STempty(ST st)
{
	if (STcount(st) == 0)
		return TRUE;
	else
		return FALSE;
}

void STdelete(ST st, EDGE e)
{
	int n1 = GETv(e), n2 = GETw(e);

	for (int i = n1; i < st->N - 1; i++)
		st->A[i] = st->A[i + 1];

	st->N--;

	for (int i = n2; i < st->N - 1; i++)
		st->A[i] = st->A[i + 1] ;

	st->N--;

}
