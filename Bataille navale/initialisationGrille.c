#include "header.h"

///déclaration de notre fonction qui initialise toutes les cases du tableau avec un espace :
void initialisationGrille(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur)
{
    int a,b;

    for (a=0; a<15; a++)
    {
        for (b=0; b<15; b++)
        {
            tabJoueur1[a][b]=' ';
            tabCibleJoueur1[a][b]=176;
            tabJoueur2[a][b]=' ';
            tabCibleJoueur2[a][b]=176;
        }
    }
    initBateauxJ1(tabJoueur1, tabCibleJoueur1, tabJoueur2, tabCibleJoueur2, B1, B2, indiceJoueur);
    initBateauxJ2(tabJoueur1, tabCibleJoueur1, tabJoueur2, tabCibleJoueur2, B1, B2, indiceJoueur);
}

///déclaration de notre fonction qui initialise les bateaux et les place aléatoirement pour le joueur 1 :
void initBateauxJ1(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur)
{
    int i=0;
    int j=0;

    ///déclaration du CUIRASSE :
    for(i=0; i<1; i++)
    {
        B1[i].type=1;    ///affectation du type de bateau à la case du tableau de bateaux correspondante.
        B1[i].taille=7;  ///affectation de la taille du bateau à la case du tableau de bateaux correspondante.
        B1[i].nbTirs=0; ///initialise le compteur de tirs du bateau.
        B1[i].etat=0;   ///initialise le compteur d'état du bateau (0=intact).

        int x=0;  ///coordonées lignes.
        int y=0;  ///coordonées colonnes.
        int orientation=0;  ///0=horizontal, 1=vertical.

        x = rand()%9;   ///affectation à x d'un nombre aléatoire entre 0 et 8.
        y = rand()%9;   ///affectation à y d'un nombre aléatoire entre 0 et 8.
        orientation = rand()%2; ///affectation à orientation d'un nombre aléatoire entre 0 et 1.

        ///tests pour savoir si on peux placer le bateau ou non :
        if (orientation==0)  ///si le bateau est horizontal :
        {
            for (j=0; j<7;) ///pour la case de départ et les 6 cases à droite des coordonnées de départ :
            {
                if((tabJoueur1[x][y+j]==' '))  ///si la case est un espace :
                {
                    j++;    ///on teste la case suivante.
                }
                else    ///sinon :
                {
                    x = rand()%9;   ///affectation à x d'un NOUVEAU nombre aléatoire entre 0 et 8.
                    y = rand()%9;   ///affectation à y d'un NOUVEAU nombre aléatoire entre 0 et 8.
                    j=0;    ///on relance le compteur de test.
                }
            }
        }
        if (orientation==1) ///si le bateau est vertical :
        {
            for (j=0; j<7;  ) ///pour la case de départ et les 6 cases en dessous des coordonnées de départ :
            {
                if((tabJoueur1[x+j][y]==' '))  ///si la case est un espace :
                {
                    j++;    ///on teste la case suivante.
                }
                else    ///sinon :
                {
                    x = rand()%9;   ///affectation à x d'un NOUVEAU nombre aléatoire entre 0 et 8.
                    y = rand()%9;   ///affectation à y d'un NOUVEAU nombre aléatoire entre 0 et 8.
                    j=0;    ///on relance le compteur de test.
                }
            }
        }

        ///placement du bateau et AFFECTATION au tableau de bateaux B1 des coordonnées :
        if (orientation==0) ///si le bateau est horizontal :
        {
            for (j=0; j<7; j++)
            {
                tabJoueur1[x][y+j]='C';
                B1[i].tabX[j]=x;
                B1[i].tabY[j]=y+j;
            }

        }
        if (orientation==1) ///si le bateau est vertical :
        {
            for (j=0; j<7; j++)
            {
                tabJoueur1[x+j][y]='C';
                B1[i].tabX[j]=x+j;
                B1[i].tabY[j]=y;
            }
        }
        B1[i].orientation=orientation;   ///affectation au bateau de son orientation finale.
    }
    ///fin de déclaration du CUIRASSE.

    ///déclaration des CROISEURS :
    for(i=1; i<3; i++)
    {
        B1[i].type=2;    ///affectation du type de bateau à la case du tableau de bateaux correspondante.
        B1[i].taille=5;  ///affectation de la taille du bateau à la case du tableau de bateaux correspondante.
        B1[i].nbTirs=0; ///initialise le compteur de tirs du bateau.
        B1[i].etat=0;   ///initialise le compteur d'état du bateau (0=intact).

        int x=0;  ///coordonées lignes.
        int y=0;  ///coordonées colonnes.
        int orientation=0;  ///0=horizontal, 1=vertical.

        x = rand()%11;   ///affectation à x d'un nombre aléatoire entre 0 et 10.
        y = rand()%11;   ///affectation à y d'un nombre aléatoire entre 0 et 10.
        orientation = rand()%2; ///affectation à orientation d'un nombre aléatoire entre 0 et 1.

        ///tests pour savoir si on peux placer le bateau ou non :
        if (orientation==0)  ///si le bateau est horizontal :
        {
            for (j=0; j<5;) ///pour la case de départ et les 4 cases à droite des coordonnées de départ :
            {
                if((tabJoueur1[x][y+j]==' '))  ///si la case est un espace :
                {
                    j++;    ///on teste la case suivante.
                }
                else    ///sinon :
                {
                    x = rand()%11;   ///affectation à x d'un NOUVEAU nombre aléatoire entre 0 et 10.
                    y = rand()%11;   ///affectation à y d'un NOUVEAU nombre aléatoire entre 0 et 10.
                    //orientation = rand()%2; ///affectation à orientation d'un NOUVEAU nombre aléatoire entre 0 et 1.
                    j=0;    ///on relance le compteur de test.
                }
            }
        }
        if (orientation==1) ///si le bateau est vertical :
        {
            for (j=0; j<5;) ///pour la case de départ et les 4 cases en dessous des coordonnées de départ :
            {
                if((tabJoueur1[x+j][y]==' '))  ///si la case est un espace :
                {
                    j++;    ///on teste la case suivante.
                }
                else    ///sinon :
                {
                    x = rand()%11;   ///affectation à x d'un NOUVEAU nombre aléatoire entre 0 et 10.
                    y = rand()%11;   ///affectation à y d'un NOUVEAU nombre aléatoire entre 0 et 10.
                    //orientation = rand()%2; ///affectation à orientation d'un NOUVEAU nombre aléatoire entre 0 et 1.
                    j=0;    ///on relance le compteur de test.
                }
            }
        }

        ///placement du bateau et AFFECTATION au tableau de bateaux B1 des coordonnées :
        if (orientation==0) ///si le bateau est horizontal :
        {
            for (j=0; j<5; j++)
            {
                tabJoueur1[x][y+j]='c';
                B1[i].tabX[j]=x;
                B1[i].tabY[j]=y+j;
            }
        }
        if (orientation==1) ///si le bateau est vertical :
        {
            for (j=0; j<5; j++)
            {
                tabJoueur1[x+j][y]='c';
                B1[i].tabX[j]=x+j;
                B1[i].tabY[j]=y;
            }
        }
        for(j=5; j<7; j++)
        {
            B1[i].tabX[j]=-1;
            B1[i].tabY[j]=-1;
        }
        B1[i].orientation=orientation;   ///affectation au bateau de son orientation finale.
    }
    ///fin de déclaration des CROISEURS.

    ///déclaration des DESTROYERS :
    for(i=3; i<6; i++)
    {
        B1[i].type=3;    ///affectation du type de bateau à la case du tableau de bateaux correspondante.
        B1[i].taille=3;  ///affectation de la taille du bateau à la case du tableau de bateaux correspondante.
        B1[i].nbTirs=0; ///initialise le compteur de tirs du bateau.
        B1[i].etat=0;   ///initialise le compteur d'état du bateau (0=intact).

        int x=0;  ///coordonées lignes.
        int y=0;  ///coordonées colonnes.
        int orientation=0;  ///0=horizontal, 1=vertical.

        x = rand()%13;   ///affectation à x d'un nombre aléatoire entre 0 et 12.
        y = rand()%13;   ///affectation à y d'un nombre aléatoire entre 0 et 12.
        orientation = rand()%2; ///affectation à orientation d'un nombre aléatoire entre 0 et 1.

        ///tests pour savoir si on peux placer le bateau ou non :
        if (orientation==0)  ///si le bateau est horizontal :
        {
            for (j=0; j<3;) ///pour la case de départ et les 2 cases à droite des coordonnées de départ :
            {
                if((tabJoueur1[x][y+j]==' '))  ///si la case est un espace :
                {
                    j++;    ///on teste la case suivante.
                }
                else    ///sinon :
                {
                    x = rand()%13;   ///affectation à x d'un NOUVEAU nombre aléatoire entre 0 et 12.
                    y = rand()%13;   ///affectation à y d'un NOUVEAU nombre aléatoire entre 0 et 12.
                    //orientation = rand()%2; ///affectation à orientation d'un NOUVEAU nombre aléatoire entre 0 et 1.
                    j=0;    ///on relance le compteur de test.
                }
            }
        }
        if (orientation==1) ///si le bateau est vertical :
        {
            for (j=0; j<3;) ///pour la case de départ et les 2 cases en dessous des coordonnées de départ :
            {
                if((tabJoueur1[x+j][y]==' '))  ///si la case est un espace :
                {
                    j++;    ///on teste la case suivante.
                }
                else    ///sinon :
                {
                    x = rand()%13;   ///affectation à x d'un NOUVEAU nombre aléatoire entre 0 et 12.
                    y = rand()%13;   ///affectation à y d'un NOUVEAU nombre aléatoire entre 0 et 12.
                    //orientation = rand()%2; ///affectation à orientation d'un NOUVEAU nombre aléatoire entre 0 et 1.
                    j=0;    ///on relance le compteur de test.
                }
            }
        }

        ///placement du bateau et AFFECTATION au tableau de bateaux B1 des coordonnées :
        if (orientation==0) ///si le bateau est horizontal :
        {
            for (j=0; j<3; j++)
            {
                tabJoueur1[x][y+j]='d';
                B1[i].tabX[j]=x;
                B1[i].tabY[j]=y+j;
            }

        }
        if (orientation==1) ///si le bateau est vertical :
        {
            for (j=0; j<3; j++)
            {
                tabJoueur1[x+j][y]='d';
                B1[i].tabX[j]=x+j;
                B1[i].tabY[j]=y;
            }

        }
        for(j=3; j<7; j++)
        {
            B1[i].tabX[j]=-1;
            B1[i].tabY[j]=-1;
        }
        B1[i].orientation=orientation;   ///affectation au bateau de son orientation finale.
    }
    ///fin de déclaration des DESTROYERS.

    ///déclaration des SOUS-MARINS :
    for(i=6; i<10; i++)
    {
        B1[i].type=4;    ///affectation du type de bateau à la case du tableau de bateaux correspondante.
        B1[i].taille=1;  ///affectation de la taille du bateau à la case du tableau de bateaux correspondante.
        B1[i].nbTirs=0; ///initialise le compteur de tirs du bateau.
        B1[i].etat=0;   ///initialise le compteur d'état du bateau (0=intact).

        int x=0;  ///coordonées lignes.
        int y=0;  ///coordonées colonnes.
        int orientation=2;

        x = rand()%15;   ///affectation à x d'un nombre aléatoire entre 0 et 14.
        y = rand()%15;   ///affectation à y d'un nombre aléatoire entre 0 et 14.

        ///tests pour savoir si on peux placer le bateau ou non :
        int t=1;    ///indice pour savoir si le placement est possible (1=pas possible, 0=possible).
        while(t==1)
        {
            if((tabJoueur1[x][y]==' '))  ///si la case est un espace :
            {
                t=0;    ///le placement est possible et on sort de la boucle.
            }
            else    ///sinon :
            {
                x = rand()%15;   ///affectation à x d'un NOUVEAU nombre aléatoire entre 0 et 14.
                y = rand()%15;   ///affectation à y d'un NOUVEAU nombre aléatoire entre 0 et 14.
            }
        }

        ///placement du bateau et affectation au tableau de bateaux des coordonnées.
        tabJoueur1[x][y]='s';
        B1[i].tabX[0]=x;
        B1[i].tabY[0]=y;
        for(j=1; j<7; j++)
        {
            B1[i].tabX[j]=-1;
            B1[i].tabY[j]=-1;
        }
        B1[i].orientation=orientation;   ///affectation au bateau de son orientation finale.
    }
    ///fin de déclaration des SOUS-MARINS.
}


///déclaration de notre fonction qui initialise les bateaux et les place aléatoirement pour le joueur 2 :
void initBateauxJ2(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur)
{
    int i=0;
    int j=0;

    ///déclaration du CUIRASSE :
    for(i=0; i<1; i++)
    {
        B2[i].type=1;    ///affectation du type de bateau à la case du tableau de bateaux correspondante.
        B2[i].taille=7;  ///affectation de la taille du bateau à la case du tableau de bateaux correspondante.
        B2[i].nbTirs=0; ///initialise le compteur de tirs du bateau.
        B2[i].etat=0;   ///initialise le compteur d'état du bateau (0=intact).

        int x=0;  ///coordonées lignes.
        int y=0;  ///coordonées colonnes.
        int orientation=0;  ///0=horizontal, 1=vertical.

        x = rand()%9;   ///affectation à x d'un nombre aléatoire entre 0 et 8.
        y = rand()%9;   ///affectation à y d'un nombre aléatoire entre 0 et 8.
        orientation = rand()%2; ///affectation à orientation d'un nombre aléatoire entre 0 et 1.

        ///tests pour savoir si on peux placer le bateau ou non :
        if (orientation==0)  ///si le bateau est horizontal :
        {
            for (j=0; j<7;) ///pour la case de départ et les 6 cases à droite des coordonnées de départ :
            {
                if((tabJoueur2[x][y+j]==' '))  ///si la case est un espace :
                {
                    j++;    ///on teste la case suivante.
                }
                else    ///sinon :
                {
                    x = rand()%9;   ///affectation à x d'un NOUVEAU nombre aléatoire entre 0 et 8.
                    y = rand()%9;   ///affectation à y d'un NOUVEAU nombre aléatoire entre 0 et 8.
                    j=0;    ///on relance le compteur de test.
                }
            }
        }
        if (orientation==1) ///si le bateau est vertical :
        {
            for (j=0; j<7;  ) ///pour la case de départ et les 6 cases en dessous des coordonnées de départ :
            {
                if((tabJoueur2[x+j][y]==' '))  ///si la case est un espace :
                {
                    j++;    ///on teste la case suivante.
                }
                else    ///sinon :
                {
                    x = rand()%9;   ///affectation à x d'un NOUVEAU nombre aléatoire entre 0 et 8.
                    y = rand()%9;   ///affectation à y d'un NOUVEAU nombre aléatoire entre 0 et 8.
                    j=0;    ///on relance le compteur de test.
                }
            }
        }

        ///placement du bateau et AFFECTATION au tableau de bateaux B2 des coordonnées :
        if (orientation==0) ///si le bateau est horizontal :
        {
            for (j=0; j<7; j++)
            {
                tabJoueur2[x][y+j]='C';
                B2[i].tabX[j]=x;
                B2[i].tabY[j]=y+j;
            }

        }
        if (orientation==1) ///si le bateau est vertical :
        {
            for (j=0; j<7; j++)
            {
                tabJoueur2[x+j][y]='C';
                B2[i].tabX[j]=x+j;
                B2[i].tabY[j]=y;
            }
        }
        B2[i].orientation=orientation;   ///affectation au bateau de son orientation finale.
    }
    ///fin de déclaration du CUIRASSE.

    ///déclaration des CROISEURS :
    for(i=1; i<3; i++)
    {
        B2[i].type=2;    ///affectation du type de bateau à la case du tableau de bateaux correspondante.
        B2[i].taille=5;  ///affectation de la taille du bateau à la case du tableau de bateaux correspondante.
        B2[i].nbTirs=0; ///initialise le compteur de tirs du bateau.
        B2[i].etat=0;   ///initialise le compteur d'état du bateau (0=intact).

        int x=0;  ///coordonées lignes.
        int y=0;  ///coordonées colonnes.
        int orientation=0;  ///0=horizontal, 1=vertical.

        x = rand()%11;   ///affectation à x d'un nombre aléatoire entre 0 et 10.
        y = rand()%11;   ///affectation à y d'un nombre aléatoire entre 0 et 10.
        orientation = rand()%2; ///affectation à orientation d'un nombre aléatoire entre 0 et 1.

        ///tests pour savoir si on peux placer le bateau ou non :
        if (orientation==0)  ///si le bateau est horizontal :
        {
            for (j=0; j<5;) ///pour la case de départ et les 4 cases à droite des coordonnées de départ :
            {
                if((tabJoueur2[x][y+j]==' '))  ///si la case est un espace :
                {
                    j++;    ///on teste la case suivante.
                }
                else    ///sinon :
                {
                    x = rand()%11;   ///affectation à x d'un NOUVEAU nombre aléatoire entre 0 et 10.
                    y = rand()%11;   ///affectation à y d'un NOUVEAU nombre aléatoire entre 0 et 10.
                    //orientation = rand()%2; ///affectation à orientation d'un NOUVEAU nombre aléatoire entre 0 et 1.
                    j=0;    ///on relance le compteur de test.
                }
            }
        }
        if (orientation==1) ///si le bateau est vertical :
        {
            for (j=0; j<5;) ///pour la case de départ et les 4 cases en dessous des coordonnées de départ :
            {
                if((tabJoueur2[x+j][y]==' '))  ///si la case est un espace :
                {
                    j++;    ///on teste la case suivante.
                }
                else    ///sinon :
                {
                    x = rand()%11;   ///affectation à x d'un NOUVEAU nombre aléatoire entre 0 et 10.
                    y = rand()%11;   ///affectation à y d'un NOUVEAU nombre aléatoire entre 0 et 10.
                    //orientation = rand()%2; ///affectation à orientation d'un NOUVEAU nombre aléatoire entre 0 et 1.
                    j=0;    ///on relance le compteur de test.
                }
            }
        }

        ///placement du bateau et AFFECTATION au tableau de bateaux B2 des coordonnées :
        if (orientation==0) ///si le bateau est horizontal :
        {
            for (j=0; j<5; j++)
            {
                tabJoueur2[x][y+j]='c';
                B2[i].tabX[j]=x;
                B2[i].tabY[j]=y+j;
            }
        }
        if (orientation==1) ///si le bateau est vertical :
        {
            for (j=0; j<5; j++)
            {
                tabJoueur2[x+j][y]='c';
                B2[i].tabX[j]=x+j;
                B2[i].tabY[j]=y;
            }
        }
        for(j=5; j<7; j++)
        {
            B2[i].tabX[j]=-1;
            B2[i].tabY[j]=-1;
        }
        B2[i].orientation=orientation;   ///affectation au bateau de son orientation finale.
    }
    ///fin de déclaration des CROISEURS.

    ///déclaration des DESTROYERS :
    for(i=3; i<6; i++)
    {
        B2[i].type=3;    ///affectation du type de bateau à la case du tableau de bateaux correspondante.
        B2[i].taille=3;  ///affectation de la taille du bateau à la case du tableau de bateaux correspondante.
        B2[i].nbTirs=0; ///initialise le compteur de tirs du bateau.
        B2[i].etat=0;   ///initialise le compteur d'état du bateau (0=intact).

        int x=0;  ///coordonées lignes.
        int y=0;  ///coordonées colonnes.
        int orientation=0;  ///0=horizontal, 1=vertical.

        x = rand()%13;   ///affectation à x d'un nombre aléatoire entre 0 et 12.
        y = rand()%13;   ///affectation à y d'un nombre aléatoire entre 0 et 12.
        orientation = rand()%2; ///affectation à orientation d'un nombre aléatoire entre 0 et 1.

        ///tests pour savoir si on peux placer le bateau ou non :
        if (orientation==0)  ///si le bateau est horizontal :
        {
            for (j=0; j<3;) ///pour la case de départ et les 2 cases à droite des coordonnées de départ :
            {
                if((tabJoueur2[x][y+j]==' '))  ///si la case est un espace :
                {
                    j++;    ///on teste la case suivante.
                }
                else    ///sinon :
                {
                    x = rand()%13;   ///affectation à x d'un NOUVEAU nombre aléatoire entre 0 et 12.
                    y = rand()%13;   ///affectation à y d'un NOUVEAU nombre aléatoire entre 0 et 12.
                    //orientation = rand()%2; ///affectation à orientation d'un NOUVEAU nombre aléatoire entre 0 et 1.
                    j=0;    ///on relance le compteur de test.
                }
            }
        }
        if (orientation==1) ///si le bateau est vertical :
        {
            for (j=0; j<3;) ///pour la case de départ et les 2 cases en dessous des coordonnées de départ :
            {
                if((tabJoueur2[x+j][y]==' '))  ///si la case est un espace :
                {
                    j++;    ///on teste la case suivante.
                }
                else    ///sinon :
                {
                    x = rand()%13;   ///affectation à x d'un NOUVEAU nombre aléatoire entre 0 et 12.
                    y = rand()%13;   ///affectation à y d'un NOUVEAU nombre aléatoire entre 0 et 12.
                    //orientation = rand()%2; ///affectation à orientation d'un NOUVEAU nombre aléatoire entre 0 et 1.
                    j=0;    ///on relance le compteur de test.
                }
            }
        }

        ///placement du bateau et AFFECTATION au tableau de bateaux B2 des coordonnées :
        if (orientation==0) ///si le bateau est horizontal :
        {
            for (j=0; j<3; j++)
            {
                tabJoueur2[x][y+j]='d';
                B2[i].tabX[j]=x;
                B2[i].tabY[j]=y+j;
            }

        }
        if (orientation==1) ///si le bateau est vertical :
        {
            for (j=0; j<3; j++)
            {
                tabJoueur2[x+j][y]='d';
                B2[i].tabX[j]=x+j;
                B2[i].tabY[j]=y;
            }

        }
        for(j=3; j<7; j++)
        {
            B2[i].tabX[j]=-1;
            B2[i].tabY[j]=-1;
        }
        B2[i].orientation=orientation;   ///affectation au bateau de son orientation finale.
    }
    ///fin de déclaration des DESTROYERS.

    ///déclaration des SOUS-MARINS :
    for(i=6; i<10; i++)
    {
        B2[i].type=4;    ///affectation du type de bateau à la case du tableau de bateaux correspondante.
        B2[i].taille=1;  ///affectation de la taille du bateau à la case du tableau de bateaux correspondante.
        B2[i].nbTirs=0; ///initialise le compteur de tirs du bateau.
        B2[i].etat=0;   ///initialise le compteur d'état du bateau (0=intact).

        int x=0;  ///coordonées lignes.
        int y=0;  ///coordonées colonnes.
        int orientation=2;

        x = rand()%15;   ///affectation à x d'un nombre aléatoire entre 0 et 14.
        y = rand()%15;   ///affectation à y d'un nombre aléatoire entre 0 et 14.

        ///tests pour savoir si on peux placer le bateau ou non :
        int t=1;    ///indice pour savoir si le placement est possible (1=pas possible, 0=possible).
        while(t==1)
        {
            if((tabJoueur2[x][y]==' '))  ///si la case est un espace :
            {
                t=0;    ///le placement est possible et on sort de la boucle.
            }
            else    ///sinon :
            {
                x = rand()%15;   ///affectation à x d'un NOUVEAU nombre aléatoire entre 0 et 14.
                y = rand()%15;   ///affectation à y d'un NOUVEAU nombre aléatoire entre 0 et 14.
            }
        }

        ///placement du bateau et affectation au tableau de bateaux des coordonnées.
        tabJoueur2[x][y]='s';
        B2[i].tabX[0]=x;
        B2[i].tabY[0]=y;
        for(j=1; j<7; j++)
        {
            B2[i].tabX[j]=-1;
            B2[i].tabY[j]=-1;
        }
        B2[i].orientation=orientation;   ///affectation au bateau de son orientation finale.
    }
    ///fin de déclaration des SOUS-MARINS.
}

