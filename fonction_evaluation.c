#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definition de nouveau types

typedef enum Joueur {
    JOUEUR_BLANC, JOUEUR_NOIR
} Joueur ;

typedef enum Case {
    VIDE, BLANC, NOIR
} Case ;

typedef struct Plateau {
    Case cases[81] ;
}plateau ;

//Prototype

double evaluater ( plateau * p, double coef, Joueur j);
int nombreDePions(plateau* p, Joueur j);
int evaluaterMateriel(plateau *p);
int evaluaterMobilite( plateau* p);
int evaluaterLigne(plateau* p,Joueur j);
int evaluateCapture(plateau* p, Joueur j);
int evaluateCentre(Joueur j, plateau *p);


int main()
{
    plateau* p;
    double coef;
    Joueur j;
    double eval = evaluater ( p,coef,j);
    printf("%f", eval);
    return 0;
}

// fonction d'evaluation finale
double evaluater ( plateau* p, double coef, Joueur j){

    double eval = 0;
    double coef1 = 5;
    double coef2 = 2;
    double coef3 = 3;
    double coef4 = 4;
    double coef5 = 2;

    if (coef == coef1){
        eval += coef1* evaluaterMateriel(p);
    }

    if (coef == coef2){
        eval += coef2* evaluaterMobilite( p);
    }

    if (coef == coef3){
        eval += coef3* evaluaterLigne(p,j);
    }

    if (coef == coef4){
        eval += coef4* evaluateCapture(p,j);
    }
        if (coef == coef5){
        eval += coef5* evaluateCentre( j, p);
    }

    return eval;

}

// Calcule le nombre de pions de chaque jiueur sur le plateau

int nombreDePions(plateau* p, Joueur j)
{
    int NbpionsJoueurBlanc = 0; //Compteur des pions noirs
    int NbpionsJoueurNoir = 0;  //Compteur des pions noirs
    int i;

    for(i=0; i<=81; i++){
            if ((*p).cases[i] == BLANC){

                NbpionsJoueurBlanc += 1;
                return NbpionsJoueurBlanc;

            }
            else if ((*p).cases[i] == NOIR){

                NbpionsJoueurNoir += 1;
                return NbpionsJoueurNoir;

            }
    }

    if (j == JOUEUR_BLANC ){
        return NbpionsJoueurBlanc;
    }
    else {
        return NbpionsJoueurNoir;
    }
}



//Evaluation dU Materiel consiste � faire la diff�rence entre le nombre de pions que poss�de chaque joueur

int evaluaterMateriel(plateau *p)
{
    int B, N;

    B = nombreDePions(p, JOUEUR_BLANC);
    N = nombreDePions(p, JOUEUR_NOIR);

    return N - B  ;
}



/* Evaluation des possibilit�s de d�placement de chaque joueur
Parcourir les pions du joueur pion par pion et Calculer le nombre de d�placements que peut faire chaque pion
Affecter la diffr�rence entre les deplacements des pions des deux joueurs � evaluateMobility */


int evaluaterMobilite( plateau* p)
{
        // JOUEUR_BLANC
        int DeplacementJoueurBlanc = 0;
        int i = 0 ;
        int droiteB =0;
        int gaucheB =0;
        int avantB =0;
        int arriereB =0;
        // JOUEUR_NOIR
        int DeplacementJoueurNoir = 0;
        int droiteN =0;
        int gaucheN =0;
        int avantN =0;
        int arriereN =0;

        int s, d, s1, d1;

 for(i=0; i<=81; i++){

    if ((*p).cases[i] == BLANC){ // JOUEUR_BLANC

            s= i+gaucheB ;
            d=i-droiteB;
            while( (s <=8) && (gaucheB != -1)){
                gaucheB ++;
                if ((*p).cases[s] == VIDE ){// pour ne pas d�border le plateau � gauche

                    DeplacementJoueurBlanc +=1 ;

                }else if ((*p).cases[s] != VIDE && (*p).cases[s+1] == VIDE){

                    DeplacementJoueurBlanc +=1 ;

                }else {
                   gaucheB=-1;
            }

        }
          while( d > 0 && droiteB != -1 ){ // pour ne pas d�border le plateau � gauche et se d�placer � droite
                droiteB ++;
                if ((*p).cases[d] == VIDE ){

                    DeplacementJoueurBlanc +=1 ;

                }else if ((*p).cases[d] != VIDE && (*p).cases[d-1] == VIDE){

                    DeplacementJoueurBlanc +=1 ;

                }else {
                    droiteB =-1;
            }

        }

            while( (i+(9*avantB))/ 9 != 8 && avantB != -1  ){
                avantB ++ ;
                if ((*p).cases[i+(9*avantB)] == VIDE ){// pour se d�placer en avant

                    DeplacementJoueurBlanc +=1 ;

                }else if ((*p).cases[i+(9*avantB)] != VIDE && (*p).cases[i+(9*avantB)+1] == VIDE){

                    DeplacementJoueurBlanc +=1 ;

                }else {
                   avantB = -1;
            }

        }
          while( (i-(9*arriereB))/ 9 != 0 && arriereB != -1  ){ // pour pouvoir reculer
                arriereN ++;
                arriereB ++;
                if ((*p).cases[i-(9*arriereB)] == VIDE ){

                    DeplacementJoueurBlanc +=1 ;

                }else if ((*p).cases[i-(9*arriereB)] != VIDE && (*p).cases[i-(9*arriereB)-1] == VIDE){

                    DeplacementJoueurBlanc +=1 ;

                }else {
                    arriereB=-1;
            }

        }

            }

      //JOUEUR_NOIR

    if ((*p).cases[i] == NOIR){

            s1= i+gaucheN ;
            d1=i-droiteN;

            while( (s1 <=8) && (gaucheN != -1)){
                gaucheN ++;
                if ((*p).cases[s1] == VIDE ){// pour ne pas d�border le plateau � gauche

                    DeplacementJoueurNoir +=1 ;

                }else if ((*p).cases[s1] != VIDE && (*p).cases[s1+1] == VIDE){

                    DeplacementJoueurNoir +=1 ;

                }else {
                   gaucheN=-1; // on a plus que deux pions qui bloquent le chemin on sort de la boucle
            }

        }
          while( d1 > 0 && droiteN != -1 ){ // pour ne pas d�border le plateau � gauche et se d�placer � droite
                droiteN ++;
                if ((*p).cases[d1] == VIDE ){

                    DeplacementJoueurNoir +=1 ;

                }else if ((*p).cases[d1] != VIDE && (*p).cases[d1-1] == VIDE){

                    DeplacementJoueurNoir +=1 ;

                }else {
                    droiteN =-1; // on a plus que deux pions qui bloquent le chemin on sort de la boucle
            }

        }

            while( (i+(9*avantN))/ 9 != 8 && avantN != -1  ){
                avantN ++ ;
                if ((*p).cases[i+(9*avantN)] == VIDE ){// pour se d�placer en avant

                    DeplacementJoueurNoir +=1 ;

                }else if ((*p).cases[i+(9*avantN)] != VIDE && (*p).cases[i+(9*avantN)+1] == VIDE){

                    DeplacementJoueurNoir +=1 ;

                }else {
                   avantN = -1; // on a plus que deux pions qui bloquent le chemin on sort de la boucle
            }

        }
          while( (i-(9*arriereN))/ 9 != 0 && arriereN != -1  ){ // pour pouvoir reculer
                arriereN ++;
                if ((*p).cases[i-(9*arriereN)] == VIDE ){ // pour reculer dans la mm colonne

                    DeplacementJoueurNoir +=1 ;

                }else if ((*p).cases[i-(9*arriereN)] != VIDE && (*p).cases[i-(9*arriereN)-1] == VIDE){

                    DeplacementJoueurNoir +=1 ;

                }else { // on a plus que deux pions qui bloquent le chemin on sort de la boucle
                    arriereN=-1;
            }

        }
    }
    return DeplacementJoueurBlanc -DeplacementJoueurNoir;
 }
}


/*evaluer la chance de gain par alignement des pions.
Si le pion n'a jamais d�plac� alors retourne 0
si deux cases successives verticalement ou diagonalement sont de mm couleur et que les 3 suivantes sont vides on attribue 2^2
si 3 cases successives verticalement ou diagonalement sont de mm couleur et que les 2 suivantes sont vides on attribue 3^2
si 4 cases successives verticalement ou diagonalement sont de mm couleur et que les 1 suivantes est vide on attribue 4^2 */

int evaluaterLigne(plateau *p,Joueur j){

    int i,k,l,m;
    int ligne2=0;
    int ligne3=0;
    int ligne4=0;
    //JOUEUR_BLANC
    //Verticalement

        if (j== JOUEUR_BLANC){
                for (i = 0 ; i < 36 ; i++) {    //On commence par 18 pour s'assurer qu'on a pas compter les pions dans la position de d�part

                    if (((*p).cases[i] == BLANC ) && ((*p).cases[i+9] == BLANC )){
                        ligne2 += 4  ;

                    }else if (((*p).cases[i] == BLANC )&& ((*p).cases[i+9] == BLANC ) && ((*p).cases[i+18] == BLANC )){
                        ligne3 += 9;

                    }else if (((*p).cases[i] == BLANC )&& ((*p).cases[i+9] == BLANC ) && ((*p).cases[i+18] == BLANC ) && ((*p).cases[i+27] == BLANC )){
                        ligne4 +=16;
                    }
             }
             // � partir de 62 on est dans le territoire des blancs
             //on suppose que les pions blancs dans ce territoire n'ont pas quitt� leur position initiale
              for (i = 36 ; i < 45 ; i++) { // � partir de ces cases on ne peut former que des lignes blanches de 3 pions
                     if (((*p).cases[i] == BLANC ) && ((*p).cases[i+9] == BLANC )){
                        ligne2 += 4  ;

                    }else if (((*p).cases[i] == BLANC )&& ((*p).cases[i+9] == BLANC ) && ((*p).cases[i+18] == BLANC )){
                        ligne3 += 9;
                    }
            }
             for (i = 45 ; i < 53 ; i++) { // � partir de ces cases on ne peut former que des lignes blanches de 2 pions
                    if (((*p).cases[i] == BLANC ) && ((*p).cases[i+9] == BLANC )){

                        ligne2 += 4  ;
                    }
            }
        }else {     //JOUEUR_NOIR

               for (k = 80 ; k < 44 ; k--) {    //On commence par la fin jusqu'a 18 pour s'assurer qu'on a pas compter les pions noirs dans la position de d�part

                    if (((*p).cases[k] == NOIR ) && ((*p).cases[k-9] == NOIR )){
                        ligne2 += 4  ;

                    }else if (((*p).cases[k] == NOIR )&& ((*p).cases[k-9] == NOIR ) && ((*p).cases[k-18] == NOIR )){
                        ligne3 += 9;

                    }else if (((*p).cases[k] == NOIR )&& ((*p).cases[k-9] == NOIR ) && ((*p).cases[k-18] == NOIR ) && ((*p).cases[k-27] == NOIR )){
                        ligne4 +=16;
                    }
             }
             // � partir de 62 on est dans le territoire des noirs
             //on suppose que les pions noirs dans ce territoire n'ont pas quitt� leur position initiale
              for (k = 44 ; k < 35 ; k--) { // � partir de ces cases on ne peut former que des lignes noires de 3 pions
                     if (((*p).cases[k] == NOIR ) && ((*p).cases[k-9] == NOIR )){
                        ligne2 += 4  ;

                    }else if (((*p).cases[k] == NOIR )&& ((*p).cases[k-9] == NOIR ) && ((*p).cases[k-18] == NOIR )){
                        ligne3 += 9;
                    }
            }
             for (k = 35 ; k < 26 ; k--) { // � partir de ces cases on ne peut former que des lignes noires de 2 pions
                    if (((*p).cases[k] == NOIR ) && ((*p).cases[k-9] == NOIR )){

                        ligne2 += 4  ;
                    }
            }
        }
    //diagonalement
    if (j== JOUEUR_BLANC){
            for (l = 0 ; l < 62 ; l++) {
                if (((l % 10)>= 0) && (((l+10) % 10)<=4)){
                    if ((((*p).cases[l] == BLANC ) && ((*p).cases[l+10] == BLANC ))||(((*p).cases[l] == BLANC ) && ((*p).cases[l-10] == BLANC ))){
                        ligne2 += 4  ;

                    }else if (((*p).cases[l] == BLANC )&& ((*p).cases[l+10] == BLANC ) && ((*p).cases[l+20] == BLANC )){
                        ligne3 += 9;

                    }else if (((*p).cases[l] == BLANC )&& ((*p).cases[l+10] == BLANC ) && ((*p).cases[l+20] == BLANC ) && ((*p).cases[l+30] == BLANC )){
                        ligne4 +=16;
                    }

                }
            }

}


/*Domination du territoire
si on a deux pions de mm couleur sur une mm ligne ou colonne
evaluer capture sera le nombre de capture possible que poss�de le joueur sur le plateau * 3 */

int evaluateCapture(plateau* p, Joueur j)
{

   int i=0;
   int k=0;
   int B,N;
   int captureLigneBlanc=0;
   int captureColonneBlanc=0;
   int captureLigneNoir=0;
   int captureColonneNoir=0;

   // Capture sur les lignes
   while (i>=0 && i < 81){

    Case case1, case2;
    case1= (*p).cases[i]; // Pour minimiser l'�criture
    case2= (*p).cases[i+3];
        //JOUEUR_BLANC

     if (j== JOUEUR_BLANC){
            if (((i+3)%9) == 8 || i > 6 ){ //pour compter les captures ligne par ligne et �viter le d�bordement de la ligne
                                            //c a d �viter le cas ou la capture commence dans une ligne et finie dans la ligne suivante
                    if (case2 == VIDE || case2 == NOIR){
                        i=i+4;
                    }else {
                        i=i+1;
                        captureLigneBlanc +=3;
                    }
            }
        //le cas d'une capture sure si un pion noir s'installe devant les deux blancs
            if (case1 == BLANC && (*p).cases[i+1]==VIDE && (*p).cases[i+2]==VIDE && case2==BLANC){
                    i=i+3;
                    captureLigneBlanc +=3;
            }else {
                i=i+1;
            }
            if ((*p).cases[i] == NOIR && (*p).cases[i+1]==VIDE && (*p).cases[i+2]==VIDE && (*p).cases[i+3]==NOIR){
                captureLigneBlanc -=3; // le blanc risque de se faire captur�
            }

     }

    //JOUEUR_NOIR

          if (j== JOUEUR_NOIR){
            if (((i+3)%9) == 8 || i > 6 ){ //pour compter les captures ligne par ligne et �viter le d�bordement de la ligne
                                            //c a d �viter le cas ou la capture commence dans une ligne et finie dans la ligne suivante
                    if (case2 == VIDE || case2 == BLANC){
                        i=i+4;
                    }else {
                        i=i+1;
                        captureLigneNoir +=3;
                    }
            }
        //le cas d'une capture sure si un pion BLANC s'installe devant les deux NOIRS
            if (case1 == NOIR && (*p).cases[i+1]==VIDE && (*p).cases[i+2]==VIDE && case2==NOIR){
                    i=i+3;
                    captureLigneNoir +=3;
            }else {
                i=i+1;
            }
            if ((*p).cases[i] == NOIR && (*p).cases[i+1]==VIDE && (*p).cases[i+2]==VIDE && (*p).cases[i+3]==NOIR){
                captureLigneNoir -=3; // le noir risque de se faire captur�
            }
     }


   }
   // Capture sur les colonnes

    while (k>=0 && k < 81){

    Case case3, case4;
    case3= (*p).cases[k];
    case4= (*p).cases[k+27];
    int l=0;
        //JOUEUR_BLANC

     if (j== JOUEUR_BLANC){
            l=l+1;
            if (((k+27)/9) == 8 || (k/9) > 6 ){ //pour compter les captures ligne par ligne et �viter le d�bordement de la ligne
                                            //c a d �viter le cas ou la capture commence dans une ligne et finie dans la ligne suivante
                    if (case4 == VIDE || case4 == NOIR){
                        k=k-45+l; // on revient de 45 case pour changer de colonne
                    }else {
                        k=k-72+l; //  on revient de toutes les cases qu'on a parcouru pour changer de colonne
                        captureColonneBlanc +=3;
                    }
            }
        //le cas d'une capture sure si un pion noir s'installe devant les deux blancs
            if (case3 == BLANC && (*p).cases[k+9]==VIDE && (*p).cases[k+18]==VIDE && case4==BLANC){
                    k=k+27;
                    captureColonneBlanc +=3;
            }else {
                k=k+9;
            }
            if (case3 == NOIR && (*p).cases[k+9]==VIDE && (*p).cases[k+18]==VIDE && case4==NOIR){
                captureColonneBlanc -=3; // le blanc risque de se faire captur�
            }

     }

    //JOUEUR_NOIR

          if (j== JOUEUR_NOIR){
            l=l+1;
            if (((k+27)/9) == 8 || (k/9) > 6 ){ //pour compter les captures ligne par ligne et �viter le d�bordement de la ligne
                                            //c a d �viter le cas ou la capture commence dans une ligne et finie dans la ligne suivante
                    if (case4 == VIDE || case4 == BLANC){
                        k=k-45+l;
                    }else {
                        k=k-72+l;
                        captureColonneNoir +=3;
                    }
            }
        //le cas d'une capture sure si un pion BLANC s'installe devant les deux NOIRS
            if (case3 == NOIR && (*p).cases[k+9]==VIDE && (*p).cases[k+18]==VIDE && case4==NOIR){
                    k=k+27;
                    captureColonneNoir +=3;
            }else {
                k=k+9;
            }
            if (case3 == NOIR && (*p).cases[k+9]==VIDE && (*p).cases[k+18]==VIDE && case4==NOIR){
                captureColonneNoir -=3; // le noir risque de se faire captur�
            }
     }


   }
   //evaluation des captures
   B =captureLigneBlanc + captureColonneBlanc;
   N= captureLigneNoir + captureColonneNoir;

       return B-N;

}



/* Valoriser les cases du centre
On retourne la diff�rence qu'on amplifie � puissance de 3 pour ne pas perdre le signe du r�sultat */

int evaluateCentre(Joueur j, plateau *p)
{
    int B, N;
    int i;

    B = nombreDePions(p, JOUEUR_BLANC);
    N = nombreDePions(p, JOUEUR_NOIR);

    for (i=18; i<62; i++){
        if ( (B-N)>3 ){
            return pow(B-N,3);
        }
    }
}

