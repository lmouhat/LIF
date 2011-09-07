/**
 * @brief       Module TDA Graphe
 * @file        Graphe.h
 * @author      lmouhat@gmail.com
 * @date        2011/08/05
 *
 */

#ifndef GRAPHE_H
#define	GRAPHE_H

#include "Objet.h"
#include "Table.h"
#include "Liste.h"

/** @struct s_Noeud
 *  @brief La structure d'un noeud / sommet
 */
struct s_Noeud {
  /** pointeur vers un objet */
  Objet* objet;
  /** liste des relations (s_Arc) de ce noeud */
  Liste* liste;
  /** identifiant du noeud */
  int id;
  /** couleur du marquage (parcours de graphe)
   *  0 : pas visité, 1 : en cours de visite, 2 : visité */
  int couleur;
  /** distance depuis le noeud de départ (parcours en largeur) */
  int distance;
  /** date de découverte (parcours en profondeur) */
  int dateDecouverte;
  /** date de fin (parcours en profondeur) */
  int dateFin;
  /** pointeur vers le noeud parent (parcours de graphe) */
  struct s_Noeud* parent;
};

/** @typedef Noeud
 *  @brief Le type Noeud
 */
typedef struct s_Noeud Noeud;

/** @struct s_Arc
 *  @brief La structure d'un arc / d'une arête (relation entre noeuds)
 */
struct s_Arc {
  /** pointeur vers l'extrémité terminale de l'arc */
  Noeud* extremite;
  /** coût de l'arc */
  int cout;
};

/** @typedef Arc
 *  @brief Le type Arc
 */
typedef struct s_Arc Arc;

/** @struct s_Graphe
 *  @brief La structure d'un graphe
 */
struct s_Graphe {
  /** table des noeuds */
  Table* table;
  /** {0,1} si le graphe est valué (coût des relations) */
  int value;
};

/** @typedef Graphe
 *  @brief Le type Graphe
 */
typedef struct s_Graphe Graphe;


/*
 * Les fonctions publiques
 */

/* construction - destruction */
Graphe* grapheCreer(int nMax, int value, char* (*toString) (Objet*), \
        int (*comparer) (Objet*, Objet*));
Graphe* grapheCreerDefaut(int nMax, int value);
void grapheDetruire(Graphe* graphe);

/* opérations élémentaires */
void grapheAjouterSommet(Graphe* graphe, Objet* objet);
void grapheAjouterArc(Graphe* graphe, Objet* init, Objet* term, int cout);
Noeud* grapheSommet(Graphe* graphe, int n);
Objet* grapheObjet(Graphe* graphe, int n);
int grapheNbSommets(Graphe* graphe);

/* algorithmes */
void grapheParcoursLargeur(Graphe* graphe, Noeud* depart);
void grapheParcoursProfondeur(Graphe* graphe);

/* entrée / sortie */
void grapheVersDot(Graphe* graphe);
void grapheAfficher(Graphe* graphe);
void grapheAfficherChemin(Graphe* graphe, Noeud* depart, Noeud* arrivee);



#endif	/* GRAPHE_H */

