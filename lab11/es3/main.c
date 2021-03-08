//**********************************************************************************************//
/* il programma, dopo aver acquisito i dati da tastiera chiama la funzione 'isAcceptable'		*/
/* che genera un multiset di disposizioni ripetute per vedere se esistono di soluzioni			*/
/* la quale combinazione sommata diano la lunghezza della parola, dopodichè genera il multiset	*/
/* delle permutazioni (semplici o ripetute a seconda di cosa ritorna la funzione 'doppioni'		*/
/* che comunque si occupa di variare la cardinalita di n_dist, e di riallocare).				*/
/* Passo finale: funzione 'decomponi', che ricorsivamente stampa gli indici giusti presi dal 	*/
/* vettore ricevuto di lunghezza 'num'.															*/
//**********************************************************************************************//
#include "HEADER1.h"
#include "ACCEPTABILITY.h"

int main()
{
	char str[255] ;
	int lungh[50] ;

	char* strD ;
	int* lunghD ;

	int cardStr, cardLung ;
	int N ;

	printf("Inserire una parola: \n") ;
	scanf("\n%s", str) ;
	cardStr = strlen(str) ;

	printf("Inserire UN valore N e DI SEGUITO N lunghezze: \n") ;
	scanf("%d", &cardLung) ;

	lungh[0] = 0 ; // creazione dell'insieme vuoto!
	cardLung += 1 ;

	for (int i = 1; i < cardLung; i++)
		scanf("%d", &lungh[i]) ;

	strD = malloc(cardStr * sizeof(int)) ;
	strncpy(strD, str, cardStr)	;
	lunghD = malloc(cardLung * sizeof(int)) ;
	lunghD = lungh ;

	N = cardLung ;

	isAcceptable(strD, lunghD, N) ;

	return 0 ;
}

void decomponi(char *str, int num, int *lungh, int i, int start)
{
	if (i >= num)
		return ;

	for (int j = start ; j < start + lungh[i] ; j++)
		printf("%c", str[j]) ;

	printf("   ") ;
	start += lungh[i] ;

	decomponi(str, num, lungh, i + 1, start) ;
	return ;
}