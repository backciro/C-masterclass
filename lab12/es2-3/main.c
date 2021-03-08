/* programma principale */
#include "POWERSET.h"


int main()
{
  QG database = dataRead();

  solve(database);

  printBest(database);

  return 0;
}

