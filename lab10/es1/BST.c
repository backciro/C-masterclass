#include "BST.h"

typedef struct BSTnode* LINK;

struct BSTnode
{
	ITEM item;
	LINK l;
	LINK r;
};

struct binarysearchtree
{
	LINK head;
	LINK z;
};

LIST UPLIST(ITEM curr, LINK h)
{
	LIST new = malloc(sizeof(*new));

	new->next = h->item->skiUsed;
	new->skiliftID = strdup(curr->skiUsed->skiliftID);
	new->last_use = curr->skiUsed->last_use;

	return new;
}

LINK NEW(ITEM item, LINK l, LINK r)
{
	LINK x = malloc(sizeof(*x));

	x->item = item;
	x->l = l;
	x->r = r;

	return x;
}

LINK UP(ITEM curr, LINK h, LINK z)
{
	h->item->skiUsed = UPLIST(curr, h);

	return h;
}

LINK rotR(LINK h)
{
	LINK x = h->l;
	h->l = x->r;
	x->r = h;
	return x;
}

LINK rotL(LINK h)
{
	LINK x = h->r;
	h->r = x->l;
	x->l = h;
	return x;
}

LINK insertT(LINK h, ITEM x, LINK z)
{
	if ( h == z)
		return NEW(x, z, z);

	//discesa ricorsiva
	if (KEYcompare(KEYget(h->item), KEYget(x)) < 0) {
		h->l = insertT(h->l, x, z);
		h = rotR(h);
	}
	//discesa ricorsiva
	if (KEYcompare(KEYget(h->item), KEYget(x)) > 0) {
		h->r = insertT(h->r, x, z);
		h = rotL(h);
	}

	return h;
}

LINK updateN(LINK h, ITEM x, LINK z)
{
	if (KEYcompare(KEYget(x), KEYget(h->item)) == 0)
		return UP(x, h, z);

	//discesa ricorsiva
	if (KEYcompare(KEYget(h->item), KEYget(x)) < 0)
		h->l = updateN(h->l, x, z);
	else
		h->r = updateN(h->r, x, z);

	return h;
}

BST BSTinit()
{
	BST bst = malloc(sizeof(*bst));
	bst->head = (bst->z = NEW(ITEMsetvoid(), NULL, NULL));
	return bst;
}

ITEM searchR(LINK h, KEY k, LINK z)
{
	if (h == z)
		return ITEMsetvoid();

	if (KEYcompare(KEYget(h->item), k) == 0)
		return (h->item);

	//discesa ricorsiva
	if (KEYcompare(KEYget(h->item), k) < 0)
		return (searchR(h->l, k, z));
	else
		return (searchR(h->r, k, z));
}

ITEM BSTsearch(BST bst, KEY k) //wrapper ponte per ADT I CLASSE
{
	return searchR(bst->head, k, bst->z);
}

void BSTinsert_root(BST* bst, ITEM item) //wrapper ponte per ADT I CLASSE
{
	(*bst)->head = insertT((*bst)->head, item, (*bst)->z);
}

void BSTupdate_node(BST* bst, ITEM item) //wrapper ponte per ADT I CLASSE
{
	(*bst)->head = updateN((*bst)->head, item, (*bst)->z);
}