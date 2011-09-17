#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Liste.h"

/*
 * Déclaration des fonctions locales
 */

static int comparerChaine(Objet* objet1, Objet* objet2);
static char* toString(Objet* objet);
static void faireTriRapide(Liste* liste, Element* pNoeud, int n_elements);
static void permuterElements(Element* e1, Element* e2);
static Objet* extraireObjet(Liste* liste, Element* elem);
static void insererApres(Liste* liste, Objet* objet, Element* apres);

/*
 * Fonctions publiques
 */

/** @brief Initialise une liste
 *  @param liste La liste
 *  @param toString Pointeur vers la fonction d'affichage
 *  @param comparer Pointeur vers la fonction de comparaison
 */
void listeInit(Liste* liste, char* (*toString) (Objet*), \
      int (*comparer) (Objet*, Objet*)) {
  liste->premier = NULL;
  liste->dernier = NULL;
  liste->courant = NULL;
  liste->nbElt = 0;
  liste->toString = toString;
  liste->comparer = comparer;
}

/** @brief Initialise une liste par défaut (liste non ordonnée)
 *  @param liste La liste
 */
void listeInitDefaut(Liste* liste) {
  listeInit(liste, toString, comparerChaine);
}

/** @brief Crée une liste et l'initialise
 *  @param toString Pointeur vers la fonction d'affichage
 *  @param comparer Pointeur vers la fonction de comparaison
 *  @return La liste créée et initialisée
 */
Liste* listeCreer(char* (*toString) (Objet*), \
        int (*comparer) (Objet*, Objet*)) {
  Liste* liste = malloc(sizeof (Liste));
  listeInit(liste, toString, comparer);
  return liste;
}

/** @brief Crée une liste et l'initialise avec les valeurs par défaut
 *  @return La liste créée et initialisée par défaut
 */
Liste* listeCreerDefaut(void) {
  Liste* liste = malloc(sizeof (Liste));
  listeInitDefaut(liste);
  return liste;
}

/** @brief Ajoute un objet en fin de liste
 *  @param liste
 *  @param objet Pointeur vers l'objet à ajouter
 */
void listeAjouterFin(Liste* liste, Objet* objet) {
  Element* elem = malloc(sizeof (Element));
  elem->reference = objet;
  if (liste->premier == NULL) {
    liste->premier = elem;
    elem->precedent = elem->suivant = NULL;
  } else {
    elem->precedent = liste->dernier;
    liste->dernier->suivant = elem;
    elem->suivant = NULL;
  }
  liste->dernier = elem;
  liste->nbElt++;
}

/** @brief Ajoute un objet en début de liste
 *  @param liste
 *  @param objet Pointeur vers l'objet à ajouter
 */
void listeAjouterDebut(Liste* liste, Objet* objet) {
  Element* elem = malloc(sizeof (Element));
  elem->reference = objet;
  elem->suivant = liste->premier;
  elem->precedent = NULL;
  if (liste->premier != NULL) {
    liste->premier->precedent = elem;
  }
  liste->premier = elem;
  if (liste->dernier == NULL) {
    liste->dernier = elem;
  }
  liste->nbElt++;
}

/** @brief Insérer un objet dans une liste triée
 *  @param liste
 *  @param objet Pointeur vers l'objet à ajouter
 *  @todo Corriger la fonction pour gérer l'ordre ASC (ok) ou DESC (pas ok)
 */
void listeInsererTri(Liste* liste, Objet* objet) {
  Element* i = liste->premier;
  int ajout;
  
  if(listeVide(liste) == 1) {
    listeAjouterDebut(liste, objet);
  } else {
    ajout = 0;
    while(i != NULL && ajout == 0) {
      if(liste->comparer(i->reference, objet) > 0) {
        if(i->precedent == NULL) {
          listeAjouterDebut(liste, objet);
        } else {
          insererApres(liste, objet, i->precedent);
        }
        ajout = 1;
      }
      i = i->suivant;
    }
    if(ajout == 0) {
      listeAjouterFin(liste, objet);
    }
  } 
}

/** @brief Retourne le nombre d'éléments de la liste
 *  @param liste
 *  @return Nombre d'éléments
 */
int listeNbElt(Liste* liste) {
  return liste->nbElt;
}

/** @brief Teste si la liste est vide
 *  @param liste
 *  @return 1 si vrai (liste vide), 0 si faux (liste non vide)
 */
int listeVide(Liste* liste) {
  if (listeNbElt(liste) > 0) {
    return 0;
  }
  return 1;
}

/** @brief Extraie le premier élément de la liste
 *  @param liste
 *  @return Pointeur vers l'objet, NULL si échec
 */
Objet* listeExtraireDebut(Liste* liste) {
  Element* p = liste->premier;
  Objet* obj = liste->premier->reference;

  if (listeVide(liste) == 0) {
    liste->premier = liste->premier->suivant;
    if (liste->premier == NULL) {
      liste->dernier = NULL;
    } else {
      liste->premier->precedent = NULL;
    }
    liste->nbElt--;
    free(p);
  }

  return obj;
}

/** @brief Retourne le nième objet de la liste
 *  @param liste
 *  @param n Le nième objet
 *  @return Pointeur vers l'objet, NULL si échec
 */
Objet* listeLireObjet(Liste* liste, int n) {
  Element* p = liste->premier;
  Objet* obj = NULL;
  int i;

  if (n <= listeNbElt(liste)) {
    for (i = 0; i < n; i++) {
      p = p->suivant;
    }
    obj = p->reference;
  }

  return obj;
}

/** @brief Extraie le dernier élément de la liste
 *  @param liste
 *  @return Pointeur vers l'objet, NULL si échec
 */
Objet* listeExtraireFin(Liste* liste) {
  Element* p = liste->dernier;
  Objet* obj = liste->dernier->reference;

  if (listeVide(liste) == 0) {
    liste->dernier = liste->dernier->precedent;
    if (liste->dernier == NULL) {
      liste->premier = NULL;
    } else {
      liste->dernier->suivant = NULL;
    }
    liste->nbElt--;
    free(p);
  }

  return obj;
}

/** @brief Recherche séquentielle d'un objet dans la liste
 *  @param liste La liste parcourue
 *  @param objet L'objet recherché
 *  @return Pointeur vers l'objet trouvé s'il existe, sinon NULL
 */
Objet* listeChercherObjet(Liste* liste, Objet* objet) {
  int trouve = 0;
  Objet* obj;
  Element* elem = liste->premier;

  while (elem != NULL && trouve == 0) {
    obj = elem->reference;
    trouve = liste->comparer(objet, obj) == 0;
    elem = elem->suivant;
  }
  return trouve == 1 ? obj : NULL;
}

/** @brief Affiche la liste de gauche à droite
 *  @param liste
 */
void listeAfficherGD(Liste* liste) {
  Element* elem = liste->premier;

  printf("%d elements : ", listeNbElt(liste));

  while (elem != NULL) {
    printf("%s ", liste->toString(elem->reference));
    elem = elem->suivant;
  }
}

/** @brief Affiche la liste de droite à gauche
 *  @param liste
 */
void listeAfficherDG(Liste* liste) {
  Element* elem = liste->dernier;

  printf("%d elements : ", listeNbElt(liste));

  while (elem != NULL) {
    printf("%s ", liste->toString(elem->reference));
    elem = elem->precedent;
  }
}

/** @brief Tri de la liste par tri rapide (QuickSort)
 *  @param liste Liste à trier
 */
void listeTriRapide(Liste* liste) {
  faireTriRapide(liste, liste->premier, liste->nbElt);
}

/** @brief Tri de la liste par insertion
 *  @param liste
 */
void listeTriInsertion(Liste* liste) {
  Element * i, * j, * suivant;
  Objet* tmp;
  int fait;

  /* pour tous les éléments de la liste */
  for(j=liste->premier->suivant; j!=NULL; j=suivant) {
    suivant = j->suivant; /* on mémorise l'élement suivant */
    fait = 0;
    i = liste->premier;
    /* on cherche à insérer notre élément */
    while(i != j && fait == 0) {
      if(liste->comparer(i->reference, j->reference) > 0) {
        tmp = extraireObjet(liste, j);
        /* ajout en tête sinon insertion */
        if(i->precedent == NULL) { 
          listeAjouterDebut(liste, tmp);
        } else {
          insererApres(liste, tmp, i->precedent);
        }
        fait = 1;
      }
      i = i->suivant;
    }
  }
}

/** @brief Vidage de la liste
 *  @param liste
 */
void listeVider(Liste* liste) {
  Element* elem = liste->premier;
  Element* suiv;

  while (elem != NULL) {
    suiv = elem->suivant;
    free(elem);
    elem = suiv;
  }
}

/** @brief Vidage et destruction de la liste
 *  @param liste
 */
void listeDetruire(Liste* liste) {
  listeVider(liste);
  free(liste);
}

/*
 * Fonctions locales
 */

static void permuterElements(Element* e1, Element* e2) {
  Objet* tmp;

  if (e1 != NULL && e2 != NULL) {
    tmp = e1->reference;
    e1->reference = e2->reference;
    e2->reference = tmp;
  }
}

static Objet* extraireObjet(Liste* liste, Element* elem) {
  Objet* objet;
  Element* tmp;
  
  if(elem == liste->premier) {
    objet = listeExtraireDebut(liste);
  } else if(elem == liste->dernier) {
    objet = listeExtraireFin(liste);
  } else {
    objet = elem->reference;
    tmp = elem->precedent;
    elem->precedent->suivant = elem->suivant;
    elem->suivant->precedent = tmp;
    free(elem);
    liste->nbElt--; 
  }
  
  return objet;
}

static void insererApres(Liste* liste, Objet* objet, Element* apres) {
  Element* elem;
  
  if(apres == NULL) {
    listeAjouterDebut(liste, objet);
  } else {
    elem = malloc(sizeof (Element));
    elem->reference = objet;
    elem->precedent = apres;
    elem->suivant = apres->suivant;
    apres->suivant = elem;
    elem->suivant->precedent = elem;
    liste->nbElt++;
  }
}

/* -- faireTriRapide
 * liste: liste à trier
 * noeud: pointeur vers le premier element de la liste à trier
 * nbElements: nombre d'éléments de cette liste
 */
static void faireTriRapide(Liste* liste, Element* noeud, int nbElements) {
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
      if (liste->comparer(i->reference, pivot->reference) < 0) {
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
    faireTriRapide(liste, noeud, n);
    faireTriRapide(liste, j->suivant, nbElements - 1 - n);
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