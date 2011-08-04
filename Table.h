/* 
 * File:   Table.h
 * Author: lmouhat
 *
 * Created on 3 août 2011, 15:56
 */

#ifndef TABLE_H
#define	TABLE_H

#include "Objet.h"

/* le type Table */
struct s_Table {
  Objet** element; /* un tableau de pointeurs vers les objets */
  int nMax; /* nombre max. d'éléments dans la table */
  int n; /* nombre réel d'éléments dans la table */
  char* (*toString) (Objet*);
  int (*comparer) (Objet*, Objet*);
};
typedef struct s_Table Table;

/*
 * Les fonctions publiques
 */
Table* tableCreer(int nMax, char* (*toString) (Objet*), \
        int (*comparer) (Objet*, Objet*));
Table* tableCreerDefaut(int nMax);
void tableDetruire(Table* table);

int tableAjouter(Table* table, Objet* objet);
int tableTaille(Table* table);
Objet* tableElement(Table* table, int pos);

void tableAfficher(Table* table);
void tableTriInsertion(Table* table);




#endif	/* TABLE_H */

