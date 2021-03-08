#include "ITEM.h"

struct item_t
{
	char* nome;
};

KEY KEYget(ITEM item)
{
	return item->nome;
}

int KEYcompare(KEY k1, KEY k2)
{
	if (strcmp(k1, k2) < 0)
		return -1;

	else if (strcmp(k1, k2) > 0)
		return 1;
	
	else return 0;
}

ITEM ITEMnew(char* name)
{
	ITEM item = malloc(sizeof(ITEM));

	if (item == NULL)
		return ITEMsetvoid();

	item->nome = strdup(name);

	return item;
}

ITEM ITEMsetvoid()
{
	ITEM tmp = (ITEM) malloc(sizeof(struct item_t));

	if (tmp != NULL)
	{
		tmp->nome = NULL;
	}

	return tmp;
}

bool ITEMcheckvoid(ITEM item)
{
	if (item->nome == NULL)
		return TRUE;
	else return FALSE;
}

void ITEMshow(ITEM item)
{
	fprintf(stdout, "Nome: %s\n", item->nome);
	return;
}