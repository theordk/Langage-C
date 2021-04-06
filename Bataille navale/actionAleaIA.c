#include "header.h"

void actionAleaIA(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur, int *typePartie)
{
    int i;
    int temp;
    int ligneFusee; ///Variable qui prend la valeur de la ligne � laquelle une fus�e �clairante est tir�e.
    int colonneFusee;   ///Variable qui prend la valeur de la colonne � laquelle une fus�e �clairante est tir�e.
    int indiceFusee=0;  ///Variable qui indique si une fus�e �clairante a �t� tir�e (0=non, 1=oui).

    int indiceBatCoule=0;   ///Indice qui indique si un bateau a �t� coul� � ce tour (0=non, 1=oui, permet de remettre des icones "� l'eau" au tour suivant).
    int numBatCoule=0;    ///Variable qui contient le num�ro du bateau adverse coul� :

    system("cls");

    temp=rand()%10;

    if(temp==0)
        i=2;
    if(temp!=0)
        i=1;

    switch (i)  /// 1 ere boucle pour choisir si le joueur veut attaquer ou d�placer son bateau
    {
    case 1 :
        attaqueAleaIA(tabJoueur1,tabCibleJoueur1,tabJoueur2,tabCibleJoueur2, B1, B2, indiceJoueur, &ligneFusee, &colonneFusee, &indiceFusee, &indiceBatCoule, &numBatCoule);
        break;
    case 2 :
        deplacementAleaIA(tabJoueur1,tabCibleJoueur1,tabJoueur2,tabCibleJoueur2, B1, B2, indiceJoueur);
        break;
    }

    changementJoueur(tabJoueur1,tabCibleJoueur1,tabJoueur2,tabCibleJoueur2, B1, B2, indiceJoueur, &ligneFusee, &colonneFusee, &indiceFusee, &indiceBatCoule, &numBatCoule, typePartie);    ///On appelle la fonction de changement de joueur une fois que l'action a �t� ex�cut�e.

}


///D�claration de notre fonction attaque pour l'ordinateur :
void attaqueAleaIA (char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur, int *ligneFusee, int *colonneFusee, int *indiceFusee, int *indiceBatCoule, int *numBatCoule)
{
    ///D�claration des variables de la fonction :
    int ligne=0, colonne=0; ///Ligne et colonne du bateau attaquant.

    int i,j;    ///Variables pour les boucles.
    int k, l; ///Variables pour les boucles.

    int m, n; ///Variables pour les boucles de parcours des bateaux adverses et des leurs coordonn�es.
    int o;  ///Variable pour la boucle de parcours des cases du bateau adverse pour savoir s'il est coul�.

    char charLigne;


    int test=0; ///Variable pour savoir si la case s�l�ctionn�e en tireur est valide.
    int resultatRecherche=0;   ///Variable pour le blindage.
    int ligne_attaque;  ///Ligne du bateau.
    int colonne_attaque;    ///Colonne du bateau.
    int coordBateauToucheX; ///Coordonn�e X de la case touch�e.
    int coordBateauToucheY; ///Coordonn�e Y de la case touch�e.
    int numeroDuBateau;     ///Variable qui indique quel bateau attaque.
    int possibiliteTir=0;   ///Variable qui indique si l'attaque est possible (0=impossible, 1=possible).

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
    gotoligcol(1,1);   ///Revient au d�but de la zone de texte.

    printf("L'ordinateur a choisi d'attaquer.\n");


    while (test==0) ///Tant que la case choisie n'est pas valide.
    {
        /// L'utilisateur rentre la ligne et la colonne du bateau qui va attaquer :

        ligne=rand()%15;

        colonne=rand()%15;

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
        gotoligcol(33,0);   ///Revient au d�but de la zone de texte.

        ///Si la case est vide ou a �t� touch�e :
        if (tabJoueur1[ligne][colonne]==' ' || tabJoueur1[ligne][colonne]=='X')
        {
            test=0;

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
            gotoligcol(33,0);   ///Revient au d�but de la zone de texte.


        }
        else    ///Sinon :
        {
            test=1;
        }
    }


    /// /!\ SI C'EST LE TOUR DU JOUEUR 2 /!\ :
    if(*indiceJoueur==2)
    {
        for (i=0; i<10; i++)  ///Pour chacuns des bateaux du tableau de bateau :
        {
            for (j=0; j<7; j++)   ///Et pour chacunes des coordonn�es X et Y des bateaux :
            {
                if (B2[i].tabX[j]==ligne && B2[i].tabY[j]==colonne) ///Si les coordonn�es d'un bateau correspondent aux coordonn�es entr�es :
                {
                    resultatRecherche=1;    ///On indique que la case contient un bateau.
                    numeroDuBateau=i;   ///On r�cup�re le numero du bateau trouv�.
                    j=7;    ///On sort de la boucle de j.
                    i=10;   ///On sort de la boucle de i.
                }
            }
        }
        if(resultatRecherche==1)  ///si la case contient un bateau :
        {

            ///si c'est un CUIRASSE :
            if(B2[numeroDuBateau].type==1)
            {
                gotoligcol(3,1);
                printf("L'ordinateur a attaqu%c avec un Cuirass%c.\n\n", 130, 130);



                ///TESTS POUR SAVOIR SI LA CASE ATTAQUEE EST VALIDE :

                ///Si les coordonn�es choisies ne d�passent pas ni � droite ni en bas :
                while(possibiliteTir==0)
                {


                    ligne_attaque=rand()%13;

                    colonne_attaque=rand()%13;

                    if(ligne_attaque>=0 && ligne_attaque<=12 && colonne_attaque>=0 && colonne_attaque<=12)
                    {
                        possibiliteTir=1;   ///Alors le tir est possible.

                    }
                    else
                    {
                        possibiliteTir=0;   ///Alors le tir est impossible.

                    }
                }

                ///TESTS POUR SAVOIR SI LE TIR EST REUSSI :
                for (k=0; k<3; k++) ///Pour k allant de 0 � 2 :
                {
                    for (l=0; l<3; l++) ///Et l allant de 0 � 2 :
                    {
                        ///Si la cases touch�e est un espace ou un sous-marin :
                        if ((tabJoueur2[ligne_attaque+k][colonne_attaque+l]==' ') || (tabJoueur2[ligne_attaque+k][colonne_attaque+l]=='s'))
                        {
                            tabCibleJoueur1[ligne_attaque+k][colonne_attaque+l]=126;    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                            B2[numeroDuBateau].nbTirs++;    ///On incr�mente le compteur de tir du bateau.
                        }

                        else
                        {

                            ///Si les cases touch�es �taient d�j� touch�es :
                            if((tabJoueur2[ligne_attaque+k][colonne_attaque+l]=='X'))
                            {
                                tabCibleJoueur1[ligne_attaque+k][colonne_attaque+l]='X';    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                                B2[numeroDuBateau].nbTirs++;    ///On incr�mente le compteur de tir du bateau.
                            }

                            ///Si la case touch�e contient un bateau :
                            else
                            {
                                tabCibleJoueur1[ligne_attaque+k][colonne_attaque+l]='X';    ///Alors on affiche un X sur le tableau cible du joueur 1.
                                tabJoueur2[ligne_attaque+k][colonne_attaque+l]='X'; ///Alors on affiche un X sur le tableau du joueur 2.
                                B2[numeroDuBateau].nbTirs++;    ///On incr�mente le compteur de tir du bateau.

                                ///Tests pour savoir si des bateaux sont coul�s :

                                coordBateauToucheX=ligne_attaque+k; ///On r�cup�re la coordonn�e de la ligne touch�e.
                                coordBateauToucheY=colonne_attaque+l;   ///On r�cup�re la coordonn�e de la colonne touch�e.

                                ///On cherche quel bateau adverse a �t� touch� :
                                for (m=0; m<10; m++)  ///Pour chacuns des bateaux du tableau de bateau adverse :
                                {
                                    for (n=0; n<7; n++)   ///Et pour chacunes des coordonn�es X et Y des bateaux :
                                    {
                                        if(B1[m].tabX[n]==coordBateauToucheX && B1[m].tabY[n]==coordBateauToucheY)  ///Si il y a correspondance avec la case attaqu�e :
                                        {
                                            B1[m].etat++;   ///Alors on incr�mente le compteur d'�tat du bateau.

                                        }
                                    }

                                    if(B1[m].etat==B1[m].taille)    ///Si le bateau a �t� touch� autant de fois qu'il n'a de cases :
                                    {
                                        ///Alors le bateau est COULE et on va l'afficher sur le tableau cible ainsi que le supprimer du tableau du joueur 2 :

                                        if(B1[m].orientation==0)    ///Si le bateau adverse �tait horizontal :
                                        {
                                            for(o=0; o<B1[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                            {
                                                tabCibleJoueur1[B1[m].tabX[0]][B1[m].tabY[0]+o]=178;  ///On affiche un bloc sur le tableau cible.
                                                tabJoueur2[B1[m].tabX[0]][B1[m].tabY[0]+o]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                                *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a �t� coul� � ce tour � 1.
                                                *numBatCoule=m;
                                            }
                                        }

                                        if(B1[m].orientation==1)    ///Si le bateau adverse �tait vertical :
                                        {
                                            for(o=0; o<B1[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                            {
                                                tabCibleJoueur1[B1[m].tabX[0]+o][B1[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                                tabJoueur2[B1[m].tabX[0]+o][B1[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                                *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a �t� coul� � ce tour � 1.
                                                *numBatCoule=m;
                                            }
                                        }

                                        if(B1[m].orientation==2)    ///Si le bateau adverse �tait � la fois horizontal et vertical (cas des sous-marins) :
                                        {
                                            tabCibleJoueur1[B1[m].tabX[0]][B1[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                            tabJoueur2[B1[m].tabX[0]][B1[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                            *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a �t� coul� � ce tour � 1.
                                            *numBatCoule=m;
                                        }

                                    }
                                }

                            }
                        }
                    }
                }
            }


            ///si c'est un CROISEUR :
            if(B2[numeroDuBateau].type==2)
            {
                gotoligcol(3,1);
                printf("L'ordinateur a attaqu%c avec un croiseur.", 130);



                ///TESTS POUR SAVOIR SI LA CASE ATTAQUEE EST VALIDE :

                ///Si les coordonn�es choisies ne d�passent pas ni � droite ni en bas :
                while(possibiliteTir==0)
                {


                    ligne_attaque=rand()%14;

                    colonne_attaque=rand()%14;

                    if(ligne_attaque>=0 && ligne_attaque<=13 && colonne_attaque>=0 && colonne_attaque<=13)
                    {
                        possibiliteTir=1;   ///Alors le tir est possible.

                    }
                    else
                    {
                        possibiliteTir=0;   ///Alors le tir est impossible.


                    }
                }

                ///TESTS POUR SAVOIR SI LE TIR EST REUSSI :
                for (k=0; k<2; k++)
                {
                    for (l=0; l<2; l++)
                    {
                        ///Si les cases touch�es sont des espaces ou des sous-marins :
                        if ((tabJoueur2[ligne_attaque+k][colonne_attaque+l]==' ') || (tabJoueur2[ligne_attaque+k][colonne_attaque+l]=='s'))
                        {
                            tabCibleJoueur1[ligne_attaque+k][colonne_attaque+l]=126;    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                            B2[numeroDuBateau].nbTirs++;    ///On incr�mente le compteur de tir du bateau.
                        }

                        else
                        {

                            ///Si les cases touch�es �taient d�j� touch�es :
                            if((tabJoueur2[ligne_attaque+k][colonne_attaque+l]=='X'))
                            {
                                tabCibleJoueur1[ligne_attaque+k][colonne_attaque+l]='X';    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                                B2[numeroDuBateau].nbTirs++;    ///On incr�mente le compteur de tir du bateau.
                            }

                            ///Si les cases touch�es contiennent un bateau :
                            else
                            {
                                tabCibleJoueur1[ligne_attaque+k][colonne_attaque+l]='X';    ///Alors on affiche un X sur le tableau cible du joueur 1.
                                tabJoueur2[ligne_attaque+k][colonne_attaque+l]='X'; ///Alors on affiche un X sur le tableau du joueur 2.
                                B2[numeroDuBateau].nbTirs++;    ///On incr�mente le compteur de tir du bateau.

                                ///Tests pour savoir si des bateaux sont coul�s :

                                coordBateauToucheX=ligne_attaque+k; ///On r�cup�re la coordonn�e de la ligne touch�e.
                                coordBateauToucheY=colonne_attaque+l;   ///On r�cup�re la coordonn�e de la colonne touch�e.

                                ///On cherche quel bateau adverse a �t� touch� :
                                for (m=0; m<10; m++)  ///Pour chacuns des bateaux du tableau de bateau adverse :
                                {
                                    for (n=0; n<7; n++)   ///Et pour chacunes des coordonn�es X et Y des bateaux :
                                    {
                                        if(B1[m].tabX[n]==coordBateauToucheX && B1[m].tabY[n]==coordBateauToucheY)  ///Si il y a correspondance avec la case attaqu�e :
                                        {
                                            B1[m].etat++;   ///Alors on incr�mente le compteur d'�tat du bateau.

                                        }
                                    }

                                    if(B1[m].etat==B1[m].taille)    ///Si le bateau a �t� touch� autant de fois qu'il n'a de cases :
                                    {
                                        ///Alors le bateau est COULE et on va l'afficher sur le tableau cible ainsi que le supprimer du tableau du joueur 2 :

                                        if(B1[m].orientation==0)    ///Si le bateau adverse �tait horizontal :
                                        {
                                            for(o=0; o<B1[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                            {
                                                tabCibleJoueur1[B1[m].tabX[0]][B1[m].tabY[0]+o]=178;  ///On affiche un bloc sur le tableau cible.
                                                tabJoueur2[B1[m].tabX[0]][B1[m].tabY[0]+o]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                                *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a �t� coul� � ce tour � 1.
                                                *numBatCoule=m;
                                            }
                                        }

                                        if(B1[m].orientation==1)    ///Si le bateau adverse �tait vertical :
                                        {
                                            for(o=0; o<B1[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                            {
                                                tabCibleJoueur1[B1[m].tabX[0]+o][B1[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                                tabJoueur2[B1[m].tabX[0]+o][B1[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                                *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a �t� coul� � ce tour � 1.
                                                *numBatCoule=m;
                                            }
                                        }

                                        if(B1[m].orientation==2)    ///Si le bateau adverse �tait � la fois horizontal et vertical (cas des sous-marins) :
                                        {
                                            tabCibleJoueur1[B1[m].tabX[0]][B1[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                            tabJoueur2[B1[m].tabX[0]][B1[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                            *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a �t� coul� � ce tour � 1.
                                            *numBatCoule=m;
                                        }

                                    }
                                }
                            }
                        }
                    }

                }
            }

            ///si c'est un DESTROYER :
            if(B2[numeroDuBateau].type==3)
            {

                ///Si c'est son PREMIER TIR :
                if(B2[numeroDuBateau].nbTirs==0)
                {
                    gotoligcol(3,1);
                    printf("L'ordinateur a lanc%c une fus%ce %cclairante avec un destroyer.", 130, 130, 130);

                    ///TESTS POUR SAVOIR SI LA CASE ATTAQUEE EST VALIDE :

                    ///Tant que la saisie n'est pas valid�e :
                    while(possibiliteTir==0)
                    {


                        ligne_attaque=rand()%12;

                        colonne_attaque=rand()%12;

                        ///Si les coordonn�es choisies ne d�passent pas ni � droite ni en bas :
                        if(ligne_attaque>=0 && ligne_attaque<=11 && colonne_attaque>=0 && colonne_attaque<=11)
                        {
                            possibiliteTir=1;   ///Alors le tir est possible.

                        }
                        ///Sinon :
                        else
                        {
                            possibiliteTir=0;   ///Alors le tir est impossible.

                        }
                    }

                    ///Si le tir est possible :
                    if(possibiliteTir==1)
                    {
                        ///Pour un carr� de 4x4 :
                        for(k=0; k<4; k++)
                        {
                            for(l=0; l<4; l++)
                            {
                                ///On montre la contenance du tableau du joueur 2 dans le tableau cible du joueur 1:
                                tabCibleJoueur1[ligne_attaque+k][colonne_attaque+l]=tabJoueur2[ligne_attaque+k][colonne_attaque+l];
                                ///Op�rations sur des varaibles qui vont permettre de remettre la brouillard au tour suivant :
                                *ligneFusee=ligne_attaque;
                                *colonneFusee=colonne_attaque;
                                *indiceFusee=1;

                            }
                        }
                    }
                }

                ///Si ce n'est PAS son PREMIER TIR :
                if(B2[numeroDuBateau].nbTirs!=0)
                {

                    gotoligcol(3,1);
                    printf("L'ordinateur a attaqu%c avec un destroyer.", 130);

                    ///TESTS POUR SAVOIR SI LA CASE ATTAQUEE EST VALIDE :

                    ///Tant que la saisie n'est pas valid�e :
                    while(possibiliteTir==0)
                    {


                        ligne_attaque=rand()%15;

                        colonne_attaque=rand()%15;

                        ///Si les coordonn�es choisies ne d�passent pas ni � droite ni en bas :
                        if(ligne_attaque>=0 && ligne_attaque<=14 && colonne_attaque>=0 && colonne_attaque<=14)
                        {
                            possibiliteTir=1;   ///Alors le tir est possible.

                        }
                        ///Sinon :
                        else
                        {
                            possibiliteTir=0;   ///Alors le tir est impossible.


                        }
                    }

                    ///TESTS POUR SAVOIR SI LE TIR EST REUSSI :

                    ///Si la cases touch�e est un espace ou un sous-marin :
                    if ((tabJoueur2[ligne_attaque][colonne_attaque]==' ') || (tabJoueur2[ligne_attaque][colonne_attaque]=='s'))
                    {
                        tabCibleJoueur1[ligne_attaque][colonne_attaque]=126;    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                        B2[numeroDuBateau].nbTirs++;    ///On incr�mente le compteur de tir du bateau.
                    }

                    else
                    {

                        ///Si la case touch�e �tait d�j� touch�e :
                        if((tabJoueur2[ligne_attaque][colonne_attaque]=='X'))
                        {
                            tabCibleJoueur1[ligne_attaque][colonne_attaque]='X';    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                            B2[numeroDuBateau].nbTirs++;    ///On incr�mente le compteur de tir du bateau.
                        }

                        ///Si la case touch�e contient un bateau :
                        else
                        {
                            tabCibleJoueur1[ligne_attaque][colonne_attaque]='X';    ///Alors on affiche un X sur le tableau cible du joueur 1.
                            tabJoueur2[ligne_attaque][colonne_attaque]='X'; ///Alors on affiche un X sur le tableau du joueur 2.
                            B2[numeroDuBateau].nbTirs++;    ///On incr�mente le compteur de tir du bateau.

                            ///Tests pour savoir si des bateaux sont coul�s :

                            coordBateauToucheX=ligne_attaque; ///On r�cup�re la coordonn�e de la ligne touch�e.
                            coordBateauToucheY=colonne_attaque;   ///On r�cup�re la coordonn�e de la colonne touch�e.

                            ///On cherche quel bateau adverse a �t� touch� :
                            for (m=0; m<10; m++)  ///Pour chacuns des bateaux du tableau de bateau adverse :
                            {
                                for (n=0; n<7; n++)   ///Et pour chacunes des coordonn�es X et Y des bateaux :
                                {
                                    if(B1[m].tabX[n]==coordBateauToucheX && B1[m].tabY[n]==coordBateauToucheY)  ///Si il y a correspondance avec la case attaqu�e :
                                    {
                                        B1[m].etat++;   ///Alors on incr�mente le compteur d'�tat du bateau.

                                    }
                                }

                                if(B1[m].etat==B1[m].taille)    ///Si le bateau a �t� touch� autant de fois qu'il n'a de cases :
                                {
                                    ///Alors le bateau est COULE et on va l'afficher sur le tableau cible ainsi que le supprimer du tableau du joueur 2 :

                                    if(B1[m].orientation==0)    ///Si le bateau adverse �tait horizontal :
                                    {
                                        for(o=0; o<B1[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                        {
                                            tabCibleJoueur1[B1[m].tabX[0]][B1[m].tabY[0]+o]=178;  ///On affiche un bloc sur le tableau cible.
                                            tabJoueur2[B1[m].tabX[0]][B1[m].tabY[0]+o]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                            *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a �t� coul� � ce tour � 1.
                                            *numBatCoule=m;
                                        }
                                    }

                                    if(B1[m].orientation==1)    ///Si le bateau adverse �tait vertical :
                                    {
                                        for(o=0; o<B1[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                        {
                                            tabCibleJoueur1[B1[m].tabX[0]+o][B1[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                            tabJoueur2[B1[m].tabX[0]+o][B1[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                            *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a �t� coul� � ce tour � 1.
                                            *numBatCoule=m;
                                        }
                                    }

                                    if(B1[m].orientation==2)    ///Si le bateau adverse �tait � la fois horizontal et vertical (cas des sous-marins) :
                                    {
                                        tabCibleJoueur1[B1[m].tabX[0]][B1[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                        tabJoueur2[B1[m].tabX[0]][B1[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                        *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a �t� coul� � ce tour � 1.
                                        *numBatCoule=m;
                                    }

                                }
                            }

                        }
                    }
                }
                B2[numeroDuBateau].nbTirs++;    ///incr�mentation du compteur de tirs du bateau;
            }

            ///si c'est un SOUS-MARINS :
            if(B2[numeroDuBateau].type==4)
            {
                gotoligcol(3,1);
                printf("L'ordinateur a attaqu%c avec un sous-marin.", 130);



                ///TESTS POUR SAVOIR SI LA CASE ATTAQUEE EST VALIDE :

                ///Si les coordonn�es choisies ne d�passent pas ni � droite ni en bas :
                while(possibiliteTir==0)
                {


                    ligne_attaque=rand()%15;

                    colonne_attaque=rand()%15;

                    if(ligne_attaque>=0 && ligne_attaque<=14 && colonne_attaque>=0 && colonne_attaque<=14)
                    {
                        possibiliteTir=1;   ///Alors le tir est possible.

                    }
                    else
                    {
                        possibiliteTir=0;   ///Alors le tir est impossible.


                    }
                }

                ///TESTS POUR SAVOIR SI LE TIR EST REUSSI :

                ///Si la cases touch�e est un espace :
                if (tabJoueur2[ligne_attaque][colonne_attaque]==' ')
                {
                    tabCibleJoueur1[ligne_attaque][colonne_attaque]=126;    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                    B2[numeroDuBateau].nbTirs++;    ///On incr�mente le compteur de tir du bateau.
                }

                else
                {

                    ///Si la case touch�e �tait d�j� touch�e :
                    if((tabJoueur2[ligne_attaque][colonne_attaque]=='X'))
                    {
                        tabCibleJoueur1[ligne_attaque][colonne_attaque]='X';    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                        B2[numeroDuBateau].nbTirs++;    ///On incr�mente le compteur de tir du bateau.
                    }

                    ///Si la case touch�e contient un bateau :
                    else
                    {
                        tabCibleJoueur1[ligne_attaque][colonne_attaque]='X';    ///Alors on affiche un X sur le tableau cible du joueur 1.
                        tabJoueur2[ligne_attaque][colonne_attaque]='X'; ///Alors on affiche un X sur le tableau du joueur 2.
                        B2[numeroDuBateau].nbTirs++;    ///On incr�mente le compteur de tir du bateau.

                        ///Tests pour savoir si des bateaux sont coul�s :

                        coordBateauToucheX=ligne_attaque; ///On r�cup�re la coordonn�e de la ligne touch�e.
                        coordBateauToucheY=colonne_attaque;   ///On r�cup�re la coordonn�e de la colonne touch�e.

                        ///On cherche quel bateau adverse a �t� touch� :
                        for (m=0; m<10; m++)  ///Pour chacuns des bateaux du tableau de bateau adverse :
                        {
                            for (n=0; n<7; n++)   ///Et pour chacunes des coordonn�es X et Y des bateaux :
                            {
                                if(B1[m].tabX[n]==coordBateauToucheX && B1[m].tabY[n]==coordBateauToucheY)  ///Si il y a correspondance avec la case attaqu�e :
                                {
                                    B1[m].etat++;   ///Alors on incr�mente le compteur d'�tat du bateau.

                                }
                            }

                            if(B1[m].etat==B1[m].taille)    ///Si le bateau a �t� touch� autant de fois qu'il n'a de cases :
                            {
                                ///Alors le bateau est COULE et on va l'afficher sur le tableau cible ainsi que le supprimer du tableau du joueur 2 :

                                if(B1[m].orientation==0)    ///Si le bateau adverse �tait horizontal :
                                {
                                    for(o=0; o<B1[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                    {
                                        tabCibleJoueur1[B1[m].tabX[0]][B1[m].tabY[0]+o]=178;  ///On affiche un bloc sur le tableau cible.
                                        tabJoueur2[B1[m].tabX[0]][B1[m].tabY[0]+o]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                        *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a �t� coul� � ce tour � 1.
                                        *numBatCoule=m;
                                    }
                                }

                                if(B1[m].orientation==1)    ///Si le bateau adverse �tait vertical :
                                {
                                    for(o=0; o<B1[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                    {
                                        tabCibleJoueur1[B1[m].tabX[0]+o][B1[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                        tabJoueur2[B1[m].tabX[0]+o][B1[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                        *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a �t� coul� � ce tour � 1.
                                        *numBatCoule=m;
                                    }
                                }

                                if(B1[m].orientation==2)    ///Si le bateau adverse �tait � la fois horizontal et vertical (cas des sous-marins) :
                                {
                                    tabCibleJoueur1[B1[m].tabX[0]][B1[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                    tabJoueur2[B1[m].tabX[0]][B1[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                    *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a �t� coul� � ce tour � 1.
                                    *numBatCoule=m;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    gotoligcol(5,1);
    charLigne=ligne_attaque+97;
    printf("L'ordinateur a attaqu%c en %c %d.", 130, charLigne, colonne_attaque);

}


///D�claration de notre fonction d�placement pour l'ordinateur   :
void deplacementAleaIA(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur)
{
    int test=0; ///variable pour le blindage de saisie.
    int ligne;  ///Coordonn�e de la ligne s�l�ctionn�e.
    int colonne;    ///Coordonn�e de la colonne s�l�ctionn�e.
    int numeroDuBateau; ///Num�ro du bateau � d�placer (1 � 10).
    int i;  ///Compteur.
    int j;  ///Compteur.
    int deplacementGauche=0;  ///variable qui indique si on peut se d�placer � gauche (0=non, 1=oui).
    int deplacementDroite=0;  ///variable qui indique si on peut se d�placer � droite (0=non, 1=oui).
    int deplacementHaut=0;  ///variable qui indique si on peut se d�placer en haut (0=non, 1=oui).
    int deplacementBas=0;  ///variable qui indique si on peut se d�placer en bas (0=non, 1=oui).
    int tailleEffective=0;  ///=taille-1 pour utiliser dans les conditiond de tests (pour selectionner la derni�re case d'un bateau).
    int choixDeplacement=0;  ///Variable pour choisir le bateau que le joueur veut d�placer.
    int deplacementImpossible=1;    ///Variable qui indique si le d�placement est possible (pour blinder, 0=possible, 1=impossible)

    int choixDeplacementValide=0;   ///0=invalide, 1=valide.

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
    gotoligcol(0,0);   ///Revient au d�but de la zone de texte.





    ///SI C'EST LE TOUR DU JOUEUR 2 (FONCTIONNE):
    if(*indiceJoueur==2)
    {
        while(deplacementImpossible==1)
        {
            while (test==0)
            {
                /// L'utilisateur rentre la ligne et la colonne du bateau � d�placer :


                ligne=rand()%15;

                colonne=rand()%15;

                ///V�rification que la case s�l�ctionn�e contienne un bateau :
                if (tabJoueur1[ligne][colonne]==' ' || tabJoueur1[ligne][colonne]=='X')
                {
                    test=0;

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
                    gotoligcol(33,0);   ///Revient au d�but de la zone de texte


                }
                else
                {
                    test=1;
                }
            }

            ///Parcours des coordonn�es des bateaux afin de trouver une correspondance :
            for (i=0; i<10; i++)  ///Pour i allant de 0 � 10 :
            {
                for (j=0; j<7; j++)   ///Et j allant de 0 � 7 :
                {
                    if ((B2[i].tabX[j])==ligne && (B2[i].tabY[j])==colonne) ///Si les coordonn�es d'un bateau sont les m�mes que les coordonn�es entr�es :
                    {
                        numeroDuBateau=i ;
                        j=7;    ///alors on sort de la boucle de j.
                        i=10;    ///et on sort de la boucle de i.
                    }
                }
            }

            ///Tests pour savoir comment on peut d�placer le bateau :
            ///(On utilisera d�sormais B2[numeroDuBateau] et on jouera avec les tabX et tabY)

            tailleEffective=(B2[numeroDuBateau].taille)-1;

            ///Si le bateau est horizontal (test� et FONCTIONNE) :
            if(B2[numeroDuBateau].orientation==0)
            {
                deplacementHaut=0;  ///Le d�placement en haut est impossible.
                deplacementBas=0;   ///Le d�placement en bas est impossible.

                ///d�placement � gauche :
                if(B2[numeroDuBateau].tabY[0]==0)   ///si la coordonn�e Y de la premi�re case du bateau est �gale � 0 :
                {
                    deplacementGauche=0;    ///alors le d�placement � gauche est impossible.
                }

                else
                {
                    if(tabJoueur1[B2[numeroDuBateau].tabX[0]][B2[numeroDuBateau].tabY[0]-1]!=' ') ///Si la case pr�c�dant la premi�re case du bateau n'est pas libre :
                    {
                        deplacementGauche=0;    ///Le d�placement � gauche est impossible.
                    }

                    else
                    {
                        deplacementGauche=1;
                    }
                }

                ///d�placement � droite :
                if(B2[numeroDuBateau].tabY[tailleEffective]==14)  ///si la coordonn�e Y de la derni�re case du bateau est �gale � 14 :
                {
                    deplacementDroite=0;     ///alors le d�placement � droite est impossible.

                }
                else
                {
                    if(tabJoueur1[B2[numeroDuBateau].tabX[0]][B2[numeroDuBateau].tabY[tailleEffective]+1]!=' ') ///Si la case suivant la derni�re case du bateau n'est pas libre :
                    {
                        deplacementDroite=0;    ///Le d�placement � droite est impossible.

                    }

                    else
                    {
                        deplacementDroite=1;

                    }
                }

                ///Test pour savoir si le bateau est touch� :
                for(j=0; j<=tailleEffective; j++)
                {
                    if(tabJoueur1[B2[numeroDuBateau].tabX[0]][B2[numeroDuBateau].tabY[0]+j]=='X')   ///Si le bateau contient un X :
                    {
                        deplacementHaut=0;  ///Le d�placement en haut est impossible.
                        deplacementBas=0;   ///Le d�placement en bas est impossible.
                        deplacementGauche=0;    ///alors le d�placement � gauche est impossible.
                        deplacementDroite=0;     ///alors le d�placement � droite est impossible.
                    }
                }

            }

            ///Si le bateau est vertical (test� et FONCTIONNE) :
            if(B2[numeroDuBateau].orientation==1)
            {
                deplacementGauche=0;  ///Le d�placement en haut est impossible.
                deplacementDroite=0;   ///Le d�placement en bas est impossible.


                ///d�placement en haut :
                if(B2[numeroDuBateau].tabX[0]==0)   ///si la coordonn�e X de la premi�re case du bateau est �gale � 0 :
                {
                    deplacementHaut=0;    ///alors le d�placement en haut est impossible.

                }

                else
                {
                    if(tabJoueur1[B2[numeroDuBateau].tabX[0]-1][B2[numeroDuBateau].tabY[0]]!=' ') ///Si la case pr�c�dant la premi�re case du bateau n'est pas libre :
                    {
                        deplacementHaut=0;    ///Le d�placement en haut est impossible.

                    }

                    else
                    {
                        deplacementHaut=1;

                    }
                }

                ///d�placement en bas :
                if(B2[numeroDuBateau].tabX[tailleEffective]==14)  ///si la coordonn�e X de la derni�re case du bateau est �gale � 14 :
                {
                    deplacementBas=0;     ///alors le d�placement en bas est impossible.

                }
                else
                {
                    if(tabJoueur1[B2[numeroDuBateau].tabX[tailleEffective]+1][B2[numeroDuBateau].tabY[0]]!=' ') ///Si la case suivant la derni�re case du bateau n'est pas libre :
                    {
                        deplacementBas=0;    ///Le d�placement en bas est impossible.

                    }

                    else
                    {
                        deplacementBas=1;

                    }
                }

                ///Test pour savoir si le bateau est touch� :
                for(j=0; j<=tailleEffective; j++)
                {
                    if(tabJoueur1[B2[numeroDuBateau].tabX[0]+j][B2[numeroDuBateau].tabY[0]]=='X')
                    {
                        deplacementHaut=0;  ///Le d�placement en haut est impossible.
                        deplacementBas=0;   ///Le d�placement en bas est impossible.
                        deplacementGauche=0;    ///alors le d�placement � gauche est impossible.
                        deplacementDroite=0;     ///alors le d�placement � droite est impossible.
                    }
                }
            }

            ///Si le bateau est � la fois horizontal et vertical (cas des sous-marins, test� et FONCTIONNE) :
            if(B2[numeroDuBateau].orientation==2)
            {

                ///d�placement � gauche :
                if(B2[numeroDuBateau].tabY[0]==0)   ///si la coordonn�e Y de la premi�re case du bateau est �gale � 0 :
                {
                    deplacementGauche=0;    ///alors le d�placement � gauche est impossible.

                }

                else
                {
                    if(tabJoueur1[B2[numeroDuBateau].tabX[0]][B2[numeroDuBateau].tabY[0]-1]!=' ') ///Si la case pr�c�dant la premi�re case du bateau n'est pas libre :
                    {
                        deplacementGauche=0;    ///Le d�placement � gauche est impossible.

                    }

                    else
                    {
                        deplacementGauche=1;

                    }
                }

                ///d�placement � droite :
                if(B2[numeroDuBateau].tabY[tailleEffective]==14)  ///si la coordonn�e Y de la derni�re case du bateau est �gale � 14 :
                {
                    deplacementDroite=0;     ///alors le d�placement � droite est impossible.

                }
                else
                {
                    if(tabJoueur1[B2[numeroDuBateau].tabX[0]][B2[numeroDuBateau].tabY[tailleEffective]+1]!=' ') ///Si la case suivant la derni�re case du bateau n'est pas libre :
                    {
                        deplacementDroite=0;    ///Le d�placement � droite est impossible.

                    }

                    else
                    {
                        deplacementDroite=1;

                    }
                }

                ///d�placement en haut :
                if(B2[numeroDuBateau].tabX[0]==0)   ///si la coordonn�e X de la premi�re case du bateau est �gale � 0 :
                {
                    deplacementHaut=0;    ///alors le d�placement en haut est impossible.

                }

                else
                {
                    if(tabJoueur1[B2[numeroDuBateau].tabX[0]-1][B2[numeroDuBateau].tabY[0]]!=' ') ///Si la case pr�c�dant la premi�re case du bateau n'est pas libre :
                    {
                        deplacementHaut=0;    ///Le d�placement en haut est impossible.

                    }

                    else
                    {
                        deplacementHaut=1;

                    }
                }

                ///d�placement en bas :
                if(B2[numeroDuBateau].tabX[tailleEffective]==14)  ///si la coordonn�e X de la derni�re case du bateau est �gale � 14 :
                {
                    deplacementBas=0;     ///alors le d�placement en bas est impossible.

                }
                else
                {
                    if(tabJoueur1[B2[numeroDuBateau].tabX[tailleEffective]+1][B2[numeroDuBateau].tabY[0]]!=' ') ///Si la case suivant la derni�re case du bateau n'est pas libre :
                    {
                        deplacementBas=0;    ///Le d�placement en bas est impossible.

                    }

                    else
                    {
                        deplacementBas=1;

                    }
                }

                ///Test pour savoir si le bateau est touch� :
                if(tabJoueur1[B2[numeroDuBateau].tabX[0]][B2[numeroDuBateau].tabY[0]]=='X')
                {
                    deplacementHaut=0;  ///Le d�placement en haut est impossible.
                    deplacementBas=0;   ///Le d�placement en bas est impossible.
                    deplacementGauche=0;    ///alors le d�placement � gauche est impossible.
                    deplacementDroite=0;     ///alors le d�placement � droite est impossible.
                }
            }


            ///Demande � l'utilisateur de la direction souhait�e :

            if(deplacementDroite==0 && deplacementGauche==0 && deplacementBas==0 && deplacementHaut==0) ///Si le d�placement n'est possible dans aucune direction :
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
                gotoligcol(33,0);   ///Revient au d�but de la zone de texte.


                deplacementImpossible=1; ///On met d�placement impossible � 1.
                test=0; ///On met le test � 0 pour pouvoir entrer de nouvelles coordonn�es.
            }
            else
            {
                deplacementImpossible=0; ///On met d�placement impossible � 0.
            }

        }



        ///DEPLACEMENT PUR DES BATEAUX :

        ///Si le joueur a choisi de d�placer le bateau � droite (test� et FONCTIONNE) :
        while(choixDeplacementValide==0)
        {
            ///Affichage personalis� en fonction des d�placement possibles :
            if(deplacementDroite==1)
            {
                deplacementImpossible=0;
            }
            if(deplacementGauche==1)
            {
                deplacementImpossible=0;
            }
            if(deplacementBas==1)
            {
                deplacementImpossible=0;
            }
            if(deplacementHaut==1)
            {
                deplacementImpossible=0;
            }


            choixDeplacement=rand()%4+1;  ///Saisie du choix de l'utilisateur.

            if(choixDeplacement==1 && deplacementDroite==1)
            {
                choixDeplacementValide=1;
                for(i=0; i<B2[numeroDuBateau].taille; i++)  ///Pour toutes les cases du bateau :
                {
                    ///d�calage vers la droite des cases du tableau de char correspondantes au bateau s�l�ctionn� :
                    tabJoueur1[B2[numeroDuBateau].tabX[i]][B2[numeroDuBateau].tabY[i]+1]=tabJoueur1[B2[numeroDuBateau].tabX[i]][B2[numeroDuBateau].tabY[i]];
                    B2[numeroDuBateau].tabY[i]+=1;  ///Incr�mentation de 1 des coordonn�es des colonnes du bateau (ATTENTION : respecter cet ordre sinon �a ne marche pas).
                }
                tabJoueur1[B2[numeroDuBateau].tabX[0]][B2[numeroDuBateau].tabY[0]-1]=' ';   ///Suppression de l'icone du bateau sur l'ancienne premi�re case.
            }
            if(choixDeplacement==1 && deplacementDroite==0) ///Si le joueur choisit d'aller � droite alors qu'il ne peut pas :
            {
                choixDeplacementValide=0;

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
                gotoligcol(33,0);   ///Revient au d�but de la zone de texte.


            }

            ///Si le joueur a choisi de d�placer le bateau � gauche (test� et FONCTIONNE) :
            if(choixDeplacement==2 && deplacementGauche==1)
            {
                choixDeplacementValide=1;

                for(i=0; i<B2[numeroDuBateau].taille; i++)  ///Pour toutes les cases du bateau :
                {
                    ///d�calage vers la gauche des cases du tableau de char correspondantes au bateau s�l�ctionn� :
                    tabJoueur1[B2[numeroDuBateau].tabX[i]][B2[numeroDuBateau].tabY[i]-1]=tabJoueur1[B2[numeroDuBateau].tabX[i]][B2[numeroDuBateau].tabY[i]];
                    B2[numeroDuBateau].tabY[i]-=1;  ///Incr�mentation de -1 des coordonn�es des colonnes du bateau (ATTENTION : respecter cet ordre sinon �a ne marche pas).
                }
                tabJoueur1[B2[numeroDuBateau].tabX[0]][B2[numeroDuBateau].tabY[0]+B2[numeroDuBateau].taille]=' ';   ///Suppression de l'icone du bateau sur l'ancienne derni�re case.
            }
            if(choixDeplacement==2 && deplacementGauche==0) ///Si le joueur choisit d'aller � droite alors qu'il ne peut pas :
            {
                choixDeplacementValide=0;

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
                gotoligcol(33,0);   ///Revient au d�but de la zone de texte.



            }

            ///Si le joueur a choisi de d�placer le bateau en bas (test� et FONCTIONNE) :
            if(choixDeplacement==3 && deplacementBas==1)
            {
                choixDeplacementValide=1;

                for(i=0; i<B2[numeroDuBateau].taille; i++)  ///Pour toutes les cases du bateau :
                {
                    ///d�calage vers le bas des cases du tableau de char correspondantes au bateau s�l�ctionn� :
                    tabJoueur1[B2[numeroDuBateau].tabX[i]+1][B2[numeroDuBateau].tabY[i]]=tabJoueur1[B2[numeroDuBateau].tabX[i]][B2[numeroDuBateau].tabY[i]];
                    B2[numeroDuBateau].tabX[i]+=1;  ///Incr�mentation de 1 des coordonn�es des colonnes du bateau (ATTENTION : respecter cet ordre sinon �a ne marche pas).
                }
                tabJoueur1[B2[numeroDuBateau].tabX[0]-1][B2[numeroDuBateau].tabY[0]]=' ';   ///Suppression de l'icone du bateau sur l'ancienne premi�re case.
            }
            if(choixDeplacement==3 && deplacementBas==0) ///Si le joueur choisit d'aller � droite alors qu'il ne peut pas :
            {
                choixDeplacementValide=0;

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
                gotoligcol(33,0);   ///Revient au d�but de la zone de texte.



            }

            ///Si le joueur a choisi de d�placer le bateau en haut (test� et FONCTIONNE) :
            if(choixDeplacement==4 && deplacementHaut==1)
            {
                choixDeplacementValide=1;

                for(i=0; i<B2[numeroDuBateau].taille; i++)  ///Pour toutes les cases du bateau :
                {
                    ///d�calage vers le haut des cases du tableau de char correspondantes au bateau s�l�ctionn� :
                    tabJoueur1[B2[numeroDuBateau].tabX[i]-1][B2[numeroDuBateau].tabY[i]]=tabJoueur1[B2[numeroDuBateau].tabX[i]][B2[numeroDuBateau].tabY[i]];
                    B2[numeroDuBateau].tabX[i]-=1;  ///Incr�mentation de -1 des coordonn�es des colonnes du bateau (ATTENTION : respecter cet ordre sinon �a ne marche pas).
                }
                tabJoueur1[B2[numeroDuBateau].tabX[0]+B2[numeroDuBateau].taille][B2[numeroDuBateau].tabY[0]]=' ';   ///Suppression de l'icone du bateau sur l'ancienne derni�re case.
            }
            if(choixDeplacement==4 && deplacementHaut==0) ///Si le joueur choisit d'aller � droite alors qu'il ne peut pas :
            {
                choixDeplacementValide=0;

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
                gotoligcol(33,0);   ///Revient au d�but de la zone de texte.



            }
        }
    }
    gotoligcol(1,1);
    if(B2[numeroDuBateau].type==1)
        printf("L'ordinateur a d%cplac%c un Cuirass%c.", 130, 130, 130);
    if(B2[numeroDuBateau].type==2)
        printf("L'ordinateur a d%cplac%c un croiseur.", 130, 130);
    if(B2[numeroDuBateau].type==3)
        printf("L'ordinateur a d%cplac%c un destroyer.", 130, 130);
    if(B2[numeroDuBateau].type==4)
        printf("L'ordinateur a d%cplac%c un sous-marin.", 130, 130);

}
