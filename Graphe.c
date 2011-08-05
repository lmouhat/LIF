#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graphe.h"

/*
 * Déclaration des fonctions locales
 */

static int comparerChaine(Objet* objet1, Objet* objet2);
static char* toString(Objet* objet);


/*
 * Fonctions publiques
 */

/** @brief Création du graphe
 *  @param nMax Le nombre de sommets max
 *  @param value {0,1} Indique si le graphe est valué
 *  @param toString Pointeur de fonction vers la fonction d'affichage
 *  @param comparer Pointeur de fonction vers la fonction de comparaison
 *  @return Pointeur vers le graphe
 */
Graphe* grapheCreer(int nMax, int value, char* (*toString) (Objet*), \
        int (*comparer) (Objet*, Objet*)) {
  Graphe* graphe = malloc(sizeof(Graphe));
  graphe->table = tableCreer(nMax, toString, comparer);
  graphe->value = value;
  
  return graphe;
}

/** @brief Création du graphe avec les paramètres par défaut
 *  @param nMax Le nombre de sommets max
 *  @param value {0,1} Indique si le graphe est valué
 *  @return Pointeur vers le graphe
 */
Graphe* grapheCreerDefaut(int nMax, int value) {
  return grapheCreer(nMax, value, toString, comparerChaine);
}

/** @brief Destruction d'un graphe
 *  @param graphe Le graphe à détruire
 *  @return rien
 */
void grapheDetruire(Graphe* graphe) {
  tableDetruire(graphe->table);
  free(graphe);
}


/*
 * Fonctions locales
 */

/* comparer deux chaînes de caractères
   fournit <0 si ch1 < ch2; 0 si ch1=ch2; >0 sinon */
static int comparerChaine(Objet* objet1, Objet* objet2) {
  return strcmp((char*) objet1, (char*) objet2);
}

/* retourne une chaine de caractères */
static char* toString(Objet* objet) {
  return (char*) objet;
}