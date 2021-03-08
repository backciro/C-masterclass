#include "PQ.h"
#include "ITEM.h"

int main(int argc, char *argv[]) {

	PQ pq = PQinit(7);

	PQinsert(pq, ITEMnew("bene", 2));
	PQinsert(pq, ITEMnew("va?", 8));
	PQinsert(pq, ITEMnew("ciao", 15));
	PQinsert(pq, ITEMnew("tutto", 4));
	PQinsert(pq, ITEMnew("io", 6));
	PQinsert(pq, ITEMnew("come", 10));
	PQinsert(pq, ITEMnew("grazie!", 1));

	while (!PQempty(pq)) 
		ITEMshow(PQget(pq));

	return 0;
}