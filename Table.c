/* 
 * File:   Table.c
 * Author: lmouhat
 *
 * Created on 3 août 2011, 15:56
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Table.h"

/* Déclaration des fonctions locales */

/* comparer deux chaînes de caractères
   fournit <0 si ch1 < ch2; 0 si ch1=ch2; >0 sinon */
static int comparerChaine(Objet* objet1, Objet* objet2) {
  return strcmp((char*) objet1, (char*) objet2);
}

static char* toString(Objet* objet) {
  return (char*) objet;
}

static void tablePermuter(Table* table, int i, int j);

/* Fonctions publiques */

Table* tableCreer(int nMax, char* (*toString) (Objet*), \
        int (*comparer) (Objet*, Objet*)) {
  Table* table = malloc(sizeof (Table));
  table->nMax = nMax;
  table->element = malloc(sizeof (Objet*) * nMax);
  table->n = 0;
  table->comparer = comparer;
  table->toString = toString;

  return table;
}

Table* tableCreerDefaut(int nMax) {
  return tableCreer(nMax, toString, comparerChaine);
}

void tableDetruire(Table* table) {
  free(table->element);
  free(table);
}

int tableTaille(Table* table) {
  return table->n;
}

int tableAjouter(Table* table, Objet* objet) {
  int i;
  if (table->n < table->nMax) {
    i = table->n++;
    table->element[i] = objet;
    return 1;
  } else {
    return 0;
  }
}


Objet* tableElement(Table* table, int i) {
  Objet* objet;
  if ((i >= 0) && (i < table->n)) {
    objet = table->element[i];
    return objet;
  } else {
    return NULL;
  }
}

void tableAfficher(Table* table) {
  Objet* objet;
  int i;

  for (i = 0; i < tableTaille(table); i++) {
    objet = tableElement(table, i);
    printf("%d.%s ", i, table->toString(objet));
  }
  printf("\n");
}

/*
void triInsertion(int *tab, int taille) {
  int i,j,cle;
  
  for(j=1;j<taille;j++) {
    cle = tab[j];
    i = j-1;
    while(i>=0 && tab[i] > cle) {
      tab[i+1] = tab[i];
      i--;
    }
    tab[i+1] = cle;
  }
}
*/

void tableTriInsertion(Table* table) {
  int i, j;
  Objet* cle;
  
  for(j=1; j<table->n; j++) {
    cle = table->element[j];
    i = j-1;
    while(i >= 0 && table->comparer(table->element[i], cle) > 0) {
      table->element[i+1] = table->element[i];
      i--;
    }
    table->element[i+1] = cle;
  }
}

void tableTriRapide(Table* table) {
  
}



/*
 * Fonctions locales
 */

static void tablePermuter(Table* table, int i, int j) {
  Objet* tmp = table->element[i];
  table->element[i] = table->element[j];
  table->element[j] = tmp;
}