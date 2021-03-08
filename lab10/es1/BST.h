#include "ITEM.h"

#ifndef _HEADER1
#define _HEADER1 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DAY 1440

typedef enum {FALSE, TRUE} bool;

#endif

#ifndef BST_H
#define BST_H 1

typedef struct binarysearchtree *BST;

BST BSTinit() ;
ITEM BSTsearch(BST b, KEY k) ;
void BSTinsert_root(BST* b, ITEM i) ;
void BSTupdate_node(BST* b, ITEM i) ;

#endif