/* 
 * File:   Tri.c
 * Author: lmouhat
 *
 * Created on 26 juillet 2011, 09:33
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tri.h"

/* Déclaration des fonctions locales */
static void tasEntasserMax(int * tab, int taille, int ind);
static void tasConstruireTasMax(int * tab, int taille);

/*
 * Fonctions publiques
 */
void initialiseTableau(int * tab, int taille, int max) {
  int i;
  
  srand(time(NULL));
  for(i=0; i<taille; i++) {
    tab[i] = rand()%max;
  } 
}

void afficheTableau(int * tab, int taille) {
  int i;
  
  for(i=0; i<taille; i++) {
    printf("%d ", tab[i]);
  }
  printf("\n");
}

void triSelection(int * tab, int taille) {
  int i, j, indmin, min;
  
  for(i=0; i<taille-1; i++) {
    indmin = i;
    for(j=i+1; j<taille; j++) {
      if(tab[j] < tab[indmin]) {
        indmin = j;
      }
    }
    min = tab[indmin];
    tab[indmin] = tab[i];
    tab[i] = min;
  }
}

void triTas(int * tab, int taille) {
  int i, tmp;
  
  tasConstruireTasMax(tab, taille);
  
  for(i=taille-1; i>0; i--) {
    tmp = tab[0];
    tab[0] = tab[i];
    tab[i] = tmp;
    tasEntasserMax(tab, i, 0);
  }
}

/* Fonctions privées */
static void tasEntasserMax(int * tab, int taille, int ind) {
  int gauche, droite, max, tmp;
  
  gauche = 2 * ind + 1;
  droite = gauche + 1;
  
  if(gauche < taille && tab[gauche] > tab[ind]) {
    max = gauche;
  } else {
    max = ind;
  }
  
  if(droite < taille && tab[droite] > tab[max]) {
    max = droite;
  }
  
  if(max != ind) {
    tmp = tab[ind];
    tab[ind] = tab[max];
    tab[max] = tmp;
    tasEntasserMax(tab, taille, max);
  }
}

static void tasConstruireTasMax(int * tab, int taille) {
  int i;
  
  for(i=taille/2-1; i>=0; i--) {
    tasEntasserMax(tab, taille, i);
  }
}
