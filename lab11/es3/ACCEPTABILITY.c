#include "ACCEPTABILITY.h"

void isAcceptable(char* str, int* lungh, int N)
{
	int* sol;
	int pos = 0;
	bool isAcc = FALSE;
	int card = (int)strlen(str);
	sol = malloc(card * sizeof(int));

	powerRecursive(pos, 0, sol, str, N, lungh, card, &isAcc);

	if (!isAcc)
		printf("NESSUNA SCOMPOSIZIONE TROVATA!\n");
}

void powerRecursive(int pos, int start, int* sol, char* str, int N, int* lungh, int card, bool* isAcc)
{
	if (pos >= card)
	{
		if (check(sol, card, card))
		{
			compatter(sol, card, str);
			(*isAcc) = TRUE;
		}

		return;
	}

	for (int i = start; i < N; i++)
	{
		sol[pos] = lungh[i];
		powerRecursive(pos + 1, i, sol, str, N, lungh, card, isAcc);
	}

	return;
}

bool check(int* sol, int card, int n)
{
	int cardTOT = 0;

	for (int i = 0; i < n; i++)
		cardTOT += sol[i];

	if (cardTOT == card)
		return TRUE;
	else
		return FALSE;
}

void compatter(int* sol, int card, char* str)
{
	int* val;
	int* mark;
	int n, n_dist, j;

	j = 0;
	n = 0;

	for (int i = 0; i < card; i++)
		if (sol[i])
			n++;

	val = malloc(n * sizeof(int));
	mark = malloc(n * sizeof(int));

	for (int i = 0; i < n; i++) { mark[i] = 1; }
	for (int i = 0; i < card; i++) { if (sol[i]) val[j++] = sol[i]; }

	quickSort(&val, j) ;

	n_dist = checkDoppi(&val, &mark, n) ;

	permuta(val, mark, n, str, n_dist) ;
}

void permuta(int* val, int* mark, int n, char* str, int k)
{
	int* sol = malloc(n * sizeof(int));

	permRecursive(0, strlen(str), val, sol, mark, n, k, str);
}

void permRecursive(int pos, int card, int *val, int *sol, int *mark, int n, int n_dist, char* str)
{
	if (pos >= n)
	{
		if (check(sol, card, n))
		{
			decomponi(str, n, sol, 0, 0) ;
			printf("\n") ;
//			for (int i = 0; i < n; i++) printf("%d ", sol[i]); printf("\n");
		}
		return ;
	}

	for (int i = 0; i < n_dist; i++)
		if (mark[i] > 0)
		{
			mark[i]--;
			sol[pos] = val[i];
			permRecursive(pos + 1, card, val, sol, mark, n, n_dist, str);
			mark[i]++;
		}

	return;
}

int checkDoppi(int** sol, int** mark, int card)
{
	int adder = 0; 
	int *new = malloc(card * sizeof(int));
	bool duplicato, needRealloc = FALSE;

	for (int i = 0; i < card; i++)
	{
		duplicato = FALSE;

		for (int j = i + 1; j < card; j++)
		{
			if ((*sol)[i] == (*sol)[j])
			{
				duplicato = TRUE;
				needRealloc = TRUE;
			}
		}

		if (!duplicato)
			new[adder++] = (*sol)[i];

		else
			(*mark)[adder]++;
	}

	if (needRealloc)
	{
		(*sol) = realloc(new, adder);
		(*mark) = realloc(*mark, adder);
	}

	return adder;
}