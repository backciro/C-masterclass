#include "ITEM.h"

struct item_t
{
	char* cod;
	int priority;
};

KEY KEYget(ITEM item)
{
	return (item->priority);
}

int KEYcompare(KEY k1, KEY k2)
{
	if (k1 > k2)
		return -1;

	else if (k1 < k2)
		return 1;

	else return 0;
}

ITEM ITEMnew(char* str, int prio)
{
	ITEM tmp = malloc(sizeof(*tmp));

	if (tmp == NULL)
		return ITEMsetvoid();

	else {
		tmp->cod = strdup(str);
		tmp->priority = prio;
	}

	return tmp;
}

ITEM ITEMsetvoid()
{
	char name[MAXC] = "";
	ITEM tmp = (ITEM) malloc(sizeof(struct item_t));

	if (tmp != NULL)
	{
		tmp->cod = strdup(name);
		tmp->priority = -1;
	}

	return tmp;

}

void ITEMshow(ITEM item)
{
	printf("Codice: %s Priority: %d\n", item->cod, item->priority);
	return;
}