//
// created by Matteo Minutti on 14/11/2016
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo *link;

typedef enum {FALSE, TRUE} bool;

struct nodo
	{
	char *val;
	link next;
	};

void printList(link head, link sentinella);

link splitStringa(char *str, const char *t);

int main(void)
{
	char straux[100];
	char *str;
	const char *t = strdup(".");

	printf("Inserire una stringa separata dal separatore '%s'\n", t);
	scanf("\n%s", straux);
	printf("\n");

	str = malloc(strlen(straux) * sizeof(char));
	strcpy(str, straux);

	link x = malloc(sizeof *x);
	link head = malloc(sizeof *head);

	head = splitStringa(str, t);
	x = head;

	printList(head, x);
	printf("\n"); printf("\n"); 


	return 0;
}

link splitStringa(char *str, const char *t){

	link x ;
	link head = malloc(sizeof *head);

	int count = 0, i=0;

	while(str[i++] != t[0])
		count++;
		
	bool ciclo = TRUE;
	
	head -> val = malloc(count * sizeof (char));
	head -> val = strtok(str, t);
	head -> next = NULL;

	x = head;

	while(ciclo){
	
	count = 0;
	while( (str[i++] != t[0]) && i < strlen(str) )
		count++;

	x -> next = malloc(sizeof *x);
	x -> next -> val = malloc((count +1) * sizeof(char));
	x -> next -> val = strtok(NULL, t);

		if (x->val == NULL)
			ciclo = FALSE;
	
	x = x -> next;
	}

	return head;
}

void printList(link head, link sentinella){

	if ( (head->val) == NULL )
		return;

	printf("%s -> ", head->val);
	printList(head->next, sentinella);

	if ( !strcmp(head->val, sentinella->val) )
		printf("/");
	return;
}