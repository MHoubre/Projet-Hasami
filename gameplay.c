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


void deplacer_piece(Plateau* p, Joueur j, int debut, int fin) { //d�place une pi�ce depuis la position debut, jusqu'� la position fin

    if (coup_legal(p, j, debut, fin)) {
            Case piece = (*p).cases[debut] ;
            p->cases[debut] = VIDE ;
            p->cases[fin] = piece ;
    }
}


int coup_legal(Plateau* p, Joueur j, int debut, int fin) {

    int booleen = 0 ; //bool�en d�terminant si le coup est l�gal ou non
    Case case_depart = (*p).cases[debut] ;
    Case case_arrivee = (*p).cases[fin] ;

    if (debut>=0 && debut<81) { //la case de d�part doit �tre sur le plateau

        if (fin>=0 && fin<81) { //la case d'arriv�e doit �tre sur le plateau

            if (j+1 == case_depart) { //la pi�ce doit appartenir au joueur courant

                if (debut != fin) { //les cases de d�part et d'arriv�e doivent �tre diff�rentes

                    if (debut/9 == fin/9) { //d�placement horizontal

                        if (fin>debut) { //d�placement de gauche � droite
                            int temp = debut+1 ;

                            while ((*p).cases[temp]==VIDE && temp!=fin) {
                            temp++ ;
                            }

                            //la case d'arriv�e doit �tre vide, et il ne doit pas y avoir de pi�ce
                            //sur le chemin du d�placement, sauf la case pr�c�dent la case d'arriv�e
                            booleen = (fin-temp < 2) && (case_arrivee == VIDE) ;
                        }

                        else {
                            int temp = debut-1 ;

                            while ((*p).cases[temp]==VIDE && temp!=fin) {
                            temp-- ;
                            }

                            //la case d'arriv�e doit �tre vide, et il ne doit pas y avoir de pi�ce
                            //sur le chemin du d�placement, sauf la case pr�c�dent la case d'arriv�e
                            booleen = (temp-fin < 2) && (case_arrivee == VIDE) ;
                        }
                    }

                    if ((fin-debut)%9 == 0) { //d�placement vertical

                        if (fin>debut) {

                            int temp = debut+9 ;

                            while ((*p).cases[temp]==VIDE && temp!=fin) {
                                temp+=9 ;
                            }

                            //la case d'arriv�e doit �tre vide, et il ne doit pas y avoir de pi�ce
                            //sur le chemin du d�placement, sauf la case pr�c�dent la case d'arriv�e
                            booleen = ((temp == fin) || (temp == fin-9)) && (case_arrivee == VIDE) ;

                        }
                        else {
                            int temp = debut-9 ;

                            while ((*p).cases[temp]==VIDE && temp!=fin) {
                                temp-=9 ;
                            }

                            //la case d'arriv�e doit �tre vide, et il ne doit pas y avoir de pi�ce
                            //sur le chemin du d�placement, sauf la case pr�c�dent la case d'arriv�e
                            booleen = ((temp == fin) || (temp == fin+9)) && (case_arrivee == VIDE) ;
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
