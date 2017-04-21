#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"

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

    //le déplacement est-il en ligne ?
    if (depart%9 == arrivee%9) {
    //le déplacement est-il de gauche à droite ?
        if (arrivee > depart) {
            //une pièce sur la même ligne peut être mangée si et seulement si
            //la case à gauche de l'arrivee est occupée par une pièce du joueur
            //adverse et qu'il y a une pièce du joueur courant à gauche de la case depart.
            if ((*p).cases[arrivee-1] == ((joueur+1)%2)+1) {
                int i = (depart/9)*9+8;
                while (i>depart && (*p).cases[i]!=joueur+1) {
                    i-- ;
                }
                //si c'est le cas, la pièce est mangée
                if (i>depart) {
                    (*p).cases[arrive+1] = VIDE ;
                }
            }
        }

        else {
            //une pièce sur la même ligne peut être mangée si et seulement si
            //la case à droite de l'arrivee est occupée par une pièce du joueur
            //adverse et qu'il y a une pièce du joueur courant à droite de la case depart.
            if ((*p).cases[arrivee+1] == ((joueur+1)%2)+1) {
                int i = (depart/9)*9 ;
                while (i<depart && (*p).cases[i]!=joueur+1) {
                    i++ ;
                }
                //si c'est le cas, la pièce est mangée
                if (i<depart) {
                    (*p).cases[arrive-1] = VIDE ;
                }
            }
        }

        //puis, il faut vérifier si une pièce est mangée sur la colonne
        int j = arrivee%9 ;

        //tout d'abord, en bas de la case arrivee !
        //il faut trouver une case contenant une autre pièce du joueur courant
        while (j<arrivee && (*p).cases[j]!=joueur+1) {
            j+=9 ;
        }
        //en a-t-on trouvé ?
        if (j < arrivee) {
            while (j < arrivee) {
                //si on tombe sur une pièce du joueur adverse, on vide la case
                if ((*p).cases[j] == ((joueur+1)%2)+1) {
                    (*p).cases[j] = VIDE ;
                }
                j+=9 ;
            }
        }

        //maintenant, au-dessus ! on a ici j == arrivee ;
        //on se place sur la ligne la plus "haute" du plateau
        j = (arrive%9)+72 ;

        //on cherche une case contenant une autre pièce du joueur courant
        while (j>arrivee && (*p).cases[j]!=joueur+1) {
            j-=9 ;
        }
        //en a-t-on trouvé ?
        if (j > arrivee) {
            while (j > arrivee) {
                //si on tombe sur une pièce du joueur adverse, on vide la case
                if ((*p).cases[j] == ((joueur+1)%2)+1) {
                    (*p).cases[j] = VIDE ;
                }
                j-=9 ;
            }
        }

    }


    //sinon, il est en colonne, et suivant la même logique on obtient :
    else {
        //le déplacement est-il de bas en haut ?
        if (arrivee > depart) {
            //une pièce sur la même colonne peut être mangée si et seulement si
            //la case en bas de l'arrivee est occupée par une pièce du joueur
            //adverse et qu'il y a une pièce du joueur courant en bas de la case depart.
            if ((*p).cases[arrivee-9] == ((joueur+1)%2)+1) {
                int j = depart%9 ;
                while (j<depart && (*p).cases[j]!=joueur+1) {
                    j+=9 ;
                }
                //si c'est le cas, la pièce est mangée
                if (j<depart) {
                    (*p).cases[arrive-9] = VIDE ;
                }
            }
        }

        //sinon, le déplacement est de haut en bas
        else {
            //une pièce sur la même colonne peut être mangée si et seulement si
            //la case en haut de l'arrivee est occupée par une pièce du joueur
            //adverse et qu'il y a une pièce du joueur courant en haut de la case depart.
            if ((*p).cases[arrivee+9] == ((joueur+1)%2)+1) {
                int j = (depart%9)+72 ;
                while (j>depart && (*p).cases[j]!=joueur+1) {
                    j-=9 ;
                }
                //si c'est le cas, la pièce est mangée
                if (j>depart) {
                    (*p).cases[arrive+9] = VIDE ;
                }
            }
        }

        //puis, il faut vérifier si une pièce est mangée sur la ligne
        int i = (arrivee/9)*9 ;

        //tout d'abord, à gauche de la case arrivee !
        //il faut trouver une case contenant une autre pièce du joueur courant
        while (i<arrivee && (*p).cases[i]!=joueur+1) {
            i++ ;
        }
        //en a-t-on trouvé ?
        if (i < arrivee) {
            while (i < arrivee) {
                //si on tombe sur une pièce du joueur adverse, on vide la case
                if ((*p).cases[i] == ((joueur+1)%2)+1) {
                    (*p).cases[i] = VIDE ;
                }
                i++ ;
            }
        }

        //maintenant, au-dessus ! on a ici j == arrivee ;
        //on se place sur la ligne la plus à droite du plateau
        i = (arrivee/9)*9+8 ;

        //on cherche une case contenant une autre pièce du joueur courant
        while (i>arrivee && (*p).cases[i]!=joueur+1) {
            i-- ;
        }
        //en a-t-on trouvé ?
        if (i > arrivee) {
            while (i > arrivee) {
                //si on tombe sur une pièce du joueur adverse, on vide la case
                if ((*p).cases[i] == ((joueur+1)%2)+1) {
                    (*p).cases[i] = VIDE ;
                }
                i-- ;
            }
        }

    }

    return p ;

}
