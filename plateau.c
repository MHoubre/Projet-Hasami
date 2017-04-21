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


Plateau* deplacer_piece(Plateau* p, Joueur j, int depart, int arrivee) { //d�place une pi�ce depuis la position depart, jusqu'� la position arrivee

    if (coup_legal(p, j, depart, arrivee)) {
            //on d�place la pi�ce
            Case piece = (*p).cases[depart] ;
            p->cases[depart] = VIDE ;
            p->cases[arrivee] = piece ;

            //on "mange" les pi�ces qu'il faut
            return manger(p, j, depart, arrivee) ;
    }

    else {
        return p ;
    }
}


int coup_legal(Plateau* p, Joueur j, int depart, int arrivee) {

    int booleen = 0 ; //bool�en d�terminant si le coup est l�gal ou non
    Case case_depart = (*p).cases[depart] ;
    Case case_arrivee = (*p).cases[arrivee] ;

    if (depart>=0 && depart<81) { //la case de d�part doit �tre sur le plateau

        if (arrivee>=0 && arrivee<81) { //la case d'arriv�e doit �tre sur le plateau

            if (j+1 == case_depart) { //la pi�ce doit appartenir au joueur courant

                if (depart != arrivee) { //les cases de d�part et d'arriv�e doivent �tre diff�rentes

                    if (depart/9 == arrivee/9) { //d�placement horizontal

                        if (arrivee>depart) { //d�placement de gauche � droite
                            int temp = depart+1 ;

                            while ((*p).cases[temp]==VIDE && temp!=arrivee) {
                            temp++ ;
                            }

                            //la case d'arriv�e doit �tre vide, et il ne doit pas y avoir de pi�ce
                            //sur le chemin du d�placement, sauf la case pr�c�dent la case d'arriv�e
                            booleen = (arrivee-temp < 2) && (case_arrivee == VIDE) ;
                        }

                        else {
                            int temp = depart-1 ;

                            while ((*p).cases[temp]==VIDE && temp!=arrivee) {
                            temp-- ;
                            }

                            //la case d'arriv�e doit �tre vide, et il ne doit pas y avoir de pi�ce
                            //sur le chemin du d�placement, sauf la case pr�c�dent la case d'arriv�e
                            booleen = (temp-arrivee < 2) && (case_arrivee == VIDE) ;
                        }
                    }

                    if ((arrivee-depart)%9 == 0) { //d�placement vertical

                        if (arrivee>depart) {

                            int temp = depart+9 ;

                            while ((*p).cases[temp]==VIDE && temp!=arrivee) {
                                temp+=9 ;
                            }

                            //la case d'arriv�e doit �tre vide, et il ne doit pas y avoir de pi�ce
                            //sur le chemin du d�placement, sauf la case pr�c�dent la case d'arriv�e
                            booleen = ((temp == arrivee) || (temp == arrivee-9)) && (case_arrivee == VIDE) ;

                        }
                        else {
                            int temp = depart-9 ;

                            while ((*p).cases[temp]==VIDE && temp!=arrivee) {
                                temp-=9 ;
                            }

                            //la case d'arriv�e doit �tre vide, et il ne doit pas y avoir de pi�ce
                            //sur le chemin du d�placement, sauf la case pr�c�dent la case d'arriv�e
                            booleen = ((temp == arrivee) || (temp == arrivee+9)) && (case_arrivee == VIDE) ;
                        }

                    }

                    else {
                        //printf("D�placement non autoris�.\n") ;
                    }

                }
                else {
                    //printf("Les cases de d�part et d'arriv�e doivent �tre diff�rentes.\n") ;
                }

            }
            else {
                if (case_depart == VIDE) {
                    //printf("La case s�lectionn�e est vide.\n") ;
                }
                else {
                    //printf("La pi�ce doit appartenir au joueur courant !\n") ;
                }
            }

        }
        else {
            //printf("La case d'arriv�e est hors du plateau !\n") ;
        }
    }
    else {
        //printf("La case de d�part est hors du plateau !\n") ;
    }

    return booleen ;
}


Plateau* manger(Plateau* p, Joueur joueur, int depart, int arrivee) {

    //le d�placement est-il en ligne ?
    if (depart%9 == arrivee%9) {
    //le d�placement est-il de gauche � droite ?
        if (arrivee > depart) {
            //une pi�ce sur la m�me ligne peut �tre mang�e si et seulement si
            //la case � gauche de l'arrivee est occup�e par une pi�ce du joueur
            //adverse et qu'il y a une pi�ce du joueur courant � gauche de la case depart.
            if ((*p).cases[arrivee-1] == ((joueur+1)%2)+1) {
                int i = (depart/9)*9+8;
                while (i>depart && (*p).cases[i]!=joueur+1) {
                    i-- ;
                }
                //si c'est le cas, la pi�ce est mang�e
                if (i>depart) {
                    (*p).cases[arrive+1] = VIDE ;
                }
            }
        }

        else {
            //une pi�ce sur la m�me ligne peut �tre mang�e si et seulement si
            //la case � droite de l'arrivee est occup�e par une pi�ce du joueur
            //adverse et qu'il y a une pi�ce du joueur courant � droite de la case depart.
            if ((*p).cases[arrivee+1] == ((joueur+1)%2)+1) {
                int i = (depart/9)*9 ;
                while (i<depart && (*p).cases[i]!=joueur+1) {
                    i++ ;
                }
                //si c'est le cas, la pi�ce est mang�e
                if (i<depart) {
                    (*p).cases[arrive-1] = VIDE ;
                }
            }
        }

        //puis, il faut v�rifier si une pi�ce est mang�e sur la colonne
        int j = arrivee%9 ;

        //tout d'abord, en bas de la case arrivee !
        //il faut trouver une case contenant une autre pi�ce du joueur courant
        while (j<arrivee && (*p).cases[j]!=joueur+1) {
            j+=9 ;
        }
        //en a-t-on trouv� ?
        if (j < arrivee) {
            while (j < arrivee) {
                //si on tombe sur une pi�ce du joueur adverse, on vide la case
                if ((*p).cases[j] == ((joueur+1)%2)+1) {
                    (*p).cases[j] = VIDE ;
                }
                j+=9 ;
            }
        }

        //maintenant, au-dessus ! on a ici j == arrivee ;
        //on se place sur la ligne la plus "haute" du plateau
        j = (arrive%9)+72 ;

        //on cherche une case contenant une autre pi�ce du joueur courant
        while (j>arrivee && (*p).cases[j]!=joueur+1) {
            j-=9 ;
        }
        //en a-t-on trouv� ?
        if (j > arrivee) {
            while (j > arrivee) {
                //si on tombe sur une pi�ce du joueur adverse, on vide la case
                if ((*p).cases[j] == ((joueur+1)%2)+1) {
                    (*p).cases[j] = VIDE ;
                }
                j-=9 ;
            }
        }

    }


    //sinon, il est en colonne, et suivant la m�me logique on obtient :
    else {
        //le d�placement est-il de bas en haut ?
        if (arrivee > depart) {
            //une pi�ce sur la m�me colonne peut �tre mang�e si et seulement si
            //la case en bas de l'arrivee est occup�e par une pi�ce du joueur
            //adverse et qu'il y a une pi�ce du joueur courant en bas de la case depart.
            if ((*p).cases[arrivee-9] == ((joueur+1)%2)+1) {
                int j = depart%9 ;
                while (j<depart && (*p).cases[j]!=joueur+1) {
                    j+=9 ;
                }
                //si c'est le cas, la pi�ce est mang�e
                if (j<depart) {
                    (*p).cases[arrive-9] = VIDE ;
                }
            }
        }

        //sinon, le d�placement est de haut en bas
        else {
            //une pi�ce sur la m�me colonne peut �tre mang�e si et seulement si
            //la case en haut de l'arrivee est occup�e par une pi�ce du joueur
            //adverse et qu'il y a une pi�ce du joueur courant en haut de la case depart.
            if ((*p).cases[arrivee+9] == ((joueur+1)%2)+1) {
                int j = (depart%9)+72 ;
                while (j>depart && (*p).cases[j]!=joueur+1) {
                    j-=9 ;
                }
                //si c'est le cas, la pi�ce est mang�e
                if (j>depart) {
                    (*p).cases[arrive+9] = VIDE ;
                }
            }
        }

        //puis, il faut v�rifier si une pi�ce est mang�e sur la ligne
        int i = (arrivee/9)*9 ;

        //tout d'abord, � gauche de la case arrivee !
        //il faut trouver une case contenant une autre pi�ce du joueur courant
        while (i<arrivee && (*p).cases[i]!=joueur+1) {
            i++ ;
        }
        //en a-t-on trouv� ?
        if (i < arrivee) {
            while (i < arrivee) {
                //si on tombe sur une pi�ce du joueur adverse, on vide la case
                if ((*p).cases[i] == ((joueur+1)%2)+1) {
                    (*p).cases[i] = VIDE ;
                }
                i++ ;
            }
        }

        //maintenant, au-dessus ! on a ici j == arrivee ;
        //on se place sur la ligne la plus � droite du plateau
        i = (arrivee/9)*9+8 ;

        //on cherche une case contenant une autre pi�ce du joueur courant
        while (i>arrivee && (*p).cases[i]!=joueur+1) {
            i-- ;
        }
        //en a-t-on trouv� ?
        if (i > arrivee) {
            while (i > arrivee) {
                //si on tombe sur une pi�ce du joueur adverse, on vide la case
                if ((*p).cases[i] == ((joueur+1)%2)+1) {
                    (*p).cases[i] = VIDE ;
                }
                i-- ;
            }
        }

    }

    return p ;

}
