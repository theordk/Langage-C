#include "header.h" ///insertion de notre bibliothèque qui contient les prototypes de nos fonctions.

int main()  ///début du programme.
{
    srand(time(NULL));  ///initialise la fonction srand sur le temps actuel (sert pour les randoms).

    char tabJoueur1[15][15];  ///déclaration du tableau du joueur 1.
    char tabCibleJoueur1[15][15];   ///déclaration du tableau de cible du joueur 1.
    char tabJoueur2[15][15];    ///déclaration du tableau du joueur 2.
    char tabCibleJoueur2[15][15];   ///déclaration du tableau de cible du joueur 2.
    int indiceJoueur=1; ///indice qui permet de savoir quel joueur joue (1=joueur 1, 2=joueur 2).

    t_bateau B1[10];    ///déclaration d'un tableau contenant 10 bateaux pour le joueur 1.
    t_bateau B2[10];    ///déclaration d'un tableau contenant 10 bateaux pour le joueur 2.

    menu(tabJoueur1, tabCibleJoueur1, tabJoueur2, tabCibleJoueur2, B1, B2, &indiceJoueur); ///appel de la fonction menu.

    return 0;
}


void gotoligcol( int lig, int col ) ///déclaration de la fonction gotoligcol qui permet de déplacer le curseur dans la console.
{
COORD mycoord;

mycoord.X = col;
mycoord.Y = lig;
SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}
