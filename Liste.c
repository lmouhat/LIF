/* 
 * File:   Liste.c
 * Author: lmouhat
 *
 * Created on 29 juillet 2011, 17:49
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Liste.h"

/* Déclaration des fonctions locales */

/* comparer deux chaînes de caractères
   fournit <0 si ch1 < ch2; 0 si ch1=ch2; >0 sinon */
static int comparerChaine(Objet* objet1, Objet* objet2) {
  return strcmp((char*) objet1, (char*) objet2);
}

static char* toString(Objet* objet) {
  return (char*) objet;
}

/*
static Element* elementCourant (Liste* l) {
  Element* p = l->courant;
  if (l->courant != NULL) {
    l->courant = l->courant->suivant;
  }
  return p;
}
*/

/* Fonctions publiques */

void initListe(Liste* l, int type, char* (*toString) (Objet*), \
      int (*comparer) (Objet*, Objet*)) {
  l->premier = NULL;
  l->dernier = NULL;
  l->courant = NULL;
  l->nbElt = 0;
  l->type = type;
  l->toString = toString;
  l->comparer = comparer;
}

void initListeDefaut(Liste* l) {
  initListe(l, NONORDONNE, toString, comparerChaine);
}

Liste* creerListe(int type, char* (*toString) (Objet*), \
        int (*comparer) (Objet*, Objet*)) {
  Liste* l = (Liste*) malloc(sizeof (Liste));
  initListe(l, type, toString, comparer);
  return l;
}

Liste* creerListeDefaut(void) {
  Liste* l = (Liste*) malloc(sizeof (Liste));
  initListeDefaut(l);
  return l;
}

void ajouterFinListe(Liste* l, Objet* objet) {
  Element* e = (Element*) malloc(sizeof (Element));
  e->reference = objet;
  if (l->premier == NULL) {
    l->premier = e;
    e->precedent = NULL;
  } else {
    e->precedent = l->dernier;
    l->dernier->suivant = e;
  }
  l->dernier = e;
  l->nbElt++;
}

void ajouterDebutListe(Liste* l, Objet* objet) {
  Element* e = (Element*) malloc(sizeof (Element));
  e->reference = objet;
  e->suivant = l->premier;
  e->precedent = NULL;
  if (l->premier != NULL) {
    l->premier->precedent = e;
  }
  l->premier = e;
  if (l->dernier == NULL) {
    l->dernier = e;
  }
  l->nbElt++;
}

int nbEltListe(Liste* l) {
  return l->nbElt;
}

int listeVide(Liste* l) {
  if (nbEltListe(l) > 0) {
    return 0;
  }
  return 1;
}

Objet* extraireDebutListe(Liste* l) {
  Element* p = l->premier;
  Objet* obj = l->premier->reference;

  if (listeVide(l) == 0) {
    l->premier = l->premier->suivant;
    if (l->premier == NULL) {
      l->dernier = NULL;
    } else {
      l->premier->precedent = NULL;
    }
    l->nbElt--;
    free(p);
  }

  return obj;
}

Objet* extraireFinListe(Liste* l) {
  Element* p = l->dernier;
  Objet* obj = l->dernier->reference;

  if (listeVide(l) == 0) {
    l->dernier = l->dernier->precedent;
    if (l->dernier == NULL) {
      l->premier = NULL;
    } else {
      l->dernier->suivant = NULL;
    }
    l->nbElt--;
    free(p);
  }

  return obj;
}

void afficherListe(Liste* l) {
  Element* e = l->premier;

  printf("%d elements : ", nbEltListe(l));

  while(e != NULL) {
    printf("%s ", l->toString(e->reference));
    e = e->suivant;
  }
}

void viderListe(Liste* l) {
  Element* e = l->premier;
  Element* suiv;

  while (e != NULL) {
    suiv = e->suivant;
    free(e);
    e = suiv;
  }
}

void detruireListe(Liste* l) {
  viderListe(l);
  free(l);
}

