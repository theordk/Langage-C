#include "header.h"

///déclaration de notre fonction menu :
void menu (char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur)
{
    int choixMenu=0, a=0;  ///déclaration des variables

    ///affichage de l'interface du menu.
    printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
    printf("\t%c Bataille Navale 2.0 %c\n",186,186);
    printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\n",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);

    printf("\tChoix 1   -   Jouer\n");
    printf("\tChoix 2   -   R%cgles\n",138);
    printf("\tChoix 3   -   Quitter\n\n");
    printf("\t\tTapez 1, 2 ou 3 : ");

    scanf("%d",&choixMenu); ///saisie du choix

    switch (choixMenu)
    {
    case 1:
        jouer(tabJoueur1, tabCibleJoueur1, tabJoueur2, tabCibleJoueur2, B1, B2, indiceJoueur);
        break;

    case 2:
        regles(tabJoueur1, tabCibleJoueur1, tabJoueur2, tabCibleJoueur2, B1, B2, indiceJoueur);
        break;

    case 3:
        system("cls");
        break;

    default:
    {
        printf("Valeur incorrecte, tapez 1 pour retourner au menu :\n");
        scanf("%d",&a);
        if(a==1)
        {
            system("cls");
            menu(tabJoueur1, tabCibleJoueur1, tabJoueur2, tabCibleJoueur2, B1, B2, indiceJoueur);
        }
    }
    }
}


///déclaration de notre fonction jouer :
void jouer(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur)
{
    int choixMenu=0;
    int i, j; ///Compteurs.
    int typePartie=0; ///Variable pour savoir si on va jouer contre un joueur où l'oridnateur (1=jcj, 2=jco).

    while(choixMenu==0)
    {
        ///Permet de nettoyer la zone d'affichage de texte :
    gotoligcol(4,0);   ///Va au début de la zone de texte.
    for(i=0; i<20; i++) ///Pour les 20 lignes :
    {
        for(j=0; j<15; j++)    ///Et les 120 colonnes de la console :
        {
            printf("        ");    ///Afficher des espaces sur toutes la ligne.
        }
        printf("\n");   ///Recommence sur la ligne en dessous.
    }
    gotoligcol(4,0);   ///Revient au début de la zone de texte.

        printf("\tChoix 1   -   Jouer contre un ami\n");
    printf("\tChoix 2   -   Jouer contre l'ordinateur\n\n");
    printf("\t\tTapez 1 ou 2 : ");
        scanf("%d",&choixMenu);
    switch(choixMenu)
    {
    case 1:
        joueurContreJoueur(tabJoueur1, tabCibleJoueur1, tabJoueur2, tabCibleJoueur2, B1, B2, indiceJoueur, &typePartie);
        break;

    case 2:
        joueurContreOrdinateur(tabJoueur1, tabCibleJoueur1, tabJoueur2, tabCibleJoueur2, B1, B2, indiceJoueur, &typePartie);
        break;

    default:
        {
            choixMenu=0;

        }
    }
    }

}


///déclaration de notre fonction joueurContreJoueur :
void joueurContreJoueur(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur, int *typePartie)
{
    *typePartie=1;

    initialisationGrille(tabJoueur1, tabCibleJoueur1, tabJoueur2, tabCibleJoueur2, B1, B2, indiceJoueur);
    affichageGrille(tabJoueur1, tabCibleJoueur1, tabJoueur2, tabCibleJoueur2, B1, B2, indiceJoueur);
    choixAction(tabJoueur1, tabCibleJoueur1, tabJoueur2, tabCibleJoueur2, B1, B2, indiceJoueur, typePartie);
}


///déclaration de notre fonction joueurContreOrdinateur :
void joueurContreOrdinateur(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur, int *typePartie)
{
    *typePartie=2;

    initialisationGrille(tabJoueur1, tabCibleJoueur1, tabJoueur2, tabCibleJoueur2, B1, B2, indiceJoueur);
    affichageGrille(tabJoueur1, tabCibleJoueur1, tabJoueur2, tabCibleJoueur2, B1, B2, indiceJoueur);
    choixAction(tabJoueur1, tabCibleJoueur1, tabJoueur2, tabCibleJoueur2, B1, B2, indiceJoueur, typePartie);
}


///déclaration de notre fonction règles :
void regles(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur)  /// affichage des règles : cas numéro 2 du menu
{
    int temporisateur;

    system("cls");

    printf("\t\t\t\t\t\tR%cgles du jeu :\n\n\n",138); //
    printf("\t\tI - Caract%cristiques :\n\n",130);
    printf("Le joueur et l%cordinateur disposent chacun de deux grilles de 15*15 cases :\n",39);
    printf("\t- Une grille n%c1 pour positionner et visualiser ses navires\n",167);
    printf("\t- Une grille n%c2 pour visualiser les d%cg%cts caus%cs %c l%cadversaire\n\n",167,130,131,130,131,39);
    printf("Chaque joueur poss%cde une flotte de 10 navires :\n",138);
    printf("\t- 1 cuirass%c\n",130);
    printf("\t- 2 croiseurs\n");
    printf("\t- 3 destroyers\n");
    printf("\t- 4 sous-marins\n\n");
    printf("Chaque type de navires est de taille diff%crente :\n",130);
    printf("\t- cuirass%c --> 7 cases\n",130);
    printf("\t- croiseur --> 5 cases\n");
    printf("\t- destroyeur --> 3 cases\n");
    printf("\t- sous-marin --> 1 case\n\n");
    printf("La puissance de tir (nombre de cases touch%ces autour du point d%cimpact) d%cpend du type de navires :\n",130,39,130);
    printf("\t- cuirass%c --> 9 cases\n",130);
    printf("\t- croiseur --> 4 cases\n");
    printf("\t- destroyeur --> 1 case\n");
    printf("\t- sous-marin --> 1 case\n\n\n\n");
    printf("\t\tII - Le positionnement des navires :\n\n");
    printf("En d%cbut de jeu les navires sont positionn%cs al%catoirement et bien r%cpartis dans la grille n%c1 de chaque joueur.\n",130,130,130,130,167);
    printf("C%cest le joueur 1 qui commence la partie ou le joueur humain si c%cest contre l%cordinateur.\n",39,39,39);
    printf("Les navires peuvent %ctre positionn%cs verticalement ou horizontalement sur la grille.\n",136,130);
    printf("Mais attention, deux navires ne peuvent occuper la m%cme case.\n\n\n\n",136);
    printf("\t\tIII - Les actions d%cun navire par tour de jeu et par joueur :\n",39);
    printf("\n");
    printf("A chaque tour de jeu, les joueurs peuvent choisir l%cune des 2 actions suivantes sur un seul navire de leur choix de la\n",39);
    printf("grille n%c1, en choisissant les coordonn%ces de l%cune des cases du navire :\n",167,130,39);
    printf("\n");
    printf("\t1) Tirer :\n");
    printf("Le joueur tire en choisissant les coordonn%ces d%cune case valide de l%cadversaire (grille n%c2).\n",130,39,39,167);
    printf("Chaque destroyer n%cest muni que d%cune seule fus%ce %cclairante.\n",39,39,130,130);
    printf("Le premier tir d%cun destroyer d%cvoile un carr%c de 4*4 cases dans la grille adverse %c partir du coin haut et gauche.\n",39,130,130,133);
    printf("Mais attention, les navires adverses de ce carr%c ne seront visibles que lors du tour du jeu (quelques secondes).\n",130);
    printf("Pour couler un navire, il faut avoir touch%c toutes les cases qu%cil occupe : un cuirass%c est plus r%csistant qu%cun simple destroyer,  les sous-marins ne peuvent %ctre coul%cs que par d%cautres sous-marins.\n",130,39,130,130,39,136,130,39);
    printf("Dans ce cas, le navire adverse coul%c dispara%ct et la case touch%ce s%caffiche sur la grille n%c2.\n",130,140,130,39,167);
    printf("\n");
    printf("\t2) D%cplacer le navire d%cune seule case sauf s%cil est touch%c :\n",130,39,39,130);
    printf("Un navire ne peut pas se d%cplacer en diagonale.\n",130);
    printf("Il ne peut se d%cplacer que dans sa direction horizontale ou verticale, et d%cune seule case %c la fois, et le point\ncardinal de d%cplacement (est ou ouest s%cil est horizontal, nord ou sud s%cil est vertical).\n",130,39,133,130,39,39);
    printf("Evidemment, en cas d%cobstacle (case de d%cplacement occup%ce par un autre navire ou le bord de la grille), un navire ne\npourra pas effectuer son d%cplacement et devra tenter une nouvelle action.\n",39,130,130,130);
    printf("\n\n\n");
    printf("\t\tIV - Victoire d%cune partie\n\n",39);
    printf("Le premier qui a coul%c toute la flotte de son adversaire a gagn%c la partie !\n",130,130);
    printf ("\n\n");
    printf ("Tapez un chiffre pour revenir au menu :\n");

    scanf ("%d", &temporisateur);
    system("cls");
    menu(tabJoueur1, tabCibleJoueur1, tabJoueur2, tabCibleJoueur2, B1, B2, indiceJoueur);
}
