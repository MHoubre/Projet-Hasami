jeu: Menu.c 1VIA.o version_essai.o
	gcc -c Menu.c -lSDL -lSDL_image


1VIA.o: 1VIA.c min_max.o plateau.o
	gcc -c 1VIA.c -lSDL -lSDL_image -lSDL_mixer

version_essai.o: version_essai.c  plateau.o
	gcc -c version_essai.c -lSDL -lSDL_image -lSDL_mixer

arbres.o: arbres.c arbres.h 
	gcc -c arbres.c

min_max.o: min_max.c min_max.h arbres.h plateau.h fonction_evaluation.o
	gcc -c min_max.c

fonction_evaluation.o: fonction_evaluation.c fonction_evaluation.h plateau.o
	gcc -c fonction_evaluation.c

plateau.o: plateau.c plateau.h fonction_evaluation.h
	gcc -c plateau.c





