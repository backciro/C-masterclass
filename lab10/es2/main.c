#include "INVENTARIO.h"
#include "POWERSET.h"

int** matr_inv;
ITEM* item;
int* best;
int O;

int main(int argc, char *argv[])
{
	bool exist = FALSE;

	if (argc != 3) {
		printf("%s\n", "\nERRORE NEI PARAMETRI! \n"
		       "(PASSARE DIMENSIONI INVENTARIO COME ARGV[1] e ARGV[2])\n");
		exit(EXIT_FAILURE);
	} matr_inv = loadInventario(&O, argv[1], argv[2], &item);

	best = calloc(O , sizeof(int));

	generaSpazio(item, matr_inv, atoi(argv[1]), atoi(argv[2]));

	printf("\n");
	for (int i = 0; i < 20; i++) 
		if (best[i]) {
			printf("Elemento: %d = '%s' utilita\': %d\n", i+1, item[i]->nome_obj, item[i]->util);
			exist = TRUE;
		}

	if (exist) 
		stampaInventario(item, matr_inv, atoi(argv[1]), atoi(argv[2]));

	else printf("\nNESSUN INVENTARIO DISPONIBILE!\n\n");

	return 0;
}


void aggiornaBest(int* sol, int k)
{
	for (int i = 0; i < k; i++)
		best[i] = sol[i];
}

void aggiornaBestMat(int** m, int dim1, int dim2)
{
	for (int i = 0; i < dim1; i++)
		for (int j = 0; j < dim2; j++)
			matr_inv[i][j] = m[i][j];
}
