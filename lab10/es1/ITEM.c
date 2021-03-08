#include "ITEM.h"

static int cD, T;
static char slD[10 + 1];

KEY KEYget(ITEM item)
{
	return (item->cardID);
}

int KEYcompare(KEY k1, KEY k2)
{
	if (k1 > k2)
		return -1;

	if (k1 < k2)
		return 1;

	else
		return 0;
}

ITEM ITEMsetvoid()
{
	ITEM v = malloc(sizeof(*v));

	v->cardID = 0;
	v->skiUsed = NULL;

	return v;
}

ITEM ITEMscan()
{
	printf("Inserire skiliftID cardID e T\n"
	       "<skiliftXXX> <1...inf> - <current time>\n");
	scanf("%s%d%d", slD, &cD, &T);

	return (ITEMnew());
}

ITEM ITEMnew()
{
	ITEM new = malloc(sizeof(*new));

	new->cardID = cD;
	new->skiUsed = LISTnew();

	return new;
}

LIST LISTnew()
{
	LIST l = malloc(sizeof(*l));

	l->skiliftID = strdup(slD);
	l->last_use = T;
	l->next = NULL;

	return l;
}