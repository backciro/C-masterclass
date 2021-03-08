#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum {FALSE, TRUE} bool;

typedef struct 
{
	int x;
	int y;
	double dist;
} Item;

typedef struct nodo *link;

typedef struct nodo
{
	Item val;
	link next;
} punto;

double distanzaO(int x, int y);

link getTesta(link* head);

void printLista(link head, int count);

link newNode(int x, int y, link next);

void inserisciDati(link* head, int x, int y);

int main()
{
	link head = NULL;

	head = getTesta(&head);

	printLista(head, 1);

	return 0;
}

link newNode(int x, int y, link next)
{ 	
	link p = malloc(sizeof *p); 
	
	if (p == NULL)
		return NULL; 

	else { 
		p->val.dist = distanzaO(x,y); 
		p->val.x = x;
		p->val.y = y;
		p->next = next;
	} return p;
}

link getTesta(link* head)
{
	int x = -1;
	int y = -1;

	link *h = head;

	while ( ((x != 0) || (y != 0)) ){

		printf("Inserie due punti del piano cartesiano: \n");
		scanf("\n%d%d", &x, &y);

		inserisciDati(head, x, y);
	}

	return (*h);
}

void inserisciDati(link* head, int x, int y)
{
	link r;
	link s;
	link t;

	bool inserito = FALSE;
	double d = distanzaO(x,y);

	if ( ((x == 0) && (y == 0)) )
		return;

	if ( (*head) == NULL ){
		s = newNode(x, y, NULL);
		(*head) = s;
	}

	else {
		if ( ((*head)->val.dist) > d ){
			s = newNode(x, y, (*head));
			(*head) = s;
		}

		else {
			r = (*head);
			
			for (t = (*head); t->next != NULL; t = t->next){
				
				if (t->next->val.dist > d){
					s = newNode(x, y, t->next);
					t->next = s;
					inserito = TRUE;
					break;
				}

				r = t->next;
			}
			
			if (!inserito){
				s = newNode(x, y, NULL);
				r->next = s;
			}
		}
	}

	return ;
}

void printLista(link head, int count)
{
	if (head == NULL){
		printf("\n");
		return;
	}	
		printf("punto %d: (%d, %d) = distanza origine: %.2f \n", count, head->val.x, head->val.y, head->val.dist);
		printLista(head->next, count+1);	
}

double distanzaO(int x, int y)
{
	double res;

	res = (x * x) + (y * y);

	return sqrt(res);
}
