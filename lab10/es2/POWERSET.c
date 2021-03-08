#include "INVENTARIO.h"
#include "POWERSET.h"

void generaSpazio(ITEM* item, int** matr_inv, int dim1, int dim2)
{
	int pos = 0, bv = 0, util_curr;
	int *sol = calloc(O, sizeof(int));

	powerRecursive(pos, sol, O, &bv, &util_curr, item, matr_inv, dim1, dim2);
}

void powerRecursive(int pos, int* sol, int k, int *bv, int *util_curr, ITEM* item, int** matr_inv, int dim1, int dim2)
{
	if (pos >= k) {
		if (check(sol, k, bv, util_curr, item, matr_inv, dim1, dim2)) {
			for (int i = 0; i < O; i++)
				printf("%d ", sol[i]);
			printf("\n");
		}
		return;
	}

	sol[pos] = 1;
	(*util_curr) += item[pos]->util;
	powerRecursive(pos + 1, sol, O, bv, util_curr, item, matr_inv, dim1, dim2);

	sol[pos] = 0;
	(*util_curr) -= item[pos]->util;
	powerRecursive(pos + 1, sol, O, bv, util_curr, item, matr_inv, dim1, dim2);
}

bool check(int* sol, int k, int *bv, int *util_curr, ITEM* item, int** matr_inv, int dim1, int dim2)
{
	bool arma, armatura, pozione;
	int AreaTot, AreaInv = (dim1 * dim2);
	int contaInv;

	arma = armatura = pozione = FALSE;
	(*util_curr) = 0;
	AreaTot = 0;
	contaInv = 0;

	for (int i = 0; i < k; i++) {
		if (sol[i]) {
			if (strcmp(item[i]->cat, "arma") == 0)
				arma = TRUE;
			if (strcmp(item[i]->cat, "armatura") == 0)
				armatura = TRUE;
			if (strcmp(item[i]->cat, "pozione") == 0)
				pozione = TRUE;

			if (item[i]->dim1 > dim1 || item[i]->dim2 > dim2)
				return FALSE;

			(*util_curr) += item[i]->util;

			AreaTot += (item[i]->dim1 * item[i]->dim2);

			contaInv++;
		}
	}

	if (AreaInv < AreaTot)
		return FALSE;

	if (arma && armatura && pozione)
		return GuardaSeCiEntra(sol, bv, util_curr, k, matr_inv, item, dim1, dim2, contaInv);

	else return FALSE;
}

bool GuardaSeCiEntra(int* sol, int* bv, int *util_curr, int k, int** matr_inv, ITEM* item, int dim1, int dim2, int contaInv)
{
	int max, cntPezzi;
	int* mark = malloc(k * sizeof(int));
	for (int i = 0; i < k; i++) mark[i] = 0;

	int** m_exp;

	m_exp = malloc(dim1 * sizeof(*m_exp));
	for (int i = 0; i < dim1; i++) m_exp[i] = malloc(dim2 * sizeof((*m_exp)[i]));

	for (int i = 0; i < dim1; i++)
		for (int j = 0; j < dim2; j++)
			m_exp[i][j] = -1;

	if ((*util_curr) >= (*bv)) {
		(*bv) = (*util_curr);

		cntPezzi = 0;

		for (int l = 0; l < contaInv; l++) {

			max = estraiGreater(item, sol, &mark, k);

			if (provaAMettere(item, &m_exp, sol, max, dim1, dim2))
			{
				cntPezzi++;
				continue;
			}
		}
		if (cntPezzi == contaInv) {
			aggiornaBest(sol, k);
			aggiornaBestMat(m_exp, dim1, dim2);
			return TRUE;
		}
	}

	return FALSE;
}
