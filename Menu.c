#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "version_essai.c"
#include "1VIA.c"


int main(){

int continuer=1;

	SDL_Surface *ecranMenu=NULL;
    ecranMenu= SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE|SDL_RESIZABLE); // chargement d'une fenêtre dans l'espace écran

	SDL_Surface *imageDeFond=NULL;
	SDL_Surface *Bouton=NULL;

	SDL_Rect positionImage;
	SDL_Rect positionBouton;

	positionImage.x=0; // Positions d'ancrage de l'image de fond
	positionImage.y=0; 

	positionBouton.x=1300;
	positionBouton.y=200;

    SDL_Init(SDL_INIT_VIDEO);// Initialisation de la SDL


	imageDeFond= IMG_Load("menu.jpg");
	Bouton= IMG_Load("bouton1.png");

	if(ecranMenu==NULL){
		printf("Erreur de chargement du mode vidéo %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}


	SDL_WM_SetCaption("Watashi no Hasami Shogi", NULL);

	SDL_BlitSurface(imageDeFond,NULL,ecranMenu,&positionImage); // on Blit toutes les images nécessaires à l'affichage du plateau de jeu
	SDL_BlitSurface(Bouton,NULL,ecranMenu, &positionBouton);

	SDL_Flip(ecranMenu);
	
	SDL_Event event;

	while (continuer)
    {

        SDL_WaitEvent(&event); // on attend qu'un évènement se passe

        switch(event.type){
            case SDL_QUIT:
				
                continuer = 0;

				break;

			case SDL_MOUSEMOTION:
				if(event.motion.y >= positionBouton.y && event.motion.y <= positionBouton.y+59 && event.motion.x >= positionBouton.x && event.motion.x <= positionBouton.x + 110){

						Bouton= IMG_Load("bouton2.png");

						SDL_BlitSurface(Bouton,NULL,ecranMenu, &positionBouton);
						SDL_Flip(ecranMenu);
						break;
				}else{
						Bouton= IMG_Load("bouton1.png");

						SDL_BlitSurface(Bouton,NULL,ecranMenu, &positionBouton);
						SDL_Flip(ecranMenu);

				}

			case SDL_MOUSEBUTTONDOWN:
				if(event.button.y >= positionBouton.y && event.button.y <= positionBouton.y+59 && event.button.x >= positionBouton.x && event.button.x <= positionBouton.x + 110){ // si on fait un clic gauche, on prend les coordonnées du curseur pour savoir quel pion déplacer
					continuer=0;					
					SDL_Quit();

					jeuIA();

				}


		}


	}
 

	SDL_FreeSurface(imageDeFond);
	SDL_FreeSurface(Bouton);

}
