#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Table.h"


/*
 * Déclaration des fonctions locales
 */

static int comparerChaine(Objet* objet1, Objet* objet2);
static char* toString(Objet* objet);
static void tablePermuter(Table* table, int i, int j);


/*
 * Fonctions publiques
 */

/** @brief Création de la table
 *  @param table La table
 *  @param nMax Taille de la table
 *  @param toString Pointeur de fonction vers la fonction d'affichage
 *  @param comparer Pointeur de fonction vers la fonction de comparaison
 *  @return Pointeur vers la table
 */
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

/** @brief Création de la table par défaut
 *  @param nMax Taille de la table
 *  @return Pointeur vers la table
 */
Table* tableCreerDefaut(int nMax) {
  return tableCreer(nMax, toString, comparerChaine);
}

/** @brief Destruction de la table
 *  @param table La table
 *  @return rien
 */
void tableDetruire(Table* table) {
  free(table->element);
  free(table);
}

/** @brief Retourne la taille effective de la table
 *  @param table La table
 *  @return La taille effective de la table
 */
int tableTaille(Table* table) {
  return table->n;
}

/** @brief Ajout d'un objet à la table
 *  @param table La table destinataire
 *  @param objet L'objet à ajouter
 *  @return 1 si réussite, 0 si échec
 */
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

/** @brief Retourne l'objet à la position donnée
 *  @param table La table dans laquelle la consultation est effectuée
 *  @param pos La position
 *  @return Le pointeur vers l'objet ou NULL si non trouvé
 */
Objet* tableElement(Table* table, int pos) {
  Objet* objet;
  if ((pos >= 0) && (pos < table->n)) {
    objet = table->element[pos];
    return objet;
  } else {
    return NULL;
  }
}

/** @brief Recherche séquentielle d'un objet
 *  @param table La table dans laquelle la recherche est effectuée
 *  @param objet L'objet recherché
 *  @return Pointeur vers l'objet trouvé, sinon renvoie NULL
 */
Objet* tableRechercheSeq(Table* table, Objet* objet) {
  int i = 0;
  Objet* trouve = NULL;
  
  while((i < table->n) && (trouve == NULL)) {
    if(table->comparer(table->element[i], objet) == 0) {
      trouve = table->element[i];
    }
    i++;
  }
  
  return trouve;
}

/** @brief Recherche dichotomique d'un objet
 *  @param table La table dans laquelle la recherche est effectuée
 *  @param objet L'objet recherché
 *  @return Pointeur vers l'objet trouvé, sinon renvoie NULL
 */
Objet* tableRechercheDicho(Table* table, Objet* objet) {
  Objet* trouve = NULL;
  int gauche = 0;
  int droite = table->n - 1;
  int pos;
  int comp;
  
  while((trouve == NULL) && (gauche <= droite)) {
    pos = (droite + gauche) / 2;
    comp = table->comparer(table->element[pos], objet);
    if(comp == 0) {
      trouve = table->element[pos];
    } else if(comp > 0) {
      droite = pos - 1;
    } else {
      gauche = pos + 1;
    }
  }
  
  return trouve;
}

/** @brief Affichage de la table
 *  @param table La table à afficher
 *  @return rien
 */
void tableAfficher(Table* table) {
  Objet* objet;
  int i;

  for (i = 0; i < tableTaille(table); i++) {
    objet = tableElement(table, i);
    printf("%d.%s ", i, table->toString(objet));
  }
  printf("\n");
}

/** @brief Tri par insertion de la table
 *  @param table La table à trier
 *  @return rien
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

/** @brief Tri rapide de la table
 *  @param table La table à trier
 *  @return rien
 *  @todo A programmer
 */
void tableTriRapide(Table* table) {
  
}


/*
 * Fonctions locales
 */

/* permuter 2 objets de la table */
static void tablePermuter(Table* table, int i, int j) {
  Objet* tmp = table->element[i];
  table->element[i] = table->element[j];
  table->element[j] = tmp;
}

/* comparer deux chaînes de caractères
   fournit <0 si ch1 < ch2; 0 si ch1=ch2; >0 sinon */
static int comparerChaine(Objet* objet1, Objet* objet2) {
  return strcmp((char*) objet1, (char*) objet2);
}

/* retourne une chaine de caractères */
static char* toString(Objet* objet) {
  return (char*) objet;
}