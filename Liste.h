/**
 * @brief       Module TDA Liste
 * @file        Liste.h
 * @author      lmouhat@gmail.com
 * @date        2011/08/03
 *
 */

#ifndef LISTE_H
#define	LISTE_H

#include "Objet.h"

/* Les types de chaine */
#define NONORDONNE  0
#define CROISSANT   1
#define DECROISSANT 2

/* le type Element (élément de la liste) */
struct s_Element {
  Objet* reference; /* référence un objet */
  struct s_Element* suivant; /* élément suivant de la liste */
  struct s_Element* precedent; /* élément suivant de la liste */
};
typedef struct s_Element Element;

/* le type Liste */
struct s_Liste {
  Element* premier; /* premier élément de la liste */
  Element* dernier; /* dernier élément de la liste */
  Element* courant; /* élément en cours de traitement */
  int nbElt; /* nombre d'élements dans la liste */
  int type; /* type de liste */
  char* (*toString) (Objet*);
  int (*comparer) (Objet*, Objet*);
};
typedef struct s_Liste Liste;


/*
 * Les fonctions publiques
 */

void listeInit(Liste* liste, int type, char* (*toString) (Objet*), \
      int (*comparer) (Objet*, Objet*));
void listeInitDefaut(Liste* liste);
Liste* listeCreer(int type, char* (*toString) (Objet*), \
        int (*comparer) (Objet*, Objet*));
Liste* listeCreerDefaut(void);
void listeAjouterFin(Liste* liste, Objet* objet);
void listeAjouterDebut(Liste* liste, Objet* objet);
void listeInsererApres(Liste* liste, Objet* objet, Element* apres);
int listeNbElt(Liste* liste);
int listeVide(Liste* liste);
Objet* listeChercherObjet(Liste* liste, Objet* objet);
void listeAfficherGD(Liste* liste);
void listeAfficherDG(Liste* liste);
Objet* listeExtraireDebut(Liste* liste);
Objet* listeExtraireFin(Liste* liste);
void listeTriInsertion(Liste* liste);
void listeTriRapide(Liste* liste);
void listeVider(Liste* liste);
void listeDetruire(Liste* liste);


#endif	/* LISTE_H */