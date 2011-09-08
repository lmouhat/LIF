/* 
 * File:   main.c
 * Author: lmouhat
 *
 * Created on 26 juillet 2011, 09:33
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Objet.h"
#include "Tri.h"
#include "Liste.h"
#include "Table.h"
#include "Graphe.h"

struct s_Test {
  int entier;
  float reel;
  char mot[25];
};
typedef struct s_Test Test;

Test* nouveau(char* mot, int entier, float reel) {
  Test* test = malloc(sizeof (Test));
  
  test->entier = entier;
  test->reel = reel;
  strcpy(test->mot, mot);
  
  return test;
}

/* fournir les caractéristiques d'une Test */
char* toStringTest(Objet* objet) {
  Test* test = objet;
  return test->mot;
}

char* toStringSommet(Objet* objet) {
  Noeud* sommet = objet;
  Test* t = sommet->objet;
  return t->mot;
}

/* <0 si objet1 < objet2; 0 si objet1=objet2; >0 sinon */
int comparerTest(Objet* objet1, Objet* objet2) {
  Test* t1 = objet1;
  Test* t2 = objet2;
  return strcmp(t1->mot, t2->mot);
}

int comparerSommet(Objet* objet1, Objet* objet2) {
  Noeud* s1 = objet1;
  Noeud* s2 = objet2;
  Test* t1 = s1->objet;
  Test* t2 = s2->objet;
  return strcmp(t1->mot, t2->mot);
}

void affTest(Test* t) {
  printf("%s [%d - %f]\n", t->mot, t->entier, t->reel);
}

#define TAILLE 15

/*
 * 
 */

void testListe(void) {
  Liste* liste;
  Test* test;
  Test* recherche;
  
  printf("=== TEST LISTE ===\n");
  
  printf("\n01) Création d'une liste non ordonnée \n");
  liste = listeCreer(toStringTest, comparerTest);
  
  printf("\n02) Ajout d'éléments à la liste \n");
  test = nouveau("test", 12, 123.677);
  listeAjouterDebut(liste, test);

  test = nouveau("kikoo", 6, 1.2);
  listeAjouterDebut(liste, test);
  
  test = nouveau("pladamousse", 89, 3.9);
  listeAjouterDebut(liste, test);
  
  test = nouveau("pasteque", 1, 3.14);
  listeAjouterDebut(liste, test);
  
  test = nouveau("vertu", 2, 5.14);
  listeAjouterDebut(liste, test);
  
  test =  nouveau("dell", 7, 3.67);
  listeAjouterFin(liste, test);
  
  test =  nouveau("zobi", 76, 1.7);
  listeAjouterFin(liste, test);
  
  test =  nouveau("monster", 9, 0.67);
  listeAjouterFin(liste, test);
  
  printf("\n03) Affiche de gauche à droite \n");
  listeAfficherGD(liste);
  
  printf("\n");
  printf("\n04) Affichage de droite a gauche \n");
  listeAfficherDG(liste);
  
  printf("\n");
  printf("\n05) Tri par QuickSort : \n");
  listeTriRapide(liste);
/*
  listeTriInsertion(liste);
*/
  listeAfficherGD(liste);
  
  printf("\n");
  printf("\nxx) Extraction en début de liste : ");
  test = listeExtraireDebut(liste);
  affTest(test);
  free(test);
  listeAfficherGD(liste);
  
  printf("\n");
  printf("\nxx) Extraction en fin de liste : ");
  test = listeExtraireFin(liste);
  affTest(test);
  free(test);
  
  printf("\nxx) Recherche séquentielle de l'objet \"kikoo\" ");
  recherche = nouveau("kikoo", 3, 12.1);
  test = listeChercherObjet(liste, recherche);
  printf("\nObjet \"kikoo\" trouve : ");
  affTest(test);
  free(recherche);
  
  printf("\nxx) On affiche la liste, puis on extrait tout et destruction : \n");
  listeAfficherGD(liste);
  while(listeVide(liste) == 0) {
    test = listeExtraireDebut(liste);
    affTest(test);
    free(test);
  }
  listeDetruire(liste);
  printf("\n");
}

void testTri(void) {
  int tab[TAILLE];
  
  printf("\n\n01) Tableau initialise et non trie \n");
  initialiseTableau(tab, TAILLE, 100);
  afficheTableau(tab, TAILLE);
/*
  triSelection(tab, TAILLE);
*/
  triTas(tab, TAILLE);
  afficheTableau(tab, TAILLE);
}

void testGraphe(void) {
  Graphe* graphe;
  Test* tmp, * a, * b, * c, * d, * e;
  int i;
  
  printf("=== TEST GRAPHE ===\n");
  
  printf("\n01) Création d'un graphe, capacité 25, valué \n");
  graphe = grapheCreer(25, 1, toStringSommet, comparerSommet);
  
  printf("\nxx) Ajout de noeuds \n");
  a = nouveau("kikoo", 5, 1.2);
  grapheAjouterSommet(graphe, a);
  
  b = nouveau("lol", 6, 1.3);
  grapheAjouterSommet(graphe, b);
  
  c = nouveau("pastèque", 7, 5.9);
  grapheAjouterSommet(graphe, c);
  
  d = nouveau("carotte", 8, 2.3);
  grapheAjouterSommet(graphe, d);
  
  e = nouveau("melon", 9, 3.2);
  grapheAjouterSommet(graphe, e);
  
  printf("\nxx) Ajout des arcs \n");
  grapheAjouterArc(graphe, a, b, 15);
  grapheAjouterArc(graphe, a, a, 1);
  grapheAjouterArc(graphe, a, c, 22);
  grapheAjouterArc(graphe, b, c, 11);
  grapheAjouterArc(graphe, b, a, 13);
  grapheAjouterArc(graphe, c, b, 50);
  grapheAjouterArc(graphe, d, e, 5);
  grapheAjouterArc(graphe, c, e, 9);
  
  printf("\nxx) Parcours en largeur depuis kikoo \n");
  grapheParcoursLargeur(graphe, grapheSommet(graphe, 0));
  grapheAfficher(graphe);
  
  printf("\nxx) Affichage du chemin entre kikoo et melon \n");
  grapheAfficherChemin(graphe, grapheSommet(graphe, 0), grapheSommet(graphe, 4));
  printf("\n");
  
  printf("\nxx) Parcours en profondeur du graphe \n");
  grapheParcoursProfondeur(graphe);
  grapheAfficher(graphe);
  
  printf("\nxx) Enregistrement dans graphe.dot \n");
  grapheVersDot(graphe);
  
  printf("\nxx) Destruction du graphe et de ses données \n");
  printf("On détruit les données encapsulées : \n");
  for(i=0; i<grapheNbSommets(graphe); i++) {
    tmp = grapheObjet(graphe, i);
    printf(" - suppression de : ");
    affTest(tmp);
    free(tmp);
  }
  printf("et le graphe en lui même. \n");
  grapheDetruire(graphe);
}

void testTable(void) {
  Table* table;
  Test* test;
  Test* tmp;
  int retour;
  int i;
  
  printf("=== TEST TABLE ===\n");
  
  table = tableCreer(25, toStringTest, comparerTest);

  test = nouveau("test", 12, 123.677);
  retour = tableAjouter(table, test);
  if(retour == 0) {
    printf("Echec d'ajout au tableau !\n");
    exit(1);
  }
  
  test = nouveau("lol", 1, 3.14);
  retour = tableAjouter(table, test);
  
  test = nouveau("kikoo", 7, 6.19);
  retour = tableAjouter(table, test);
  
  test = nouveau("pladamousse", 9, 5.14);
  retour = tableAjouter(table, test);
  
  test = nouveau("carotte", 9, 5.14);
  retour = tableAjouter(table, test);
  
  test = nouveau("tomate", 9, 5.14);
  retour = tableAjouter(table, test);
  
  test = nouveau("poivron", 12, 3.123);
  retour = tableAjouter(table, test);

  printf("\n01) Ajout d'elements au tableau et affichage \n");
  tableAfficher(table);
  
  printf("\nxx) Recherche sequentielle de l'element tomate \n");
  tmp = nouveau("tomate", 0, 0.0);
  test = tableRechercheSeq(table, tmp);
  free(tmp);
  if(test == NULL) {
    printf("Element non trouve !\n");
  } else {
    printf("Element trouve, adresse : 0x%x \n", (unsigned int) test);
    printf("Affichage de l'element : ");
    affTest(test);
  }
  
  printf("\nxx) Tri par insertion de la table \n");
  tableTriInsertion(table);
  tableAfficher(table);
  
  printf("\nxx) Recherche dichotomique de l'element poivron \n");
  tmp = nouveau("poivron", 0, 0.0);
  test = tableRechercheDicho(table, tmp);
  free(tmp);
  if(test == NULL) {
    printf("Element non trouve !\n");
  } else {
    printf("Element trouve, adresse : 0x%x \n", (unsigned int) test);
    printf("Affichage de l'element : ");
    affTest(test);
  }
  
  printf("\nxx) Retrait du dernier element de la table : ");
  test = tableRetirer(table);
  affTest(test);
  free(test);
  
  printf("\nxx) Destruction de la table\n");
  for(i=0; i<table->n; i++) {
    test = tableElement(table, i);
    printf("Suppression de : ");
    affTest(test);
    free(test);
  }
  tableDetruire(table);
}


int main(int argc, char** argv) {
/*
  testTri();
 */
  
  testListe();
  
/*
  testTable();
*/
  
/*
  testGraphe();
*/
  return (EXIT_SUCCESS);
}

