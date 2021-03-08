#include "ITEM.h"

#ifndef _HEADER1
#define _HEADER1 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DAY 1440

typedef enum {FALSE, TRUE} bool;

#endif

#ifndef SKILIFT_H
#define SKILIFT_H 1

typedef struct skilift_t* SKI;

struct skilift_t
{
	char* skiliftID;
	int time_interval;
};

SKI SKIget();

bool authorize(KEY cardId, char* skiliftId, int time);

int GETinterval(char* str, KEY k);
int GETlastT(char* str, KEY k);


#endif