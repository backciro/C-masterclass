//
// created by Matteo Minutti on 23/11/2016
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAXstr = 255;

typedef enum {FALSE, TRUE} bool;

typedef struct 
{
	char **title;
	int num;		
} blocco;

blocco* allocaTore(int* A);

void powerSet(int A, blocco* V);

void powerSetR(int pos, blocco* V, int start, int* sol, int n, int k, int* cnt);

bool check(blocco* V, int* sol, int n, int k);

int main()
{
	int A, i, j;
	blocco* V;

	V = allocaTore(&A);

	powerSet(A, V);

	return 0;
}

blocco* allocaTore(int* A)
{
	int num_blocco, i, j, k;
	char str[MAXstr+1];

	blocco* p;
	char** m;

	FILE *fp = fopen("./brani.txt", "r");
	fscanf(fp, "%d", A);

	p = malloc((*A) * sizeof(*p));

	for (i = 0; i < (*A); i++){
	
		fscanf(fp, "%d", &num_blocco);
		m = malloc(num_blocco * sizeof(*m));
  		
  		p[i].title = m;
  		p[i].num = num_blocco;

		for (j = 0; j < num_blocco; j++){
			strcpy(str, "\0");	
			fscanf(fp, "%s ", str);
  			
  			m[j] = strdup(str); 	//uso della strdup poiché malloc+strcpy mi ha dato problemi
  			p[i].title[j] = m[j];	
		} 
	}		

	return p;
}

void powerSet(int A, blocco* V)
{
	int pos, k = A, cnt = 0;

	int *sol = calloc(k , sizeof(int));

	powerSetR(0, V, 0, sol, A, k, &cnt);

	printf("\n");	
}

void powerSetR(int pos, blocco* V, int start, int* sol, int n, int k, int* cnt)
{
	int i;

	if (pos >= k) { 
		if(check(V, sol, n, k)){
			printf("Playlist %d  -> ", ++(*cnt));
			for (i = 0; i < k; i++)
				printf(" %s ", V[i].title[sol[i]]);
			printf("\n"); 
		}
		return ; 
	} 

		for (i = 0; i < k; i++) { 
			sol[pos] = i; 
			powerSetR(pos+1, V, i, sol, n, k, cnt); 			
		} 

	return ;
}

bool check(blocco* V, int* sol, int n, int k)
{

	for (int i = 0; i < k; i++)
	{
		if (sol[i] > (V[i].num)-1)
			return FALSE;
	}

	return TRUE;
}