#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Liste.h"

/*
 * Déclaration des fonctions locales
 */

static int comparerChaine(Objet* objet1, Objet* objet2);
static char* toString(Objet* objet);
static void faireTriRapide(Liste* l, Element* pNoeud, int n_elements);
static void permuterElements(Element* e1, Element* e2);


/*
 * Fonctions publiques
 */

void listeInit(Liste* l, int type, char* (*toString) (Objet*), \
      int (*comparer) (Objet*, Objet*)) {
  l->premier = NULL;
  l->dernier = NULL;
  l->courant = NULL;
  l->nbElt = 0;
  l->type = type;
  l->toString = toString;
  l->comparer = comparer;
}

void listeInitDefaut(Liste* l) {
  listeInit(l, NONORDONNE, toString, comparerChaine);
}

Liste* listeCreer(int type, char* (*toString) (Objet*), \
        int (*comparer) (Objet*, Objet*)) {
  Liste* l = malloc(sizeof (Liste));
  listeInit(l, type, toString, comparer);
  return l;
}

Liste* listeCreerDefaut(void) {
  Liste* l = malloc(sizeof (Liste));
  listeInitDefaut(l);
  return l;
}

void listeAjouterFin(Liste* l, Objet* objet) {
  Element* e = malloc(sizeof (Element));
  e->reference = objet;
  if (l->premier == NULL) {
    l->premier = e;
    e->precedent = e->suivant = NULL;
  } else {
    e->precedent = l->dernier;
    l->dernier->suivant = e;
    e->suivant = NULL;
  }
  l->dernier = e;
  l->nbElt++;
}

void listeAjouterDebut(Liste* l, Objet* objet) {
  Element* e = malloc(sizeof (Element));
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

void listeInsererApres(Liste* l, Objet* objet, Element* apres) {
  Element* e = malloc(sizeof (Element));
  e->reference = objet;
  e->precedent = apres;
  e->suivant = apres->suivant;
  apres->suivant = e;
  l->nbElt++;
}

int listeNbElt(Liste* l) {
  return l->nbElt;
}

int listeVide(Liste* l) {
  if (listeNbElt(l) > 0) {
    return 0;
  }
  return 1;
}

Objet* listeExtraireDebut(Liste* l) {
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

Objet* listeExtraireFin(Liste* l) {
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

Objet* listeChercherObjet(Liste* l, Objet* objet) {
  int trouve = 0;
  Objet* obj;
  Element* e = l->premier;

  while (e != NULL && trouve == 0) {
    obj = e->reference;
    trouve = l->comparer(objet, obj) == 0;
    e = e->suivant;
  }
  return trouve == 1 ? obj : 0;
}

void listeAfficherGD(Liste* l) {
  Element* e =  l->premier;

  printf("%d elements : ", listeNbElt(l));

  while (e != NULL) {
    printf("%s ", l->toString(e->reference));
    e = e->suivant;
  }
}

void listeAfficherDG(Liste* l) {
  Element* e = l->dernier;

  printf("%d elements : ", listeNbElt(l));

  while (e != NULL) {
    printf("%s ", l->toString(e->reference));
    e = e->precedent;
  }
}

void listeTriRapide(Liste* l) {
  faireTriRapide(l, l->premier, l->nbElt);
}

void listeTriInsertion(Liste* l) {
  /*
    int i,j;
    int cle;
  
    for(j=1; j<sizeof; j++) {
      cle = tab[j];
      i = j-1;
      while(i>=0 && tab[i] > cle) {
        tab[i+1] = tab[i];
        i--;
      }
      tab[i+1] = cle;
    }
   */
}

void listeVider(Liste* l) {
  Element* e = l->premier;
  Element* suiv;

  while (e != NULL) {
    suiv = e->suivant;
    free(e);
    e = suiv;
  }
}

void listeDetruire(Liste* l) {
  listeVider(l);
  free(l);
}


/*
 * Fonctions locales
 */

static void permuterElements(Element* e1, Element* e2) {
  void* tmp;

  if (e1 != NULL && e2 != NULL) {
    tmp = e1->reference;
    e1->reference = e2->reference;
    e2->reference = tmp;
  }
}

/* -- faireQSort
 * l: liste à trier
 * noeud: pointeur vers le premier element de la liste à trier
 * nbElements: nombre d'éléments de cette liste
 */
static void faireTriRapide(Liste* l, Element* noeud, int nbElements) {
  if (nbElements > 1) {
    /* -- variables
     * i : pointeur pour le parcours de liste
     * i_pos : position dans la liste de i
     * pivot : pointeur vers un noeud choisi arbitrairement
     * n : nombre d'éléments inférieurs à pivot
     * j : pointeur vers le noeud d'indice n
     */
    Element * i, * j, * pivot;
    int pos_i, n;

    /* On choisi le premier noeud comme pivot */
    pivot = noeud;

    /* Premier noeud = pivot, donc on passe directement au suivant */
    i = noeud->suivant;
    pos_i = 1;

    /* On a actuellement 0 elements 'inferieurs' a pivot */
    j = noeud;
    n = 0;

    while (pos_i < nbElements) {
      /* i '<' pivot */
      if (l->comparer(i->reference, pivot->reference) < 0) {
        /* Incrementer n (et donc deplacer j) */
        j = j->suivant;
        n++;

        /* Ce serait une perte de temps de permuter i avec lui-meme */
        if (pos_i != n) { 
          permuterElements(i, j);
        }
      }

      i = i->suivant;
      pos_i++;
    }

    /* S'il existe des elements 'inferieurs' a pivot */
    if (n > 0) {
      permuterElements(pivot, j);
    }

    /* Et on applique l'algorithme pour chaque partie de la liste */
    faireTriRapide(l, noeud, n);
    faireTriRapide(l, j->suivant, nbElements - 1 - n);
  }
}

/* comparer deux chaînes de caractères
   fournit <0 si ch1 < ch2; 0 si ch1=ch2; >0 sinon */
static int comparerChaine(Objet* objet1, Objet* objet2) {
  return strcmp((char*) objet1, (char*) objet2);
}

static char* toString(Objet* objet) {
  return (char*) objet;
}