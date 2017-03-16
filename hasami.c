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
	SDL_Rect position1;
	SDL_Rect position2;

	position1.x=0;
	position1.y=0;
	position2.x=25;
	position2.y=250;
 // Je crée un pointeur sur une SDL_Surface car c'est ce que SetVideoMode renvoie
	
    SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL
 
    ecran= SDL_SetVideoMode(736, 1000, 32, SDL_HWSURFACE|SDL_RESIZABLE); // chargement d'une fenêtre dans l'espace écran
	plateau= SDL_CreateRGBSurface(SDL_HWSURFACE,685,700,32,0,0,0,0);	

	imageDeFond= IMG_Load("hasami_fond.jpg");
	SDL_FillRect(plateau,NULL,SDL_MapRGB(plateau->format,200,173,127));

	if(ecran==NULL){
		printf("Erreur de chargement du mode vidéo %s\n", SDL_GetError());
		exit(EXIT_FAILURE);

	}
	SDL_WM_SetCaption("Watashi no Hasami Shogi. Dozoo Yorochiku", NULL);
	SDL_BlitSurface(imageDeFond,NULL,ecran,&position1);
	SDL_BlitSurface(plateau,NULL,ecran,&position2);



	SDL_Flip(ecran);
    
    pause(); // Mise en pause du programme
	SDL_FreeSurface(imageDeFond);
 
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
