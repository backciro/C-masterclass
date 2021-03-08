#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAXS 11 /* 10 + 1 per '\0' */

// Definizione delle strutture dati usate
typedef enum {FALSE, TRUE} bool;

typedef struct nodo* link;

struct nodo {
  char val[MAXS];
  link left;
  link right;
};

link new_nodo(char *val);
link leggi_nodo(FILE *in);
link leggi_albero(char *filename);

void libera_albero(link root);
void display_albero(link root);
void contaCompleti(link n, int L1, int L2, int level, int *count);
int contaArchi(bool *found1, bool *found2, link n, char *k1, char *k2);
void distanza(int *count1, int *count2, bool *found1, bool *found2, bool *camCom, int *cntCom, link n, char *k1, char *k2);
int height(link h);
void checkSwap(char *str1, char *str2, bool *swap);

int main(int argc, char **argv) {
  
    int L1, L2, count;
    int *mark;
    int cnt;
    char str1[4], str2[4];
    bool found1 = FALSE;
    bool found2 = FALSE;
    bool swap = FALSE;

    link root;
    root = leggi_albero(argv[1]);
    printf("\n"); display_albero(root);

    //contaNodi
    printf("\ninserire intervallo dei livelli da analizzare: \n");
    scanf("%d%d", &L1, &L2);

    if( (L1 < 0) || (L2 > height(root)) )
        printf("Errore nella scelta dei livelli\n Altezza massima albero = %d\n", height(root));

    if( (L1 >= 0) && (L2 <= height(root)) )
    {
        contaCompleti(root, L1, L2, 0, &count);
        printf("\nnodi completi: %d\n", count);
    }

    //contaArchi
    printf("\ninserire nodo partenza e nodo arrivo per contare gli archi\n");
    scanf("%s%s", str1, str2);

    checkSwap(str1, str2, &swap);

    cnt = contaArchi(&found1, &found2, root, str1, str2);

    if (swap)
    printf("Archi tra %s e %s : %d\n\n", str2, str1, cnt);    
    
    if (!swap)
    printf("Archi tra %s e %s : %d\n\n", str1, str2, cnt);    

    //
      
    libera_albero(root);
    return 0;
    }

link new_nodo(char *val) {
    link n = malloc(1*sizeof(*n));
    strcpy (n->val,val);
    n->left = NULL;
    n->right = NULL;
    return n;
}

link leggi_nodo(FILE *in) {
    char val[MAXS];
    int l, r;
    if (fscanf(in, "%s %d %d", val, &l, &r) != 3) return NULL;
    link n = new_nodo(val);
    if (l!=0) n->left = leggi_nodo(in);
    if (r!=0) n->right = leggi_nodo(in);
    return n;
}

link leggi_albero(char *filename) {
    FILE *in;
    in = fopen(filename, "r");
    link root = leggi_nodo(in);
    fclose(in);
    return root;
}

void display_albero(link root) {
    if (root == NULL) 
      return;
    
    printf("nodo %s\n", root->val);
    display_albero(root->left);
    display_albero(root->right);
}

void libera_albero(link root) {
    if (root == NULL) 
      return;
    libera_albero(root->left);
    libera_albero(root->right);
    free(root);
}

void contaCompleti(link n, int L1, int L2, int level, int *count) {

  if (n == NULL)
    return ;

    if ((level>=L1) && (level<=L2)) {
        if ((n->left != NULL) && (n->right != NULL))
            (*count)++;
    }   

    contaCompleti(n->left, L1, L2, level+1, count);
    contaCompleti(n->right, L1, L2, level+1, count);
}

int contaArchi(bool *found1, bool *found2, link n, char *k1, char *k2){

    link rt = n;

    int cnt = 0;
    int count1 = 0, count2 = 0;
    int cnt1 = 0, cnt2 = 0;
    bool camCom = FALSE;
    int cntCom = 0;
    int aux = 0;

    char *temp = strdup(rt->val);

    if ((strcmp(k1, n->val) <= 0 && strcmp(k2, n->val) <= 0) || 
        (strcmp(k1, n->val) >= 0 && strcmp(k2, n->val) >= 0)) 
    {
        distanza(&cnt1, &cnt2, found1, found2, &camCom, &cntCom, rt, temp, k1);

        *found1 = FALSE;    *found2 = FALSE;
        count1 = (cnt1 + cnt2);
        cnt1 = 0;   cnt2 = 0;

        if(camCom)
            aux = cntCom;
        camCom = FALSE; cntCom = 0;

        distanza(&cnt1, &cnt2, found1, found2, &camCom, &cntCom, rt, temp, k2);
        
        count2 = (cnt1 + cnt2);

        if ( count1 > count2 )
            cnt = (count1 - count2);

        if ( count2 > count1 )
            cnt = (count2 - count1);

        if (camCom) 
        {   
        aux += cntCom;

        if ( count1 > count2 )
            cnt = (count1 - aux) + abs(count2 - aux); 

        if ( count2 > count1 )
            cnt = (count2 - aux) + abs(count1 - aux); 
        
        if ( count1 == count2)
            cnt = abs(count1 - aux) + abs(count2 - aux); 
        }
    }

    else if ((strcmp(k1, n->val) < 0 && strcmp(k2, n->val) > 0) || 
        (strcmp(k1, n->val) > 0 && strcmp(k2, n->val) < 0))
    {    
        distanza(&count1, &count2, found1, found2, &camCom, &cntCom, rt, temp, k1);

        cnt = (count1 + count2) ;

        *found1 = FALSE;  *found2 = FALSE;
        count1=0;   count2=0;

        distanza(&count1, &count2, found1, found2, &camCom, &cntCom, rt, temp, k2);

        cnt += (count1 + count2) ;   
    }

    return cnt;
}

void distanza(int *count1, int *count2, bool *found1, bool *found2, bool *camCom, int *cntCom, link n, char *k1, char *k2) {

    if ( ((*found1) && (*found2)) ){
        return ;
    }
    
    //controllo ricorsivo su k1
    if ( !(*found1) && strcmp(k1, n->val ) == 0)
    {
        (*found1) = TRUE;
        (*count1) += 0;
    }

    if( !(*found1) && strcmp(k1, n->val ) < 0)
    {
        if ( strcmp(k1, n->val ) < 0 && strcmp(k2, n->val ) < 0 )
        {
            (*camCom) = TRUE;
            (*cntCom) += 1;
        }

        (*count1) += 1;
        distanza(count1, count2, found1, found2, camCom, cntCom, n->left, k1, k2);    
    }
        
    if( !(*found1) && strcmp(k1, n->val) > 0)
    {       
        if ( strcmp(k1, n->val ) > 0 && strcmp(k2, n->val ) > 0 )
        {
            (*camCom) = TRUE;
            (*cntCom) += 1;
        }
        (*count1) += 1;
        distanza(count1, count2, found1, found2, camCom, cntCom, n->right, k1, k2);    
    }

    if (!*found1) 
    {
        (*found1) = TRUE;
    }

    //controllo ricorsivo su k2
    if ( !(*found2) && strcmp(k2, n->val ) == 0)
    {
        (*found2) = TRUE;
        (*count2) += 0;
    }

    if( !(*found2) && strcmp(k2, n->val ) < 0)
    {
        if ( strcmp(k1, n->val ) < 0 && strcmp(k2, n->val ) < 0 )
        {
            (*camCom) = TRUE;
            (*cntCom) += 1;
        }
        (*count2) += 1;
        distanza(count1, count2, found1, found2, camCom, cntCom, n->left, k1, k2);     
    }
        
    if( !(*found2) && strcmp(k2, n->val) > 0)
    {
        if ( strcmp(k1, n->val ) > 0 && strcmp(k2, n->val) > 0 )
        {
            (*camCom) = TRUE;
            (*cntCom) += 1;
        }
        (*count2) += 1;
        distanza(count1, count2, found1, found2, camCom, cntCom, n->right, k1, k2);      
    }

    if (!*found2) {
        (*found2) = TRUE;
    }
    
    return;
}

int height(link h){
  int u, v;

    if (h == NULL)
      return -1;

    u = height(h->left); 
    v = height(h->right);

    if (u>v)
      return u+1;

    else
      return v+1;
}

void checkSwap(char *str1, char *str2, bool *swap){

    char *temp;

    if(strcmp(str1, str2) < 0){
        temp = malloc(strlen(str1) * sizeof(char));
        strcpy(temp, str1);
        strcpy(str1, str2);
        strcpy(str2, temp);
        (*swap) = TRUE;
    }

    return;
}
