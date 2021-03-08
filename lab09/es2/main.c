#include "ITEM.h"
#include "PQ.h"

int main()
{
	bool ciclo = TRUE;
	bool inizio = TRUE;

	srand(time(NULL));

	PQinit();

	do
	{
		if (inizio)
			printf("\n** TORNEO DEI MICCI IMPERIALI**\n"
			       "1) Stampa lo stato attuale della classifica\n"
			       "2) Inserisci un nuovo partecipante\n"
			       "3) Elimina uno dei partecipanti\n"
			       "4) NEXT MATCH!\n\n"
			       "5) Carica dati da file\n"
			       "6) Salva dati su file\n"
			       "... 0 per uscire\n");
		if (!inizio)
			printf("Effettua una scelta <1..6>\n");
			
		scanf("\n%d", &s);

		switch (s)
		{
		case 0:
			ciclo = FALSE;
			break;

		case 1:
			PQdisplay(NULL, 0);
			break;

		case 2:
			PlayerInsert();
			inizio = FALSE;
			break;

		case 3:
			PlayerDelete();
			inizio = FALSE;
			break;

		case 4:
			MATCH();
			inizio = FALSE;
			break;

		case 5:
			BufferInsert();
			inizio = TRUE;
			break;

		case 6:
			saveRanking();
			inizio = TRUE;
			break;

		default:
			break;
		}

	} while (ciclo);

	return 0;
}