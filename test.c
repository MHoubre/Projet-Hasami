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
