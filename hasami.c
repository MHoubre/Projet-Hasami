#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#define TailleLigne 9
#define NbLignes 8

void pause();

int plateau(){

	int i=0;

// On dessine le plateau
	SDL_Surface *ecran=NULL; 
	SDL_Surface *imageDeFond=NULL;
	SDL_Surface *plateau=NULL;
	SDL_Surface *lignes[NbLignes]={NULL};	
	SDL_Surface *colonnes[NbLignes]={NULL};

// On s'occupe des pions
	SDL_Surface *noirL1[TailleLigne]={NULL}; //première ligne de pions
	SDL_Surface *noirL2[TailleLigne]={NULL}; // deuxième ligne de pions
	SDL_Surface *blancL1[TailleLigne]={NULL}; //première ligne de pions
	SDL_Surface *blancL2[TailleLigne]={NULL}; // deuxième ligne de pions


	SDL_Rect positionsLignes[NbLignes];
	SDL_Rect positionsColonnes[NbLignes];
	SDL_Rect positionImage;

	SDL_Rect positionPlateau;
	SDL_Rect positionNoirL1[TailleLigne];
	SDL_Rect positionNoirL2[TailleLigne];


	SDL_Rect positionBlancL1[TailleLigne];
	SDL_Rect positionBlancL2[TailleLigne];



	positionImage.x=0; // Positions d'ancrage de l'image de fond
	positionImage.y=0; 
	positionPlateau.x=25; // Positions d'ancrage du plateau de jeu
	positionPlateau.y=75;

	for(i=0;i<TailleLigne;++i){

		positionNoirL1[i].x=5+i*100;
		positionNoirL1[i].y=5;
		positionNoirL2[i].x=5+i*100;
		positionNoirL2[i].y=105;

		positionBlancL1[i].x=5+i*100;
		positionBlancL1[i].y=705;
		positionBlancL2[i].x=5+i*100;
		positionBlancL2[i].y=805;

	}

	

 // Je crée un pointeur sur une SDL_Surface car c'est ce que SetVideoMode renvoie
	
    SDL_Init(SDL_INIT_VIDEO);// Initialisation de la SDL
 
    ecran= SDL_SetVideoMode(2000, 1300, 32, SDL_HWSURFACE|SDL_RESIZABLE); // chargement d'une fenêtre dans l'espace écran	

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

	imageDeFond= IMG_Load("ponton2.jpg");
	plateau = IMG_Load("bois.jpg");

	for(i=0;i<TailleLigne;i++){

		noirL1[i] = IMG_Load("noire_transparent.png");
		noirL2[i] = IMG_Load("noire_transparent.png");
		blancL1[i] = IMG_Load("blanche_transparent.png");
		blancL2[i] = IMG_Load("blanche_transparent.png");
	}


	if(ecran==NULL){
		printf("Erreur de chargement du mode vidéo %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_WM_SetCaption("Watashi no Hasami Shogi. Dozoo Yorochiku", NULL);

	for(i=0;i<TailleLigne;i++){
		SDL_BlitSurface(noirL1[i],NULL,plateau,&positionNoirL1[i]);
		SDL_BlitSurface(noirL2[i],NULL,plateau,&positionNoirL2[i]);
		SDL_BlitSurface(blancL1[i],NULL,plateau,&positionBlancL1[i]);
		SDL_BlitSurface(blancL2[i],NULL,plateau,&positionBlancL2[i]);

	}





	for(i=0; i<8;i++){

		SDL_BlitSurface(lignes[i],NULL,plateau,&positionsLignes[i]);
		SDL_BlitSurface(colonnes[i],NULL,plateau,&positionsColonnes[i]);

	}


	SDL_BlitSurface(imageDeFond,NULL,ecran,&positionImage);
	SDL_BlitSurface(plateau,NULL,ecran,&positionPlateau);	






	SDL_Flip(ecran);
    
    pause(); // Mise en pause du programme
	SDL_FreeSurface(imageDeFond);

	for(i=0;i<TailleLigne;i++){
		SDL_FreeSurface(noirL1[i]);
		SDL_FreeSurface(noirL2[i]);
	}

	SDL_FreeSurface(ecran);


	for(i=0;i<NbLignes;i++){
		SDL_FreeSurface(colonnes[i]);
		SDL_FreeSurface(lignes[i]);
	}

 
    SDL_Quit(); // Arrêt de la SDL
 
    return EXIT_SUCCESS; // Fermeture du programme
}
 





 
int main(int argc, char *argv[]){

	plateau();
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
