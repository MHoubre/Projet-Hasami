#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fonction_evaluation.h"
#include "plateau.h"
#include "plateau.c"


//Fonction d'evaluation finale
int evaluer (Plateau* p, Joueur j){

    int eval = 0 ;

    int coef1 = 1 ;
    int coef2 = 2 ;
    int coef3 = 1 ;
    int coef4 = 1 ;

    eval += coef1* evaluerMateriel(p, j);
    eval += coef2* evaluerMobilite(p, j);
    eval += coef3* evaluerLigne(p,j);
    eval += coef4* evaluerDominationTerritoire(p,j);

    return eval;

}

// Calcule le nombre de pions de chaque jiueur sur le plateau

int nombreDePions(Plateau* p, Joueur j)
{
    int nbPions = 0; //Compteur des pions
    int i;

    for(i=0; i<81; i++){
            if ((*p).cases[i] == j+1){
                nbPions++ ;
            }
    }

    return nbPions ;
}



//Evaluation dU Materiel consiste à faire la différence entre le nombre de pions que possède chaque joueur

int evaluerMateriel(Plateau *p, Joueur j) {

    int nb1, nb2;

    nb1 = nombreDePions(p, j) ;
    nb2 = nombreDePions(p, (j+1)%2) ;

    return nb1-nb2 ;
}



/* Evaluation des possibilités de déplacement de chaque joueur
Parcourir les pions du joueur pion par pion et Calculer le nombre de déplacements que peut faire chaque pion
Affecter la diffrérence entre les deplacements des pions des deux joueurs à evaluateMobility */


int evaluerMobilite(Plateau* p, Joueur joueur) {

    int mob1 = 0 ;
    int mob2 = 0 ;

    int depart ;
    int arrivee ;
    Case c ;

    //Premier indice de la ligne
    int i ;
    //Premier indice de la colonne
    int j ;
    int k ;

    for(depart=0 ; depart<81 ; depart++) {

        c = (*p).cases[depart] ;

        if (c!=VIDE) {

            i = (depart/9)*9 ;
            j = depart%9 ;

            //tests sur la ligne
            for(k=0 ; k<9 ; k++) {
                arrivee = i+k ;
                if (c-1==joueur && coup_legal(p, joueur, depart, arrivee)) {
                    mob1++ ;
                }
                else {
                    if (coup_legal(p, (joueur+1)%2, depart, arrivee)) {
                        mob2++ ;
                    }
                }
            }

            //test sur la colonne
            for(k=0 ; k<9 ; k++) {
                arrivee = j+k*9 ;
                if (c-1==joueur && coup_legal(p, joueur, depart, arrivee)) {
                    mob1++ ;
                }
                else {
                    if (coup_legal(p, (joueur+1)%2, depart, arrivee)) {
                        mob2++ ;
                    }
                }
            }
        }
    }

    return mob1-mob2 ;
}


/*evaluer la chance de gain par alignement des pions.
Si le pion n'a jamais déplacé alors retourne 0
si deux cases successives verticalement ou diagonalement sont de mm couleur et que les 3 suivantes sont vides on attribue 2^2
si 3 cases successives verticalement ou diagonalement sont de mm couleur et que les 2 suivantes sont vides on attribue 3^2
si 4 cases successives verticalement ou diagonalement sont de mm couleur et que les 1 suivantes est vide on attribue 4^2 */

int evaluerLigne(Plateau *p, Joueur j){

    int scoreB = 0 ;
    int scoreN = 0 ;
    int depart ;

    int ddb, dgb, vb, ddn, dgn, vn ;

    for (depart=0 ; depart<81 ; depart++) {
        ddb = diagonale_droite_blanc(p, depart) ;
        dgb = diagonale_gauche_blanc(p, depart) ;
        vb = verticale_blanc(p, depart) ;
        ddn = diagonale_droite_noir(p, depart) ;
        dgn = diagonale_gauche_noir(p, depart) ;
        vn = verticale_noir(p, depart) ;
        if (ddb>1) {
            scoreB += ddb ;
        }
        if (dgb>1) {
            scoreB += dgb ;
        }
        if (vb>1) {
            scoreB += vb ;
        }
        if (ddn>1) {
            scoreN += ddn ;
        }
        if (dgn>1) {
            scoreN += dgn ;
        }
        if (vn>1) {
            scoreN += vn ;
        }
    }

    if (j == JOUEUR_BLANC) {
        return scoreB-scoreN ;
    }
    else {
        return scoreN-scoreB ;
    }
}

//diagonale droite pour les blancs
int diagonale_droite_blanc(Plateau *p, int depart) {

    int k = depart ;
    int longueur = 0 ;

    while (k<63 && k%9<8 && (*p).cases[k]==BLANC) {
        k+=10 ;
        longueur++ ;
    }

    if (k%9==8 && (*p).cases[k]==BLANC) {
        longueur++ ;
    }

    return longueur ;
}

//diagonale gauche pour les blancs
int diagonale_gauche_blanc(Plateau *p, int depart) {

    int k = depart ;
    int longueur = 0 ;

    while (k<63 && k%9>0 && (*p).cases[k]==BLANC) {
        k+=8 ;
        longueur++ ;
    }

    if (k%9==0 && (*p).cases[k]==BLANC) {
        longueur++ ;
    }

    return longueur ;
}

//diagonale droite pour les noirs
int diagonale_droite_noir(Plateau *p, int depart) {

    int k = depart ;
    int longueur = 0 ;

    while (k>17 && k<81 && k%9<8 && (*p).cases[k]==NOIR) {
        k+=10 ;
        longueur++ ;
    }

    if (k%9==8 && (*p).cases[k]==NOIR) {
        longueur++ ;
    }

    return longueur ;
}

//diagonale gauche pour les noirs
int diagonale_gauche_noir(Plateau *p, int depart) {

    int k = depart ;
    int longueur = 0 ;

    while (k>17 && k<81 && k%9>0 && (*p).cases[k]==NOIR) {
        k+=8 ;
        longueur++ ;
    }

    if (k%9==0 && (*p).cases[k]==NOIR) {
        longueur++ ;
    }

    return longueur ;
}

//ligne verticale pour les blancs
int verticale_blanc(Plateau *p, int depart) {

    int k = depart ;
    int longueur = 0 ;

    while (k<63 && (*p).cases[k]==BLANC) {
        k+=9 ;
        longueur++ ;
    }

    return longueur ;
}

//ligne verticale pour les noirs
int verticale_noir(Plateau *p, int depart) {

    int k = depart ;
    int longueur = 0 ;

    while (k>17 && k<81 && (*p).cases[k]==NOIR) {
        k+=9 ;
        longueur++ ;
    }

    return longueur ;
}


/*Domination du territoire*/

int evaluerDominationTerritoire(Plateau* p, Joueur joueur) {

    int zonesB = 0 ;
    int zonesN = 0 ;
    int k ;

    int nbB = 0 ;
    int nbN = 0 ;

    //On regarde la zone de départ des noirs
    for (k=0 ; k<18 ; k++) {
        if ((*p).cases[k]==BLANC) {
            nbB++ ;
        }
        else {
            if ((*p).cases[k]==NOIR) {
                nbN++ ;
            }
        }
    }

    if (nbB>nbN) {
        zonesB++ ;
    }
    else {
        if (nbN>nbB) {
            zonesN++ ;
        }
    }

    //On regarde la zone de départ des blancs
    nbB = 0 ;
    nbN = 0 ;

    for (k=63 ; k<81 ; k++) {
        if ((*p).cases[k]==BLANC) {
            nbB++ ;
        }
        else {
            if ((*p).cases[k]==NOIR) {
                nbN++ ;
            }
        }
    }

    if (nbB>nbN) {
        zonesB++ ;
    }
    else {
        if (nbN>nbB) {
            zonesN++ ;
        }
    }

    //on regarde la zone du centre gauche
    //c'est-à-dire la sous-matrice contenant
    //les lignes 2 à 6 et les colonnes 0 à 2
    int i ;
    int j ;

    nbB = 0 ;
    nbN = 0 ;

    for (i=2 ; i<7 ; i++) {
        for (j=0 ; j<3 ; j++) {
            if ((*p).cases[i*9+j]==BLANC) {
                nbB++ ;
            }
            else {
                if ((*p).cases[i*9+j]==NOIR) {
                    nbN++ ;
                }
            }
        }
    }

    if (nbB>nbN) {
        zonesB++ ;
    }
    else {
        if (nbN>nbB) {
            zonesN++ ;
        }
    }

    //on regarde la zone du centre centre
    //c'est-à-dire la sous-matrice contenant
    //les lignes 2 à 6 et les colonnes 3 à 5
    nbB = 0 ;
    nbN = 0 ;

    for (i=2 ; i<7 ; i++) {
        for (j=3 ; j<6 ; j++) {
            if ((*p).cases[i*9+j]==BLANC) {
                nbB++ ;
            }
            else {
                if ((*p).cases[i*9+j]==NOIR) {
                    nbN++ ;
                }
            }
        }
    }

    if (nbB>nbN) {
        zonesB++ ;
    }
    else {
        if (nbN>nbB) {
            zonesN++ ;
        }
    }

    //on regarde la zone du centre centre
    //c'est-à-dire la sous-matrice contenant
    //les lignes 2 à 6 et les colonnes 6 à 8
    nbB = 0 ;
    nbN = 0 ;

    for (i=2 ; i<7 ; i++) {
        for (j=6 ; j<9 ; j++) {
            if ((*p).cases[i*9+j]==BLANC) {
                nbB++ ;
            }
            else {
                if ((*p).cases[i*9+j]==NOIR) {
                    nbN++ ;
                }
            }
        }
    }

    if (nbB>nbN) {
        zonesB++ ;
    }
    else {
        if (nbN>nbB) {
            zonesN++ ;
        }
    }

    //on renvoie le résultat
    if (joueur == JOUEUR_BLANC) {
        return zonesB-zonesN ;
    }
    else {
        return zonesN-zonesB ;
    }


}

