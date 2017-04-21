#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

typedef enum Joueur {
    JOUEUR_BLANC, JOUEUR_NOIR
} Joueur ;

typedef enum Case {
    VIDE, BLANC, NOIR
} Case ;

typedef struct Plateau {
    Case cases[81] ;
}Plateau ;


Plateau* manger(Plateau* p, Joueur j, int depart, int arrivee) ;
void initialiser_plateau(Plateau* p) ;
Plateau* deplacer_piece(Plateau* p, Joueur j, int depart, int arrivee) ;
int coup_legal(Plateau* p, Joueur j, int depart, int arrivee) ;

#endif // PLATEAU_H_INCLUDED
