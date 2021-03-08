#include "EDGE.h"

EDGE EDGEcreate(int v, int w, int wt)
{
	EDGE e; 

	e.v = v;
	e.w = w; 
	e.wt = wt; 

	return e;
}