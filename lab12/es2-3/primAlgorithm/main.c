#include "GRAPH.h"

int S;


int getV() {
	int v;
	FILE* fp = fopen("./amici.txt", "r");
	if (fp == NULL) exit(-1);
	fscanf(fp, "%d", &v);
	fclose(fp);
	return v;
}

int main()
{
	GRAPH G = GRAPHinit(getV());
	GRAPHread(G);

	fprintf(stdout, "\n*** ATTENZIONE!! ACHTUNG!! WARNING!! ***\n"
		"PROGRAMMA SVILUPPATO PER SMART INC.\n"
		"IL PROGRAMMA FUNZIONA SOLO CON MACCHINE Smart ForTwo DELLA COMPAGNIA! \n"
		"premi 1 per procedere ...\n\n");
	fscanf(stdin, "\n%d", &S);

	switch (S) {
	default:
		exit(0);

	case 1:
		GRAPHmstPrim(G);
		break;
	}
	return 0;
}