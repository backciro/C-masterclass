#include "SKILIFT.h"
#include "ITEM.h"
#include "BST.h"

bool ciclo = TRUE;
	
static BST Skiers;		//
static SKI Skilifts;	//	variabili globali visibile solo al client
static ITEM curr_ski;	//

int main()
{
	Skilifts = SKIget();
	Skiers = BSTinit();

	do {
		//acquisisco lo sciatore
		curr_ski = ITEMscan();

		//controllo se gia presente nel BST
		//caso affermativo: vedo se puo passare e lo aggiorno dov'è nell'albero
		if (KEYcompare(KEYget(BSTsearch(Skiers, KEYget(curr_ski))), KEYget(curr_ski)) == 0)
		{
			if (authorize(KEYget(curr_ski), curr_ski->skiUsed->skiliftID, curr_ski->skiUsed->last_use))
			{
				BSTupdate_node(&Skiers, curr_ski);
				printf("%s\n\n", "*SCIATORE AUTORIZZATO*");
			}
			else 
				printf("%s\n\n", "*SCIATORE NON AUTORIZZATO*");
		}
		//	caso negativo: lo aggiungo da qualche parte
		//	(o in testa o in qualche ramo log(n))
		//	se non è mai passato È autorizzato per forza
		else {
			BSTinsert_root(&Skiers, curr_ski);
			printf("%s\n\n", "*SCIATORE AUTORIZZATO*");
		}
	} while (ciclo);

	return 0;
}

//getter #1 [authorize] per gli intervalli
int GETinterval(char* skID, int N)
{
	int i, t;

	for (i = 0; i < N; i++)
		if (strcmp(skID, Skilifts[i].skiliftID) == 0)
			t = Skilifts[i].time_interval;

	return t;
}
//getter #2 [authorize] per ultimo accesso
int GETlastT(char* skID, KEY cID)
{
	ITEM item = BSTsearch(Skiers, cID);
	LIST x;

	for (x = item->skiUsed; x != NULL; x = x->next)
		if (strcmp(x->skiliftID, skID) == 0)
			return (x->last_use);

	return (-MAX_DAY);
}