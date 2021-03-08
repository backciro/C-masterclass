#include "ST.h"

typedef struct quasi_grafo *QG;

QG 		dataRead();

void	takeBest(QG qg);
void 	solve(QG qg);
void 	recurse(QG qg, int pos);
void	printBest(QG qg);