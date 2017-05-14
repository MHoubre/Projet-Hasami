#ifndef MIN_MAX_H_INCLUDED
#define MIN_MAX_H_INCLUDED
#include "arbres.h"
#include "plateau.h"

Arbre* initialiser_arbre_coups(Arbre* a, Plateau* p, int pieces[], Joueur joueur) ;
Plateau* copy_to(Plateau* p, Plateau* p_copy) ;
int mini(Plateau* p, Arbre* a, Joueur joueur, int profondeur) ;
int gagnant(Plateau* p) ;

#endif // MIN_MAX_H_INCLUDED
