/* 
 * File:   main.c
 * Author: lmouhat
 *
 * Created on 26 juillet 2011, 09:33
 */

#include <stdio.h>
#include <stdlib.h>
#include "Tri.h"
#include "Liste.h"

#define TAILLE 15

/*
 * 
 */
int main(int argc, char** argv) {
  int tab[TAILLE];
  Liste* liste;
  
  printf("01) Tableau initialise et non trie \n");
  initialiseTableau(tab, TAILLE, 100);
  afficheTableau(tab, TAILLE);
  
/*
  triSelection(tab, TAILLE);
*/
  triTas(tab, TAILLE);
  afficheTableau(tab, TAILLE);
  
  liste = creerListeDefaut();
  ajouterFinListe(liste, "test");
  ajouterFinListe(liste, "kikoo");
  ajouterDebutListe(liste, "pladamousse");
  ajouterDebutListe(liste, "chupa");
  ajouterDebutListe(liste, "zobi");
  afficherListe(liste);
  printf("\nExtraction debut de liste : %s \n", extraireDebutListe(liste));
  afficherListe(liste);
  printf("\nExtraction fin de liste : %s \n", extraireFinListe(liste));
  afficherListe(liste);
  detruireListe(liste);

  printf("\n");
  return (EXIT_SUCCESS);
}

