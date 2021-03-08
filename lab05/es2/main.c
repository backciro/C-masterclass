//
// created by Matteo Minutti on 11/11/2016
//
#include <stdio.h>
#include <stdlib.h>

typedef enum {FALSE, TRUE} bool;

void trasformaBase(int N, int B, bool flag);

int main()
{
	int N, B, num;
	bool flag=TRUE;

	printf("Inserire un numero e una base per la conversione!\n");
	scanf("\n%d%d", &N, &B);

	trasformaBase(N, B, flag);

	printf("\n");
	return 0;
}

void trasformaBase(int N, int B, bool flag)
{
	int num;

	if (flag == FALSE)
		return;

	num = N % B;  

	if (N < B){
		flag=FALSE;
	}

	N = N / B;

	trasformaBase(N, B, flag);

	printf("%d", num);
}