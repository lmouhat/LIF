#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graphe.h"

/*
 * Déclaration des fonctions locales
 */

static int comparerChaineSommet(Objet* objet1, Objet* objet2);
static char* toStringSommet(Objet* objet);

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
  Graphe* graphe = malloc(sizeof (Graphe));
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
  return grapheCreer(nMax, value, toStringSommet, comparerChaineSommet);
}

/** @brief Destruction d'un graphe
 *  @param graphe Le graphe à détruire
 *  @return rien
 */
void grapheDetruire(Graphe* graphe) {
  int i, j, nb;
  Noeud* sommet;
  Arc* arc;

  for (i = 0; i < grapheNbSommets(graphe); i++) {
    sommet = grapheSommet(graphe, i);
    nb = listeNbElt(sommet->liste);
    for (j = 0; j < nb; j++) {
      arc = listeExtraireFin(sommet->liste);
      free(arc);
    }
    listeDetruire(sommet->liste);
    free(sommet);
  }

  tableDetruire(graphe->table);
  free(graphe);
}

/** @brief Ajout d'un noeud à un graphe
 *  @param graphe Le graphe de destination
 *  @param objet objet L'objet (le noeud) à ajouter au graphe
 *  @return rien
 */
void grapheAjouterSommet(Graphe* graphe, Objet* objet) {
  int retour = 0;
  Noeud* noeud = malloc(sizeof (Noeud));
  noeud->objet = objet;
  noeud->marque = 0;
  noeud->id = tableTaille(graphe->table);
  noeud->liste = listeCreerDefaut();
  retour = tableAjouter(graphe->table, noeud);
  if (retour == 0) {
    printf("Erreur : le sommet n'a pas pu être ajouté \n");
  } else {
    printf("Ajout du sommet %s réussit. \n", graphe->table->toString(noeud));
  }
}

/** @brief Ajout un arc à un graphe
 *  @param graphe Le graphe de destination
 *  @param init Le sommet initial
 *  @param term Le sommet terminal
 *  @param cout Le cout de l'arc
 *  @return rien
 */
void grapheAjouterArc(Graphe* graphe, Objet* init, Objet* term, int cout) {
  Arc* arc;
  Noeud* sommetInit;
  Noeud tmp;
  Noeud* sommetTerm;

  tmp.objet = init;
  sommetInit = tableRechercheSeq(graphe->table, &tmp.objet);
  if (sommetInit == NULL) {
    printf("Erreur : sommet initial non trouvé ! \n");
    return;
  }

  tmp.objet = term;
  sommetTerm = tableRechercheSeq(graphe->table, &tmp);
  if (sommetTerm == NULL) {
    printf("Erreur : sommet terminal non trouvé ! \n");
    return;
  }

  arc = malloc(sizeof (Arc));
  arc->extremite = sommetTerm;
  arc->cout = cout;
  listeAjouterFin(sommetInit->liste, arc);
  printf("Ajout de l'arc : %s vers %s \n", \
              graphe->table->toString(sommetInit), \
              graphe->table->toString(sommetTerm));
}

/** @brief Récupère le nième sommet du graphe
 *  @param graphe Le graphe
 *  @param n L'id du sommet
 *  @return Le noeud correspondant
 */
Noeud* grapheSommet(Graphe* graphe, int n) {
  return graphe->table->element[n];
}

/** @brief Récupère l'objet contenu dans le nième sommet du graphe
 *  @param graphe Le graphe
 *  @param n L'id du sommet
 *  @return L'objet encapsulé
 */
Objet* grapheObjet(Graphe* graphe, int n) {
  Noeud* tmp = graphe->table->element[n];
  return tmp->objet;
}

/** @brief Récupère le nombre de sommets du graphe
 *  @param graphe Le graphe
 *  @return Le nombre de sommets
 */
int grapheNbSommets(Graphe* graphe) {
  return graphe->table->n;
}

/** @brief Ecrit le graphe au format DOT de GraphViz
 *  @param graphe Le graphe à exporter
 *  @return rien
 */
void grapheVersDot(Graphe* graphe) {
  FILE* fichier;
  Noeud* sommet;
  Arc* arc;
  int i, j, nb;
  
  fichier = fopen("graphe.dot", "w");
  if(fichier == NULL) {
    printf("Erreur : impossible d'ouvrir le fichier \n");
    exit(EXIT_FAILURE);
  }
  
  fprintf(fichier, "digraph G {");
  for(i=0; i<grapheNbSommets(graphe); i++) {
    sommet = grapheSommet(graphe, i);
    nb = listeNbElt(sommet->liste);
    for(j=0; j<nb; j++) {
      arc = listeLireElement(sommet->liste, j);
      fprintf(fichier, "\n\t%s -> %s", graphe->table->toString(sommet), \
              graphe->table->toString(arc->extremite));
      if(graphe->value == 1 && arc->cout >= 0) {
        fprintf(fichier, " [label=%d]", arc->cout);
      }
      fprintf(fichier, ";");
    }
    
  }

  fprintf(fichier, "\n}\n");
  
  printf("Ecriture réussie ! \n");
  fclose(fichier);
}

/*
 * Fonctions locales
 */

/* comparer deux chaînes de caractères
   fournit <0 si ch1 < ch2; 0 si ch1=ch2; >0 sinon */
static int comparerChaineSommet(Objet* objet1, Objet* objet2) {
  return strcmp((char*) objet1, (char*) objet2);
}

/* retourne une chaine de caractères */
static char* toStringSommet(Objet* objet) {
  Noeud* sommet = objet;
  return (char*) sommet->objet;
}