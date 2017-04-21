#include <stdio.h>
#include <stdlib.h>
#include "arbres.h"

//FONCTIONS SUR LES ARBRES

//Taille d'un arbre.
int taille(Arbre* a) {

    int somme = 1 ;
    Arbre* f ;

    //taille(a) = 1 + taille(ses fils)
    // = 1 + taille(fils) + taille(frere) + traille(frere) + ...
    for (f = a->fils ; f != NULL ; f = f->frere) {
        somme += taille(f) ;
    }

    return somme ;
}


//Hauteur d'un arbre.
int hauteur(Arbre* a) {
    Arbre* fils ;

    int maxi = 0 ;

    //hauteur(a) = 1 + max(hauteur(ses fils))
    // = 1 + max[taille(fils), taille(frere), traille(frere), ...]
    for (fils = a->fils ; fils != NULL ; fils = fils->frere) {
        if (hauteur(fils) > maxi) {
            maxi = hauteur(fils) ;
        }
    }

    return 1 + maxi ;
}


//On ajoute à l'arbre a un fils ayant comme noeud
//les éléments coup et valeur.
Arbre* ajouter_fils(Arbre* a, Coup coup, int valeur) {

    //On crée un nouvel élément
    Arbre* f = malloc(sizeof(Arbre)) ;

    //On renseigne les valeurs
    f->coup = coup ;
    f->valeur = valeur ;
    f->fils = NULL ;
    f->frere = a->fils ;

    //Le nouveau fils de a est f
    a->fils = f ;

    return a ;
}


//On ajoute à l'arbre a un frere ayant comme noeuf
//les éléments coup et valeur.
Arbre* ajouter_frere(Arbre* a, Coup coup, int valeur) {

    //On crée un nouvel élément
    Arbre* f = malloc(sizeof(Arbre)) ;

    //On renseigne les valeurs
    f->coup = coup ;
    f->valeur = valeur ;
    f->fils = NULL ;
    f->frere = a->frere ;

    //Le nouveau frere de a est f
    a->frere = f ;

    return a ;
}


void afficher(Arbre* a) {

    int val ;
    int val_fils ;
    int val_frere ;

    val = (*a).valeur ;
    if (((*a).fils) != NULL) {
        val_fils = ((*a).fils)->valeur ;
        if (((*a).frere) != NULL) {
            val_frere = ((*a).frere)->valeur ;
            printf("Noeud numéro %d\nFils : %d\nFrere : %d\n\n",val,val_fils,val_frere) ;
        }
        else {
            printf("Noeud numéro %d\nFils : %d\nFrere : NULL\n\n",val,val_fils) ;
        }
    }
    else {
        if (((*a).frere) != NULL) {
            val_frere = ((*a).frere)->valeur ;
            printf("Noeud numéro %d\nFils : NULL\nFrere : %d\n\n",val,val_frere) ;
        }
        else {
            printf("Noeud numéro %d\nFils : NULL\nFrere : NULL\n\n",val) ;
        }
    }

    Arbre* f ;
    for (f = a->fils ; f != NULL ; f = f->frere) {
        afficher(f) ;
    }

}
