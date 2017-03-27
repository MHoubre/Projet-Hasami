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


void deplacer_piece(Plateau* p, Joueur j, int depart, int arrivee) { //déplace une pièce depuis la position depart, jusqu'à la position arrivee

    if (coup_legal(p, j, depart, arrivee)) {
            Case piece = (*p).cases[depart] ;
            p->cases[depart] = VIDE ;
            p->cases[arrivee] = piece ;
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
                        printf("Déplacement non autorisé.\n") ;
                    }

                }
                else {
                    printf("Les cases de départ et d'arrivée doivent être différentes.\n") ;
                }

            }
            else {
                if (case_depart == VIDE) {
                    printf("La case sélectionnée est vide.\n") ;
                }
                else {
                    printf("La pièce doit appartenir au joueur courant !\n") ;
                }
            }

        }
        else {
            printf("La case d'arrivée est hors du plateau !\n") ;
        }
    }
    else {
        printf("La case de départ est hors du plateau !\n") ;
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
