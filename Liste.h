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
#define NORMAL 0
#define CROISSANT 1
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

/* construction - destruction */
void listeInit(Liste* liste, int type, char* (*toString) (Objet*), \
      int (*comparer) (Objet*, Objet*));
void listeInitDefaut(Liste* liste);
Liste* listeCreer(int type, char* (*toString) (Objet*), \
        int (*comparer) (Objet*, Objet*));
Liste* listeCreerDefaut(void);
void listeVider(Liste* liste);
void listeDetruire(Liste* liste);

/* opérations élémentaires */
void listeAjouterFin(Liste* liste, Objet* objet);
void listeAjouterDebut(Liste* liste, Objet* objet);
void listeInsererTri(Liste* liste, Objet* objet);
Objet* listeLireObjet(Liste* liste, int n);
Objet* listeExtraireDebut(Liste* liste);
Objet* listeExtraireFin(Liste* liste);
int listeNbElt(Liste* liste);
int listeVide(Liste* liste);

/* recherche */
Objet* listeChercherObjet(Liste* liste, Objet* objet);

/* affichage et tri */
void listeAfficherGD(Liste* liste);
void listeAfficherDG(Liste* liste);
void listeTriInsertion(Liste* liste);
void listeTriRapide(Liste* liste);


#endif	/* LISTE_H */