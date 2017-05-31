#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED
#define NbPions 36

typedef enum Joueur {
    JOUEUR_BLANC, JOUEUR_NOIR
} Joueur ;

typedef enum Case {
    VIDE, BLANC, NOIR
} Case ;

typedef struct Plateau {
    Case cases[81] ;
}Plateau ;


void initialiser_plateau(Plateau* p) ;
Plateau* deplacer_piece(Plateau* p, Joueur j, int depart, int arrivee) ;
void free_Plateau(Plateau* p);
int dessiner(Plateau* p, SDL_Surface* ecran, SDL_Surface* pions[NbPions], SDL_Rect positionsPions[NbPions]);
int coup_legal(Plateau* p, Joueur j, int depart, int arrivee) ;
Plateau* manger(Plateau* p, Joueur j, int depart, int arrivee) ;
int gagnant(Plateau* p) ;
Plateau* copy_to(Plateau* p, Plateau* p_copy) ;
int evaluer (Plateau* p, Joueur j);
int nombreDePions(Plateau* p, Joueur j);
int evaluerMateriel(Plateau *p, Joueur j);
int evaluerMobilite(Plateau* p, Joueur joueur);
int evaluerLigne(Plateau *p, Joueur j);
int diagonale_droite_blanc(Plateau *p, int depart);
int diagonale_gauche_blanc(Plateau *p, int depart);
int diagonale_droite_noir(Plateau *p, int depart);
int diagonale_gauche_noir(Plateau *p, int depart);
int verticale_blanc(Plateau *p, int depart);
int verticale_noir(Plateau *p, int depart);
int evaluerDominationTerritoire(Plateau* p, Joueur joueur);




#endif // PLATEAU_H_INCLUDED
