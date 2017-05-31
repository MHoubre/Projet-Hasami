#include <math.h>
#ifndef PLATEAU_C_INCLUDED
#define PLATEAU_C_INCLUDED
#define Xplateau 25
#define Yplateau 75
#define TailleCase 100
#define TailleMatrice 81
#define NbPions 36
#define TailleLigne 9
#define NbLignes 8
#define NbPions  36
#define UneLigne 9
#define DeuxLignes 18
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_image.h>
#include "plateau.h"



void initialiser_plateau(Plateau* p) {

    int k ;

    for (k = 0 ; k < 18 ; k++) {
        p->cases[k] = NOIR ;
    }

    for( k = 18 ; k < 63 ; k++){
        p->cases[k] = VIDE ;
    }

    for (k = 63 ; k < 81 ; k++) {
        p->cases[k] = BLANC ;
    }
}


Plateau* deplacer_piece(Plateau* p, Joueur j, int depart, int arrivee) { //déplace une pièce depuis la position depart, jusqu'à la position arrivee

    if (coup_legal(p, j, depart, arrivee)) {
            //on déplace la pièce
            Case piece = (*p).cases[depart] ;
            p->cases[depart] = VIDE ;
            p->cases[arrivee] = piece ;

            //on "mange" les pièces qu'il faut
            return manger(p, j, depart, arrivee) ;
    }

    else {
        return p ;
    }
}



void free_Plateau(Plateau* p){
	int i;	

	for (i=0;i<TailleMatrice;i++){
		free(&(p->cases[i]));
	}
}


int dessiner(Plateau* p, SDL_Surface* ecran, SDL_Surface* pions[NbPions], SDL_Rect positionsPions[NbPions]){

	int i=0;

	int compteur=0;	//constante qui servira pour la recherche des coeff du plateau et le tracé des pions.


	for(i=0;i<81;i++){

		if(p->cases[i]==NOIR){
			pions[compteur]=IMG_Load("noire_transparent.png");
			positionsPions[compteur].x=((i%9)*100)+Xplateau+5;
			positionsPions[compteur].y=((i/9)*100)+Yplateau+5;
			compteur++;
//			printf("%d\n",compteur);
		}

		if(p->cases[i]==BLANC){
			pions[compteur]=IMG_Load("blanche_transparent.png");
			positionsPions[compteur].x=((i%9)*100)+Xplateau+5;
			positionsPions[compteur].y=((i/9)*100)+Yplateau+5;
			compteur++;
//			printf("%d\n",compteur);
		}

	}


}





int coup_legal(Plateau* p, Joueur j, int depart, int arrivee) {

    int booleen = 0 ; //booléen déterminant si le coup est légal ou non
    Case case_depart = (*p).cases[depart] ;
    Case case_arrivee = (*p).cases[arrivee] ;

    if (depart>=0 && depart<81) { //la case de départ doit être sur le plateau

        if (arrivee>=0 && arrivee<81) { //la case d'arrivée doit être sur le plateau

            if (j+1 == case_depart) { //la pièce doit appartenir au joueur courant

                if (depart != arrivee) { //les cases de départ et d'arrivée doivent être différentes

                    if (depart/9 == arrivee/9) { //déplacement horizontal

                        if (arrivee>depart) { //déplacement de gauche à droite
                            int temp = depart+1 ;

                            while ((*p).cases[temp]==VIDE && temp!=arrivee) {
                            temp++ ;
                            }

                            //la case d'arrivée doit être vide, et il ne doit pas y avoir de pièce
                            //sur le chemin du déplacement, sauf la case précédent la case d'arrivée
                            booleen = (arrivee-temp < 2) && (case_arrivee == VIDE) ;
                        }

                        else {
                            int temp = depart-1 ;

                            while ((*p).cases[temp]==VIDE && temp!=arrivee) {
                            temp-- ;
                            }

                            //la case d'arrivée doit être vide, et il ne doit pas y avoir de pièce
                            //sur le chemin du déplacement, sauf la case précédent la case d'arrivée
                            booleen = (temp-arrivee < 2) && (case_arrivee == VIDE) ;
                        }
                    }

                    if ((arrivee-depart)%9 == 0) { //déplacement vertical

                        if (arrivee>depart) {

                            int temp = depart+9 ;

                            while ((*p).cases[temp]==VIDE && temp!=arrivee) {
                                temp+=9 ;
                            }

                            //la case d'arrivée doit être vide, et il ne doit pas y avoir de pièce
                            //sur le chemin du déplacement, sauf la case précédent la case d'arrivée
                            booleen = ((temp == arrivee) || (temp == arrivee-9)) && (case_arrivee == VIDE) ;

                        }
                        else {
                            int temp = depart-9 ;

                            while ((*p).cases[temp]==VIDE && temp!=arrivee) {
                                temp-=9 ;
                            }

                            //la case d'arrivée doit être vide, et il ne doit pas y avoir de pièce
                            //sur le chemin du déplacement, sauf la case précédent la case d'arrivée
                            booleen = ((temp == arrivee) || (temp == arrivee+9)) && (case_arrivee == VIDE) ;
                        }

                    }

                    else {
                        //printf("Déplacement non autorisé.\n") ;
                    }

                }
                else {
                    //printf("Les cases de départ et d'arrivée doivent être différentes.\n") ;
                }

            }
            else {
                if (case_depart == VIDE) {
                    //printf("La case sélectionnée est vide.\n") ;
                }
                else {
                    //printf("La pièce doit appartenir au joueur courant !\n") ;
                }
            }

        }
        else {
            //printf("La case d'arrivée est hors du plateau !\n") ;
        }
    }
    else {
        //printf("La case de départ est hors du plateau !\n") ;
    }

    return booleen ;
}


Plateau* manger(Plateau* p, Joueur joueur, int depart, int arrivee) {

    //le déplacement est-il en lignes ?
    if (depart%9 == arrivee%9) {
        //le déplacement est-il de haut en bas ?
        if (arrivee > depart) {
            //on teste s'il y a une pièce du joueur adverse en bas
            if (arrivee+18<81 && (*p).cases[arrivee+9]==((joueur+1)%2)+1) {
                int i = arrivee+18 ;
                //tant qu'on a des pièces du joueur adverse alignées, on continue
                while (i<81 && (*p).cases[i]==((joueur+1)%2)+1) {
                    i+=9 ;
                }
                //si lorsqu'on s'arrête on est sur une case contenant un pion
                //du joueur courant, alors on mange la ligne de pion adverse
                if (i<81 && (*p).cases[i]==joueur+1){
                    int k ;
                    for (k = arrivee+9 ; k<i ; k+=9) {
                        (*p).cases[k]=VIDE ;
                    }
                }
            }
        }
        //sinon, le déplacement est de bas en haut
        else {
            //on teste s'il y a une pièce du joueur adverse en haut
            if (arrivee-18>0 && (*p).cases[arrivee-9]==((joueur+1)%2)+1) {
                int i = arrivee-18 ;
                //tant qu'on a des pièces du joueur adverse alignées, on continue
                while (i>0 && (*p).cases[i]==((joueur+1)%2)+1) {
                    i-=9 ;
                }
                //si lorsqu'on s'arrête on est sur une case contenant un pion
                //du joueur courant, alors on mange la ligne de pion adverse
                if (i>0 && (*p).cases[i]==joueur+1){
                    int k ;
                    for (k = arrivee-9 ; k>i ; k-=9) {
                        (*p).cases[k]=VIDE ;
                    }
                }
            }
        }

        //il y a-t-il une pièce adverse à droite ?
        if (arrivee%9<7 && (*p).cases[arrivee+1]==((joueur+1)%2)+1) {
            int j = arrivee+1 ;
            //tant qu'il y a des pièces du joueur adverse alignées, on continue
            while (j%9!=8 && (*p).cases[j]==((joueur+1)%2)+1) {
                j++ ;
            }
            //si lorsqu'on s'arrête on est sur une case contenant un pion
            //du joueur courant, alors on mange la ligne de pion adverse
            if (j%9!=8 && (*p).cases[j]==joueur+1){
                int k ;
                for (k = arrivee+1 ; k<j ; k++) {
                    (*p).cases[k]=VIDE ;
                }
            }
        }

        //il y a-t-il une pièce adverse à droite ?
        if (arrivee%9>1 && (*p).cases[arrivee-1]==((joueur+1)%2)+1) {
            int j = arrivee-1 ;
            //tant qu'il y a des pièces du joueur adverse alignées, on continue
            while (j%9!=0 && (*p).cases[j]==((joueur+1)%2)+1) {
                j-- ;
            }
            //si lorsqu'on s'arrête on est sur une case contenant un pion
            //du joueur courant, alors on mange la ligne de pion adverse
            if (j%9!=0 && (*p).cases[j]==joueur+1){
                int k ;
                for (k = arrivee-1 ; k>j ; k--) {
                    (*p).cases[k]=VIDE ;
                }
            }
        }
    }

    //sinon le déplacement est en colonnes
    else {
        //le déplacement est-il de gauche à droite ?
        if (arrivee > depart) {
            //on teste s'il y a une pièce du joueur adverse à droite
            if (arrivee%9<7 && (*p).cases[arrivee+1]==((joueur+1)%2)+1) {
                int j = arrivee+1 ;
                //tant qu'on a des pièces du joueur adverse alignées, on continue
                while (j%9!=8 && (*p).cases[j]==((joueur+1)%2)+1) {
                    j++ ;
                }
                //si lorsqu'on s'arrête on est sur une case contenant un pion
                //du joueur courant, alors on mange la ligne de pion adverse
                if (j%9!=8 && (*p).cases[j]==joueur+1){
                    int k ;
                    for (k = arrivee+1 ; k<j ; k++) {
                        (*p).cases[k]=VIDE ;
                    }
                }
            }
        }
        //sinon, le déplacement est de droite à gauche
        else {
            //on teste s'il y a une pièce du joueur adverse à gauche
            if (arrivee%9>1 && (*p).cases[arrivee-1]==((joueur+1)%2)+1) {
                int j = arrivee-1 ;
                //tant qu'on a des pièces du joueur adverse alignées, on continue
                while (j%9!=0 && (*p).cases[j]==((joueur+1)%2)+1) {
                    j-- ;
                }
                //si lorsqu'on s'arrête on est sur une case contenant un pion
                //du joueur courant, alors on mange la ligne de pion adverse
                if (j%9!=0 && (*p).cases[j]==joueur+1){
                    int k ;
                    for (k = arrivee-1 ; k>j ; k--) {
                        (*p).cases[k]=VIDE ;
                    }
                }
            }
        }

        //il y a-t-il une pièce adverse en bas ?
        if (arrivee+18<81 && (*p).cases[arrivee+9]==((joueur+1)%2)+1) {
            int i = arrivee+9 ;
            //tant qu'il y a des pièces du joueur adverse alignées, on continue
            while (i<81 && (*p).cases[i]==((joueur+1)%2)+1) {
                i+=9 ;
            }
            //si lorsqu'on s'arrête on est sur une case contenant un pion
            //du joueur courant, alors on mange la ligne de pion adverse
            if (i<81 && (*p).cases[i]==joueur+1){
                int k ;
                for (k = arrivee+9 ; k<i ; k+=9) {
                    (*p).cases[k]=VIDE ;
                }
            }
        }

        //il y a-t-il une pièce adverse en haut ?
        if (arrivee-18>0 && (*p).cases[arrivee-9]==((joueur+1)%2)+1) {
            int i = arrivee-9 ;
            //tant qu'il y a des pièces du joueur adverse alignées, on continue
            while (i>0 && (*p).cases[i]==((joueur+1)%2)+1) {
                i-=9 ;
            }
            //si lorsqu'on s'arrête on est sur une case contenant un pion
            //du joueur courant, alors on mange la ligne de pion adverse
            if (i>0 && (*p).cases[i]==joueur+1){
                int k ;
                for (k = arrivee-9 ; k>i ; k-=9) {
                    (*p).cases[k]=VIDE ;
                }
            }
        }
    }

    return p ;

}


void pause(SDL_Surface* ecran, SDL_Surface* image){
    int continuer_fin = 1;
    SDL_Event event_fin;
 
    while (continuer_fin)
    {
        SDL_WaitEvent(&event_fin);
        switch(event_fin.type)
        {
            case SDL_QUIT:


                continuer_fin = 0;
        }
    }

				SDL_FreeSurface(ecran);
				SDL_FreeSurface(image);

	SDL_Quit();	

}


//on renvoie -1 s'il n'y a pas de gagnant, sinon l'entier correspondant
//au joueur qui gagne la partie
int gagnant(Plateau* p) {

	SDL_Surface *ecranFin=NULL;
	SDL_Surface *imageFin=NULL;

	SDL_Rect position;
	
	position.x=0;
	position.y=0;

    //si le joueur blanc a 1 ou 0 pion, il a perdu
    int nb_blanc = nombreDePions(p, JOUEUR_BLANC) ;
    if (nb_blanc<2) {
			
		ecranFin= SDL_SetVideoMode(500, 250, 32, SDL_HWSURFACE); 
		imageFin=IMG_Load("zen_N.png");

		SDL_BlitSurface(imageFin,NULL,ecranFin,&position);

		SDL_Flip(ecranFin);

		pause(ecranFin,imageFin);

        return JOUEUR_NOIR ;
    }

    else {
        //si le joueur noir a 1 ou 0 pion, il a perdu
        int nb_noir = nombreDePions(p, JOUEUR_NOIR) ;
        if (nb_noir<2) {
			
			ecranFin= SDL_SetVideoMode(500, 250, 32, SDL_HWSURFACE); 
			imageFin=IMG_Load("zen_B.png");

			SDL_BlitSurface(imageFin,NULL,ecranFin,&position);

			SDL_Flip(ecranFin);

			pause(ecranFin,imageFin);

            return JOUEUR_BLANC ;
        }

        //sinon, on cherche une ligne ou diagonale gagnante
        else {
            int k = 0 ;
            int ddb, dgb, vb, ddn, dgn, vn ;

            int gagnant_blanc = 0 ;
            int gagnant_noir = 0 ;

            while(k<81 && gagnant_blanc==gagnant_noir) {
                ddb = diagonale_droite_blanc(p, k) ;
                dgb = diagonale_gauche_blanc(p, k) ;
                vb = verticale_blanc(p, k) ;
                ddn = diagonale_droite_noir(p, k) ;
                dgn = diagonale_gauche_noir(p, k) ;
                vn = verticale_noir(p, k) ;

                if (ddb>4 || dgb>4 || vb>4) {
                    gagnant_blanc = 1 ;
                }
                else {
                    if (ddn>4 || dgn>4 || vn>4) {
                        gagnant_noir = 1 ;
                    }
                }

                k++ ;
            }

            if (gagnant_blanc==1) {

			ecranFin= SDL_SetVideoMode(500, 250, 32, SDL_HWSURFACE); 
			imageFin=IMG_Load("zen_B.png");

			SDL_BlitSurface(imageFin,NULL,ecranFin,&position);
	
			SDL_Flip(ecranFin);

			pause(ecranFin, imageFin);


                return JOUEUR_BLANC ;
            }
            else {
                if (gagnant_noir==1) {

			ecranFin= SDL_SetVideoMode(500, 250, 32, SDL_HWSURFACE); 
			imageFin=IMG_Load("zen_N.png");

			SDL_BlitSurface(imageFin,NULL,ecranFin,&position);
	
			SDL_Flip(ecranFin);

			pause(ecranFin, imageFin);

                    return JOUEUR_NOIR ;
                }
                else {
                    return -1 ;
                }
            }
        }
    }
}


//on copie un plateau dans un autre
Plateau* copy_to(Plateau* p, Plateau* p_copy) {
    int k ;
    for (k=0 ; k<81 ; k++) {
        p_copy->cases[k] = (*p).cases[k] ;
    }
    return p_copy ;
}


//Fonction d'evaluation finale
int evaluer (Plateau* p, Joueur j){

    int eval = 0 ;
    int nbB = nombreDePions(p, JOUEUR_BLANC);
    int nbN = nombreDePions(p, JOUEUR_NOIR);

    int coef1;
    int coef2;
    int coef3;
    int coef4;

    if (nbB > 12 && nbN > 12 ){
        coef1 = 150;
        coef2 = 3;
        coef3 = 60;
        coef4 = 300;
    } else if (nbB > 5 && nbN > 5 ){
        coef1 = 225;
        coef2 = 1;
        coef3 = 90;
        coef4 = 150;
    } else {
        coef1 = 300;
        coef2 = 1;
        if (nbB < 5 && nbN < 5){
           coef3 = 0;
        }else {
            coef3 = 90;
        }
        coef4 = 225;
    }

    eval += coef1* evaluerMateriel(p, j);
    eval += coef2* evaluerMobilite(p, j);
    eval += coef3* evaluerLigne(p,j);
    eval += coef4* evaluerDominationTerritoire(p,j);

    return eval;

}

// Calcule le nombre de pions de chaque jiueur sur le plateau

int nombreDePions(Plateau* p, Joueur j)
{
    int nbPions = 0; //Compteur des pions
    int i;

    for(i=0; i<81; i++){
            if ((*p).cases[i] == j+1){
                nbPions++ ;
            }
    }

    return nbPions ;
}



//Evaluation dU Materiel consiste à faire la différence entre le nombre de pions que possède chaque joueur

int evaluerMateriel(Plateau *p, Joueur j) {

    int nb1, nb2;

    nb1 = nombreDePions(p, j) ;
    nb2 = nombreDePions(p, (j+1)%2) ;

    return nb1-nb2 ;
}



/* Evaluation des possibilités de déplacement de chaque joueur
Parcourir les pions du joueur pion par pion et Calculer le nombre de déplacements que peut faire chaque pion
Affecter la diffrérence entre les deplacements des pions des deux joueurs à evaluateMobility */


int evaluerMobilite(Plateau* p, Joueur joueur) {

    int mob1 = 0 ;
    int mob2 = 0 ;

    int depart ;
    int arrivee ;
    Case c ;

    //Premier indice de la ligne
    int i ;
    //Premier indice de la colonne
    int j ;
    int k ;

    for(depart=0 ; depart<81 ; depart++) {

        c = (*p).cases[depart] ;

        if (c!=VIDE) {

            i = (depart/9)*9 ;
            j = depart%9 ;

            //tests sur la ligne
            for(k=0 ; k<9 ; k++) {
                arrivee = i+k ;
                if (c-1==joueur && coup_legal(p, joueur, depart, arrivee)) {
                    mob1++ ;
                }
                else {
                    if (coup_legal(p, (joueur+1)%2, depart, arrivee)) {
                        mob2++ ;
                    }
                }
            }

            //test sur la colonne
            for(k=0 ; k<9 ; k++) {
                arrivee = j+k*9 ;
                if (c-1==joueur && coup_legal(p, joueur, depart, arrivee)) {
                    mob1++ ;
                }
                else {
                    if (coup_legal(p, (joueur+1)%2, depart, arrivee)) {
                        mob2++ ;
                    }
                }
            }
        }
    }

    return mob1-mob2 ;
}


/*evaluer la chance de gain par alignement des pions.
Si le pion n'a jamais déplacé alors retourne 0
si deux cases successives verticalement ou diagonalement sont de mm couleur et que les 3 suivantes sont vides on attribue 2^2
si 3 cases successives verticalement ou diagonalement sont de mm couleur et que les 2 suivantes sont vides on attribue 3^2
si 4 cases successives verticalement ou diagonalement sont de mm couleur et que les 1 suivantes est vide on attribue 4^2 */

int evaluerLigne(Plateau *p, Joueur j){

    int scoreB = 0 ;
    int scoreN = 0 ;
    int depart ;

    int ddb, dgb, vb, ddn, dgn, vn ;

    for (depart=0 ; depart<81 ; depart++) {
        ddb = diagonale_droite_blanc(p, depart) ;
        dgb = diagonale_gauche_blanc(p, depart) ;
        vb = verticale_blanc(p, depart) ;
        ddn = diagonale_droite_noir(p, depart) ;
        dgn = diagonale_gauche_noir(p, depart) ;
        vn = verticale_noir(p, depart) ;
        if (ddb>1) {
            scoreB += ddb ;
        }
        if (dgb>1) {
            scoreB += dgb ;
        }
        if (vb>1) {
            scoreB += vb ;
        }
        if (ddn>1) {
            scoreN += ddn ;
        }
        if (dgn>1) {
            scoreN += dgn ;
        }
        if (vn>1) {
            scoreN += vn ;
        }
    }

    if (j == JOUEUR_BLANC) {
        return scoreB-scoreN ;
    }
    else {
        return scoreN-scoreB ;
    }
}

//diagonale droite pour les blancs
int diagonale_droite_blanc(Plateau *p, int depart) {

    int k = depart ;
    int longueur = 0 ;

    while (k<63 && k%9<8 && (*p).cases[k]==BLANC) {
        k+=10 ;
        longueur++ ;
    }

    if (k%9==8 && (*p).cases[k]==BLANC) {
        longueur++ ;
    }

    return longueur ;
}

//diagonale gauche pour les blancs
int diagonale_gauche_blanc(Plateau *p, int depart) {

    int k = depart ;
    int longueur = 0 ;

    while (k<63 && k%9>0 && (*p).cases[k]==BLANC) {
        k+=8 ;
        longueur++ ;
    }

    if (k%9==0 && (*p).cases[k]==BLANC) {
        longueur++ ;
    }

    return longueur ;
}

//diagonale droite pour les noirs
int diagonale_droite_noir(Plateau *p, int depart) {

    int k = depart ;
    int longueur = 0 ;

    while (k>17 && k<81 && k%9<8 && (*p).cases[k]==NOIR) {
        k+=10 ;
        longueur++ ;
    }

    if (k%9==8 && (*p).cases[k]==NOIR) {
        longueur++ ;
    }

    return longueur ;
}

//diagonale gauche pour les noirs
int diagonale_gauche_noir(Plateau *p, int depart) {

    int k = depart ;
    int longueur = 0 ;

    while (k>17 && k<81 && k%9>0 && (*p).cases[k]==NOIR) {
        k+=8 ;
        longueur++ ;
    }

    if (k%9==0 && (*p).cases[k]==NOIR) {
        longueur++ ;
    }

    return longueur ;
}

//ligne verticale pour les blancs
int verticale_blanc(Plateau *p, int depart) {

    int k = depart ;
    int longueur = 0 ;

    while (k<63 && (*p).cases[k]==BLANC) {
        k+=9 ;
        longueur++ ;
    }

    return longueur ;
}

//ligne verticale pour les noirs
int verticale_noir(Plateau *p, int depart) {

    int k = depart ;
    int longueur = 0 ;

    while (k>17 && k<81 && (*p).cases[k]==NOIR) {
        k+=9 ;
        longueur++ ;
    }

    return longueur ;
}


/*Domination du territoire*/

int evaluerDominationTerritoire(Plateau* p, Joueur joueur) {

    int zonesB = 0 ;
    int zonesN = 0 ;
    int k ;

    int nbB = 0 ;
    int nbN = 0 ;

    //On regarde la zone de départ des noirs
    for (k=0 ; k<18 ; k++) {
        if ((*p).cases[k]==BLANC) {
            nbB++ ;
        }
        else {
            if ((*p).cases[k]==NOIR) {
                nbN++ ;
            }
        }
    }

    if (nbB>nbN) {
        zonesB++ ;
    }
    else {
        if (nbN>nbB) {
            zonesN++ ;
        }
    }

    //On regarde la zone de départ des blancs
    nbB = 0 ;
    nbN = 0 ;

    for (k=63 ; k<81 ; k++) {
        if ((*p).cases[k]==BLANC) {
            nbB++ ;
        }
        else {
            if ((*p).cases[k]==NOIR) {
                nbN++ ;
            }
        }
    }

    if (nbB>nbN) {
        zonesB++ ;
    }
    else {
        if (nbN>nbB) {
            zonesN++ ;
        }
    }

    //on regarde la zone du centre gauche
    //c'est-à-dire la sous-matrice contenant
    //les lignes 2 à 6 et les colonnes 0 à 2
    int i ;
    int j ;

    nbB = 0 ;
    nbN = 0 ;

    for (i=2 ; i<7 ; i++) {
        for (j=0 ; j<3 ; j++) {
            if ((*p).cases[i*9+j]==BLANC) {
                nbB++ ;
            }
            else {
                if ((*p).cases[i*9+j]==NOIR) {
                    nbN++ ;
                }
            }
        }
    }

    if (nbB>nbN) {
        zonesB++ ;
    }
    else {
        if (nbN>nbB) {
            zonesN++ ;
        }
    }

    //on regarde la zone du centre centre
    //c'est-à-dire la sous-matrice contenant
    //les lignes 2 à 6 et les colonnes 3 à 5
    nbB = 0 ;
    nbN = 0 ;

    for (i=2 ; i<7 ; i++) {
        for (j=3 ; j<6 ; j++) {
            if ((*p).cases[i*9+j]==BLANC) {
                nbB++ ;
            }
            else {
                if ((*p).cases[i*9+j]==NOIR) {
                    nbN++ ;
                }
            }
        }
    }

    if (nbB>nbN) {
        zonesB++ ;
    }
    else {
        if (nbN>nbB) {
            zonesN++ ;
        }
    }

    //on regarde la zone du centre centre
    //c'est-à-dire la sous-matrice contenant
    //les lignes 2 à 6 et les colonnes 6 à 8
    nbB = 0 ;
    nbN = 0 ;

    for (i=2 ; i<7 ; i++) {
        for (j=6 ; j<9 ; j++) {
            if ((*p).cases[i*9+j]==BLANC) {
                nbB++ ;
            }
            else {
                if ((*p).cases[i*9+j]==NOIR) {
                    nbN++ ;
                }
            }
        }
    }

    if (nbB>nbN) {
        zonesB++ ;
    }
    else {
        if (nbN>nbB) {
            zonesN++ ;
        }
    }

    //on renvoie le résultat
    if (joueur == JOUEUR_BLANC) {
        return zonesB-zonesN ;
    }
    else {
        return zonesN-zonesB ;
    }


}


#endif // FONCTION_EVALUATION_C_INCLUDED
