#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

///insertion des biblioth�ques n�cessaires :
#include <stdio.h>
#include <stdlib.h>
#include <string.h>     ///n�cessaire pour manier les cha�nes de caract�res.
#include <time.h>       ///n�cessaire pour les randoms.
#include <windows.h>    ///n�cessaire pour gotoligcol.


///d�claration de la structure bateau.

typedef struct bateau
{
    int type;   ///1=cuirass�, 2=croiseur, 3=destroyer, 4=sous-marin.
    int taille;
    int orientation;    ///0=horizontal, 1=vertical, 2=horizontal ou vertical (cas des sous-marins).
    int tabX[7];    ///Tableau des coordonn�es des lignes du bateau (0, 1, 2,...,14 si utilis�es, -1 si inexistantes).
    int tabY[7];    ///Tableau des coordonn�es des colonnes du bateau (0, 1, 2,...,14 si utilis�es, -1 si inexistantes).
    int etat;   ///0=intact, 1=touch� 1 fois,...etc..., -1=coul�.
    int nbTirs; ///compte le nombre de fois qu'un bateau a tir�.

} t_bateau;


///Prototypes de nos fonctions :

///Fonction donn�e par les professeurs d'informatique qui permet d    e d�placer le curseur dans la console :
void gotoligcol( int lig, int col );

///Fonction menu pour l'affichage des diff�rents choix possibles :
void menu (char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur);
///Fonction regles qui explique les diff�rentes r�gles du jeu au joueur :
void regles(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur);
///Fonction qui permet le choix entre le mode "Joueur contre Joueur" et "Joueur contre Ordinateur" :
void jouer(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur);

///Fonction qui appelle les diff�rentes fonctions n�cessaires au mode "Joueur contre Joueur" :
void joueurContreJoueur(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur, int *typePartie);
///Fonction qui appelle les diff�rentes fonctions n�cessaires au mode "Joueur contre Ordinateur" :
void joueurContreOrdinateur(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur, int *typePartie);

///Fonction qui permet l'initialisation de nos tableaux de char.
void initialisationGrille(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur);
///Fonction qui permet l'initialisation du tableau de bateaux du joueur 1 ainsi que de leurs diff�rentes varaibles :
void initBateauxJ1(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur);
///Fonction qui permet l'initialisation du tableau de bateaux du joueur 2 ainsi que de leurs diff�rentes varaibles :
void initBateauxJ2(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur);

///Fonction qui permet l'affichage de la grille du joueur :
void affichageGrille(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur);
///Fonction qui permet l'affichage de la grille "cible" du joueur :
void affichageGrille2(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B[10], t_bateau B2[10], int *indiceJoueur);

///Fonction qui permet au joueur de choisir entre "attaquer" et "d�placer" et qui appelle les fonctions correspondantes :
void choixAction(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur, int *typePartie);
///Fonction qui g�re l'attaque :
void attaque(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur, int *ligneFusee, int *colonneFusee, int *indiceFusee, int *indiceBatCoule, int *numBatCoule);
///Fonction qui g�re les d�placements :
void deplacement(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur);

///Fonctions qui permettent � l'ordinateur de jouer :
void actionAleaIA(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur, int *typePartie);
void attaqueAleaIA(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur, int *ligneFusee, int *colonneFusee, int *indiceFusee, int *indiceBatCoule, int *numBatCoule);
void deplacementAleaIA(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur);

///Fonction qui permet le passage du joueur 1 au joueur 2 et vice-versa :
void changementJoueur(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur, int *ligneFusee, int *colonneFusee, int *indiceFusee, int *indiceBatCoule, int *numBatCoule, int *typePartie);

#endif // HEADER_H_INCLUDED
