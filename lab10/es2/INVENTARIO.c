#include "INVENTARIO.h"

static int a, b, c;
char buf1[100], buf2[100];

int** loadInventario(int* tot, char* inv1, char* inv2, ITEM** item)
{
	int** inv;

	FILE *fp = fopen("equip.txt", "r");
	fscanf(fp, "%d", &O); (*tot) = O;

	inv = malloc(atoi(inv1) * sizeof(*inv));
	for (int j = 0; j < O; j++) {
		inv[j] = malloc(atoi(inv2) * sizeof(*inv[j]));
	}

	for (int i = 0; i < atoi(inv1); i++) {
		for (int j = 0; j < atoi(inv2); j++)
			inv[i][j] = FREE;
	}

	(*item) = malloc(O * sizeof(struct inventario_t*));
	for (int j = 0; j < O; j++)
		(*item)[j] = malloc(sizeof(struct inventario_t));

	for (int j = 0; j < O; j++) {
		fscanf(fp, "%s%s%d%d%d", buf1, buf2, &a, &b, &c);

		(*item)[j]->nome_obj = strdup(buf1);
		(*item)[j]->cat = strdup(buf2);

		(*item)[j]->dim1 = a;
		(*item)[j]->dim2 = b;
		(*item)[j]->util = c;
	}

	fclose(fp);
	return inv;
}

int estraiGreater(ITEM* item, int* sol, int** mark, int k)
{
	int m = 0, max = 0, max_i;
	for (int i = 0; i < k; i++)
	{
		if ((sol)[i])
		{
			if ((*mark)[i] == 0)
			{
				m = (item[i]->dim1 * item[i]->dim2);
				if (m > max)
				{
					max = m;
					max_i = i;
				}
			}
		}
	}	(*mark)[max_i] = 1;
	return max_i;
}

bool provaAMettere(ITEM* item, int*** m_exp, int* sol, int max, int dim1, int dim2)
{
	ITEM to_place = item[max];

	for (int i = 0; i < dim1; i++) {
		for (int j = 0; j < dim2; j++) {


			if ((*m_exp)[i][j] == FREE) { // cella libera
				if ((i + to_place->dim1 - 1 <= dim1) || (j + to_place->dim2 - 1 <= dim2)) {

					for (int x = i; x <= i + to_place->dim1 - 1; x++) {
						for (int y = j; y <= j + to_place->dim2 - 1; y++) {

							if (x + to_place->dim1 - 1 > dim1 || y + to_place->dim2 - 1 > dim2)
								continue;

							if ((x > dim1 && y <= dim2) || (x <= dim1 && y >= dim2))
								continue;

							if (x + to_place->dim1 - 1 > dim1 && y + to_place->dim2 - 1 > dim2)
								return FALSE;

							else
								(*m_exp)[x][y] = max + 1;
						}
					}

					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

void stampaInventario(ITEM* item, int** matr_inv, int dim1, int dim2)
{
	printf("\n");

	for (int i = 0; i < dim1; i++) {
		for (int j = 0; j < dim2; j++) {
			if (matr_inv[i][j] != FREE)
				printf("%d\t", matr_inv[i][j]);
			else printf("NULL\t");
		}
		printf("\n");
	}
}

