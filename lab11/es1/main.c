#include "GRAPH.h"

int getV() {
	int v;
	FILE* fp = fopen("./grafo.txt", "r");
	if (fp == NULL) exit(-1);
	fscanf(fp, "%d", &v);
	fclose(fp);
	return v;
}

int main()
{
	int V = getV(), S;

	GRAPH G = GRAPHinit(V);
	GRAPHread(G);

	fprintf(stdout, "1) stampa grafo\n"
	        "2) stampa lista adiacenze\n"
	        "3) genera e stampa matrice adiacenze\n");
	do 
	{
		fprintf(stdout, "effettuare una scelta: <1..3>\n");
		fscanf(stdin, "\n%d", &S);

		switch (S) {
			case 0:
				exit(0);

			case 1:
				GRAPHshow(G);
				break;

			case 2:
				ADJListPrint(G);
				break;

			case 3:
				ADJMatFromList(G);
				ADJMatPrint(G);
				break;
		}
	} while (1);
}