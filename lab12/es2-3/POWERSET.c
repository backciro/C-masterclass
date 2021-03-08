#include "POWERSET.h"

// struttura dati dinamica che contiene tutto il necessario per controllare la ricorsione 
// (è compresa una ST giusto per stampare i nomi e non i numeri dei riferimenti)
struct quasi_grafo
{
	int N;
	int M;
	int K;
	float media_best;
	int* sol;
	int* best;
	int* sol_umore;
	int* best_umore;
	int* occ;
	int** adj;
	ST st;
};

int** MATRIXinit(FILE* fp, int N)
{
	int** mat = malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++) mat[i] = malloc(N * sizeof(int));

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			fscanf(fp, "%d ", &mat[i][j]);

	return mat;
}

QG dataRead()
{
	QG data = malloc(sizeof(*data));

	FILE *fp = fopen("./amici.txt", "r");
	fscanf(fp, "%d%d%d%*d", &data->N, &data->M, &data->K);

	data->adj = MATRIXinit(fp, data->N);
	data->st = STinit(data->N);

	data->sol = calloc(data->N , sizeof(int));
	data->best = calloc(data->N , sizeof(int));
	data->sol_umore = calloc(data->M , sizeof(int));
	data->best_umore = calloc(data->M , sizeof(int));
	data->occ = calloc(data->M , sizeof(int));

	data->media_best = 0;

	return data;
}

void solve(QG db) // wrapper della funzione ricorsiva
{
	for (int i = 0; i < db->M; i++) db->occ[i] = db->K;

	recurse(db, 0);
}

void recurse(QG db, int pos)
{
	if (pos >= db->N) {
		takeBest(db);

		for (int j = 0; j < db->N; j++) printf("%d ", db->sol[j]); printf("\n");
		return;
	}

	for (int i = 0; i < db->M ; i++) // ciclo delle scelte sui blocchi
	{
		if (db->occ[i] > 0) // controllo occorrenze per ogni blocco (inizializzate a K)
		{
			db->occ[i]--;
			db->sol[pos] = i;
			recurse(db, pos + 1);
			db->occ[i]++;
		}
		if (db->occ[i] == 0) break; // "pruning" per non generare soluzioni simmetriche
	}
}

void takeBest(QG db) // funzione di verifica e salvataggio della best solution
{
	float sumTOT = 0, mediaTOT = 0;
	int i, i_1, i_2, iCars, umore = 0;

	for (iCars = 0; iCars < db->M; iCars++)
	{
		for (i_1 = 0; i_1 < db->N; i_1++)
			for (i_2 = i_1 + 1; i_2 < db->N; i_2++)
				if (db->sol[i_1] == iCars && db->sol[i_1] == db->sol[i_2])
					umore += db->adj[i_1][i_2];

		db->sol_umore[iCars] = umore;
		umore = 0;
	}

	for (iCars = 0; iCars < db->M; iCars++) sumTOT += db->sol_umore[iCars];

	mediaTOT = (sumTOT / db->M);

	if (mediaTOT > db->media_best)
	{
		db->media_best = mediaTOT;

		for (i = 0; i < db->N; i++)	db->best[i] = db->sol[i];
		for (iCars = 0; iCars < db->M; iCars++) db->best_umore[iCars] = db->sol_umore[iCars];
	}
}

void printBest(QG db) // funzione di stampa della best solution compresa nella struttura dati principale
{
	fprintf(stdout, "\nMIGLIOR COMITIVA POSSIBILE: \n\n" );

	for (int i = 0; i < db->M; i++)
	{
		fprintf(stdout, "| ");
		for (int j = 0; j < db->N; j++)
		{
			if (db->best[j] == i)
			{
				fprintf(stdout, "%s | ", KEYget(STretrieve(db->st, j)));
			}
		}
		fprintf(stdout, "\nMacchina #%d ; Umore = %d\n\n", i + 1, db->best_umore[i]);
	}

	fprintf(stdout, "Media umore generale della comitiva: %.1f\n\n", db->media_best);
}