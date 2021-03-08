#include "GRAPH.h"

int getS()
{
	int S;
	FILE* fp = fopen("./tempio.txt", "r");
	fscanf(fp, "%d", &S);
	fclose(fp);
	return S;
}

int main()
{
	int S;

	GRAPH G = GRAPHinit(getS());
	GRAPHread(G);

	fprintf(stdout, "-- EFFETTUE UNA SCELTA : --\n"
	        "1) Stampa Grafo\n2) Genera BEST PATH\n");
	fscanf(stdin, "%d", &S);

	switch (S)
	{
		case 1:
			GRAPHshow(G);
			break;

		case 2:
			GRAPHbestPath(G);
			break;
	}
}