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


void deplacer_piece(Plateau* p, int depart, int arrivee) { //déplace une pièce depuis la position depart, jusqu'à la position arrivee

            Case piece = (*p).cases[depart] ;
            p->cases[depart] = VIDE ;
            p->cases[arrivee] = piece ;    
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


void pause(Plateau pla)
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer =0;
	
				

        }
    }
}






int main(){

int i=0;

int compteur=0;

int continuer=1;

int depart;
int arrivee;


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



	Plateau pla;
	initialiser_plateau(&pla);
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

		SDL_BlitSurface(imageDeFond,NULL,ecran,&positionImage);

		SDL_BlitSurface(plateau,NULL,ecran,&positionPlateau);	



    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;

				break;

			case SDL_MOUSEBUTTONUP:
				if(event.button.button==SDL_BUTTON_LEFT){

					depart= ((((event.button.y/100)-1)*9)+(event.button.x/100)); // indice de départ du nombre associé au pion dans le plateau
				}else if(event.button.button==SDL_BUTTON_RIGHT){

				arrivee= ((((event.button.y/100)-1)*9)+(event.button.x/100)); // indice d'arrivée

				deplacer_piece(&pla,depart,arrivee);

		SDL_BlitSurface(imageDeFond,NULL,ecran,&positionImage);

		SDL_BlitSurface(plateau,NULL,ecran,&positionPlateau);	
				dessiner(&pla, ecran, pions, positionsPions);

				break;


				}

        }

				for(i=0;i<NbPions;i++){
			 	SDL_BlitSurface(pions[i], NULL, ecran, &positionsPions[i]);
				}
			

			    SDL_Flip(ecran);


	
    }


    

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


}





















