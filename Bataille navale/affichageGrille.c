#include "header.h" ///contient nos prototypes de fonctions.

///déclaration de notre fonction qui permet l'affichage de la 1ère grille :
void affichageGrille (char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur)
{
    ///déclaration des variables :
    int l=0;    ///compteur des lignes.
    int c=0;    ///compteur des colonnes.
    int i=0;    ///compteur pour les nombres et les lettres.

    system("cls");  ///réinitialise la console.

    for(l=1; l<=31; l+=2)   ///pour les lignes {1;3;...;31} :
    {
        for(c=5; c<=44; c+=3)   ///et les colonnes {5;8;...;44} :
        {
            gotoligcol(l,c+2); ///met le curseur à l'endroit donné.
            printf("%c",179);   ///affiche une barre verticale simple.
        }
    }

    for(l=4; l<=30; l+=2)   ///pour les lignes {4;6;...;30} :
    {
        for(c=1; c<=46;)   ///et les colonnes {1;3;4;6;7;...;46} :
        {
            gotoligcol(l,c+2); ///met le curseur à l'endroit donné.
            printf("%c",196);   ///affiche une barre horizontale simple.
            ///incrémentation de c :
            if(c%3==0)
                c++;
            else
                c+=2;
        }
    }

    for(l=4; l<=30; l+=2)   ///pour les lignes {4;6;...;30} :
    {
        for(c=5; c<=44; c+=3)   ///et les colonnes {5;8;11;...;44} :
        {
            gotoligcol(l,c+2); ///met le curseur à l'endroit donné.
            printf("%c",197);   ///affiche une croix.
        }
    }

    for(l=1; l<=31;)   ///pour les lignes {1;3;4;5;...;31} :
    {
        for(c=0; c<=47;)   ///et les colonnes {0;2;47} :
        {
            if(l==1 && c==0)    ///suppression d'une double barre verticale.
            {
            }
            else
            {
                gotoligcol(l,c+2); ///met le curseur à l'endroit donné.
                printf("%c",186);   ///affiche une double barre verticale.
            }
            ///incrémentation de c :
            if(c==0)
                c+=2;
            else
                c+=45;
        }
        ///incrémentation de l :
        if(l==1)
            l+=2;
        else
            l++;
    }

    for(l=0; l<=32;)   ///pour les lignes {0;2;32} :
    {
        for(c=1; c<=46;)   ///et les colonnes {1;3;4;5;...;46} :
        {
            if(l==0 && c==1)    ///suppression d'une double barre horizontale.
            {
            }
            else
            {
                gotoligcol(l,c+2); ///met le curseur à l'endroit donné.
                printf("%c",205);   ///affiche une double barre horizontale.
            }
            ///incrémentation de c :
            if(c==1)
                c+=2;
            else
                c++;
        }
        ///incrémentation de l :
        if(l==0)
                l+=2;
            else
                l+=30;
    }

    gotoligcol(2,2+2); ///met le curseur à l'endroit donné.
    printf("%c",206);   ///affiche une croix double.

    gotoligcol(32,0+2); ///met le curseur à l'endroit donné.
    printf("%c",200);   ///affiche un double coin.

    gotoligcol(0,2+2); ///met le curseur à l'endroit donné.
    printf("%c",201);   ///affiche un double coin.
    gotoligcol(2,0+2); ///met le curseur à l'endroit donné.
    printf("%c",201);   ///affiche un double coin.

    gotoligcol(0,47+2); ///met le curseur à l'endroit donné.
    printf("%c",187);   ///affiche un double coin.

    gotoligcol(32,47+2); ///met le curseur à l'endroit donné.
    printf("%c",188);   ///affiche un double coin.

    gotoligcol(32,2+2); ///met le curseur à l'endroit donné.
    printf("%c",202);   ///affiche un double T.

    gotoligcol(2,47+2); ///met le curseur à l'endroit donné.
    printf("%c",185);   ///affiche un double T.

    ///affichage des nombres :
    for(i=0; i<=14; i++)
    {
        if(i<10)
        {
            gotoligcol(1,4+3*i+2); ///met le curseur à l'endroit donné.
            printf("%d",i); ///affiche la valeur de i.
        }
        else
        {
            gotoligcol(1,3+3*i+2); ///met le curseur à l'endroit donné.
            printf("%d",i); ///affiche la valeur de i.
        }
    }

    ///affichage des lettres :
    for(i=0; i<=14; i++)
    {
        gotoligcol(3+2*i,1+2); ///met le curseur à l'endroit donné.
        printf("%c",i+97);  ///affiche le caractère correspondant à i+97 dans la table ASCII.
    }

    ///affichage des cases (contenance du tableau tabJoueur1) :
    for(l=0; l<15; l++)
    {
        for(c=0; c<15; c++)
        {
            gotoligcol(2*l+3,3*c+5);    ///place le curseur sur le premier point de chaque case.
            printf("%c",tabJoueur1[l][c]);  ///affiche la valeur de la case du tableau correspondante.
            gotoligcol(2*l+3,3*c+6);    ///place le curseur sur le deuxième point de chaque case.
            printf("%c",tabJoueur1[l][c]);  ///affiche la valeur de la case du tableau correspondante.
        }
    }

    affichageGrille2(tabJoueur1, tabCibleJoueur1, tabJoueur2, tabCibleJoueur2, B1, B2, indiceJoueur);
}

///déclaration de notre fonction qui permet l'affichage de la 2ème grille (grille CIBLE) :
void affichageGrille2 (char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur)
{
    ///déclaration des variables :
    int l=0;    ///compteur des lignes.
    int c=0;    ///compteur des colonnes.
    int i=0;    ///compteur pour les nombres et les lettres.

    for(l=1; l<=31; l+=2)   ///pour les lignes {1;3;...;31} :
    {
        for(c=5; c<=44; c+=3)   ///et les colonnes {5;8;...;44} :
        {
            gotoligcol(l,c+70); ///met le curseur à l'endroit donné + applique un décalage de 70 vers la droite.
            printf("%c",179);   ///affiche une barre verticale simple.
        }
    }

    for(l=4; l<=30; l+=2)   ///pour les lignes {4;6;...;30} :
    {
        for(c=1; c<=46;)   ///et les colonnes {1;3;4;6;7;...;46} :
        {
            gotoligcol(l,c+70); ///met le curseur à l'endroit donné + applique un décalage de 70 vers la droite.
            printf("%c",196);   ///affiche une barre horizontale simple.
            ///incrémentation de c :
            if(c%3==0)
                c++;
            else
                c+=2;
        }
    }

    for(l=4; l<=30; l+=2)   ///pour les lignes {4;6;...;30} :
    {
        for(c=5; c<=44; c+=3)   ///et les colonnes {5;8;11;...;44} :
        {
            gotoligcol(l,c+70); ///met le curseur à l'endroit donné + applique un décalage de 70 vers la droite.
            printf("%c",197);   ///affiche une croix.
        }
    }

    for(l=1; l<=31;)   ///pour les lignes {1;3;4;5;...;31} :
    {
        for(c=0; c<=47;)   ///et les colonnes {0;2;47} :
        {
            if(l==1 && c==0)    ///suppression d'une double barre verticale.
            {
            }
            else
            {
                gotoligcol(l,c+70); ///met le curseur à l'endroit donné + applique un décalage de 70 vers la droite.
                printf("%c",186);   ///affiche une double barre verticale.
            }
            ///incrémentation de c :
            if(c==0)
                c+=2;
            else
                c+=45;
        }
        ///incrémentation de l :
        if(l==1)
            l+=2;
        else
            l++;
    }

    for(l=0; l<=32;)   ///pour les lignes {0;2;32} :
    {
        for(c=1; c<=46;)   ///et les colonnes {1;3;4;5;...;46} :
        {
            if(l==0 && c==1)    ///suppression d'une double barre horizontale.
            {
            }
            else
            {
                gotoligcol(l,c+70); ///met le curseur à l'endroit donné + applique un décalage de 70 vers la droite.
                printf("%c",205);   ///affiche une double barre horizontale.
            }
            ///incrémentation de c :
            if(c==1)
                c+=2;
            else
                c++;
        }
        ///incrémentation de l :
        if(l==0)
                l+=2;
            else
                l+=30;
    }

    gotoligcol(2,2+70); ///met le curseur à l'endroit donné + applique un décalage de 70 vers la droite.
    printf("%c",206);   ///affiche une croix double.

    gotoligcol(32,0+70); ///met le curseur à l'endroit donné + applique un décalage de 70 vers la droite.
    printf("%c",200);   ///affiche un double coin.

    gotoligcol(0,2+70); ///met le curseur à l'endroit donné + applique un décalage de 70 vers la droite.
    printf("%c",201);   ///affiche un double coin.
    gotoligcol(2,0+70); ///met le curseur à l'endroit donné + applique un décalage de 70 vers la droite.
    printf("%c",201);   ///affiche un double coin.

    gotoligcol(0,47+70); ///met le curseur à l'endroit donné + applique un décalage de 70 vers la droite.
    printf("%c",187);   ///affiche un double coin.

    gotoligcol(32,47+70); ///met le curseur à l'endroit donné + applique un décalage de 70 vers la droite.
    printf("%c",188);   ///affiche un double coin.

    gotoligcol(32,2+70); ///met le curseur à l'endroit donné + applique un décalage de 70 vers la droite.
    printf("%c",202);   ///affiche un double T.

    gotoligcol(2,47+70); ///met le curseur à l'endroit donné + applique un décalage de 70 vers la droite.
    printf("%c",185);   ///affiche un double T.

    ///affichage des nombres :
    for(i=0; i<=14; i++)
    {
        if(i<10)
        {
            gotoligcol(1,4+3*i+70); ///met le curseur à l'endroit donné + applique un décalage de 70 vers la droite.
            printf("%d",i); ///affiche la valeur de i.
        }
        else
        {
            gotoligcol(1,3+3*i+70); ///met le curseur à l'endroit donné + applique un décalage de 70 vers la droite.
            printf("%d",i); ///affiche la valeur de i.
        }
    }

    ///affichage des lettres :
    for(i=0; i<=14; i++)
    {
        gotoligcol(3+2*i,1+70); ///met le curseur à l'endroit donné + applique un décalage de 70 vers la droite.
        printf("%c",i+97);  ///affiche le caractère correspondant à i+97 dans la table ASCII.
    }

    ///affichage des cases (contenance du tableau tabJoueur1) :
    for(l=0; l<15; l++)
    {
        for(c=0; c<15; c++)
        {
            gotoligcol(2*l+3,3*c+73);    ///place le curseur sur le premier point de chaque case.
            printf("%c",tabCibleJoueur1[l][c]);  ///affiche la valeur de la case du tableau correspondante.
            gotoligcol(2*l+3,3*c+74);    ///place le curseur sur le deuxième point de chaque case.
            printf("%c",tabCibleJoueur1[l][c]);  ///affiche la valeur de la case du tableau correspondante.
        }
    }

    gotoligcol(33,0);   ///replace le curseur en dessous de la 1ère grille.
}
