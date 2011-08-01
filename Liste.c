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
static int comparerChaine (Objet* objet1, Objet* objet2) {
  return strcmp ((char*) objet1, (char*) objet2);
}

static char* toString (Objet* objet) {
  return (char*) objet;
}

/*static Element* elementCourant (Liste* l) {
  Element* p = l->courant;
  if (l->courant != NULL) {
    l->courant = l->courant->suivant;
  }
  return p;
}*/

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
  Liste* l = (Liste*) malloc(sizeof(Liste));
  initListe(l, type, toString, comparer);
  return l;
}

Liste* creerListeDefaut(void) {
  Liste* l = (Liste*) malloc(sizeof(Liste));
  initListeDefaut(l);
  return l;
}

void ajouterFinListe(Liste* l, Objet* objet) {
  Element* e = (Element*) malloc(sizeof(Element*));
  e->reference = objet;
  if(l->premier == NULL) {
    l->premier = e;
  } else {
    l->dernier->suivant = e;
  }
  l->dernier = e;
  l->nbElt++;
}

void ajouterDebutListe(Liste* l, Objet* objet) {
  Element* e = (Element*) malloc(sizeof(Element*));
  e->reference = objet;
  e->suivant = l->premier;
  l->premier = e;
  if(l->dernier == NULL) {
    l->dernier = e;
  }
  l->nbElt++;
}

int nbEltListe(Liste* l) {
  return l->nbElt;
}

int listeVide(Liste* l) {
  if(nbEltListe(l) > 0) {
    return 0;
  }
  return 1;
}

Objet* extraireDebutListe(Liste* l) {
  Objet* p = l->premier->reference;
  
  if(listeVide(l) == 0) {
    l->premier = l->premier->suivant;
    if(l->premier == NULL) {
      l->dernier = NULL;
    }
    l->nbElt--;
  }
  
  return p;
}

/* TODO : a corriger */
Objet* extraireFinListe(Liste* l) {
  Element* p = l->premier;
  
  if(listeVide(l) == 0) {
    if(l->premier == l->dernier) {
      l->premier = l->dernier = NULL;
    } else {
      while(p != l->dernier) {
        p = p->suivant;
      }
      l->dernier = p;
    }
    l->nbElt--;
  }
  
  return p->reference;
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
  
  while(e != NULL) {
    suiv = e->suivant;
    free(e);
    e = suiv;
  }
}

void detruireListe(Liste* l) {
  viderListe(l);
  free(l);
}

