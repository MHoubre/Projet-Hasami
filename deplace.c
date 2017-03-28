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

void pause();

int dessiner(){

	int i=0;

// On dessine le plateau
	SDL_Surface *ecran=NULL; 
	SDL_Surface *imageDeFond=NULL;
	SDL_Surface *plateau=NULL;
	SDL_Surface *lignes[NbLignes]={NULL};	
	SDL_Surface *colonnes[NbLignes]={NULL};
	SDL_Surface *pions[NbPions]={NULL};

// On s'occupe des pions
	SDL_Surface *noir=NULL; //première ligne de pions



	SDL_Rect positionsLignes[NbLignes];
	SDL_Rect positionsColonnes[NbLignes];
	SDL_Rect positionImage;

	SDL_Rect positionPlateau;
	SDL_Rect positionNoir;



	positionImage.x=0; // Positions d'ancrage de l'image de fond
	positionImage.y=0; 
	positionPlateau.x=25; // Positions d'ancrage du plateau de jeu
	positionPlateau.y=75;

	positionNoir.x=25;
	positionNoir.y=75;

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


	noir = IMG_Load("noire_transparent.png");


	if(ecran==NULL){
		printf("Erreur de chargement du mode vidéo %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_WM_SetCaption("Watashi no Hasami Shogi. Dozoo Yorochiku", NULL);


int continuer =1;

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

            positionNoir.x =((event.button.x-positionPlateau.x)/100)*100+positionPlateau.x+5;
            positionNoir.y =((event.button.y-positionPlateau.y)/100)*100+positionPlateau.y+5;

            break;

    }

	for(i=0; i<8;i++){

		SDL_BlitSurface(lignes[i],NULL,plateau,&positionsLignes[i]);
		SDL_BlitSurface(colonnes[i],NULL,plateau,&positionsColonnes[i]);

	}


	SDL_BlitSurface(imageDeFond,NULL,ecran,&positionImage);
	SDL_BlitSurface(plateau,NULL,ecran,&positionPlateau);	

    SDL_BlitSurface(noir, NULL, ecran, &positionNoir); /* On place le pion à sa nouvelle position */

    SDL_Flip(ecran);

}

    

	SDL_FreeSurface(imageDeFond);

	SDL_FreeSurface(noir);

	SDL_FreeSurface(ecran);


	for(i=0;i<NbLignes;i++){
		SDL_FreeSurface(colonnes[i]);
		SDL_FreeSurface(lignes[i]);
	}

 
    SDL_Quit(); // Arrêt de la SDL
 
    return EXIT_SUCCESS; // Fermeture du programme
}



void main(){
	dessiner();

}


// dans le jeu, faire successivement appel à la fonction déplacer puis à une fonction matrice qui retracera tout.





