#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "min_max.h"
#include "arbres.h"
#include "plateau.h"


int main(int argc, char *argv[]){

    Joueur joueur_courant = BLANC ;
    Plateau plateau ;
    initialiser_plateau(&plateau) ;
    int pieces[18] ;

    pieces_joueur(pieces, &plateau, joueur_courant) ;

    int k ;

    for (k = 0 ; k < 18 ; k++) {
        printf("%d\n",pieces[k]) ;
    }

    Coup coup = {0,18} ;

    Arbre I = {coup, 9, NULL, NULL};
    Arbre H = {coup, 8, &I, NULL};
    Arbre G = {coup, 7, &H, NULL};
    Arbre F = {coup, 6, NULL, &G};
    Arbre E = {coup, 5, NULL, NULL};
    Arbre D = {coup, 4, &E, NULL};
    Arbre C = {coup, 3, NULL, &F};
    Arbre B = {coup, 2, &C, &D};
    Arbre A = {coup, 1, NULL, &B};

    Arbre* a = &A ;
    Arbre* d = &D ;

    afficher(a) ;

    int z ;
    for (z=0 ; z<2 ; z++) {
        d = ajouter_fils(d, coup, z+10) ;
    }

    afficher(a) ;

    printf("%d\n",hauteur(&A)) ;
    printf("%d\n",taille(&A)) ;

    printf("Arbre : %d octets\n", sizeof(Arbre));

    Plateau* p = min_max(&plateau, 2, joueur_courant) ;

    return 100 ;
}
