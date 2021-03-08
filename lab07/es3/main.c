#include "ingredienti.h"

int main()
{
	linkI p_ing;

	acquisciIngredienti(&p_ing);

	menuAscelta(p_ing);

	return 0;
}	

void menuAscelta(linkI p_ing)
{
	int opz;
	bool ciclo = TRUE;

	do{
		printf("\nEffettuare una scelta tra le seguenti:\n"
			"1) Stampare la lista degli ingredienti\n"
			"2) Ricercare un ingrediente\n"
			"3) Inserire una ricetta\n"
			"0) FINE\n\n");

		scanf("%d", &opz);

		switch(opz){

			case 0:
				ciclo = FALSE;
				break;

			case 1:
				stampaLista(p_ing);
				break;

			case 2:
				ricercaIngrediente(p_ing);
				break;

			case 3:
				calcolaRicetta(p_ing);
				break;
		}
	} while(ciclo);
}