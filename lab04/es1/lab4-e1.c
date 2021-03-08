#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXC 10
#define MAXS 25

typedef struct {
  char codice[MAXC],*nome,*categoria;
  int quant;
  struct {
    int g,m,a;
  } data;
  float prezzo;
} Prodotto;

typedef enum {
  co_stampa,co_ordina,co_aggiorna,co_ricerca,co_fine,co_err
} Comando;
// variabile globale messa accanto al tipo enum per mantenerli allineati
char *comandi[co_err]={"stampa","ordina","aggiorna","ricerca","fine"
};
typedef enum {
  cr_tutto,cr_categoria,cr_prezzoAsc,cr_prezzoDis,cr_codice,cr_nome,cr_nomeParziale,cr_err
} Criterio;
// variabile globale messa accanto al tipo enum per mantenerli allineati
char *criteri[cr_err]={
  "tutto","categoria","prezzoAsc","prezzoDis","codice","nome","nomeParziale"
};

typedef struct {
  Comando com;
  Criterio crit;
  char altro[2*MAXS]; // sovradimensionato per eventuali comandi lunghi
} ComandoCompleto;

int leggiCatalogo(Prodotto **catP);
void stampaProdotto(Prodotto p, FILE *fp);
void stampaCatalogo(Prodotto *cat, int np, FILE *f, Criterio crit);
void stampaCategorie(Prodotto *cat, int np, Criterio crit);
ComandoCompleto leggiComando();
int confrontaProdotti (Prodotto a, Prodotto b, Criterio crit);
void ordinaCatalogo (Prodotto *cat, int np, Criterio crit);
void ricercaStampa(Prodotto *cat, int np, char *s, Criterio crit, Criterio ord);
void aggiorna(Prodotto *cat, int np, char *s, Criterio crit, Criterio ord);

int main()
{
  Prodotto *catalogo;
  char str[MAXS];
  int ord=0,i,np,fine=0;
  Criterio ordinamentoAttuale=cr_err; // nessun ordinamento iniziale
  
  ComandoCompleto c;
  
  np = leggiCatalogo(&catalogo);
  if (np<=0) return 1;
  
  while(!fine) {
    c = leggiComando();
    switch(c.com) {
    case co_stampa:
      if (c.crit==cr_categoria) 
	stampaCategorie(catalogo,np,c.crit);
      else {
	if (strcmp(c.altro,"stdout")!=0) {
	  FILE *f = fopen(c.altro,"w");
	  if (f!=NULL) {
	    stampaCatalogo(catalogo,np,f,c.crit);
	    fclose(f);
	  }
	}
	else 
	  stampaCatalogo(catalogo,np,stdout,c.crit);
      }
      break;
    case co_ordina:
      ordinaCatalogo(catalogo,np,c.crit);
      ordinamentoAttuale = c.crit;
      break;
    case co_aggiorna:
      aggiorna(catalogo,np,c.altro,c.crit,ordinamentoAttuale);
      break;
    case co_ricerca:
      ricercaStampa(catalogo,np,c.altro,c.crit,ordinamentoAttuale);
      break;
    case co_fine:
      break;
    default:
      fine = 1; 
    }
  }

  return 0;
}

int leggiCatalogo(Prodotto **catP)
{
  FILE *fp;
  int i,lung, np;
  Prodotto *cat;
  char nome[MAXS], categoria[MAXS];
  
  fp=fopen("./catalogo.txt","r");
  if(fp==NULL) {
    fprintf(stderr,"Errore in apertura file");
    return 0;
  }
  fscanf(fp,"%d",&np);
  cat = (Prodotto *)malloc(np*sizeof(Prodotto));
  for(i=0; i<np; i++) {
    fscanf(fp,"%s %s %s %f %d %d/%d/%d",cat[i].codice,nome,categoria,
	   &cat[i].prezzo,&cat[i].quant,
	   &cat[i].data.g,&cat[i].data.m,&cat[i].data.a);
    cat[i].nome = strdup(nome);
    cat[i].categoria = strdup(categoria);
  }
  *catP=cat;
  return np;
}

void stampaProdotto(Prodotto p, FILE *fp) {
  fprintf(fp, "%s, %s, %s, %.2f, %d, %d/%d/%d\n", 
	  p.codice, p.nome, p.categoria, p.prezzo, p.quant, 
	  p.data.g, p.data.m, p.data.a);
}

void stampaCatalogo(Prodotto *cat, int np, FILE *f, Criterio crit) {
  int i;
  fprintf(f,"%d\n",np);
  for(i=0;i<np;i++)
    stampaProdotto(cat[i],f);
}

void stampaCategorie(Prodotto *cat, int np, Criterio crit) {
  int *stampato, i, j, nst=0;
  char *corrente;

  stampato = malloc(np*sizeof(int));
  if (stampato==NULL) return;

  for(i=0; i<np; i++)
    stampato[i]=0;

  while (nst<np) {
    corrente = NULL; // annulla puntatore per cercare il primo codice non stampato 
    for(i=0; i<np; i++) {
      if(!stampato[i]) {
	if (corrente==NULL) { // trovata nuova categoria
	  corrente = cat[i].categoria;
	  printf("\nCATEGORIA -> %s:\n", corrente);
	}
	if (strcmp(corrente,cat[i].categoria)==0) {
	  stampaProdotto(cat[i],stdout);
	  stampato[i] = 1;
	  nst++;
	}
      }
    }   
    printf("\n");
  }
  free (stampato);
}

Criterio leggiCriterio(Criterio ammessi[]) {
  int i;
  Criterio c;
  char str[MAXS];

  printf("Criteri ammessi:\n");
  for (i=0; ammessi[i]!=cr_err; i++) 
    printf(" %s", criteri[ammessi[i]]);
  printf("\nInserire un criterio: ");
  scanf("%s%*c",str);

  for (i=0; ammessi[i]!=cr_err; i++) {
    if (strcmp(str,criteri[ammessi[i]])==0) 
      return ammessi[i];
  }
  return cr_err;
}

ComandoCompleto leggiComando() {
  char str[MAXS];
  Comando c1;
  Criterio c2;
  ComandoCompleto c;

  printf("Comandi validi:\n");
  for (c1=co_stampa; c1<co_err; c1++)
    printf(" %s", comandi[c1]);
  printf("\nInserire un comando: ");
  scanf("%s%*c",str);
  c1=co_stampa;
  while(c1<co_err && strcmp(str,comandi[c1])!=0)
    c1++;

  c.com = c1;
  
  switch (c1) {
  case co_stampa:
    {
      Criterio ammessi[] = {cr_tutto,cr_categoria,cr_err};
      c.crit = leggiCriterio(ammessi);
      if (c.crit==cr_tutto) {
	printf("nome file (o stdout): ");
	scanf("%s%*c",c.altro);
      }
    }
    break;
  case co_ordina:
    {
      Criterio ammessi[] = {cr_codice,cr_nome,cr_prezzoAsc,cr_prezzoDis,cr_err};
      c.crit = leggiCriterio(ammessi);
    }
    break;
  case co_ricerca:
    {
      Criterio ammessi[] = {cr_codice,cr_nome,cr_nomeParziale,cr_err};
      c.crit = leggiCriterio(ammessi);
      printf("nome da cercare: ");
      scanf("%s*c",c.altro);
    }
    break;
  case co_aggiorna:
    {
      Criterio ammessi[] = {cr_codice,cr_nome,cr_err};
      c.crit = leggiCriterio(ammessi);
      printf("nome da aggiornare e quantita': ");
      fgets(c.altro,sizeof(c.altro),stdin);
    }
    break;
  case co_err:
  case co_fine:
  default:  
    break;
  }

  return c;
}

int confrontaProdotti (Prodotto a, Prodotto b, Criterio crit) {
  switch (crit) {
  case cr_categoria:
    return strcmp(a.categoria,b.categoria);
    break;
  case cr_prezzoAsc:
    return a.prezzo-b.prezzo;
    break;
  case cr_prezzoDis:
    return b.prezzo-a.prezzo;
    break;
  case cr_codice:
    return strcmp(a.codice,b.codice);
    break;
  case cr_nome:
    return strcmp(a.nome,b.nome);
    break;
  case cr_nomeParziale:
    { int l = strlen(b.nome);
      return strncmp(a.nome,b.nome,l);
    }
    break;
  default: fprintf(stderr,"codice errato in confronto prodotti");
    return 0; // risultato arbitrario
  }
}

void ordinaCatalogo (Prodotto *cat, int np, Criterio crit) {
  int i,j;
  Prodotto temp;

  for(i=1;i<np;i++) {
    temp=cat[i];
    j=i-1;
    while(j>=0 && confrontaProdotti(temp,cat[j],crit)<0) {
      cat[j+1]=cat[j];
      j--;
    }
    cat[j+1]=temp;
  }
}

int ricercaLineare (Prodotto *cat, int np, Prodotto p, Criterio crit) {
  int i;

  for(i=0;i<np;i++)
    if(confrontaProdotti(cat[i],p,crit)==0) {
      return i;
    }
  return -1;
}

int ricercaDicotomica(Prodotto *cat, int np, Prodotto p, Criterio crit) {
  int l=0, r=np-1;
  int m,i;
  while(l<=r) {
    m=l+(r-l)/2;
    if (confrontaProdotti(cat[m],p,crit)==0) {
      return m;
    }
    else if (confrontaProdotti(cat[m],p,crit)<0) 
      l=m+1;
    else r=m-1;
  }
  return -1;
}

void ricercaStampa(Prodotto *cat, int np, char *s, Criterio crit, Criterio ord) {
  int i, i0, i1;
  Prodotto tmp;
  if (crit==cr_codice)
    strcpy(tmp.codice,s);
  else tmp.nome=s;
  if (crit==ord)
    i = ricercaDicotomica(cat,np,tmp,crit);
  else
    i = ricercaLineare(cat,np,tmp,crit);
  if (i<0) {
    printf("prodotto non trovato\n");
    return;
  }

  for (i0=i-1; i0>=0 && confrontaProdotti(cat[i0],tmp,crit)==0; i0--);
  for (i1=i+1; i1<np && confrontaProdotti(cat[i1],tmp,crit)==0; i1++);
  
  for (i=i0+1; i<i1; i++) {
    stampaProdotto(cat[i],stdout);
  }
}

void aggiorna(Prodotto *cat, int np, char *s, Criterio crit, Criterio ord) {
  int i, q;
  char nome_o_codice[MAXS];
  Prodotto tmp;
  sscanf(s,"%s%d", nome_o_codice, &q);
  if (crit==cr_codice)
    strcpy(tmp.codice,nome_o_codice);
  else tmp.nome=nome_o_codice;
  if (crit==ord)
    i = ricercaDicotomica(cat,np,tmp,crit);
  else
    i = ricercaLineare(cat,np,tmp,crit);
  if (i<0) {
    printf("prodotto non trovato\n");
    return;
  }
  cat[i].quant = q;
  printf("Prodotto con quantita' aggiornata:\n");
  stampaProdotto(cat[i],stdout);
}

