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
  
  printf("\n\n01) Tableau initialise et non trie \n");
  initialiseTableau(tab, TAILLE, 100);
  afficheTableau(tab, TAILLE);
  
/*
  triSelection(tab, TAILLE);
*/
  triTas(tab, TAILLE);
  afficheTableau(tab, TAILLE);
  
  liste = creerListeDefaut();
  ajouterDebutListe(liste, "test");
  ajouterDebutListe(liste, "kikoo");
  ajouterFinListe(liste, "lol");
  ajouterFinListe(liste, "pasteque");
  ajouterDebutListe(liste, "pladamousse");
  afficherListe(liste);
  printf("\nAffichage de droite a gauche \n");
/*
  afficherListe(liste);
  printf("\nExtraction debut de liste : %s \n", (char*) extraireDebutListe(liste));
  afficherListe(liste);
  printf("\nExtraction fin de liste : %s \n", (char*) extraireFinListe(liste));
  afficherListe(liste);
  printf("\nOn extrait tout : ");
  while(listeVide(liste) == 0) {
    printf("%s ", (char*) extraireDebutListe(liste));
  }
*/
  detruireListe(liste);

  printf("\n");
  return (EXIT_SUCCESS);
}

