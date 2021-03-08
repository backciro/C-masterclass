#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct list_t* LIST;

LIST 	LIST_init() ;
void 	LIST_add(LIST L, int S) ;
void 	LIST_print(LIST L) ;
void 	LIST_remove(LIST L) ;
int 	LIST_clear(LIST L) ;
