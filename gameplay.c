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

    for( k = 0 ; k < 81 ; k++){
        p->cases[k] = VIDE ;
    }

    for (k = 0 ; k < 18 ; k++) {
        p->cases[k] = NOIR ;
    }

    for (k = 80 ; k > 62 ; k--) {
        p->cases[k] = BLANC ;
    }
}


void deplacer_piece(Plateau* p, Joueur j, int debut, int fin) { //déplace une pièce depuis la position debut, jusqu'à la position fin

    if (coup_legal(p, j, debut, fin)) {
            Case piece = (*p).cases[debut] ;
            p->cases[debut] = VIDE ;
            p->cases[fin] = piece ;
    }
}


int coup_legal(Plateau* p, Joueur j, int debut, int fin) {

    int booleen = 0 ; //booléen déterminant si le coup est légal ou non
    Case case_depart = (*p).cases[debut] ;
    Case case_arrivee = (*p).cases[fin] ;

    if (debut>=0 && debut<81) { //la case de départ doit être sur le plateau

        if (fin>=0 && fin<81) { //la case d'arrivée doit être sur le plateau

            if (j+1 == case_depart) { //la pièce doit appartenir au joueur courant

                if (debut != fin) { //les cases de départ et d'arrivée doivent être différentes

                    if (debut/9 == fin/9) { //déplacement horizontal

                        if (fin>debut) { //déplacement de gauche à droite
                            int temp = debut+1 ;

                            while ((*p).cases[temp]==VIDE && temp!=fin) {
                            temp++ ;
                            }

                            //la case d'arrivée doit être vide, et il ne doit pas y avoir de pièce
                            //sur le chemin du déplacement, sauf la case précédent la case d'arrivée
                            booleen = (fin-temp < 2) && (case_arrivee == VIDE) ;
                        }

                        else {
                            int temp = debut-1 ;

                            while ((*p).cases[temp]==VIDE && temp!=fin) {
                            temp-- ;
                            }

                            //la case d'arrivée doit être vide, et il ne doit pas y avoir de pièce
                            //sur le chemin du déplacement, sauf la case précédent la case d'arrivée
                            booleen = (temp-fin < 2) && (case_arrivee == VIDE) ;
                        }
                    }

                    if ((fin-debut)%9 == 0) { //déplacement vertical

                        if (fin>debut) {

                            int temp = debut+9 ;

                            while ((*p).cases[temp]==VIDE && temp!=fin) {
                                temp+=9 ;
                            }

                            //la case d'arrivée doit être vide, et il ne doit pas y avoir de pièce
                            //sur le chemin du déplacement, sauf la case précédent la case d'arrivée
                            booleen = ((temp == fin) || (temp == fin-9)) && (case_arrivee == VIDE) ;

                        }
                        else {
                            int temp = debut-9 ;

                            while ((*p).cases[temp]==VIDE && temp!=fin) {
                                temp-=9 ;
                            }

                            //la case d'arrivée doit être vide, et il ne doit pas y avoir de pièce
                            //sur le chemin du déplacement, sauf la case précédent la case d'arrivée
                            booleen = ((temp == fin) || (temp == fin+9)) && (case_arrivee == VIDE) ;
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

    Plateau plateau ;

    initialiser_plateau(&plateau) ;

    deplacer_piece(&plateau, JOUEUR_NOIR, 0, 19) ;

    deplacer_piece(&plateau, JOUEUR_NOIR, 9, 27) ;

    deplacer_piece(&plateau, JOUEUR_BLANC, 17, 26) ;

    int k ;
    int zeros = 0 ;

    for (k = 0 ; k < 81 ; k++) {
;
        printf("%d\n",plateau.cases[k]) ;

        if (plateau.cases[k]==VIDE){
            zeros++ ;
        }
    }

    return zeros ;
}
