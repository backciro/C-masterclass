#include "esercizio.h"
#include "categoria.h"

int main()
{
	wr wrap;

	wrap = allocaWrapper();

	stampaS(wrap);
	
	callRec(wrap);

	return 0;
}