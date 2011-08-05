/**
 * @brief       Module TDA Table
 * @file        Table.h
 * @author      lmouhat@gmail.com
 * @date        2011/08/03
 *
 */

#ifndef TABLE_H
#define	TABLE_H

#include "Objet.h"

/** @struct s_Table
 *  @brief La structure d'une table
 */
struct s_Table {
  Objet** element; /* un tableau de pointeurs vers les objets */
  int nMax; /* nombre max. d'éléments dans la table */
  int n; /* nombre réel d'éléments dans la table */
  char* (*toString) (Objet*);
  int (*comparer) (Objet*, Objet*);
};

/** @typedef Table
 *  @brief Le type Table
 */
typedef struct s_Table Table;


/*
 * Les fonctions publiques
 */

/* construction - destruction */
Table* tableCreer(int nMax, char* (*toString) (Objet*), \
        int (*comparer) (Objet*, Objet*));
Table* tableCreerDefaut(int nMax);
void tableDetruire(Table* table);

/* opérations élémentaires */
int tableAjouter(Table* table, Objet* objet);
int tableTaille(Table* table);
Objet* tableElement(Table* table, int pos);

/* recherche */
Objet* tableRechercheSeq(Table* table, Objet* objet);
Objet* tableRechercheDicho(Table* table, Objet* objet);

/* affichage et tri */
void tableAfficher(Table* table);
void tableTriInsertion(Table* table);
void tableTriRapide(Table* table);




#endif	/* TABLE_H */

