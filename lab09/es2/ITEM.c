#include "PQ.h"

static char buf[100];

Key KEYget(Item data)
{
	return (data->nomeP);
}

int KEYcompare(Key k1, Key k2)
{
	return (strcmp(k1, k2));
}

Item ITEMnew()
{
	Item val = malloc(sizeof(*val));

	if (val == NULL)
		return ITEMsetvoid();
	
	val->nomeP = NULL;
	val->punteggio = 10.0;

	return val;
}

Item ITEMscan()
{
	Item val = ITEMnew();

	if (val != NULL) {
		printf("Inserisci nome giocatore:\n");
		scanf("\n%s", buf);
		val->nomeP = strdup(buf);
	}

	return val;
}

Item ITEMbufferScan(FILE* fp)
{
	Item val = ITEMnew();

	if (val != NULL) {
		fscanf(fp, "%s", buf);
		val->nomeP = strdup(buf);
	}

	return val;
}

Item ITEMsetvoid()
{
	Item val = malloc(sizeof(*val));

	val->nomeP = NULL;
	val->punteggio = 0;

	return val;
}

void ITEMdisplay(Item data, int s, FILE* fpout)
{
	if (!s)
		printf("%s %.1f\n", data->nomeP, data->punteggio);

	if (s)
		fprintf(fpout, "%s %.1f\n", data->nomeP, data->punteggio);
}

void ITEMfree(Item data)
{
	if (data->nomeP != NULL)
	{
		free(data->nomeP);
		free(data);
	}
}

void PlayerInsert()
{
	PQinsert(NULL);
}

void PlayerDelete()
{
	PQdelete(NULL);
}

void BufferInsert()
{
	FILE *fp = fopen("./players.txt", "r");

	PQinsert(fp);
	fclose(fp);
}

void saveRanking()
{
	FILE *fpout = fopen("./out.txt", "w");

	PQdisplay(fpout, 1);
	fclose(fpout);
}

void MATCH()
{
	int whowin;
	Item s1, s2;

	s1 = PQextractLess();
	s2 = PQextract2Less(s1);

	whowin = ((rand() % 2) + 1);

	if (whowin == 1) {
		s1->punteggio += (s2->punteggio) / 4;
		s2->punteggio -= (s2->punteggio) / 4;
	}

	if (whowin == 2) {
		s2->punteggio += (s1->punteggio) / 4;
		s1->punteggio -= (s1->punteggio) / 4;
	}

	if (s1->punteggio < 0.1) {
		PQdelete(s1);
	}

	if (s2->punteggio < 0.1) {
		PQdelete(s2);
	}

	if (s1->punteggio) {
		PQchange(s1);
	}

	if (s2->punteggio) {
		PQchange(s2);
	}
}