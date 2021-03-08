#include "LIST.h"

struct list_t
{
	int vertex;
	LIST next;
};

LIST LIST_init()
{
	LIST L = malloc(sizeof(*L));

	L->vertex = -1;
	L->next = NULL;

	return L;
}

void LIST_add(LIST L, int S)
{
	LIST x = LIST_init();

	if (L->vertex == -1)
	{
		L->vertex = S;
		L->next = NULL;
	}

	else 
	{
		x->vertex = S;
		x->next = L;
		L = x;
	}
}

void LIST_remove(LIST L)
{
//	LIST del;

//	del = L;

//	if (del == NULL)
//		return ;

	L = L->next;

//	free(del);
}

void LIST_print(LIST L)
{
	LIST x;

	fprintf(stdout, "Cricca trovata!\t");

	for (x = L; x != NULL; x = x->next)
		fprintf(stdout, "%d ", L->vertex);

	fprintf(stderr, "\n");
}

int LIST_clear(LIST L)
{
	LIST x, p; int cnt = 0;

	for (x = L, p = NULL; x != NULL; p = x, x = x->next)
	{
		free(p);
		cnt++;
	}
	free(x);
	return cnt;
}
