#include "PQ.h"

static link head, tail;

char str[50];

link newNode(link next, FILE* fp)
{
	int i = 0;
	link d = malloc(sizeof(*d));

	if (fp == NULL)
	{
		d->player = ITEMscan();
		d->next = next;
	}

	else {

		d->player = ITEMbufferScan(fp);
		d->next = next;
		i++;
	}

	return d;
}

void PQinit()
{
	head = tail = NULL;
}

bool PQempty()
{
	return (head == NULL);
}

void PQinsert(FILE* fp)
{
	link i;
	int k;

	if (fp == NULL) {
		if (head == NULL) {
			head = tail = newNode(NULL, NULL);
		}

		else {
			head = newNode(head, NULL);
		}
	}

	else {
		k = 0;
		fscanf(fp, "%d", &s);
		while (k < s) {
			if (head == NULL) {
				head = tail = newNode(NULL, fp);
			}

			else {
				head = newNode(head, fp);
			} k++;
		}
	}
}

Item PQextractLess()
{
	link x;
	Item tmp;
	float min = 100;

	if (PQempty()) {
		return ITEMsetvoid();
	}

	for (x = head; x != NULL; x = x->next) {
		if (x->player->punteggio < min) {
			min = x->player->punteggio;
			tmp = x->player;
		}
	}

	return tmp;
}

Item PQextract2Less(Item data)
{
	link x;
	Item tmp;
	float min = 100;

	if (PQempty()) {
		printf("\n ! ! PQ empty ! !\n\n");
		return ITEMsetvoid();
	}

	for (x = head; x != NULL; x = x->next) {
		if ((x->player->punteggio <= min) &&
		        (x->player->punteggio >= data->punteggio) &&
		        (KEYcompare(KEYget(data), KEYget(x->player)) != 0) ) {
			min = x->player->punteggio;
			tmp = x->player;
		}
	}

	return tmp;
}

void PQdisplay(FILE* fp, int s)
{
	link x;

	for (x = head; x != NULL; x = x->next)
		ITEMdisplay(x->player, s, fp);
}

void PQdelete(Item data)
{
	link x, p;

	if (data == NULL) {
		printf("\nQuale giocatore vuoi eliminare?\n");
		scanf("\n%s", str);

		for (p = NULL, x = head; x != NULL; p = x, x = x->next) {
			if (KEYcompare(str, KEYget(x->player)) == 0)
			{
				if (p == NULL) {
					head = x->next;
					free(x);
				}

				else {
					p->next = x->next;
					free(x);
				}
			}
		}
	}

	else {
		for (p = NULL, x = head; x != NULL; p = x, x = x->next) {
			if (KEYcompare(data->nomeP, KEYget(x->player)) == 0)
			{
				p->next = x->next;
				free(x);
			}
		}
	}
}

void PQchange(Item data)
{
	link x;

	for (x = head; x != NULL; x = x->next)
	{
		if (KEYcompare(KEYget(data), KEYget(x->player)) == 0) {
			x->player->punteggio = data->punteggio;
		}
	}
}