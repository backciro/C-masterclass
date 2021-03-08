//
// created by Matteo Minutti on 21/11/2016
//
#include <stdio.h>
#include <stdlib.h>

const int N = 10;
const int card = N - 1;

typedef enum {FALSE, TRUE} bool;

int** leggiFile(int **S, int *n);

void cover(int **S, int n, int k);

void comboR(int pos, int **S, int *sol, int n, int k);

bool check(int *sol, int n, int k, int **S);

int main()
{
	int k;
	int n;

	int **S;

	printf("Scegli il tuo K: ");
	scanf("\t%d", &k);

	S = leggiFile(S, &n);

	cover(S, n, k);

	return 0;
}

void cover(int **S, int n, int k){

	int pos;
	
	int *sol = calloc(k , sizeof(int));

	printf("\n");
	comboR(0, S, sol, n, k);
	printf("\n");		
}

void comboR(int pos, int **S, int *sol, int n, int k) { 

	int i, j; 

	if (pos >= k) { 
		if (check(sol, n, k, S)){
			printf("Sottoinsieme -> { ");
			for (i=0; i<k; i++)
				printf("[S]%d ", sol[i]); 
			printf("}");
			printf("\n"); 
		}

		return ; 
	} 

		for (i = 0; i < n; i++) { 
			sol[pos] = i; 
			comboR(pos+1, S, sol, n, k); 
		} 

	return ;
}

bool check(int *sol, int n, int k, int **S){

	int U[card] = {1,2,3,4,5,6,7,8,9};
	int I[card] = {0,0,0,0,0,0,0,0,0};
	
	int i, j, l = 0, cnt = 0;
	bool found = FALSE;
	
	for (i = 0; i < k; i++)
		for (j = 0; j < N; j++)
			if(S[sol[i]][j] != 0)
				cnt++;
		
	if ( cnt > card )
		return FALSE;
	if ( cnt < card )
		return FALSE;

	for (i = 0; i < k; i++)
		for (j = 0; j < 10; j++)
			if(S[sol[i]][j] != 0){
				I[l] = S[sol[i]][j];
				l++;
			}

	cnt = 0;
	for(j = 0; j < card; j++){
		if (U[j] == I[j])
			cnt++;
	}

	if (cnt == card)
		return TRUE;
	else
		return FALSE;
}	
	
int** leggiFile(int **S, int *n){

	int s;
	FILE *fp;
	
	printf("Scegli: \n1) Matrice esempio\n2) Matrice complessa\n");
	scanf("%d", &s);

	if(s == 2){
	fp = fopen("./matrice.txt","r");
	fscanf(fp, "%d", &(*n));
	}

	if(s == 1){
	fp = fopen("./matrsample.txt","r");
	fscanf(fp, "%d", &(*n));
	}

	S = malloc((*n) * sizeof(*S));

	for (int i = 0; i < *n; i++){
		S[i] = malloc(10 * sizeof(*S[i]));	
	}

	for (int i = 0; i < *n; i++){
		for (int j = 0; j < 10; j++){
			fscanf(fp, "%d", &S[i][j]);
		}
	}

	return S;
}