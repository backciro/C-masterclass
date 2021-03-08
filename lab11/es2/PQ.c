#include "ITEM.h"
#include "PQ.h"

struct pqueue
{
	ITEM* heap;
	int HEAPsize;
};

int LEFT(int i)
{ return (i * 2 + 1); }

int RIGHT(int i)
{ return (i * 2 + 2); }

int PARENT(int i)
{ return ((i - 1) / 2); }

void Swap(HEAP heap, int i, int largest)
{
	ITEM tmp = malloc(sizeof(ITEM));

	tmp = heap->heap[i];
	heap->heap[i] = heap->heap[largest];
	heap->heap[largest] = tmp;

	free(tmp);
}

PQ PQinit(int maxN)
{
	PQ pq;
	pq = malloc(maxN * sizeof(*pq));
	pq->heap = (ITEM*) malloc(maxN * sizeof(ITEM));
	pq->HEAPsize = 0;

	return pq;
}

bool PQempty(PQ pq)
{
	return (pq->HEAPsize == 0);
}

int PQsize(PQ pq)
{
	return (pq->HEAPsize);
}

void PQdisplay(PQ pq)
{
	for (int i = 0; i < pq->HEAPsize; i++)
		ITEMshow(pq->heap[i]);
}

void PQinsert(PQ pq, ITEM item)
{
	int i = pq->HEAPsize++;

	while ( (i >= 1) && (KEYcompare(KEYget(pq->heap[PARENT(i)]), KEYget(item)) == 1) )
	{
		pq->heap[i] = pq->heap[PARENT(i)];
		i = (i - 1) / 2;
	}

	pq->heap[i] = item;

	return;
}

ITEM PQget(PQ pq)
{
	ITEM item;

	Swap (pq, 0, pq->HEAPsize - 1);
	item = pq->heap[pq->HEAPsize - 1];

	pq->HEAPsize--;
	HEAPify(pq, 0);

	return item;
}

void HEAPify(HEAP heap, int i)
{
	int l, r, largest;
	l = LEFT(i); 
	r = RIGHT(i);

	if ((l < heap->HEAPsize) && (KEYcompare(KEYget(heap->heap[l]), KEYget(heap->heap[i])) == -1))
		largest = l;
	else
		largest = i;

	if ((r < heap->HEAPsize) && (KEYcompare(KEYget(heap->heap[r]), KEYget(heap->heap[largest])) == -1))
		largest = r;

	if (largest != i)
	{
		Swap(heap, i, largest);
		HEAPify(heap, largest);
	}

	return;
}