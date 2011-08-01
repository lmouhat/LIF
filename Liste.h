/* 
 * File:   Liste.h
 * Author: lmouhat
 *
 * Created on 29 juillet 2011, 17:49
 */

#ifndef LISTE_H
#define	LISTE_H

/* Les types de chaine */
#define NONORDONNE  0
#define CROISSANT   1
#define DECROISSANT 2

/* un objet générique */
typedef void Objet;

/* le type Element (élément de la liste) */
struct s_Element {
  Objet* reference; /* référence un objet */
  struct s_Element* suivant; /* élément suivant de la liste */
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
void initListe(Liste* l, int type, char* (*toString) (Objet*), \
      int (*comparer) (Objet*, Objet*));
void initListeDefaut(Liste* l);
Liste* creerListe(int type, char* (*toString) (Objet*), \
        int (*comparer) (Objet*, Objet*));
Liste* creerListeDefaut(void);
void ajouterFinListe(Liste* l, Objet* objet);
void ajouterDebutListe(Liste* l, Objet* objet);
int nbEltListe(Liste* l);
int listeVide(Liste* l);
void afficherListe(Liste* l);
Objet* extraireDebutListe(Liste* l);
Objet* extraireFinListe(Liste* l);
void viderListe(Liste* l);
void detruireListe(Liste* l);


#endif	/* LISTE_H */