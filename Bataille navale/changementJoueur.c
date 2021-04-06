#include "header.h"

///D�claration de notre fonction qui permet le changement de joueurs (FONCTIONNE) :
void changementJoueur(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur, int *ligneFusee, int *colonneFusee, int *indiceFusee, int *indiceBatCoule, int *numBatCoule, int *typePartie)
{
    ///D�claration des variables de la fonction :
    int s=0;    ///valeur saisie.
    char tabTampon[15][15]; ///Tableau de char tampon qui va permettre l'�change des tableaux des joueurs.
    char tabTamponCible[15][15]; ///Tableau de char tampon qui va permettre l'�change des tableaux de cible des joueurs.
    int i=0;    ///valeur compteur.
    int j=0;    ///valeur compteur.
    int indiceJoueurTampon; ///variable qui permet l'�change de indiceJoueur.
    int comptBatCoule1=0;  ///Compte le nombre de bateaux coul�s pour le joueur 1.
    int comptBatCoule2=0;  ///Compte le nombre de bateaux coul�s pour le joueur 2.

    int o;  ///Compteur pour remplacer les cases du bateau coul� :

    ///Test pour savoir si la partie est termin�e :
    for(i=0; i<10; i++)
    {
        if(B1[i].etat==(-1))
        {
            comptBatCoule1++;
        }
        if(B2[i].etat==(-1))
        {
            comptBatCoule2++;
        }
    }

    if(comptBatCoule1==10)
     {
        while(s==0)
        {
            printf("\tTous les bateaux du joueur 1 ont %ct%c coul%cs !\n\n", 130, 130, 130);
            printf("\t\tLe joueur 2 remporte la partie !!!\n\n");

            printf("Tapez 1 pour revenir au menu : ");

            scanf("%d", &s);
            if(s==1)
            {
                menu(tabJoueur1, tabCibleJoueur1, tabJoueur2, tabCibleJoueur2, B1, B2, indiceJoueur);
            }
            else
            {
                s=0;
            }
        }
    }

    if(comptBatCoule2==10)
    {
        while(s==0)
        {
            printf("\tTous les bateaux du joueur 2 ont %ct%c coul%cs !\n\n", 130, 130, 130);
            printf("\t\tLe joueur 1 remporte la partie !!!\n\n");

            printf("Tapez 1 pour revenir au menu : ");

            scanf("%d", &s);
            if(s==1)
            {
                menu(tabJoueur1, tabCibleJoueur1, tabJoueur2, tabCibleJoueur2, B1, B2, indiceJoueur);
            }
            else
            {
                s=0;
            }
        }
    }

    ///Re-placement du brouillard si une fus�e �clairante a �t� tir�e au tour pr�c�dent :
    if(*indiceFusee==1) ///Si une fus�e �clairante a �t� tir�e au tour pr�c�dent :
    {
        for(i=0; i<4; i++)  ///Pour i allant de 0 � 3 :
        {
            for(j=0; j<4; j++)  ///Et j allant de 0 � 3 :
            {
                if(tabCibleJoueur1[*ligneFusee+i][*colonneFusee+j]=='X')    ///Si la case anciennement d�voil�e est un X :
                {
                    ///On ne fait rien.
                }
                else    ///Si la case anciennement d�voil�e est une case "mer" ou un bateau :
                {
                    tabCibleJoueur1[*ligneFusee+i][*colonneFusee+j]=176;    ///On remet une case "brouillard".
                }
            }
        }
        *indiceFusee=0; ///On remet l'indice fus�e tir�e � 0.
    }

    ///Remplacement des icones "coul�" par des icones "� l'eau" si un bateau a �t� coul� au tour pr�c�dent :

    ///Si c'�tait le tour du joueur 1 :
    if(*indiceJoueur==1)
    {
        if(*indiceBatCoule==1)  ///Si un bateau a �t� coul� au tour pr�c�dent :
        {
            if(B2[*numBatCoule].orientation==0) ///Si le bateau coul� �tait horizontal :
            {
                for(o=0; o<B2[*numBatCoule].taille; o++)    ///Pour toutes les cases du bateau :
                {
                    tabCibleJoueur1[B2[*numBatCoule].tabX[0]][B2[*numBatCoule].tabY[0]+o]=126;  ///On affiche un vague sur le tableau cible.
                    *indiceBatCoule=0;
                }
            }
            if(B2[*numBatCoule].orientation==1) ///Si le bateau coul� �tait vertical :
            {
                for(o=0; o<B2[*numBatCoule].taille; o++)    ///Pour toutes les cases du bateau :
                {
                    tabCibleJoueur1[B2[*numBatCoule].tabX[0]+o][B2[*numBatCoule].tabY[0]]=126;  ///On affiche un vague sur le tableau cible.
                    *indiceBatCoule=0;
                }

            }
            if(B2[*numBatCoule].orientation==2) ///Si le bateau coul� �tait � la fois horizontal et vertical (cas des sous-marins) :
            {
                tabCibleJoueur1[B2[*numBatCoule].tabX[0]][B2[*numBatCoule].tabY[0]]=126;  ///On affiche un vague sur le tableau cible.
                *indiceBatCoule=0;
            }

            B2[*numBatCoule].etat=-1;   ///d�clare le bateau coul�.
        }
    }

    ///Si c'�tait le tour du joueur 2 :
    if(*indiceJoueur==2)
    {
        if(*indiceBatCoule==1)  ///Si un bateau a �t� coul� au tour pr�c�dent :
        {
            if(B1[*numBatCoule].orientation==0) ///Si le bateau coul� �tait horizontal :
            {
                for(o=0; o<B1[*numBatCoule].taille; o++)    ///Pour toutes les cases du bateau :
                {
                    tabCibleJoueur1[B1[*numBatCoule].tabX[0]][B1[*numBatCoule].tabY[0]+o]=126;  ///On affiche un vague sur le tableau cible.
                    *indiceBatCoule=0;
                }
            }
            if(B1[*numBatCoule].orientation==1) ///Si le bateau coul� �tait vertical :
            {
                for(o=0; o<B1[*numBatCoule].taille; o++)    ///Pour toutes les cases du bateau :
                {
                    tabCibleJoueur1[B1[*numBatCoule].tabX[0]+o][B1[*numBatCoule].tabY[0]]=126;  ///On affiche un vague sur le tableau cible.
                    *indiceBatCoule=0;
                }

            }
            if(B1[*numBatCoule].orientation==2) ///Si le bateau coul� �tait � la fois horizontal et vertical (cas des sous-marins) :
            {
                tabCibleJoueur1[B1[*numBatCoule].tabX[0]][B1[*numBatCoule].tabY[0]]=126;  ///On affiche un vague sur le tableau cible.
                *indiceBatCoule=0;
            }

            B1[*numBatCoule].etat=-1;   ///d�clare le bateau coul�.
        }
    }

    if(*indiceJoueur==1)    ///Si c'�tait le joueur 1 qui jouait :
    {
        indiceJoueurTampon=2;
    }
    if(*indiceJoueur==2)    ///Si c'�tait le joueur 2 qui jouait :
    {
        indiceJoueurTampon=1;
    }

    *indiceJoueur=indiceJoueurTampon;

    while(s==0) ///D�but du blindage.
    {
        if(*typePartie==2 && *indiceJoueur==1)    ///Si on est en JcO et que l'ordinateur vient de jouer :
        {
            gotoligcol(9,1);
            printf("L'ordinateur a jou%c !", 130);

            gotoligcol(11,1);
            printf("C'est maintenant au tour du joueur !\n\n");

            gotoligcol(13,9);
            printf("Tapez 1 pour jouer : ");
            scanf("%d", &s);
        }

        if(*typePartie==2 && *indiceJoueur==2)    ///Si on est en JcO et que le joueur vient de jouer :
        {
            printf("\tVous avez jou%c !\n", 130);
            printf("\tC'est maintenant au tour de l'ordinateur !\n\n");
            printf("\t\tTapez 1 pour faire jouer l'ordinateur : ");
            scanf("%d", &s);
        }

        if(*typePartie==1)    ///Si on est en JcJ :
        {
            printf("\tVous avez jou%c !\n", 130);
            printf("\tC'est maintenant au tour du joueur %d !\n\n", *indiceJoueur);
            printf("\t\tTapez 1 pour changer de joueur : ");
            scanf("%d", &s);

            ///Affichage d'un �cran "passez l'ordinateur au joueur "1/2" :
            system("cls");

            if(*indiceJoueur==2)
            {
                gotoligcol(2,50);
                printf("Passez l'ordinateur au joueur 2.");
                gotoligcol(4,50);
                printf("Tapez 1 pour continuer : ");
                scanf("%d", &s);
            }
            if(*indiceJoueur==1)
            {
                gotoligcol(2,50);
                printf("Passez l'ordinateur au joueur 1.");
                gotoligcol(4,50);
                printf("Tapez 1 pour continuer : ");
                scanf("%d", &s);
            }
        }


        if(s==1)
        {
            ///Echange des tableaux des joueurs :
            for(i=0; i<15; i++)
                for(j=0; j<15; j++)
                    tabTampon[i][j]=tabJoueur1[i][j];

            for(i=0; i<15; i++)
                for(j=0; j<15; j++)
                    tabJoueur1[i][j]=tabJoueur2[i][j];

            for(i=0; i<15; i++)
                for(j=0; j<15; j++)
                    tabJoueur2[i][j]=tabTampon[i][j];

            ///Echange des tableaux de cible des joueurs :
            for(i=0; i<15; i++)
                for(j=0; j<15; j++)
                    tabTamponCible[i][j]=tabCibleJoueur1[i][j];

            for(i=0; i<15; i++)
                for(j=0; j<15; j++)
                    tabCibleJoueur1[i][j]=tabCibleJoueur2[i][j];

            for(i=0; i<15; i++)
                for(j=0; j<15; j++)
                    tabCibleJoueur2[i][j]=tabTamponCible[i][j];


            if(*typePartie==1)
            {
                affichageGrille(tabJoueur1,tabCibleJoueur1,tabJoueur2,tabCibleJoueur2, B1, B2, indiceJoueur);
                choixAction(tabJoueur1,tabCibleJoueur1,tabJoueur2,tabCibleJoueur2, B1, B2, indiceJoueur, typePartie);
            }

            if(*typePartie==2)
            {
                if(*indiceJoueur==2)
                {
                    actionAleaIA(tabJoueur1, tabCibleJoueur1, tabJoueur2, tabCibleJoueur2, B1, B2, indiceJoueur, typePartie);
                }
                if(*indiceJoueur==1)
                {
                    affichageGrille(tabJoueur1,tabCibleJoueur1,tabJoueur2,tabCibleJoueur2, B1, B2, indiceJoueur);
                    choixAction(tabJoueur1,tabCibleJoueur1,tabJoueur2,tabCibleJoueur2, B1, B2, indiceJoueur, typePartie);
                }
            }



        }
        else    ///Fin du blindage.
        {
            ///Permet de nettoyer la zone d'affichage de texte :
            gotoligcol(33,0);   ///Va au d�but de la zone de texte.
            for(i=0; i<11; i++) ///Pour les 20 lignes :
            {
                for(j=0; j<15; j++)    ///Et les 120 colonnes de la console :
                {
                    printf("        ");    ///Afficher des espaces sur toutes la ligne.
                }
                printf("\n");   ///Recommence sur la ligne en dessous.
            }
            gotoligcol(33,0);

            printf("\tSaisie incorrecte !\n\n");
            s=0;
        }
    }
}
