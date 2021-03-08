#include "ingredienti.h"
#include "ricette.h"

int main()
{
	LINKI p_ing;
	LINKR p_ric;

	p_ing = LINKI_fill();
	p_ric = LINKR_fill(p_ing);

	menu(p_ing, &p_ric);

	return 0;
}	

void menu(LINKI p_ing, LINKR* p_ric)
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
				LINKR_show(*p_ric, p_ing, 1);
				inizio = TRUE;
				break;

			case 2:
				LINKI_show(p_ing, 1);
				inizio = TRUE;
				break;

			case 3:
				LINKR_eval(*p_ric, p_ing, 1);
				inizio = FALSE;
				break;			

			case 4:
				LINKR_eval(*p_ric, p_ing, 0);
				inizio = FALSE;
				break;

			case 5:
				LINKR_show(*p_ric, p_ing, 0);
				inizio = TRUE;
				break;

			case 6:
				LINKI_show(p_ing, 0);
				inizio = TRUE;
				break;

			case 7:
				LINKR_show(*p_ric, p_ing, 2);
				inizio = FALSE;
				break;			

			case 8:
				linkr_add(p_ric, p_ing);
				break;
		}
	} while(ciclo);
}