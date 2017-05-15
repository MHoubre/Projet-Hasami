#ifndef MIN_MAX_C_INCLUDED
#define MIN_MAX_C_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "min_max.h"
#include "arbres.h"
#include "fonction_evaluation.h"
#include "plateau.h"

int INFINI = 100 ;

Plateau* min_max(Plateau *p, int profondeur, Joueur joueur) {

    //on aura recours à la méthode rand()
    srand(time(NULL)) ;

    int val_coup_max = -INFINI ;
    int val_coup ;
    Coup meilleur_coup ;
    int pieces[18] ;

    pieces_joueur(pieces, p, joueur) ;

    Arbre arbre_coups = {NULL, -1, NULL, NULL} ;
    Arbre* a = &arbre_coups ;

    //initialisation de l'arbre
    a = initialiser_arbre_coups(a, p, pieces, joueur) ;

    //on parcourt les choix de coup possibles
    Coup coup ;
    Plateau plateau_copy ;
    Plateau* p_copy = &plateau_copy ;
    Arbre* f ;
    for (f = a->fils ; f != NULL ; f = f->frere) {

        //on restaure le plateau initial et on récupère le coup à jouer
        p_copy = copy_to(p, p_copy) ;
        coup = f->coup ;
        //on joue le coup
        p_copy = deplacer_piece(p_copy, joueur, coup.depart, coup.arrivee) ;

        //on récupère la valeur associée au coup
        val_coup = mini(p_copy, f, joueur, profondeur) ;

        //si les valeurs sont égales, on choisit aléatoirement le coup à jouer
        if (val_coup > val_coup_max || ((val_coup == val_coup_max) && (rand()%2 == 0))) {
            val_coup_max = val_coup ;
            meilleur_coup = coup ;
        }
    }

    afficher(a) ;
    printf("Taille : %d\nHauteur : %d", taille(a), hauteur(a)) ;
    //on joue le meilleur coup !
    return deplacer_piece(p, joueur, meilleur_coup.depart, meilleur_coup.arrivee) ;
}



int mini(Plateau* p, Arbre* a, Joueur joueur, int profondeur) {

    if (profondeur==0 || gagnant(p)!=-1) {
        return evaluer(p, joueur) ;
    }

    else {
        int pieces[18] ;
        pieces_joueur(pieces, p, joueur) ;
        a = initialiser_arbre_coups(a, p, pieces, joueur) ;

        //on parcourt les choix de coup possibles
        int val_coup_min = INFINI ;
        int val_coup ;

        Coup coup ;
        Plateau plateau_copy ;
        Plateau* p_copy = &plateau_copy ;
        Arbre* f ;
        for (f = a->fils ; f != NULL ; f = f->frere) {

            //on restaure le plateau initial et on récupère le coup à jouer
            p_copy = copy_to(p, p_copy) ;
            coup = f->coup ;
            //on joue le coup
            p_copy = deplacer_piece(p_copy, joueur, coup.depart, coup.arrivee) ;

            //on récupère la valeur associée au coup
            val_coup = maxi(p_copy, f, joueur, profondeur-1) ;

            if (val_coup < val_coup_min) {
                val_coup_min = val_coup ;
            }
        }

        return val_coup_min ;
    }
}



int maxi(Plateau* p, Arbre* a, Joueur joueur, int profondeur) {

    if (profondeur==0 || gagnant(p)!=-1) {
        return evaluer(p, joueur) ;
    }

    else {
        int pieces[18] ;
        pieces_joueur(pieces, p, joueur) ;
        a = initialiser_arbre_coups(a, p, pieces, joueur) ;

        //on parcourt les choix de coup possibles
        int val_coup_max = -INFINI ;
        int val_coup ;

        Coup coup ;
        Plateau plateau_copy ;
        Plateau* p_copy = &plateau_copy ;
        Arbre* f ;
        for (f = a->fils ; f != NULL ; f = f->frere) {

            //on restaure le plateau initial et on récupère le coup à jouer
            p_copy = copy_to(p, p_copy) ;
            coup = f->coup ;
            //on joue le coup
            p_copy = deplacer_piece(p_copy, joueur, coup.depart, coup.arrivee) ;

            //on récupère la valeur associée au coup
            val_coup = mini(p_copy, f, joueur, profondeur-1) ;

            if (val_coup > val_coup_max) {
                val_coup_max = val_coup ;
            }
        }

        return val_coup_max ;
    }
}



Arbre* initialiser_arbre_coups(Arbre* a, Plateau* p, int pieces[], Joueur joueur) {

    Coup coup ;
    int depart ;
    int arrivee ;
    int ligne ;
    int colonne ;

    int k ;
    int i ;
    int j ;

    int cmpt = 1 ;

    for (k = 0 ; k < 18 ; k++) {

        depart = pieces[k] ;
        ligne = depart/9 ;
        colonne = depart%9 ;

        //Changement de ligne
        for (i = 0 ; i < 9 ; i++) {
            arrivee = i*9+colonne ;
            if (coup_legal(p, joueur, depart, arrivee)) {
                coup.depart = depart ;
                coup.arrivee = arrivee ;
                a = ajouter_fils(a, coup, cmpt) ;
                cmpt++ ;
            }
        }

        //Changement de colonne
        for (j = 0 ; j < 9 ; j++) {
            arrivee = ligne*9+j ;
            if (coup_legal(p, joueur, depart, arrivee)) {
                coup.depart = depart ;
                coup.arrivee = arrivee ;
                ajouter_fils(a, coup, cmpt) ;
                cmpt++ ;
            }
        }
    }

    return a ;
}



void pieces_joueur(int pieces[], Plateau *p, Joueur joueur) {

    //Initialisation
    int i ;

    for (i = 0 ; i < 18 ; i++) {
        pieces[i] = -1 ;
    }

    int ind = 0 ;
    int cmpt = 0 ;

    while (cmpt < 18 && ind < 81) {
        //Si une pièce du joueur courant est sur la case, on l'ajoute
        if (p->cases[ind] == joueur+1) {
            pieces[cmpt] = ind ;
            cmpt++ ;
        }
        //On regarde la case suivante
        ind++ ;
    }

}

#endif // MIN_MAX_C_INCLUDED
