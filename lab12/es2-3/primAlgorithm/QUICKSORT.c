#include "QUICKSORT.h"

void quickSort(int** A, int N)
{
	int l = 0;
	int r = N - 1;
	quickSortR(A, l, r);
}

void quickSortR(int** A, int l, int r)
{
	int q;
	if (r <= l) return;
	q = partition(A, l, r);
	quickSortR(A, l, q - 1);
	quickSortR(A, q + 1, r);

	return;
}


int partition(int** A, int l, int r) {
	
	int pivot, i, j, t;
	pivot = (*A)[r/2];
	i = l - 1; 
	j = r + 1;

	while ( 1 )
	{
		do ++i; 
		while ( (*A)[i] <= pivot && i <= r );
		do --j; 
		while ( (*A)[j] > pivot );
		if ( i >= j ) break;
		
		t = (*A)[i]; 
		(*A)[i] = (*A)[j]; 
		(*A)[j] = t;
	}

	t = (*A)[l]; 
	(*A)[l] = (*A)[j]; 
	(*A)[j] = t;

	return j;
}