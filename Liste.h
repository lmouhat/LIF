/* 
 * File:   Liste.h
 * Author: lmouhat
 *
 * Created on 29 juillet 2011, 17:49
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
void listeInit(Liste* l, int type, char* (*toString) (Objet*), \
      int (*comparer) (Objet*, Objet*));
void listeInitDefaut(Liste* l);
Liste* listeCreer(int type, char* (*toString) (Objet*), \
        int (*comparer) (Objet*, Objet*));
Liste* listeCreerDefaut(void);
void listeAjouterFin(Liste* l, Objet* objet);
void listeAjouterDebut(Liste* l, Objet* objet);
void listeInsererApres(Liste* l, Objet* objet, Element* apres);
int listeNbElt(Liste* l);
int listeVide(Liste* l);
Objet* listeChercherObjet(Liste* l, Objet* objet);
void listeAfficherGD(Liste* l);
void listeAfficherDG(Liste* l);
Objet* listeExtraireDebut(Liste* l);
Objet* listeExtraireFin(Liste* l);
void listeTriInsertion(Liste* l);
void listeTriRapide(Liste* l);
void listeVider(Liste* l);
void listeDetruire(Liste* l);


#endif	/* LISTE_H */