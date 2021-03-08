#include "ITEM.h"

struct item_t
{
	char* id_room;
	int gold;
	int health;
};

KEY KEYget(ITEM item)
{
	return item->id_room;
}

int GOLDget(ITEM item)
{
	return item->gold;
}

int HEALTHget(ITEM item)
{
	return item->health;
}

int MAXworth(ITEM i1, ITEM i2)
{
	if (GOLDget(i1) > GOLDget(i2))
		return -1;

	else if (GOLDget(i1) < GOLDget(i2))
		return 1;

	else return 0;
}

int KEYcompare(KEY k1, KEY k2)
{
	if (strcmp(k1, k2) < 0)
		return -1;

	else if (strcmp(k1, k2) > 0)
		return 1;
	
	else return 0;
}

ITEM ITEMnew(char* name, int gold, int health)
{
	ITEM item = malloc(sizeof(ITEM));

	if (item == NULL)
		return ITEMsetvoid();

	item->id_room = strdup(name);
	item->gold = gold;
	item->health = health;

	return item;
}

ITEM ITEMsetvoid()
{
	ITEM tmp = (ITEM) malloc(sizeof(struct item_t));

	if (tmp != NULL)
	{
		tmp->id_room = NULL;
		tmp->gold = -1;
		tmp->health = -1;
	}

	return tmp;
}

bool ITEMcheckvoid(ITEM item)
{
	if (item->id_room == NULL)
		return TRUE;
	else return FALSE;
}

void ITEMshow(ITEM item)
{
	fprintf(stdout, "Sala: %s\nOro: %d\tVita:%d", item->id_room, item->gold, item->health);
	return;
}