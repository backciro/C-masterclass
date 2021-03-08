//
// created by Matteo Minutti on 09/11/2016
//
// Massimo valore calcolabile per la sequenza: N = 131027
#include <stdio.h>
#include <stdlib.h>
const int Q1 = 1, Q2 = 1;

void Hofstadter(long *Q, long N, long *k);

int main() {

  long *Hof;
  long N;
  long k = 2;

  printf("Dove vuoi arrivare con Hofstadter? \n");
  scanf("\n%ld", &N);

  Hof = calloc(N, sizeof(long));

  Hof[0] = Q1;
  Hof[1] = Q2;

  if (N <= 0) {
    printf("Errore nella sequenza!\nProvare un altro numero\n");
    printf("\n");
    exit(EXIT_FAILURE);
  }

  if (N <= 2) {
    for (int i = 0; i < N; i++)
      printf("%ld, ", Hof[i]);
    printf("\n");
    exit(EXIT_SUCCESS);
  }

  Hofstadter(Hof, N + 2, &k); // chiamata alla funzione ricorsiva; N.B. alla
                              // funzione passo N+2 perchè ho fatto partire il
                              // contatore da k=2 in riga :12;
  printf("\n");

  return 0;
}

void Hofstadter(long *Q, long N, long *k) {

  long k1 = Q[*k - 1], k2 = Q[*k - 2];

  if (*k == N)
    return;

  Q[(*k)++] = Q[*k - k1] + Q[*k - k2];

  printf("%ld, ", Q[*k - 3]);

  Hofstadter(Q, N, k); //  chiamata ricorsiva;

  return;
}