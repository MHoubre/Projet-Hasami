project: arbres.o min_max.o plateau.o fonction_evaluation.o main.o
	gcc arbres.o min_max.o plateau.o fonction_evaluation.o -o project


main.o: main.c min_max.h arbres.h plateau.h 
	gcc main.c

arbres.o: arbres.c arbres.h 
	gcc -c arbres.c

min_max.o: min_max.c min_max.h arbres.h plateau.h fonction_evaluation.h
	gcc -c min_max.c

plateau.o: plateau.c plateau.h fonction_evaluation.h
	gcc -c plateau.c

fonction_evaluation.o: fonction_evaluation.c fonction_evaluation.h plateau.h
	gcc -c fonction_evaluation.c



