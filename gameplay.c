#include <stdio.h>
#include <stdlib.h>

typedef enum Joueur {
    JOUEUR_BLANC, JOUEUR_NOIR
} Joueur ;

typedef enum Case {
    VIDE, BLANC, NOIR
} Case ;

typedef struct Plateau {
    Case cases[81] ;
}Plateau ;

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


void deplacer_piece(Plateau* p, Joueur j, int depart, int arrivee) { //d�place une pi�ce depuis la position depart, jusqu'� la position arrivee

    if (coup_legal(p, j, depart, arrivee)) {
            Case piece = (*p).cases[depart] ;
            p->cases[depart] = VIDE ;
            p->cases[arrivee] = piece ;
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
                        printf("D�placement non autoris�.\n") ;
                    }

                }
                else {
                    printf("Les cases de d�part et d'arriv�e doivent �tre diff�rentes.\n") ;
                }

            }
            else {
                if (case_depart == VIDE) {
                    printf("La case s�lectionn�e est vide.\n") ;
                }
                else {
                    printf("La pi�ce doit appartenir au joueur courant !\n") ;
                }
            }

        }
        else {
            printf("La case d'arriv�e est hors du plateau !\n") ;
        }
    }
    else {
        printf("La case de d�part est hors du plateau !\n") ;
    }

    return booleen ;
}


int main(int argc, char *argv[]){

    Joueur joueur_courant = BLANC ;
    Plateau plateau ;
    int stop = 0 ;
    int depart ;
    int arrivee ;

    initialiser_plateau(&plateau) ;

    while (stop == 0) {
        depart = select_depart() ;
        arrivee = select_arrivee() ;

        while (!coup_legal(&p, joueur_courant, depart, arrivee)){
            depart = select_depart() ;
            arrivee = select_arrivee() ;
        }

        deplacer_piece(&p, joueur_courant, depart, arrivee) ;
        joueur_courant = (joueur_courant+1)%2 ;

        afficher(&p) ;
    }

    return 1
}
