#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void pause();

 
int main(int argc, char *argv[]){

	int i=0;
	SDL_Surface *ecran=NULL; 
	SDL_Surface *imageDeFond=NULL;
	SDL_Surface *plateau=NULL;
	SDL_Surface *lignes[8]={NULL};	
	SDL_Surface *colonnes[8]={NULL};

	SDL_Rect positionsLignes[8];
	SDL_Rect positionsColonnes[8];
	SDL_Rect position1;
	SDL_Rect position2;


	position1.x=0;
	position1.y=0;
	position2.x=25;
	position2.y=75;

 // Je crée un pointeur sur une SDL_Surface car c'est ce que SetVideoMode renvoie
	
    SDL_Init(SDL_INIT_VIDEO);// Initialisation de la SDL
 
    ecran= SDL_SetVideoMode(2000, 1300, 32, SDL_HWSURFACE|SDL_RESIZABLE); // chargement d'une fenêtre dans l'espace écran
	plateau= SDL_CreateRGBSurface(SDL_HWSURFACE,900,900,32,0,0,0,0);	

	for(i=1;i<9;i++){
		lignes[i]= SDL_CreateRGBSurface(SDL_HWSURFACE,900,6,32,0,0,0,0);
		colonnes[i]= SDL_CreateRGBSurface(SDL_HWSURFACE,6,900,32,0,0,0,0);
		positionsLignes[i].x=0;
		positionsLignes[i].y=i*100;
		positionsColonnes[i].x=i*100;
		positionsColonnes[i].y=0;
		SDL_FillRect(lignes[i],NULL,SDL_MapRGB(lignes[i]->format,255,255,255));
		SDL_FillRect(colonnes[i],NULL,SDL_MapRGB(lignes[i]->format,255,255,255));
	}

	imageDeFond= IMG_Load("ponton2.jpg");
	SDL_FillRect(plateau,NULL,SDL_MapRGB(plateau->format,200,173,127));

	if(ecran==NULL){
		printf("Erreur de chargement du mode vidéo %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_WM_SetCaption("Watashi no Hasami Shogi. Dozoo Yorochiku", NULL);

	for(i=0; i<9;i++){

		SDL_BlitSurface(lignes[i],NULL,plateau,&positionsLignes[i]);
		SDL_BlitSurface(colonnes[i],NULL,plateau,&positionsColonnes[i]);

	}

	SDL_BlitSurface(imageDeFond,NULL,ecran,&position1);
	SDL_BlitSurface(plateau,NULL,ecran,&position2);



	SDL_Flip(ecran);
    
    pause(); // Mise en pause du programme
	SDL_FreeSurface(imageDeFond);
	SDL_FreeSurface(ecran);
	for(i=0;i<9;i++){
		SDL_FreeSurface(colonnes[i]);
		SDL_FreeSurface(lignes[i]);
	}

 
    SDL_Quit(); // Arrêt de la SDL
 
    return EXIT_SUCCESS; // Fermeture du programme
}
 
void pause()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}
