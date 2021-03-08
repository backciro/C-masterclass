//algoritmo greedy ricorsivo; al caso peggiore la ricorsione fa N iterazioni
//complessita O(n) lineare (credo!)
#include <stdio.h>
#include <stdlib.h>

typedef enum {FALSE, TRUE} bool;

void greedyScontriR(int pos, int *val);

int main()
{
	int *val;
	int pos, k;

	printf("\nInserisci codifica vettore input: \n(N_elem e1 e2 e3 ... eN): ");
	scanf(" %d", &k);

	if (k%2 != 0){
		printf("Solo elementi pari! \n");
		exit(-1);
	}

	val = malloc(k + 1 * sizeof(int));
	val[0] = k;

	for (int i = 1; i < k + 1; i++) {
		scanf("%d", &val[i]);
		if (i == k) break;
	}

	printf("\nVettore di partenza\t --> \t");
	for (int i = 0; i < k + 1; i++)
		printf("%d ", val[i]);
	printf("\n");

	greedyScontriR(1, val);

	return 0;
}

void greedyScontriR(int pos, int *val)
{
	int cnt, cnt1, i_scontro;
	bool scontro_eq, uguale;

	if (pos >= val[0]){
	printf("Vettore equlibrato\t --> \t");
		for(int j = 0; j <= val[0]; j++)
			printf("%d ", val[j]);
		printf("\n\n");
		return;
	}

	cnt = 0; cnt1 = 0; scontro_eq = FALSE; uguale = TRUE;

	if (val[pos] == 1) // poiche '1' è una freccia vs sinistra
		val[pos] = 0;

	for (int i = pos; uguale; i++) // conto quante volte si ripete una freccia 
	{								// (in realta solo verso sinistra sarebbe accettabile)
		if (val[i] != val[pos]){
			i_scontro = i;
			uguale = FALSE;
		}

		if (val[i] == val[pos]){
			cnt++;
		}
	}

	if(cnt == 1){		// se è solo una freccia per essere equilibrato lo scontro
		scontro_eq = TRUE;	// sarà una coppia ' 0 1 '
		pos += cnt + 1;
	}

	else if (cnt > 1){
		for(int i = pos+cnt; i <= pos + (2*cnt); i++)
			if (val[i] == 1)
				cnt1++;
		if (cnt1 == cnt){
			pos = pos + (2*cnt);
			scontro_eq = TRUE;
		}
	}

	if (!scontro_eq){

		if ((pos + (cnt+cnt) ) > val[0]){
			
			if(val[pos+(cnt/2)] == 0){
				val[pos+(cnt/2)] = 1;
			}
			else val[pos+(cnt/2)] = 0;
		
		pos = pos+(cnt/2)+1; 
		} 
		
		else { 
			for(int j = pos + cnt; j < pos + (cnt * 2); j++){			
				if(val[j == 0]){
					val[j] = 1;
				}
				else val[j] = 0; 
			}
			pos = pos + (cnt * 2);
		}
	}

	greedyScontriR(pos, val);
}