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
char* toStringTest(Test* t) {
  return t->mot;
}

char* toStringTestObjet(Objet* objet) {
  return toStringTest((Test*) objet);
}

/* comparer deux personnes fournir <0 si p1 < p2; 0 si p1=p2; >0 sinon */
int comparerTest(Test* t1, Test* t2) {
  return strcmp(t1->mot, t2->mot);
}

int comparerTestObjet(Objet* objet1, Objet* objet2) {
  return comparerTest((Test*) objet1, (Test*) objet2);
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
  
  liste = listeCreer(NONORDONNE, toStringTestObjet, comparerTestObjet);
  
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
  
  listeAfficherGD(liste);
  printf("\nAffichage de droite a gauche \n");
  listeAfficherDG(liste);
  
  printf("\nTri par QuickSort : \n");
  listeTriRapide(liste);
  listeAfficherGD(liste);
  
  test = listeExtraireDebut(liste);
  printf("\n\nExtraction debut de liste : ");
  affTest(test);
  free(test);
  listeAfficherGD(liste);
  
  test = listeExtraireFin(liste);
  printf("\nExtraction fin de liste : ");
  affTest(test);
  free(test);
  
  recherche = nouveau("kikoo", 3, 12.1);
  test = listeChercherObjet(liste, recherche);
  printf("Objet \"kikoo\" trouve : ");
  affTest(test);
  free(recherche);
  
  listeAfficherGD(liste);
  printf("\nOn extrait tout : ");
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
  
  printf("=== TEST GRAPHE ===\n\n");
  
  printf("\n01) Création d'un graphe, capacite 25 non value \n");
  graphe = grapheCreerDefaut(25, 0);
  grapheDetruire(graphe);
}

void testTable(void) {
  Table* table;
  Test* test;
  Test* tmp;
  int retour;
  int i;
  
  printf("=== TEST TABLE ===\n");
  
  table = tableCreer(25, toStringTestObjet, comparerTestObjet);

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
  testListe();
  testTable();
*/
  testGraphe();
  return (EXIT_SUCCESS);
}

