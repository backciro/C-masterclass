#include "ingredienti.h"
#include "ricette.h"

int main()
{
	LINKI p_ing;
	LINKR p_ric;

	p_ing = acquisciIngredienti();

	p_ric = acquisciRicette(p_ing);

	menuAscelta(p_ing, &p_ric);

	return 0;
}	

void menuAscelta(LINKI p_ing, LINKR* p_ric)
{
	int opz;
	bool ciclo = TRUE;
	bool inizio = TRUE;

	do{
		if(inizio){
		printf("\nEffettuare una scelta tra le seguenti:\n"
			"1) Stampa i dettagli di una ricetta\n"
			"2) Stampa i dettagli di un ingrediente\n"
			"3) Calcola il prezzo di una ricetta\n"
			"4) Calcola l'apporto calorico di una ricetta\n"
			"5) Stampa l'elenco completo delle ricette\n"
			"6) Stampa l'elenco completo degli ingredienti\n"
			"7) Stampa le ricette nelle quali è presente un dato ingrediente\n"
			"8) Scrivi una nuova ricetta!\n"
			"...\n"
			"0) FINE\n\n");
		}

		if (!inizio)
			printf("\nEffettuare una scelta dal menu <1...8>\n");

		scanf("%d", &opz);

		switch(opz){

			case 0:
				ciclo = FALSE;
				break;

			case 1:
				stampaRicette(*p_ric, p_ing, 1);
				inizio = TRUE;
				break;

			case 2:
				stampaIngredienti(p_ing, 1);
				inizio = TRUE;
				break;

			case 3:
				calcolaRicetta(*p_ric, p_ing, 1);
				inizio = FALSE;
				break;			

			case 4:
				calcolaRicetta(*p_ric, p_ing, 0);
				inizio = FALSE;
				break;

			case 5:
				stampaRicette(*p_ric, p_ing, 0);
				inizio = TRUE;
				break;

			case 6:
				stampaIngredienti(p_ing, 0);
				inizio = TRUE;
				break;

			case 7:
				stampaRicette(*p_ric, p_ing, 2);
				inizio = FALSE;
				break;			

			case 8:
				newRicetta(p_ric, p_ing);
				break;
		}
	} while(ciclo);
}