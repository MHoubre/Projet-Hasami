#ifndef FONCTION_EVALUATION_H_INCLUDED
#define FONCTION_EVALUATION_H_INCLUDED

int evaluer(Plateau * p, Joueur j);
int nombreDePions(Plateau* p, Joueur j);
int evaluerMateriel(Plateau *p, Joueur j);
int evaluerMobilite(Plateau* p, Joueur j);
int evaluerLigne(Plateau* p, Joueur j);
int evaluerDominationTerritoire(Plateau* p, Joueur j);

#endif // FONCTION_EVALUATION_H_INCLUDED
