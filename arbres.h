#ifndef ARBRES_H_INCLUDED
#define ARBRES_H_INCLUDED

typedef struct Coup {
    int depart ;
    int arrivee ;
}Coup ;

typedef struct Arbre Arbre ;
struct Arbre {
    Coup coup ;
    int valeur ;
    Arbre* frere ;
    Arbre* fils ;
} ;

int taille(Arbre* a) ;
int hauteur(Arbre* a) ;
Arbre* ajouter_fils(Arbre* a, Coup coup, int valeur) ;
Arbre* ajouter_frere(Arbre* a, Coup coup, int valeur) ;
void afficher(Arbre* a) ;
void free_arbre(Arbre* a);

#endif // ARBRES_H_INCLUDED
