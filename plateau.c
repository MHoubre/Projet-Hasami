#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include "fonction_evaluation.c"

void initialiser_plateau(Plateau* p) {

    int k ;

    for (k = 0 ; k < 18 ; k++) {
        p->cases[k] = NOIR ;
    }

    for( k = 18 ; k < 63 ; k++){
        p->cases[k] = VIDE ;
    }

    for (k = 63 ; k < 81 ; k++) {
        p->cases[k] = BLANC ;
    }
}


Plateau* deplacer_piece(Plateau* p, Joueur j, int depart, int arrivee) { //déplace une pièce depuis la position depart, jusqu'à la position arrivee

    if (coup_legal(p, j, depart, arrivee)) {
            //on déplace la pièce
            Case piece = (*p).cases[depart] ;
            p->cases[depart] = VIDE ;
            p->cases[arrivee] = piece ;

            //on "mange" les pièces qu'il faut
            return manger(p, j, depart, arrivee) ;
    }

    else {
        return p ;
    }
}


int coup_legal(Plateau* p, Joueur j, int depart, int arrivee) {

    int booleen = 0 ; //booléen déterminant si le coup est légal ou non
    Case case_depart = (*p).cases[depart] ;
    Case case_arrivee = (*p).cases[arrivee] ;

    if (depart>=0 && depart<81) { //la case de départ doit être sur le plateau

        if (arrivee>=0 && arrivee<81) { //la case d'arrivée doit être sur le plateau

            if (j+1 == case_depart) { //la pièce doit appartenir au joueur courant

                if (depart != arrivee) { //les cases de départ et d'arrivée doivent être différentes

                    if (depart/9 == arrivee/9) { //déplacement horizontal

                        if (arrivee>depart) { //déplacement de gauche à droite
                            int temp = depart+1 ;

                            while ((*p).cases[temp]==VIDE && temp!=arrivee) {
                            temp++ ;
                            }

                            //la case d'arrivée doit être vide, et il ne doit pas y avoir de pièce
                            //sur le chemin du déplacement, sauf la case précédent la case d'arrivée
                            booleen = (arrivee-temp < 2) && (case_arrivee == VIDE) ;
                        }

                        else {
                            int temp = depart-1 ;

                            while ((*p).cases[temp]==VIDE && temp!=arrivee) {
                            temp-- ;
                            }

                            //la case d'arrivée doit être vide, et il ne doit pas y avoir de pièce
                            //sur le chemin du déplacement, sauf la case précédent la case d'arrivée
                            booleen = (temp-arrivee < 2) && (case_arrivee == VIDE) ;
                        }
                    }

                    if ((arrivee-depart)%9 == 0) { //déplacement vertical

                        if (arrivee>depart) {

                            int temp = depart+9 ;

                            while ((*p).cases[temp]==VIDE && temp!=arrivee) {
                                temp+=9 ;
                            }

                            //la case d'arrivée doit être vide, et il ne doit pas y avoir de pièce
                            //sur le chemin du déplacement, sauf la case précédent la case d'arrivée
                            booleen = ((temp == arrivee) || (temp == arrivee-9)) && (case_arrivee == VIDE) ;

                        }
                        else {
                            int temp = depart-9 ;

                            while ((*p).cases[temp]==VIDE && temp!=arrivee) {
                                temp-=9 ;
                            }

                            //la case d'arrivée doit être vide, et il ne doit pas y avoir de pièce
                            //sur le chemin du déplacement, sauf la case précédent la case d'arrivée
                            booleen = ((temp == arrivee) || (temp == arrivee+9)) && (case_arrivee == VIDE) ;
                        }

                    }

                    else {
                        //printf("Déplacement non autorisé.\n") ;
                    }

                }
                else {
                    //printf("Les cases de départ et d'arrivée doivent être différentes.\n") ;
                }

            }
            else {
                if (case_depart == VIDE) {
                    //printf("La case sélectionnée est vide.\n") ;
                }
                else {
                    //printf("La pièce doit appartenir au joueur courant !\n") ;
                }
            }

        }
        else {
            //printf("La case d'arrivée est hors du plateau !\n") ;
        }
    }
    else {
        //printf("La case de départ est hors du plateau !\n") ;
    }

    return booleen ;
}


Plateau* manger(Plateau* p, Joueur joueur, int depart, int arrivee) {

    //le déplacement est-il en lignes ?
    if (depart%9 == arrivee%9) {
        //le déplacement est-il de haut en bas ?
        if (arrivee > depart) {
            //on teste s'il y a une pièce du joueur adverse en bas
            if (arrivee+18<81 && (*p).cases[arrivee+9]==((joueur+1)%2)+1) {
                int i = arrivee+18 ;
                //tant qu'on a des pièces du joueur adverse alignées, on continue
                while (i<81 && (*p).cases[i]==((joueur+1)%2)+1) {
                    i+=9 ;
                }
                //si lorsqu'on s'arrête on est sur une case contenant un pion
                //du joueur courant, alors on mange la ligne de pion adverse
                if (i<81 && (*p).cases[i]==joueur+1){
                    int k ;
                    for (k = arrivee+9 ; k<i ; k+=9) {
                        (*p).cases[k]=VIDE ;
                    }
                }
            }
        }
        //sinon, le déplacement est de bas en haut
        else {
            //on teste s'il y a une pièce du joueur adverse en haut
            if (arrivee-18>0 && (*p).cases[arrivee-9]==((joueur+1)%2)+1) {
                int i = arrivee-18 ;
                //tant qu'on a des pièces du joueur adverse alignées, on continue
                while (i>0 && (*p).cases[i]==((joueur+1)%2)+1) {
                    i-=9 ;
                }
                //si lorsqu'on s'arrête on est sur une case contenant un pion
                //du joueur courant, alors on mange la ligne de pion adverse
                if (i>0 && (*p).cases[i]==joueur+1){
                    int k ;
                    for (k = arrivee-9 ; k>i ; k-=9) {
                        (*p).cases[k]=VIDE ;
                    }
                }
            }
        }

        //il y a-t-il une pièce adverse à droite ?
        if (arrivee%9<7 && (*p).cases[arrivee+1]==((joueur+1)%2)+1) {
            int j = arrivee+1 ;
            //tant qu'il y a des pièces du joueur adverse alignées, on continue
            while (j%9!=8 && (*p).cases[j]==((joueur+1)%2)+1) {
                j++ ;
            }
            //si lorsqu'on s'arrête on est sur une case contenant un pion
            //du joueur courant, alors on mange la ligne de pion adverse
            if (j%9!=8 && (*p).cases[j]==joueur+1){
                int k ;
                for (k = arrivee+1 ; k<j ; k++) {
                    (*p).cases[k]=VIDE ;
                }
            }
        }

        //il y a-t-il une pièce adverse à droite ?
        if (arrivee%9>1 && (*p).cases[arrivee-1]==((joueur+1)%2)+1) {
            int j = arrivee-1 ;
            //tant qu'il y a des pièces du joueur adverse alignées, on continue
            while (j%9!=0 && (*p).cases[j]==((joueur+1)%2)+1) {
                j-- ;
            }
            //si lorsqu'on s'arrête on est sur une case contenant un pion
            //du joueur courant, alors on mange la ligne de pion adverse
            if (j%9!=0 && (*p).cases[j]==joueur+1){
                int k ;
                for (k = arrivee-1 ; k>j ; k--) {
                    (*p).cases[k]=VIDE ;
                }
            }
        }
    }

    //sinon le déplacement est en colonnes
    else {
        //le déplacement est-il de gauche à droite ?
        if (arrivee > depart) {
            //on teste s'il y a une pièce du joueur adverse à droite
            if (arrivee%9<7 && (*p).cases[arrivee+1]==((joueur+1)%2)+1) {
                int j = arrivee+1 ;
                //tant qu'on a des pièces du joueur adverse alignées, on continue
                while (j%9!=8 && (*p).cases[j]==((joueur+1)%2)+1) {
                    j++ ;
                }
                //si lorsqu'on s'arrête on est sur une case contenant un pion
                //du joueur courant, alors on mange la ligne de pion adverse
                if (j%9!=8 && (*p).cases[j]==joueur+1){
                    int k ;
                    for (k = arrivee+1 ; k<j ; k++) {
                        (*p).cases[k]=VIDE ;
                    }
                }
            }
        }
        //sinon, le déplacement est de droite à gauche
        else {
            //on teste s'il y a une pièce du joueur adverse à gauche
            if (arrivee%9>1 && (*p).cases[arrivee-1]==((joueur+1)%2)+1) {
                int j = arrivee-1 ;
                //tant qu'on a des pièces du joueur adverse alignées, on continue
                while (j%9!=0 && (*p).cases[j]==((joueur+1)%2)+1) {
                    j-- ;
                }
                //si lorsqu'on s'arrête on est sur une case contenant un pion
                //du joueur courant, alors on mange la ligne de pion adverse
                if (j%9!=0 && (*p).cases[j]==joueur+1){
                    int k ;
                    for (k = arrivee-1 ; k>j ; k--) {
                        (*p).cases[k]=VIDE ;
                    }
                }
            }
        }

        //il y a-t-il une pièce adverse en bas ?
        if (arrivee+18<81 && (*p).cases[arrivee+9]==((joueur+1)%2)+1) {
            int i = arrivee+9 ;
            //tant qu'il y a des pièces du joueur adverse alignées, on continue
            while (i<81 && (*p).cases[i]==((joueur+1)%2)+1) {
                i+=9 ;
            }
            //si lorsqu'on s'arrête on est sur une case contenant un pion
            //du joueur courant, alors on mange la ligne de pion adverse
            if (i<81 && (*p).cases[i]==joueur+1){
                int k ;
                for (k = arrivee+9 ; k<i ; k+=9) {
                    (*p).cases[k]=VIDE ;
                }
            }
        }

        //il y a-t-il une pièce adverse en haut ?
        if (arrivee-18>0 && (*p).cases[arrivee-1]==((joueur+1)%2)+1) {
            int i = arrivee-9 ;
            //tant qu'il y a des pièces du joueur adverse alignées, on continue
            while (i>0 && (*p).cases[i]==((joueur+1)%2)+1) {
                i-=9 ;
            }
            //si lorsqu'on s'arrête on est sur une case contenant un pion
            //du joueur courant, alors on mange la ligne de pion adverse
            if (i>0 && (*p).cases[i]==joueur+1){
                int k ;
                for (k = arrivee-9 ; k>i ; k-=9) {
                    (*p).cases[k]=VIDE ;
                }
            }
        }
    }

    return p ;

}


//on renvoie -1 s'il n'y a pas de gagnant, sinon l'entier correspondant
//au joueur qui gagne la partie
int gagnant(Plateau* p) {

    //si le joueur blanc a 1 ou 0 pion, il a perdu
    int nb_blanc = nombreDePions(p, JOUEUR_BLANC) ;
    if (nb_blanc<2) {
        return JOUEUR_NOIR ;
    }

    else {
        //si le joueur noir a 1 ou 0 pion, il a perdu
        int nb_noir = nombreDePions(p, JOUEUR_NOIR) ;
        if (nb_noir<2) {
            return JOUEUR_BLANC ;
        }

        //sinon, on cherche une ligne ou diagonale gagnante
        else {

        }
    }

    return -1 ;

}
