#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
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

void free_Plateau(Plateau* p){
	int i;	

	for (i=0;i<TailleMatrice;i++){
		free(&(p->cases[i]));
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
                        printf("Déplacement non autorisé.\n") ;
                    }

                }
                else {
                    printf("Les cases de départ et d'arrivée doivent être différentes.\n") ;
                }

            }
            else {
                if (case_depart == VIDE) {
                    printf("La case sélectionnée est vide.\n") ;
                }
                else {
                    printf("La pièce doit appartenir au joueur courant !\n") ;
                }
            }

        }
        else {
            printf("La case d'arrivée est hors du plateau !\n") ;
        }
    }
    else {
        printf("La case de départ est hors du plateau !\n") ;
    }

    return booleen ;
}



void deplacer_piece(Plateau* p, Joueur j, int depart, int arrivee) { //déplace une pièce depuis la position depart, jusqu'à la position arrivee

    if (coup_legal(p, j, depart, arrivee)) {
            Case piece = (*p).cases[depart] ;
            p->cases[depart] = VIDE ;
            p->cases[arrivee] = piece ;
    }
}

void pris(Plateau* p, int i){

	if ( (*p).cases[i+2]== (*p).cases[i] && (*p).cases[i+1] != (*p).cases[i] && (*p).cases[i+1] != VIDE) {
		
		(*p).cases[i+1]=VIDE;
	}

	if ( (*p).cases[i-2]== (*p).cases[i] && (*p).cases[i-1] != (*p).cases[i] && (*p).cases[i-1] != VIDE) {
		
		(*p).cases[i-1]=VIDE;
	}

	if ( (*p).cases[i+DeuxLignes]== (*p).cases[i] && (*p).cases[i+UneLigne] != (*p).cases[i] && (*p).cases[i+UneLigne] != VIDE) {
		
		(*p).cases[i+UneLigne]=VIDE;
	}

	if ( (*p).cases[i-DeuxLignes]== (*p).cases[i] && (*p).cases[i-UneLigne] != (*p).cases[i] && (*p).cases[i-UneLigne] != VIDE) {
		
		(*p).cases[i-UneLigne]=VIDE;
	}

}

void afficher (Plateau* p){

int i;
int j;
int k=0;
	
	for(j=0;j<81;j++){
			k+=1;
			if(k%9==0){
				printf("%d\n",(*p).cases[k-1]);
			}else{

				printf("%d",(*p).cases[k]);
		}
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



int main(){

int i=0;

int compteur=0;
int continuer=1;

Joueur j= JOUEUR_BLANC;

int depart;
int arrivee;

Plateau pla;
initialiser_plateau(&pla);


	SDL_Surface *ecran=NULL;
    ecran= SDL_SetVideoMode(2000, 1300, 32, SDL_HWSURFACE|SDL_RESIZABLE); // chargement d'une fenêtre dans l'espace écran



// On dessine le plateau
 
	SDL_Surface *imageDeFond=NULL;
	SDL_Surface *plateau=NULL;
	SDL_Surface *lignes[NbLignes]={NULL};	
	SDL_Surface *colonnes[NbLignes]={NULL};

	SDL_Surface *pions[NbPions]={NULL};


	SDL_Rect positionsLignes[NbLignes];
	SDL_Rect positionsColonnes[NbLignes];
	SDL_Rect positionImage;
	SDL_Rect positionsPions[NbPions];

	SDL_Rect positionPlateau;

	positionImage.x=0; // Positions d'ancrage de l'image de fond
	positionImage.y=0; 
	positionPlateau.x=25; // Positions d'ancrage du plateau de jeu
	positionPlateau.y=75;

 // Je crée un pointeur sur une SDL_Surface car c'est ce que SetVideoMode renvoie


	for(i=0;i<8;i++){
		lignes[i]= SDL_CreateRGBSurface(SDL_HWSURFACE,900,3,32,0,0,0,0);
		colonnes[i]= SDL_CreateRGBSurface(SDL_HWSURFACE,3,900,32,0,0,0,0);
		positionsLignes[i].x=0;
		positionsLignes[i].y=(i+1)*100;
		positionsColonnes[i].x=(i+1)*100;
		positionsColonnes[i].y=0;
		SDL_FillRect(lignes[i],NULL,SDL_MapRGB(lignes[i]->format,0,0,0));
		SDL_FillRect(colonnes[i],NULL,SDL_MapRGB(lignes[i]->format,0,0,0));
	}




	dessiner(&pla,ecran,pions, positionsPions);

	
    SDL_Init(SDL_INIT_VIDEO);// Initialisation de la SDL

	imageDeFond= IMG_Load("ponton2.jpg");
	plateau = IMG_Load("bois.jpg");


	if(ecran==NULL){
		printf("Erreur de chargement du mode vidéo %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_WM_SetCaption("Watashi no Hasami Shogi. Dozoo Yorochiku", NULL);


		for(i=0; i<8;i++){

			SDL_BlitSurface(lignes[i],NULL,plateau,&positionsLignes[i]);
			SDL_BlitSurface(colonnes[i],NULL,plateau,&positionsColonnes[i]);
	
		}

		SDL_BlitSurface(imageDeFond,NULL,ecran,&positionImage); // on Blit toutes les images nécessaires à l'affichage du plateau de jeu

		SDL_BlitSurface(plateau,NULL,ecran,&positionPlateau);	





//Etape de jeu car régissant le déplacement des pions et la fermeture de la fenêtre

    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event); // on attend qu'un évènement se passe

        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;

				break;

			case SDL_MOUSEBUTTONUP:
				if(event.button.button==SDL_BUTTON_LEFT){ // si on fait un clic gauche, on prend les coordonnées du curseur pour savoir quel pion déplacer

					depart= ((((event.button.y/100)-1)*9)+(event.button.x/100)); // indice de départ du nombre associé au pion dans le plateau


				}else if(event.button.button==SDL_BUTTON_RIGHT){ // si on fait un clic droit, on prend les coordonnées du curseur pour savoir où déplacer le pion

				arrivee= ((((event.button.y/100)-1)*9)+(event.button.x/100)); // indice d'arrivée

				deplacer_piece(&pla, j, depart,arrivee); // on déplace la pièce dans la matrice
	
				pris(&pla, arrivee);
			

				SDL_BlitSurface(imageDeFond,NULL,ecran,&positionImage); // on Reblit tout pour cacher les précédentes places des pions

				SDL_BlitSurface(plateau,NULL,ecran,&positionPlateau);	

				dessiner(&pla, ecran, pions, positionsPions); // on rdéfini  les coordonnées des pions en fonction de leur place dans la matrice de contrôle.

				if (j== JOUEUR_BLANC){  // on passe au joueur suivant
					j= JOUEUR_NOIR;
				}else{
					j= JOUEUR_BLANC;
				}


				break;


				}

        }

				for(i=0;i<NbPions;i++){
			 	SDL_BlitSurface(pions[i], NULL, ecran, &positionsPions[i]); // on Blit "dessine" les pions en fonction des coordonnées données avec la fonction dessiner
				}
			

			    SDL_Flip(ecran); // on met à jour l'écran


	
    }



// Si on décide de quitter le jeu (que l'on sort de la boucle while(continuer)), on libère les différents espaces mémoire alloués.    


	SDL_FreeSurface(imageDeFond);

	SDL_FreeSurface(ecran);


	for(i=0;i<NbLignes;i++){
		SDL_FreeSurface(colonnes[i]);
		SDL_FreeSurface(lignes[i]);
	}

	for(i=0;i<NbPions;i++){
		SDL_FreeSurface(pions[i]);
	}


 
    SDL_Quit(); // Arrêt de la SDL
 
    return EXIT_SUCCESS; // Fermeture du programme

	free_Plateau(&pla);

}





















