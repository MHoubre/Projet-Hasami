#ifndef FONCTION_EVALUATION_H_INCLUDED
#define FONCTION_EVALUATION_H_INCLUDED

int evaluer(Plateau * p, Joueur j);
int nombreDePions(Plateau* p, Joueur j);
int evaluerMateriel(Plateau *p, Joueur j);
int evaluerMobilite(Plateau* p, Joueur j);
int evaluerLigne(Plateau* p, Joueur j);
int evaluerDominationTerritoire(Plateau* p, Joueur j);

int diagonale_droite_blanc(Plateau *p, int depart) ;
int diagonale_gauche_blanc(Plateau *p, int depart) ;
int diagonale_droite_noir(Plateau *p, int depart) ;
int diagonale_gauche_noir(Plateau *p, int depart) ;
int verticale_blanc(Plateau *p, int depart) ;
int verticale_noir(Plateau *p, int depart) ;

#endif // FONCTION_EVALUATION_H_INCLUDED
