#include "ITEM.h"

struct item_t
{
	KEY id_elab;
	KEY id_net;
};

KEY KEYget(ITEM item)
{
	return (item->id_elab);
}

KEY NETget(ITEM item)
{
	return (item->id_net);
}

int KEYcompare(KEY k1, KEY k2)
{
	if (strcmp(k1, k2) < 0)
		return -1;

	else if (strcmp(k1, k2) > 0)
		return 1;

	else return 0;
}

ITEM ITEMnew(char* id1, char* id2)
{
	ITEM tmp = malloc(sizeof(*tmp));

	if (tmp == NULL)
		return ITEMsetvoid();

	else {
		tmp->id_elab = strdup(id1);
		tmp->id_net = strdup(id2);
	}

	return tmp;
}

ITEM ITEMsetvoid()
{
	ITEM tmp = (ITEM) malloc(sizeof(struct item_t));

	if (tmp != NULL)
	{
		tmp->id_elab = NULL;
		tmp->id_net = NULL;
	}

	return tmp;
}

bool ITEMcheckvoid(ITEM item)
{
	if (item->id_elab == NULL)
		return TRUE;
	else return FALSE;
}


void ITEMshow(ITEM item)
{
	printf("elaboratore: %s rete: %s\n", item->id_elab, item->id_net);
	return;
}