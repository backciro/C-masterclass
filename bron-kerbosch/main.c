#include "header.h"

GRAPH G;

int main()
{
	G = GRAPHinit(MAXVERTEX);
	GRAPHread(G);

	int k = serial(G);
}