#ifndef MIN_MAX_H_INCLUDED
#define MIN_MAX_H_INCLUDED
#include "arbres.h"
#include "plateau.h"

Plateau* min_max(Plateau *p, int profondeur, Joueur joueur) ;
Arbre* initialiser_arbre_coups(Arbre* a, Plateau* p, int pieces[], Joueur joueur) ;
Plateau* copy_to(Plateau* p, Plateau* p_copy) ;
int mini(Plateau* p, Arbre* a, Joueur joueur, int profondeur) ;
int maxi(Plateau* p, Arbre* a, Joueur joueur, int profondeur) ;
int pieces_joueur(int pieces[], Plateau *p, Joueur joueur) ;

#endif // MIN_MAX_H_INCLUDED
