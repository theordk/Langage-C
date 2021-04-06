#include "header.h"

void choixAction(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur, int *typePartie)
{
    int c;   /// variable pour le blindage
    int i;
    int ligneFusee; ///Variable qui prend la valeur de la ligne à laquelle une fusée éclairante est tirée.
    int colonneFusee;   ///Variable qui prend la valeur de la colonne à laquelle une fusée éclairante est tirée.
    int indiceFusee=0;  ///Variable qui indique si une fusée éclairante a été tirée (0=non, 1=oui).

    int indiceBatCoule=0;   ///Indice qui indique si un bateau a été coulé à ce tour (0=non, 1=oui, permet de remettre des icones "à l'eau" au tour suivant).
    int numBatCoule=0;    ///Variable qui contient le numéro du bateau adverse coulé :



    if(*indiceJoueur==1)
    {
        printf("\tC'est au tour du joueur 1 !\n\n");
    }
    if(*indiceJoueur==2)
    {
        printf("\tC'est au tour du joueur 2 !\n\n");
    }

    printf ("\tVoulez-vous attaquer ou d%cplacer un bateau ?\n\n", 130);
    printf("\t1 - Attaquer\n\n");
    printf("\t2 - D%cplacer un bateau d'une case\n\n",130);
    printf ("\t\tTapez 1 ou 2 : ");   /// le joueur choisit ce qu'il veut faire : attaquer ou se déplacer

    while (scanf("%d",&i) !=1 || i==0 || i>=3)  /// blindage
    {
        printf("\nValeur incorrecte, entrer un choix valide : ");   /// on recommence si la saisie n'est pas valide
        while ((c=getchar())!='\n' && c!=EOF);
    }

    switch (i)  /// 1 ere boucle pour choisir si le joueur veut attaquer ou déplacer son bateau
    {
    case 1 :
        attaque(tabJoueur1,tabCibleJoueur1,tabJoueur2,tabCibleJoueur2, B1, B2, indiceJoueur, &ligneFusee, &colonneFusee, &indiceFusee, &indiceBatCoule, &numBatCoule);
        break;
    case 2 :
        deplacement(tabJoueur1,tabCibleJoueur1,tabJoueur2,tabCibleJoueur2, B1, B2, indiceJoueur);
        break;
    }

    affichageGrille(tabJoueur1,tabCibleJoueur1,tabJoueur2,tabCibleJoueur2, B1, B2, indiceJoueur); ///On appelle la fonction d'affichage une fois que l'action a été exécutée.
    changementJoueur(tabJoueur1,tabCibleJoueur1,tabJoueur2,tabCibleJoueur2, B1, B2, indiceJoueur, &ligneFusee, &colonneFusee, &indiceFusee, &indiceBatCoule, &numBatCoule, typePartie);    ///On appelle la fonction de changement de joueur une fois que l'action a été exécutée.

}


///Déclaration de notre fonction attaque (EN COURS DE TEST) :
void attaque (char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur, int *ligneFusee, int *colonneFusee, int *indiceFusee, int *indiceBatCoule, int *numBatCoule)
{
    ///Déclaration des variables de la fonction :
    char charLigne;  ///Coordonnée de la ligne séléctionnée en char.
    int ligne=0, colonne=0; ///Ligne et colonne du bateau attaquant.

    int i,j;    ///Variables pour les boucles.
    int k, l; ///Variables pour les boucles.

    int m, n; ///Variables pour les boucles de parcours des bateaux adverses et des leurs coordonnées.
    int o;  ///Variable pour la boucle de parcours des cases du bateau adverse pour savoir s'il est coulé.


    int test=0; ///Variable pour savoir si la case séléctionnée en tireur est valide.
    int resultatRecherche=0;   ///Variable pour le blindage.
    int ligne_attaque;  ///Ligne du bateau.
    int colonne_attaque;    ///Colonne du bateau.
    int coordBateauToucheX; ///Coordonnée X de la case touchée.
    int coordBateauToucheY; ///Coordonnée Y de la case touchée.
    int numeroDuBateau;     ///Variable qui indique quel bateau attaque.
    int possibiliteTir=0;   ///Variable qui indique si l'attaque est possible (0=impossible, 1=possible).

    ///Permet de nettoyer la zone d'affichage de texte :
    gotoligcol(33,0);   ///Va au début de la zone de texte.
    for(i=0; i<11; i++) ///Pour les 20 lignes :
    {
        for(j=0; j<15; j++)    ///Et les 120 colonnes de la console :
        {
            printf("        ");    ///Afficher des espaces sur toutes la ligne.
        }
        printf("\n");   ///Recommence sur la ligne en dessous.
    }
    gotoligcol(33,0);   ///Revient au début de la zone de texte.

    printf("\tEntrez la ligne puis la colonne du bateau qui va attaquer :\n\n");  ///Dialogue utilisateur.

    while (test==0) ///Tant que la case choisie n'est pas valide.
    {
        /// L'utilisateur rentre la ligne et la colonne du bateau qui va attaquer :
        printf("\t\tEntrez la ligne : ");
        scanf(" %c", &charLigne);
        ligne=charLigne-97;
        printf("\t\tEntrez la colonne : ");
        scanf("%d", &colonne);

        ///Permet de nettoyer la zone d'affichage de texte :
        gotoligcol(33,0);   ///Va au début de la zone de texte.
        for(i=0; i<11; i++) ///Pour les 20 lignes :
        {
            for(j=0; j<15; j++)    ///Et les 120 colonnes de la console :
            {
                printf("        ");    ///Afficher des espaces sur toutes la ligne.
            }
            printf("\n");   ///Recommence sur la ligne en dessous.
        }
        gotoligcol(33,0);   ///Revient au début de la zone de texte.

        ///Si la case est vide ou a été touchée :
        if (tabJoueur1[ligne][colonne]==' ' || tabJoueur1[ligne][colonne]=='X')
        {
            test=0;

            ///Permet de nettoyer la zone d'affichage de texte :
            gotoligcol(33,0);   ///Va au début de la zone de texte.
            for(i=0; i<11; i++) ///Pour les 20 lignes :
            {
                for(j=0; j<15; j++)    ///Et les 120 colonnes de la console :
                {
                    printf("        ");    ///Afficher des espaces sur toutes la ligne.
                }
                printf("\n");   ///Recommence sur la ligne en dessous.
            }
            gotoligcol(33,0);   ///Revient au début de la zone de texte.

            printf("\tLa case est invalide, veuillez saisir de nouvelles coordonn%ces\n", 130);
        }
        else    ///Sinon :
        {
            test=1;
        }
    }

    /// /!\ SI C'EST LE TOUR DU JOUEUR 1 /!\ :
    if(*indiceJoueur==1)
    {
        for (i=0; i<10; i++)  ///Pour chacuns des bateaux du tableau de bateau :
        {
            for (j=0; j<7; j++)   ///Et pour chacunes des coordonnées X et Y des bateaux :
            {
                if (B1[i].tabX[j]==ligne && B1[i].tabY[j]==colonne) ///Si les coordonnées d'un bateau correspondent aux coordonnées entrées :
                {
                    resultatRecherche=1;    ///On indique que la case contient un bateau.
                    numeroDuBateau=i;   ///On récupère le numero du bateau trouvé.
                    j=7;    ///On sort de la boucle de j.
                    i=10;   ///On sort de la boucle de i.
                }
            }
        }
        if(resultatRecherche==1)  ///si la case contient un bateau :
        {

            ///si c'est un CUIRASSE :
            if(B1[numeroDuBateau].type==1)
            {
                printf("\tVous allez attaquer avec un Cuirass%c.\n\n",130);



                ///TESTS POUR SAVOIR SI LA CASE ATTAQUEE EST VALIDE :

                ///Si les coordonnées choisies ne dépassent pas ni à droite ni en bas :
                while(possibiliteTir==0)
                {
                    printf("\tEntrez la ligne puis la colonne %c attaquer :\n\n",133);
                    printf("\t\tEntrez la ligne : ");
                    scanf(" %c", &charLigne);
                    ligne_attaque=charLigne-97;
                    printf("\t\tEntrez la colonne : ");
                    scanf("%d", &colonne_attaque);

                    if(ligne_attaque>=0 && ligne_attaque<=12 && colonne_attaque>=0 && colonne_attaque<=12)
                    {
                        possibiliteTir=1;   ///Alors le tir est possible.
                        printf("Test : tir possible");
                    }
                    else
                    {
                        possibiliteTir=0;   ///Alors le tir est impossible.
                        printf("Tir impossible");

                    }
                }

                ///TESTS POUR SAVOIR SI LE TIR EST REUSSI :
                for (k=0; k<3; k++) ///Pour k allant de 0 à 2 :
                {
                    for (l=0; l<3; l++) ///Et l allant de 0 à 2 :
                    {
                        ///Si la cases touchée est un espace ou un sous-marin :
                        if ((tabJoueur2[ligne_attaque+k][colonne_attaque+l]==' ') || (tabJoueur2[ligne_attaque+k][colonne_attaque+l]=='s'))
                        {
                            tabCibleJoueur1[ligne_attaque+k][colonne_attaque+l]=126;    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                            B1[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.
                        }

                        else
                        {

                            ///Si les cases touchées étaient déjà touchées :
                            if((tabJoueur2[ligne_attaque+k][colonne_attaque+l]=='X'))
                            {
                                tabCibleJoueur1[ligne_attaque+k][colonne_attaque+l]='X';    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                                B1[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.
                            }

                            ///Si la case touchée contient un bateau :
                            else
                            {
                                tabCibleJoueur1[ligne_attaque+k][colonne_attaque+l]='X';    ///Alors on affiche un X sur le tableau cible du joueur 1.
                                tabJoueur2[ligne_attaque+k][colonne_attaque+l]='X'; ///Alors on affiche un X sur le tableau du joueur 2.
                                B1[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.

                                ///Tests pour savoir si des bateaux sont coulés :

                                coordBateauToucheX=ligne_attaque+k; ///On récupère la coordonnée de la ligne touchée.
                                coordBateauToucheY=colonne_attaque+l;   ///On récupère la coordonnée de la colonne touchée.

                                ///On cherche quel bateau adverse a été touché :
                                for (m=0; m<10; m++)  ///Pour chacuns des bateaux du tableau de bateau adverse :
                                {
                                    for (n=0; n<7; n++)   ///Et pour chacunes des coordonnées X et Y des bateaux :
                                    {
                                        if(B2[m].tabX[n]==coordBateauToucheX && B2[m].tabY[n]==coordBateauToucheY)  ///Si il y a correspondance avec la case attaquée :
                                        {
                                            B2[m].etat++;   ///Alors on incrémente le compteur d'état du bateau.
                                            printf("test : num bateau touche recupere, etat : %d",B2[m].etat);
                                        }
                                    }

                                    if(B2[m].etat==B2[m].taille)    ///Si le bateau a été touché autant de fois qu'il n'a de cases :
                                    {
                                        ///Alors le bateau est COULE et on va l'afficher sur le tableau cible ainsi que le supprimer du tableau du joueur 2 :

                                        if(B2[m].orientation==0)    ///Si le bateau adverse était horizontal :
                                        {
                                            for(o=0; o<B2[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                            {
                                                tabCibleJoueur1[B2[m].tabX[0]][B2[m].tabY[0]+o]=178;  ///On affiche un bloc sur le tableau cible.
                                                tabJoueur2[B2[m].tabX[0]][B2[m].tabY[0]+o]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                                *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
                                                *numBatCoule=m;
                                            }
                                        }

                                        if(B2[m].orientation==1)    ///Si le bateau adverse était vertical :
                                        {
                                            for(o=0; o<B2[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                            {
                                                tabCibleJoueur1[B2[m].tabX[0]+o][B2[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                                tabJoueur2[B2[m].tabX[0]+o][B2[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                                *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
                                                *numBatCoule=m;
                                            }
                                        }

                                        if(B2[m].orientation==2)    ///Si le bateau adverse était à la fois horizontal et vertical (cas des sous-marins) :
                                        {
                                            tabCibleJoueur1[B2[m].tabX[0]][B2[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                            tabJoueur2[B2[m].tabX[0]][B2[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                            *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
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
            if(B1[numeroDuBateau].type==2)
            {
                printf("\tVous allez attaquer avec un croiseur.\n\n");

                ///TESTS POUR SAVOIR SI LA CASE ATTAQUEE EST VALIDE :

                ///Si les coordonnées choisies ne dépassent pas ni à droite ni en bas :
                while(possibiliteTir==0)
                {
                    printf("\tEntrez la ligne puis la colonne %c attaquer :\n\n",133);
                    printf("\t\tEntrez la ligne : ");
                    scanf(" %c", &charLigne);
                    ligne_attaque=charLigne-97;
                    printf("\t\tEntrez la colonne : ");
                    scanf("%d", &colonne_attaque);

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
                        ///Si les cases touchées sont des espaces ou des sous-marins :
                        if ((tabJoueur2[ligne_attaque+k][colonne_attaque+l]==' ') || (tabJoueur2[ligne_attaque+k][colonne_attaque+l]=='s'))
                        {
                            tabCibleJoueur1[ligne_attaque+k][colonne_attaque+l]=126;    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                            B1[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.
                        }

                        else
                        {

                            ///Si les cases touchées étaient déjà touchées :
                            if((tabJoueur2[ligne_attaque+k][colonne_attaque+l]=='X'))
                            {
                                tabCibleJoueur1[ligne_attaque+k][colonne_attaque+l]='X';    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                                B1[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.
                            }

                            ///Si les cases touchées contiennent un bateau :
                            else
                            {
                                tabCibleJoueur1[ligne_attaque+k][colonne_attaque+l]='X';    ///Alors on affiche un X sur le tableau cible du joueur 1.
                                tabJoueur2[ligne_attaque+k][colonne_attaque+l]='X'; ///Alors on affiche un X sur le tableau du joueur 2.
                                B1[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.

                                ///Tests pour savoir si des bateaux sont coulés :

                                coordBateauToucheX=ligne_attaque+k; ///On récupère la coordonnée de la ligne touchée.
                                coordBateauToucheY=colonne_attaque+l;   ///On récupère la coordonnée de la colonne touchée.

                                ///On cherche quel bateau adverse a été touché :
                                for (m=0; m<10; m++)  ///Pour chacuns des bateaux du tableau de bateau adverse :
                                {
                                    for (n=0; n<7; n++)   ///Et pour chacunes des coordonnées X et Y des bateaux :
                                    {
                                        if(B2[m].tabX[n]==coordBateauToucheX && B2[m].tabY[n]==coordBateauToucheY)  ///Si il y a correspondance avec la case attaquée :
                                        {
                                            B2[m].etat++;   ///Alors on incrémente le compteur d'état du bateau.

                                        }
                                    }

                                    if(B2[m].etat==B2[m].taille)    ///Si le bateau a été touché autant de fois qu'il n'a de cases :
                                    {
                                        ///Alors le bateau est COULE et on va l'afficher sur le tableau cible ainsi que le supprimer du tableau du joueur 2 :

                                        if(B2[m].orientation==0)    ///Si le bateau adverse était horizontal :
                                        {
                                            for(o=0; o<B2[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                            {
                                                tabCibleJoueur1[B2[m].tabX[0]][B2[m].tabY[0]+o]=178;  ///On affiche un bloc sur le tableau cible.
                                                tabJoueur2[B2[m].tabX[0]][B2[m].tabY[0]+o]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                                *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
                                                *numBatCoule=m;
                                            }
                                        }

                                        if(B2[m].orientation==1)    ///Si le bateau adverse était vertical :
                                        {
                                            for(o=0; o<B2[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                            {
                                                tabCibleJoueur1[B2[m].tabX[0]+o][B2[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                                tabJoueur2[B2[m].tabX[0]+o][B2[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                                *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
                                                *numBatCoule=m;
                                            }
                                        }

                                        if(B2[m].orientation==2)    ///Si le bateau adverse était à la fois horizontal et vertical (cas des sous-marins) :
                                        {
                                            tabCibleJoueur1[B2[m].tabX[0]][B2[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                            tabJoueur2[B2[m].tabX[0]][B2[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                            *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
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
            if(B1[numeroDuBateau].type==3)
            {
                printf("\tVous allez attaquer avec un destroyer.\n\n");

                ///Si c'est son PREMIER TIR :
                if(B1[numeroDuBateau].nbTirs==0)
                {
                    printf("\tVotre premier tir avec un destroyer est une fus%ce %cclairante.\n\n", 130, 130);

                    ///TESTS POUR SAVOIR SI LA CASE ATTAQUEE EST VALIDE :

                    ///Tant que la saisie n'est pas validée :
                    while(possibiliteTir==0)
                    {
                        printf("\tEntrez la ligne puis la colonne %c attaquer :\n\n",133);
                        printf("\t\tEntrez la ligne : ");
                        scanf(" %c", &charLigne);
                        ligne_attaque=charLigne-97;
                        printf("\t\tEntrez la colonne : ");
                        scanf("%d", &colonne_attaque);

                        ///Si les coordonnées choisies ne dépassent pas ni à droite ni en bas :
                        if(ligne_attaque>=0 && ligne_attaque<=11 && colonne_attaque>=0 && colonne_attaque<=11)
                        {
                            possibiliteTir=1;   ///Alors le tir est possible.
                            printf("\nTest : tir possible");
                        }
                        ///Sinon :
                        else
                        {
                            possibiliteTir=0;   ///Alors le tir est impossible.
                            printf("\tVous ne pouvez pas tirer une fus%ce %cclairante %c ces coordonn%ces. Essayez de vous rapprocher du centre.\n", 130, 130, 133, 130);
                        }
                    }

                    ///Si le tir est possible :
                    if(possibiliteTir==1)
                    {
                        ///Pour un carré de 4x4 :
                        for(k=0; k<4; k++)
                        {
                            for(l=0; l<4; l++)
                            {
                                ///On montre la contenance du tableau du joueur 2 dans le tableau cible du joueur 1:
                                tabCibleJoueur1[ligne_attaque+k][colonne_attaque+l]=tabJoueur2[ligne_attaque+k][colonne_attaque+l];
                                ///Opérations sur des varaibles qui vont permettre de remettre la brouillard au tour suivant :
                                *ligneFusee=ligne_attaque;
                                *colonneFusee=colonne_attaque;
                                *indiceFusee=1;

                            }
                        }
                    }
                }

                ///Si ce n'est PAS son PREMIER TIR :
                if(B1[numeroDuBateau].nbTirs!=0)
                {

                    ///TESTS POUR SAVOIR SI LA CASE ATTAQUEE EST VALIDE :

                    ///Tant que la saisie n'est pas validée :
                    while(possibiliteTir==0)
                    {
                        printf("\tEntrez la ligne puis la colonne %c attaquer :\n\n",133);
                        printf("\t\tEntrez la ligne : ");
                        scanf(" %c", &charLigne);
                        ligne_attaque=charLigne-97;
                        printf("\t\tEntrez la colonne : ");
                        scanf("%d", &colonne_attaque);

                        ///Si les coordonnées choisies ne dépassent pas ni à droite ni en bas :
                        if(ligne_attaque>=0 && ligne_attaque<=14 && colonne_attaque>=0 && colonne_attaque<=14)
                        {
                            possibiliteTir=1;   ///Alors le tir est possible.
                            printf("\nTest : tir possible");
                        }
                        ///Sinon :
                        else
                        {
                            possibiliteTir=0;   ///Alors le tir est impossible.
                            printf("Tir impossible");

                        }
                    }

                    ///TESTS POUR SAVOIR SI LE TIR EST REUSSI :

                    ///Si la cases touchée est un espace ou un sous-marin :
                    if ((tabJoueur2[ligne_attaque][colonne_attaque]==' ') || (tabJoueur2[ligne_attaque][colonne_attaque]=='s'))
                    {
                        tabCibleJoueur1[ligne_attaque][colonne_attaque]=126;    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                        B1[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.
                    }

                    else
                    {

                        ///Si la case touchée était déjà touchée :
                        if((tabJoueur2[ligne_attaque][colonne_attaque]=='X'))
                        {
                            tabCibleJoueur1[ligne_attaque][colonne_attaque]='X';    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                            B1[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.
                        }

                        ///Si la case touchée contient un bateau :
                        else
                        {
                            tabCibleJoueur1[ligne_attaque][colonne_attaque]='X';    ///Alors on affiche un X sur le tableau cible du joueur 1.
                            tabJoueur2[ligne_attaque][colonne_attaque]='X'; ///Alors on affiche un X sur le tableau du joueur 2.
                            B1[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.

                            ///Tests pour savoir si des bateaux sont coulés :

                            coordBateauToucheX=ligne_attaque; ///On récupère la coordonnée de la ligne touchée.
                            coordBateauToucheY=colonne_attaque;   ///On récupère la coordonnée de la colonne touchée.

                            ///On cherche quel bateau adverse a été touché :
                            for (m=0; m<10; m++)  ///Pour chacuns des bateaux du tableau de bateau adverse :
                            {
                                for (n=0; n<7; n++)   ///Et pour chacunes des coordonnées X et Y des bateaux :
                                {
                                    if(B2[m].tabX[n]==coordBateauToucheX && B2[m].tabY[n]==coordBateauToucheY)  ///Si il y a correspondance avec la case attaquée :
                                    {
                                        B2[m].etat++;   ///Alors on incrémente le compteur d'état du bateau.
                                        printf("test : num bateau touche recupere, etat : %d",B2[m].etat);
                                    }
                                }

                                if(B2[m].etat==B2[m].taille)    ///Si le bateau a été touché autant de fois qu'il n'a de cases :
                                {
                                    ///Alors le bateau est COULE et on va l'afficher sur le tableau cible ainsi que le supprimer du tableau du joueur 2 :

                                    if(B2[m].orientation==0)    ///Si le bateau adverse était horizontal :
                                    {
                                        for(o=0; o<B2[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                        {
                                            tabCibleJoueur1[B2[m].tabX[0]][B2[m].tabY[0]+o]=178;  ///On affiche un bloc sur le tableau cible.
                                            tabJoueur2[B2[m].tabX[0]][B2[m].tabY[0]+o]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                            *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
                                            *numBatCoule=m;
                                        }
                                    }

                                    if(B2[m].orientation==1)    ///Si le bateau adverse était vertical :
                                    {
                                        for(o=0; o<B2[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                        {
                                            tabCibleJoueur1[B2[m].tabX[0]+o][B2[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                            tabJoueur2[B2[m].tabX[0]+o][B2[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                            *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
                                            *numBatCoule=m;
                                        }
                                    }

                                    if(B2[m].orientation==2)    ///Si le bateau adverse était à la fois horizontal et vertical (cas des sous-marins) :
                                    {
                                        tabCibleJoueur1[B2[m].tabX[0]][B2[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                        tabJoueur2[B2[m].tabX[0]][B2[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                        *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
                                        *numBatCoule=m;
                                    }

                                }
                            }

                        }
                    }
                }
                B1[numeroDuBateau].nbTirs++;    ///incrémentation du compteur de tirs du bateau;
            }

            ///si c'est un SOUS-MARINS :
            if(B1[numeroDuBateau].type==4)
            {
                printf("\tVous allez attaquer avec un sous-marin.\n\n");



                ///TESTS POUR SAVOIR SI LA CASE ATTAQUEE EST VALIDE :

                ///Si les coordonnées choisies ne dépassent pas ni à droite ni en bas :
                while(possibiliteTir==0)
                {
                    printf("\tEntrez la ligne puis la colonne %c attaquer :\n\n",133);
                    printf("\t\tEntrez la ligne : ");
                    scanf(" %c", &charLigne);
                    ligne_attaque=charLigne-97;
                    printf("\t\tEntrez la colonne : ");
                    scanf("%d", &colonne_attaque);

                    if(ligne_attaque>=0 && ligne_attaque<=14 && colonne_attaque>=0 && colonne_attaque<=14)
                    {
                        possibiliteTir=1;   ///Alors le tir est possible.
                        printf("\nTest : tir possible");
                    }
                    else
                    {
                        possibiliteTir=0;   ///Alors le tir est impossible.
                        printf("Tir impossible");

                    }
                }

                ///TESTS POUR SAVOIR SI LE TIR EST REUSSI :

                ///Si la cases touchée est un espace :
                if (tabJoueur2[ligne_attaque][colonne_attaque]==' ')
                {
                    tabCibleJoueur1[ligne_attaque][colonne_attaque]=126;    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                    B1[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.
                }

                else
                {

                    ///Si la case touchée était déjà touchée :
                    if((tabJoueur2[ligne_attaque][colonne_attaque]=='X'))
                    {
                        tabCibleJoueur1[ligne_attaque][colonne_attaque]='X';    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                        B1[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.
                    }

                    ///Si la case touchée contient un bateau :
                    else
                    {
                        tabCibleJoueur1[ligne_attaque][colonne_attaque]='X';    ///Alors on affiche un X sur le tableau cible du joueur 1.
                        tabJoueur2[ligne_attaque][colonne_attaque]='X'; ///Alors on affiche un X sur le tableau du joueur 2.
                        B1[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.

                        ///Tests pour savoir si des bateaux sont coulés :

                        coordBateauToucheX=ligne_attaque; ///On récupère la coordonnée de la ligne touchée.
                        coordBateauToucheY=colonne_attaque;   ///On récupère la coordonnée de la colonne touchée.

                        ///On cherche quel bateau adverse a été touché :
                        for (m=0; m<10; m++)  ///Pour chacuns des bateaux du tableau de bateau adverse :
                        {
                            for (n=0; n<7; n++)   ///Et pour chacunes des coordonnées X et Y des bateaux :
                            {
                                if(B2[m].tabX[n]==coordBateauToucheX && B2[m].tabY[n]==coordBateauToucheY)  ///Si il y a correspondance avec la case attaquée :
                                {
                                    B2[m].etat++;   ///Alors on incrémente le compteur d'état du bateau.
                                    printf("test : num bateau touche recupere, etat : %d",B2[m].etat);
                                }
                            }

                            if(B2[m].etat==B2[m].taille)    ///Si le bateau a été touché autant de fois qu'il n'a de cases :
                            {
                                ///Alors le bateau est COULE et on va l'afficher sur le tableau cible ainsi que le supprimer du tableau du joueur 2 :

                                if(B2[m].orientation==0)    ///Si le bateau adverse était horizontal :
                                {
                                    for(o=0; o<B2[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                    {
                                        tabCibleJoueur1[B2[m].tabX[0]][B2[m].tabY[0]+o]=178;  ///On affiche un bloc sur le tableau cible.
                                        tabJoueur2[B2[m].tabX[0]][B2[m].tabY[0]+o]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                        *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
                                        *numBatCoule=m;
                                    }
                                }

                                if(B2[m].orientation==1)    ///Si le bateau adverse était vertical :
                                {
                                    for(o=0; o<B2[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                    {
                                        tabCibleJoueur1[B2[m].tabX[0]+o][B2[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                        tabJoueur2[B2[m].tabX[0]+o][B2[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                        *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
                                        *numBatCoule=m;
                                    }
                                }

                                if(B2[m].orientation==2)    ///Si le bateau adverse était à la fois horizontal et vertical (cas des sous-marins) :
                                {
                                    tabCibleJoueur1[B2[m].tabX[0]][B2[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                    tabJoueur2[B2[m].tabX[0]][B2[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                    *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
                                    *numBatCoule=m;
                                }

                            }
                        }

                    }
                }
            }
        }
    }


    /// /!\ SI C'EST LE TOUR DU JOUEUR 2 /!\ :
    if(*indiceJoueur==2)
    {
        for (i=0; i<10; i++)  ///Pour chacuns des bateaux du tableau de bateau :
        {
            for (j=0; j<7; j++)   ///Et pour chacunes des coordonnées X et Y des bateaux :
            {
                if (B2[i].tabX[j]==ligne && B2[i].tabY[j]==colonne) ///Si les coordonnées d'un bateau correspondent aux coordonnées entrées :
                {
                    resultatRecherche=1;    ///On indique que la case contient un bateau.
                    numeroDuBateau=i;   ///On récupère le numero du bateau trouvé.
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
                printf("\tVous allez attaquer avec un Cuirass%c.\n\n",130);



                ///TESTS POUR SAVOIR SI LA CASE ATTAQUEE EST VALIDE :

                ///Si les coordonnées choisies ne dépassent pas ni à droite ni en bas :
                while(possibiliteTir==0)
                {
                    printf("\tEntrez la ligne puis la colonne %c attaquer :\n\n",133);
                    printf("\t\tEntrez la ligne : ");
                    scanf(" %c", &charLigne);
                    ligne_attaque=charLigne-97;
                    printf("\t\tEntrez la colonne : ");
                    scanf("%d", &colonne_attaque);

                    if(ligne_attaque>=0 && ligne_attaque<=12 && colonne_attaque>=0 && colonne_attaque<=12)
                    {
                        possibiliteTir=1;   ///Alors le tir est possible.
                        printf("Test : tir possible");
                    }
                    else
                    {
                        possibiliteTir=0;   ///Alors le tir est impossible.
                        printf("Tir impossible");

                    }
                }

                ///TESTS POUR SAVOIR SI LE TIR EST REUSSI :
                for (k=0; k<3; k++) ///Pour k allant de 0 à 2 :
                {
                    for (l=0; l<3; l++) ///Et l allant de 0 à 2 :
                    {
                        ///Si la cases touchée est un espace ou un sous-marin :
                        if ((tabJoueur2[ligne_attaque+k][colonne_attaque+l]==' ') || (tabJoueur2[ligne_attaque+k][colonne_attaque+l]=='s'))
                        {
                            tabCibleJoueur1[ligne_attaque+k][colonne_attaque+l]=126;    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                            B2[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.
                        }

                        else
                        {

                            ///Si les cases touchées étaient déjà touchées :
                            if((tabJoueur2[ligne_attaque+k][colonne_attaque+l]=='X'))
                            {
                                tabCibleJoueur1[ligne_attaque+k][colonne_attaque+l]='X';    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                                B2[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.
                            }

                            ///Si la case touchée contient un bateau :
                            else
                            {
                                tabCibleJoueur1[ligne_attaque+k][colonne_attaque+l]='X';    ///Alors on affiche un X sur le tableau cible du joueur 1.
                                tabJoueur2[ligne_attaque+k][colonne_attaque+l]='X'; ///Alors on affiche un X sur le tableau du joueur 2.
                                B2[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.

                                ///Tests pour savoir si des bateaux sont coulés :

                                coordBateauToucheX=ligne_attaque+k; ///On récupère la coordonnée de la ligne touchée.
                                coordBateauToucheY=colonne_attaque+l;   ///On récupère la coordonnée de la colonne touchée.

                                ///On cherche quel bateau adverse a été touché :
                                for (m=0; m<10; m++)  ///Pour chacuns des bateaux du tableau de bateau adverse :
                                {
                                    for (n=0; n<7; n++)   ///Et pour chacunes des coordonnées X et Y des bateaux :
                                    {
                                        if(B1[m].tabX[n]==coordBateauToucheX && B1[m].tabY[n]==coordBateauToucheY)  ///Si il y a correspondance avec la case attaquée :
                                        {
                                            B1[m].etat++;   ///Alors on incrémente le compteur d'état du bateau.
                                            printf("test : num bateau touche recupere, etat : %d",B1[m].etat);
                                        }
                                    }

                                    if(B1[m].etat==B1[m].taille)    ///Si le bateau a été touché autant de fois qu'il n'a de cases :
                                    {
                                        ///Alors le bateau est COULE et on va l'afficher sur le tableau cible ainsi que le supprimer du tableau du joueur 2 :

                                        if(B1[m].orientation==0)    ///Si le bateau adverse était horizontal :
                                        {
                                            for(o=0; o<B1[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                            {
                                                tabCibleJoueur1[B1[m].tabX[0]][B1[m].tabY[0]+o]=178;  ///On affiche un bloc sur le tableau cible.
                                                tabJoueur2[B1[m].tabX[0]][B1[m].tabY[0]+o]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                                *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
                                                *numBatCoule=m;
                                            }
                                        }

                                        if(B1[m].orientation==1)    ///Si le bateau adverse était vertical :
                                        {
                                            for(o=0; o<B1[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                            {
                                                tabCibleJoueur1[B1[m].tabX[0]+o][B1[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                                tabJoueur2[B1[m].tabX[0]+o][B1[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                                *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
                                                *numBatCoule=m;
                                            }
                                        }

                                        if(B1[m].orientation==2)    ///Si le bateau adverse était à la fois horizontal et vertical (cas des sous-marins) :
                                        {
                                            tabCibleJoueur1[B1[m].tabX[0]][B1[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                            tabJoueur2[B1[m].tabX[0]][B1[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                            *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
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
                printf("\tVous allez attaquer avec un croiseur.\n\n");



                ///TESTS POUR SAVOIR SI LA CASE ATTAQUEE EST VALIDE :

                ///Si les coordonnées choisies ne dépassent pas ni à droite ni en bas :
                while(possibiliteTir==0)
                {
                    printf("\tEntrez la ligne puis la colonne %c attaquer :\n\n",133);
                    printf("\t\tEntrez la ligne : ");
                    scanf(" %c", &charLigne);
                    ligne_attaque=charLigne-97;
                    printf("\t\tEntrez la colonne : ");
                    scanf("%d", &colonne_attaque);

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
                        ///Si les cases touchées sont des espaces ou des sous-marins :
                        if ((tabJoueur2[ligne_attaque+k][colonne_attaque+l]==' ') || (tabJoueur2[ligne_attaque+k][colonne_attaque+l]=='s'))
                        {
                            tabCibleJoueur1[ligne_attaque+k][colonne_attaque+l]=126;    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                            B2[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.
                        }

                        else
                        {

                            ///Si les cases touchées étaient déjà touchées :
                            if((tabJoueur2[ligne_attaque+k][colonne_attaque+l]=='X'))
                            {
                                tabCibleJoueur1[ligne_attaque+k][colonne_attaque+l]='X';    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                                B2[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.
                            }

                            ///Si les cases touchées contiennent un bateau :
                            else
                            {
                                tabCibleJoueur1[ligne_attaque+k][colonne_attaque+l]='X';    ///Alors on affiche un X sur le tableau cible du joueur 1.
                                tabJoueur2[ligne_attaque+k][colonne_attaque+l]='X'; ///Alors on affiche un X sur le tableau du joueur 2.
                                B2[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.

                                ///Tests pour savoir si des bateaux sont coulés :

                                coordBateauToucheX=ligne_attaque+k; ///On récupère la coordonnée de la ligne touchée.
                                coordBateauToucheY=colonne_attaque+l;   ///On récupère la coordonnée de la colonne touchée.

                                ///On cherche quel bateau adverse a été touché :
                                for (m=0; m<10; m++)  ///Pour chacuns des bateaux du tableau de bateau adverse :
                                {
                                    for (n=0; n<7; n++)   ///Et pour chacunes des coordonnées X et Y des bateaux :
                                    {
                                        if(B1[m].tabX[n]==coordBateauToucheX && B1[m].tabY[n]==coordBateauToucheY)  ///Si il y a correspondance avec la case attaquée :
                                        {
                                            B1[m].etat++;   ///Alors on incrémente le compteur d'état du bateau.

                                        }
                                    }

                                    if(B1[m].etat==B1[m].taille)    ///Si le bateau a été touché autant de fois qu'il n'a de cases :
                                    {
                                        ///Alors le bateau est COULE et on va l'afficher sur le tableau cible ainsi que le supprimer du tableau du joueur 2 :

                                        if(B1[m].orientation==0)    ///Si le bateau adverse était horizontal :
                                        {
                                            for(o=0; o<B1[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                            {
                                                tabCibleJoueur1[B1[m].tabX[0]][B1[m].tabY[0]+o]=178;  ///On affiche un bloc sur le tableau cible.
                                                tabJoueur2[B1[m].tabX[0]][B1[m].tabY[0]+o]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                                *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
                                                *numBatCoule=m;
                                            }
                                        }

                                        if(B1[m].orientation==1)    ///Si le bateau adverse était vertical :
                                        {
                                            for(o=0; o<B1[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                            {
                                                tabCibleJoueur1[B1[m].tabX[0]+o][B1[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                                tabJoueur2[B1[m].tabX[0]+o][B1[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                                *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
                                                *numBatCoule=m;
                                            }
                                        }

                                        if(B1[m].orientation==2)    ///Si le bateau adverse était à la fois horizontal et vertical (cas des sous-marins) :
                                        {
                                            tabCibleJoueur1[B1[m].tabX[0]][B1[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                            tabJoueur2[B1[m].tabX[0]][B1[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                            *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
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
                printf("\tVous allez attaquer avec un destroyer.\n\n");

                ///Si c'est son PREMIER TIR :
                if(B2[numeroDuBateau].nbTirs==0)
                {
                    printf("\tVotre premier tir avec un destroyer est une fus%ce %cclairante.\n\n", 130, 130);

                    ///TESTS POUR SAVOIR SI LA CASE ATTAQUEE EST VALIDE :

                    ///Tant que la saisie n'est pas validée :
                    while(possibiliteTir==0)
                    {
                        printf("\tEntrez la ligne puis la colonne %c attaquer :\n\n",133);
                        printf("\t\tEntrez la ligne : ");
                        scanf(" %c", &charLigne);
                        ligne_attaque=charLigne-97;
                        printf("\t\tEntrez la colonne : ");
                        scanf("%d", &colonne_attaque);

                        ///Si les coordonnées choisies ne dépassent pas ni à droite ni en bas :
                        if(ligne_attaque>=0 && ligne_attaque<=11 && colonne_attaque>=0 && colonne_attaque<=11)
                        {
                            possibiliteTir=1;   ///Alors le tir est possible.
                            printf("\nTest : tir possible");
                        }
                        ///Sinon :
                        else
                        {
                            possibiliteTir=0;   ///Alors le tir est impossible.
                            printf("\tVous ne pouvez pas tirer une fus%ce %cclairante %c ces coordonn%ces. Essayez de vous rapprocher du centre.\n", 130, 130, 133, 130);
                        }
                    }

                    ///Si le tir est possible :
                    if(possibiliteTir==1)
                    {
                        ///Pour un carré de 4x4 :
                        for(k=0; k<4; k++)
                        {
                            for(l=0; l<4; l++)
                            {
                                ///On montre la contenance du tableau du joueur 2 dans le tableau cible du joueur 1:
                                tabCibleJoueur1[ligne_attaque+k][colonne_attaque+l]=tabJoueur2[ligne_attaque+k][colonne_attaque+l];
                                ///Opérations sur des varaibles qui vont permettre de remettre la brouillard au tour suivant :
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

                    ///TESTS POUR SAVOIR SI LA CASE ATTAQUEE EST VALIDE :

                    ///Tant que la saisie n'est pas validée :
                    while(possibiliteTir==0)
                    {
                        printf("\tEntrez la ligne puis la colonne %c attaquer :\n\n",133);
                        printf("\t\tEntrez la ligne : ");
                        scanf(" %c", &charLigne);
                        ligne_attaque=charLigne-97;
                        printf("\t\tEntrez la colonne : ");
                        scanf("%d", &colonne_attaque);

                        ///Si les coordonnées choisies ne dépassent pas ni à droite ni en bas :
                        if(ligne_attaque>=0 && ligne_attaque<=14 && colonne_attaque>=0 && colonne_attaque<=14)
                        {
                            possibiliteTir=1;   ///Alors le tir est possible.
                            printf("\nTest : tir possible");
                        }
                        ///Sinon :
                        else
                        {
                            possibiliteTir=0;   ///Alors le tir est impossible.
                            printf("Tir impossible");

                        }
                    }

                    ///TESTS POUR SAVOIR SI LE TIR EST REUSSI :

                    ///Si la cases touchée est un espace ou un sous-marin :
                    if ((tabJoueur2[ligne_attaque][colonne_attaque]==' ') || (tabJoueur2[ligne_attaque][colonne_attaque]=='s'))
                    {
                        tabCibleJoueur1[ligne_attaque][colonne_attaque]=126;    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                        B2[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.
                    }

                    else
                    {

                        ///Si la case touchée était déjà touchée :
                        if((tabJoueur2[ligne_attaque][colonne_attaque]=='X'))
                        {
                            tabCibleJoueur1[ligne_attaque][colonne_attaque]='X';    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                            B2[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.
                        }

                        ///Si la case touchée contient un bateau :
                        else
                        {
                            tabCibleJoueur1[ligne_attaque][colonne_attaque]='X';    ///Alors on affiche un X sur le tableau cible du joueur 1.
                            tabJoueur2[ligne_attaque][colonne_attaque]='X'; ///Alors on affiche un X sur le tableau du joueur 2.
                            B2[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.

                            ///Tests pour savoir si des bateaux sont coulés :

                            coordBateauToucheX=ligne_attaque; ///On récupère la coordonnée de la ligne touchée.
                            coordBateauToucheY=colonne_attaque;   ///On récupère la coordonnée de la colonne touchée.

                            ///On cherche quel bateau adverse a été touché :
                            for (m=0; m<10; m++)  ///Pour chacuns des bateaux du tableau de bateau adverse :
                            {
                                for (n=0; n<7; n++)   ///Et pour chacunes des coordonnées X et Y des bateaux :
                                {
                                    if(B1[m].tabX[n]==coordBateauToucheX && B1[m].tabY[n]==coordBateauToucheY)  ///Si il y a correspondance avec la case attaquée :
                                    {
                                        B1[m].etat++;   ///Alors on incrémente le compteur d'état du bateau.
                                        printf("test : num bateau touche recupere, etat : %d",B1[m].etat);
                                    }
                                }

                                if(B1[m].etat==B1[m].taille)    ///Si le bateau a été touché autant de fois qu'il n'a de cases :
                                {
                                    ///Alors le bateau est COULE et on va l'afficher sur le tableau cible ainsi que le supprimer du tableau du joueur 2 :

                                    if(B1[m].orientation==0)    ///Si le bateau adverse était horizontal :
                                    {
                                        for(o=0; o<B1[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                        {
                                            tabCibleJoueur1[B1[m].tabX[0]][B1[m].tabY[0]+o]=178;  ///On affiche un bloc sur le tableau cible.
                                            tabJoueur2[B1[m].tabX[0]][B1[m].tabY[0]+o]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                            *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
                                            *numBatCoule=m;
                                        }
                                    }

                                    if(B1[m].orientation==1)    ///Si le bateau adverse était vertical :
                                    {
                                        for(o=0; o<B1[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                        {
                                            tabCibleJoueur1[B1[m].tabX[0]+o][B1[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                            tabJoueur2[B1[m].tabX[0]+o][B1[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                            *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
                                            *numBatCoule=m;
                                        }
                                    }

                                    if(B1[m].orientation==2)    ///Si le bateau adverse était à la fois horizontal et vertical (cas des sous-marins) :
                                    {
                                        tabCibleJoueur1[B1[m].tabX[0]][B1[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                        tabJoueur2[B1[m].tabX[0]][B1[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                        *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
                                        *numBatCoule=m;
                                    }

                                }
                            }

                        }
                    }
                }
                B2[numeroDuBateau].nbTirs++;    ///incrémentation du compteur de tirs du bateau;
            }

            ///si c'est un SOUS-MARINS :
            if(B2[numeroDuBateau].type==4)
            {
                printf("\tVous allez attaquer avec un sous-marin.\n\n");



                ///TESTS POUR SAVOIR SI LA CASE ATTAQUEE EST VALIDE :

                ///Si les coordonnées choisies ne dépassent pas ni à droite ni en bas :
                while(possibiliteTir==0)
                {
                    printf("\tEntrez la ligne puis la colonne %c attaquer :\n\n",133);
                    printf("\t\tEntrez la ligne : ");
                    scanf(" %c", &charLigne);
                    ligne_attaque=charLigne-97;
                    printf("\t\tEntrez la colonne : ");
                    scanf("%d", &colonne_attaque);

                    if(ligne_attaque>=0 && ligne_attaque<=14 && colonne_attaque>=0 && colonne_attaque<=14)
                    {
                        possibiliteTir=1;   ///Alors le tir est possible.
                        printf("\nTest : tir possible");
                    }
                    else
                    {
                        possibiliteTir=0;   ///Alors le tir est impossible.
                        printf("Tir impossible");

                    }
                }

                ///TESTS POUR SAVOIR SI LE TIR EST REUSSI :

                ///Si la cases touchée est un espace :
                if (tabJoueur2[ligne_attaque][colonne_attaque]==' ')
                {
                    tabCibleJoueur1[ligne_attaque][colonne_attaque]=126;    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                    B2[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.
                }

                else
                {

                    ///Si la case touchée était déjà touchée :
                    if((tabJoueur2[ligne_attaque][colonne_attaque]=='X'))
                    {
                        tabCibleJoueur1[ligne_attaque][colonne_attaque]='X';    ///Alors on affiche une vague sur le tableau cible du joueur 1.
                        B2[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.
                    }

                    ///Si la case touchée contient un bateau :
                    else
                    {
                        tabCibleJoueur1[ligne_attaque][colonne_attaque]='X';    ///Alors on affiche un X sur le tableau cible du joueur 1.
                        tabJoueur2[ligne_attaque][colonne_attaque]='X'; ///Alors on affiche un X sur le tableau du joueur 2.
                        B2[numeroDuBateau].nbTirs++;    ///On incrémente le compteur de tir du bateau.

                        ///Tests pour savoir si des bateaux sont coulés :

                        coordBateauToucheX=ligne_attaque; ///On récupère la coordonnée de la ligne touchée.
                        coordBateauToucheY=colonne_attaque;   ///On récupère la coordonnée de la colonne touchée.

                        ///On cherche quel bateau adverse a été touché :
                        for (m=0; m<10; m++)  ///Pour chacuns des bateaux du tableau de bateau adverse :
                        {
                            for (n=0; n<7; n++)   ///Et pour chacunes des coordonnées X et Y des bateaux :
                            {
                                if(B1[m].tabX[n]==coordBateauToucheX && B1[m].tabY[n]==coordBateauToucheY)  ///Si il y a correspondance avec la case attaquée :
                                {
                                    B1[m].etat++;   ///Alors on incrémente le compteur d'état du bateau.
                                    printf("test : num bateau touche recupere, etat : %d",B1[m].etat);
                                }
                            }

                            if(B1[m].etat==B1[m].taille)    ///Si le bateau a été touché autant de fois qu'il n'a de cases :
                            {
                                ///Alors le bateau est COULE et on va l'afficher sur le tableau cible ainsi que le supprimer du tableau du joueur 2 :

                                if(B1[m].orientation==0)    ///Si le bateau adverse était horizontal :
                                {
                                    for(o=0; o<B1[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                    {
                                        tabCibleJoueur1[B1[m].tabX[0]][B1[m].tabY[0]+o]=178;  ///On affiche un bloc sur le tableau cible.
                                        tabJoueur2[B1[m].tabX[0]][B1[m].tabY[0]+o]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                        *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
                                        *numBatCoule=m;
                                    }
                                }

                                if(B1[m].orientation==1)    ///Si le bateau adverse était vertical :
                                {
                                    for(o=0; o<B1[m].taille; o++)    ///Pour chacunes des cases du bateau :
                                    {
                                        tabCibleJoueur1[B1[m].tabX[0]+o][B1[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                        tabJoueur2[B1[m].tabX[0]+o][B1[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                        *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
                                        *numBatCoule=m;
                                    }
                                }

                                if(B1[m].orientation==2)    ///Si le bateau adverse était à la fois horizontal et vertical (cas des sous-marins) :
                                {
                                    tabCibleJoueur1[B1[m].tabX[0]][B1[m].tabY[0]]=178;  ///On affiche un bloc sur le tableau cible.
                                    tabJoueur2[B1[m].tabX[0]][B1[m].tabY[0]]=' ';   ///On affiche un espace sur le tableau du joueur 2.
                                    *indiceBatCoule=1;   ///On met l'indice qui indique qu'un bateau a été coulé à ce tour à 1.
                                    *numBatCoule=m;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


///Déclaration de notre fonction déplacement (FONCTIONNE) :
void deplacement(char tabJoueur1[15][15], char tabCibleJoueur1[15][15], char tabJoueur2[15][15], char tabCibleJoueur2[15][15], t_bateau B1[10], t_bateau B2[10], int *indiceJoueur)
{
    int test=0; ///variable pour le blindage de saisie.
    char charLigne;  ///Coordonnée de la ligne séléctionnée en char.
    int ligne;  ///Coordonnée de la ligne séléctionnée.
    int colonne;    ///Coordonnée de la colonne séléctionnée.
    int numeroDuBateau; ///Numéro du bateau à déplacer (1 à 10).
    int i;  ///Compteur.
    int j;  ///Compteur.
    int deplacementGauche=0;  ///variable qui indique si on peut se déplacer à gauche (0=non, 1=oui).
    int deplacementDroite=0;  ///variable qui indique si on peut se déplacer à droite (0=non, 1=oui).
    int deplacementHaut=0;  ///variable qui indique si on peut se déplacer en haut (0=non, 1=oui).
    int deplacementBas=0;  ///variable qui indique si on peut se déplacer en bas (0=non, 1=oui).
    int tailleEffective=0;  ///=taille-1 pour utiliser dans les conditiond de tests (pour selectionner la dernière case d'un bateau).
    int choixDeplacement=0;  ///Variable pour choisir le bateau que le joueur veut déplacer.
    int deplacementImpossible=1;    ///Variable qui indique si le déplacement est possible (pour blinder, 0=possible, 1=impossible)

    int choixDeplacementValide=0;   ///0=invalide, 1=valide.

    ///Permet de nettoyer la zone d'affichage de texte :
    gotoligcol(33,0);   ///Va au début de la zone de texte.
    for(i=0; i<11; i++) ///Pour les 20 lignes :
    {
        for(j=0; j<15; j++)    ///Et les 120 colonnes de la console :
        {
            printf("        ");    ///Afficher des espaces sur toutes la ligne.
        }
        printf("\n");   ///Recommence sur la ligne en dessous.
    }
    gotoligcol(33,0);   ///Revient au début de la zone de texte.

    printf("\tEntrez la ligne puis la colonne du bateau %c d%cplacer :\n\n", 133, 130);

    ///SI C'EST LE TOUR DU JOUEUR 1 (FONCTIONNE):
    if(*indiceJoueur==1)
    {
        while(deplacementImpossible==1)
        {
            while (test==0)
            {
                /// L'utilisateur rentre la ligne et la colonne du bateau à déplacer :
                printf("\t\tS%clectionnez la ligne : ", 130);
                scanf(" %c", &charLigne);
                ligne=charLigne-97;
                printf("\t\tS%clectionnez la colonne : ", 130);
                scanf("%d", &colonne);

                ///Vérification que la case séléctionnée contienne un bateau :
                if (tabJoueur1[ligne][colonne]==' ' || tabJoueur1[ligne][colonne]=='X')
                {
                    test=0;

                    ///Permet de nettoyer la zone d'affichage de texte :
                    gotoligcol(33,0);   ///Va au début de la zone de texte.
                    for(i=0; i<11; i++) ///Pour les 20 lignes :
                    {
                        for(j=0; j<15; j++)    ///Et les 120 colonnes de la console :
                        {
                            printf("        ");    ///Afficher des espaces sur toutes la ligne.
                        }
                        printf("\n");   ///Recommence sur la ligne en dessous.
                    }
                    gotoligcol(33,0);   ///Revient au début de la zone de texte

                    printf("\tLa case est invalide, veuillez saisir de nouvelles coordonn%ces :\n", 130);
                }
                else
                {
                    test=1;
                }
            }

            ///Parcours des coordonnées des bateaux afin de trouver une correspondance :
            for (i=0; i<10; i++)  ///Pour i allant de 0 à 10 :
            {
                for (j=0; j<7; j++)   ///Et j allant de 0 à 7 :
                {
                    if ((B1[i].tabX[j])==ligne && (B1[i].tabY[j])==colonne) ///Si les coordonnées d'un bateau sont les mêmes que les coordonnées entrées :
                    {
                        numeroDuBateau=i ;
                        j=7;    ///alors on sort de la boucle de j.
                        i=10;    ///et on sort de la boucle de i.
                    }
                }
            }

            ///Tests pour savoir comment on peut déplacer le bateau :
            ///(On utilisera désormais B1[numeroDuBateau] et on jouera avec les tabX et tabY)

            tailleEffective=(B1[numeroDuBateau].taille)-1;

            ///Si le bateau est horizontal (testé et FONCTIONNE) :
            if(B1[numeroDuBateau].orientation==0)
            {
                deplacementHaut=0;  ///Le déplacement en haut est impossible.
                deplacementBas=0;   ///Le déplacement en bas est impossible.

                ///déplacement à gauche :
                if(B1[numeroDuBateau].tabY[0]==0)   ///si la coordonnée Y de la première case du bateau est égale à 0 :
                {
                    deplacementGauche=0;    ///alors le déplacement à gauche est impossible.
                }

                else
                {
                    if(tabJoueur1[B1[numeroDuBateau].tabX[0]][B1[numeroDuBateau].tabY[0]-1]!=' ') ///Si la case précédant la première case du bateau n'est pas libre :
                    {
                        deplacementGauche=0;    ///Le déplacement à gauche est impossible.
                    }

                    else
                    {
                        deplacementGauche=1;
                    }
                }

                ///déplacement à droite :
                if(B1[numeroDuBateau].tabY[tailleEffective]==14)  ///si la coordonnée Y de la dernière case du bateau est égale à 14 :
                {
                    deplacementDroite=0;     ///alors le déplacement à droite est impossible.

                }
                else
                {
                    if(tabJoueur1[B1[numeroDuBateau].tabX[0]][B1[numeroDuBateau].tabY[tailleEffective]+1]!=' ') ///Si la case suivant la dernière case du bateau n'est pas libre :
                    {
                        deplacementDroite=0;    ///Le déplacement à droite est impossible.

                    }

                    else
                    {
                        deplacementDroite=1;

                    }
                }

                ///Test pour savoir si le bateau est touché :
                for(j=0; j<=tailleEffective; j++)
                {
                    if(tabJoueur1[B1[numeroDuBateau].tabX[0]][B1[numeroDuBateau].tabY[0]+j]=='X')   ///Si le bateau contient un X :
                    {
                        deplacementHaut=0;  ///Le déplacement en haut est impossible.
                        deplacementBas=0;   ///Le déplacement en bas est impossible.
                        deplacementGauche=0;    ///alors le déplacement à gauche est impossible.
                        deplacementDroite=0;     ///alors le déplacement à droite est impossible.
                    }
                }

            }

            ///Si le bateau est vertical (testé et FONCTIONNE) :
            if(B1[numeroDuBateau].orientation==1)
            {
                deplacementGauche=0;  ///Le déplacement en haut est impossible.
                deplacementDroite=0;   ///Le déplacement en bas est impossible.


                ///déplacement en haut :
                if(B1[numeroDuBateau].tabX[0]==0)   ///si la coordonnée X de la première case du bateau est égale à 0 :
                {
                    deplacementHaut=0;    ///alors le déplacement en haut est impossible.

                }

                else
                {
                    if(tabJoueur1[B1[numeroDuBateau].tabX[0]-1][B1[numeroDuBateau].tabY[0]]!=' ') ///Si la case précédant la première case du bateau n'est pas libre :
                    {
                        deplacementHaut=0;    ///Le déplacement en haut est impossible.

                    }

                    else
                    {
                        deplacementHaut=1;

                    }
                }

                ///déplacement en bas :
                if(B1[numeroDuBateau].tabX[tailleEffective]==14)  ///si la coordonnée X de la dernière case du bateau est égale à 14 :
                {
                    deplacementBas=0;     ///alors le déplacement en bas est impossible.

                }
                else
                {
                    if(tabJoueur1[B1[numeroDuBateau].tabX[tailleEffective]+1][B1[numeroDuBateau].tabY[0]]!=' ') ///Si la case suivant la dernière case du bateau n'est pas libre :
                    {
                        deplacementBas=0;    ///Le déplacement en bas est impossible.

                    }

                    else
                    {
                        deplacementBas=1;

                    }
                }

                ///Test pour savoir si le bateau est touché :
                for(j=0; j<=tailleEffective; j++)
                {
                    if(tabJoueur1[B1[numeroDuBateau].tabX[0]+j][B1[numeroDuBateau].tabY[0]]=='X')
                    {
                        deplacementHaut=0;  ///Le déplacement en haut est impossible.
                        deplacementBas=0;   ///Le déplacement en bas est impossible.
                        deplacementGauche=0;    ///alors le déplacement à gauche est impossible.
                        deplacementDroite=0;     ///alors le déplacement à droite est impossible.
                    }
                }
            }

            ///Si le bateau est à la fois horizontal et vertical (cas des sous-marins, testé et FONCTIONNE) :
            if(B1[numeroDuBateau].orientation==2)
            {

                ///déplacement à gauche :
                if(B1[numeroDuBateau].tabY[0]==0)   ///si la coordonnée Y de la première case du bateau est égale à 0 :
                {
                    deplacementGauche=0;    ///alors le déplacement à gauche est impossible.

                }

                else
                {
                    if(tabJoueur1[B1[numeroDuBateau].tabX[0]][B1[numeroDuBateau].tabY[0]-1]!=' ') ///Si la case précédant la première case du bateau n'est pas libre :
                    {
                        deplacementGauche=0;    ///Le déplacement à gauche est impossible.

                    }

                    else
                    {
                        deplacementGauche=1;

                    }
                }

                ///déplacement à droite :
                if(B1[numeroDuBateau].tabY[tailleEffective]==14)  ///si la coordonnée Y de la dernière case du bateau est égale à 14 :
                {
                    deplacementDroite=0;     ///alors le déplacement à droite est impossible.

                }
                else
                {
                    if(tabJoueur1[B1[numeroDuBateau].tabX[0]][B1[numeroDuBateau].tabY[tailleEffective]+1]!=' ') ///Si la case suivant la dernière case du bateau n'est pas libre :
                    {
                        deplacementDroite=0;    ///Le déplacement à droite est impossible.

                    }

                    else
                    {
                        deplacementDroite=1;

                    }
                }

                ///déplacement en haut :
                if(B1[numeroDuBateau].tabX[0]==0)   ///si la coordonnée X de la première case du bateau est égale à 0 :
                {
                    deplacementHaut=0;    ///alors le déplacement en haut est impossible.

                }

                else
                {
                    if(tabJoueur1[B1[numeroDuBateau].tabX[0]-1][B1[numeroDuBateau].tabY[0]]!=' ') ///Si la case précédant la première case du bateau n'est pas libre :
                    {
                        deplacementHaut=0;    ///Le déplacement en haut est impossible.

                    }

                    else
                    {
                        deplacementHaut=1;

                    }
                }

                ///déplacement en bas :
                if(B1[numeroDuBateau].tabX[tailleEffective]==14)  ///si la coordonnée X de la dernière case du bateau est égale à 14 :
                {
                    deplacementBas=0;     ///alors le déplacement en bas est impossible.

                }
                else
                {
                    if(tabJoueur1[B1[numeroDuBateau].tabX[tailleEffective]+1][B1[numeroDuBateau].tabY[0]]!=' ') ///Si la case suivant la dernière case du bateau n'est pas libre :
                    {
                        deplacementBas=0;    ///Le déplacement en bas est impossible.

                    }

                    else
                    {
                        deplacementBas=1;

                    }
                }

                ///Test pour savoir si le bateau est touché :
                if(tabJoueur1[B1[numeroDuBateau].tabX[0]][B1[numeroDuBateau].tabY[0]]=='X')
                {
                    deplacementHaut=0;  ///Le déplacement en haut est impossible.
                    deplacementBas=0;   ///Le déplacement en bas est impossible.
                    deplacementGauche=0;    ///alors le déplacement à gauche est impossible.
                    deplacementDroite=0;     ///alors le déplacement à droite est impossible.
                }
            }


            ///Demande à l'utilisateur de la direction souhaitée :

            if(deplacementDroite==0 && deplacementGauche==0 && deplacementBas==0 && deplacementHaut==0) ///Si le déplacement n'est possible dans aucune direction :
            {
                ///Permet de nettoyer la zone d'affichage de texte :
                gotoligcol(33,0);   ///Va au début de la zone de texte.
                for(i=0; i<11; i++) ///Pour les 20 lignes :
                {
                    for(j=0; j<15; j++)    ///Et les 120 colonnes de la console :
                    {
                        printf("        ");    ///Afficher des espaces sur toutes la ligne.
                    }
                    printf("\n");   ///Recommence sur la ligne en dessous.
                }
                gotoligcol(33,0);   ///Revient au début de la zone de texte.

                printf("\tVous ne pouvez pas d%cplacer ce bateau ! Veuillez en choisir un autre :\n\n", 130);
                deplacementImpossible=1; ///On met déplacement impossible à 1.
                test=0; ///On met le test à 0 pour pouvoir entrer de nouvelles coordonnées.
            }
            else
            {
                deplacementImpossible=0; ///On met déplacement impossible à 0.
            }


            ///Phrase personalisée en fonction du type de bateau :
            if(deplacementImpossible==0)
            {
                if(B1[numeroDuBateau].type==1)  ///Si le bateau séléctionné est un cuirassé :
                {
                    printf("\n\tDans quelle direction voulez-vous d%cplacer ce Cuirass%c ?\n", 130, 130);
                }
                if(B1[numeroDuBateau].type==2)  ///Si le bateau séléctionné est un croiseur :
                {
                    printf("\n\tDans quelle direction voulez-vous d%cplacer ce croiseur ?\n", 130);
                }
                if(B1[numeroDuBateau].type==3)  ///Si le bateau séléctionné est un destroyer :
                {
                    printf("\n\tDans quelle direction voulez-vous d%cplacer ce destroyer ?\n", 130);
                }
                if(B1[numeroDuBateau].type==4)  ///Si le bateau séléctionné est un sous-marins :
                {
                    printf("\n\tDans quelle direction voulez-vous d%cplacer ce sous-marin ?\n", 130);
                }
            }



        }



        ///DEPLACEMENT PUR DES BATEAUX :

        ///Si le joueur a choisi de déplacer le bateau à droite (testé et FONCTIONNE) :
        while(choixDeplacementValide==0)
        {
            ///Affichage personalisé en fonction des déplacement possibles :
            if(deplacementDroite==1)
            {
                printf("\tTapez 1 pour aller %c Droite.\n", 133);
                deplacementImpossible=0;
            }
            if(deplacementGauche==1)
            {
                printf("\tTapez 2 pour aller %c Gauche.\n", 133);
                deplacementImpossible=0;
            }
            if(deplacementBas==1)
            {
                printf("\tTapez 3 pour aller en Bas.\n");
                deplacementImpossible=0;
            }
            if(deplacementHaut==1)
            {
                printf("\tTapez 4 pour aller en Haut.\n");
                deplacementImpossible=0;
            }

            printf("\n\t\tChoix : ");

            scanf("%d",&choixDeplacement);  ///Saisie du choix de l'utilisateur.

            if(choixDeplacement==1 && deplacementDroite==1)
            {
                choixDeplacementValide=1;
                for(i=0; i<B1[numeroDuBateau].taille; i++)  ///Pour toutes les cases du bateau :
                {
                    ///décalage vers la droite des cases du tableau de char correspondantes au bateau séléctionné :
                    tabJoueur1[B1[numeroDuBateau].tabX[i]][B1[numeroDuBateau].tabY[i]+1]=tabJoueur1[B1[numeroDuBateau].tabX[i]][B1[numeroDuBateau].tabY[i]];
                    B1[numeroDuBateau].tabY[i]+=1;  ///Incrémentation de 1 des coordonnées des colonnes du bateau (ATTENTION : respecter cet ordre sinon ça ne marche pas).
                }
                tabJoueur1[B1[numeroDuBateau].tabX[0]][B1[numeroDuBateau].tabY[0]-1]=' ';   ///Suppression de l'icone du bateau sur l'ancienne première case.
            }
            if(choixDeplacement==1 && deplacementDroite==0) ///Si le joueur choisit d'aller à droite alors qu'il ne peut pas :
            {
                choixDeplacementValide=0;

                ///Permet de nettoyer la zone d'affichage de texte :
                gotoligcol(33,0);   ///Va au début de la zone de texte.
                for(i=0; i<11; i++) ///Pour les 20 lignes :
                {
                    for(j=0; j<15; j++)    ///Et les 120 colonnes de la console :
                    {
                        printf("        ");    ///Afficher des espaces sur toutes la ligne.
                    }
                    printf("\n");   ///Recommence sur la ligne en dessous.
                }
                gotoligcol(33,0);   ///Revient au début de la zone de texte.

                printf("\tVous ne pouvez pas aller %c droite !\n\n", 133);
                printf("\tVeuillez choisir une nouvelle direction :\n\n");

            }

            ///Si le joueur a choisi de déplacer le bateau à gauche (testé et FONCTIONNE) :
            if(choixDeplacement==2 && deplacementGauche==1)
            {
                choixDeplacementValide=1;

                for(i=0; i<B1[numeroDuBateau].taille; i++)  ///Pour toutes les cases du bateau :
                {
                    ///décalage vers la gauche des cases du tableau de char correspondantes au bateau séléctionné :
                    tabJoueur1[B1[numeroDuBateau].tabX[i]][B1[numeroDuBateau].tabY[i]-1]=tabJoueur1[B1[numeroDuBateau].tabX[i]][B1[numeroDuBateau].tabY[i]];
                    B1[numeroDuBateau].tabY[i]-=1;  ///Incrémentation de -1 des coordonnées des colonnes du bateau (ATTENTION : respecter cet ordre sinon ça ne marche pas).
                }
                tabJoueur1[B1[numeroDuBateau].tabX[0]][B1[numeroDuBateau].tabY[0]+B1[numeroDuBateau].taille]=' ';   ///Suppression de l'icone du bateau sur l'ancienne dernière case.
            }
            if(choixDeplacement==2 && deplacementGauche==0) ///Si le joueur choisit d'aller à droite alors qu'il ne peut pas :
            {
                choixDeplacementValide=0;

                ///Permet de nettoyer la zone d'affichage de texte :
                gotoligcol(33,0);   ///Va au début de la zone de texte.
                for(i=0; i<11; i++) ///Pour les 20 lignes :
                {
                    for(j=0; j<15; j++)    ///Et les 120 colonnes de la console :
                    {
                        printf("        ");    ///Afficher des espaces sur toutes la ligne.
                    }
                    printf("\n");   ///Recommence sur la ligne en dessous.
                }
                gotoligcol(33,0);   ///Revient au début de la zone de texte.

                printf("\tVous ne pouvez pas aller %c gauche !\n\n", 133);
                printf("\tVeuillez choisir une nouvelle direction :\n\n");

            }

            ///Si le joueur a choisi de déplacer le bateau en bas (testé et FONCTIONNE) :
            if(choixDeplacement==3 && deplacementBas==1)
            {
                choixDeplacementValide=1;

                for(i=0; i<B1[numeroDuBateau].taille; i++)  ///Pour toutes les cases du bateau :
                {
                    ///décalage vers le bas des cases du tableau de char correspondantes au bateau séléctionné :
                    tabJoueur1[B1[numeroDuBateau].tabX[i]+1][B1[numeroDuBateau].tabY[i]]=tabJoueur1[B1[numeroDuBateau].tabX[i]][B1[numeroDuBateau].tabY[i]];
                    B1[numeroDuBateau].tabX[i]+=1;  ///Incrémentation de 1 des coordonnées des colonnes du bateau (ATTENTION : respecter cet ordre sinon ça ne marche pas).
                }
                tabJoueur1[B1[numeroDuBateau].tabX[0]-1][B1[numeroDuBateau].tabY[0]]=' ';   ///Suppression de l'icone du bateau sur l'ancienne première case.
            }
            if(choixDeplacement==3 && deplacementBas==0) ///Si le joueur choisit d'aller à droite alors qu'il ne peut pas :
            {
                choixDeplacementValide=0;

                ///Permet de nettoyer la zone d'affichage de texte :
                gotoligcol(33,0);   ///Va au début de la zone de texte.
                for(i=0; i<11; i++) ///Pour les 20 lignes :
                {
                    for(j=0; j<15; j++)    ///Et les 120 colonnes de la console :
                    {
                        printf("        ");    ///Afficher des espaces sur toutes la ligne.
                    }
                    printf("\n");   ///Recommence sur la ligne en dessous.
                }
                gotoligcol(33,0);   ///Revient au début de la zone de texte.

                printf("\tVous ne pouvez pas aller en bas !\n\n");
                printf("\tVeuillez choisir une nouvelle direction :\n\n");

            }

            ///Si le joueur a choisi de déplacer le bateau en haut (testé et FONCTIONNE) :
            if(choixDeplacement==4 && deplacementHaut==1)
            {
                choixDeplacementValide=1;

                for(i=0; i<B1[numeroDuBateau].taille; i++)  ///Pour toutes les cases du bateau :
                {
                    ///décalage vers le haut des cases du tableau de char correspondantes au bateau séléctionné :
                    tabJoueur1[B1[numeroDuBateau].tabX[i]-1][B1[numeroDuBateau].tabY[i]]=tabJoueur1[B1[numeroDuBateau].tabX[i]][B1[numeroDuBateau].tabY[i]];
                    B1[numeroDuBateau].tabX[i]-=1;  ///Incrémentation de -1 des coordonnées des colonnes du bateau (ATTENTION : respecter cet ordre sinon ça ne marche pas).
                }
                tabJoueur1[B1[numeroDuBateau].tabX[0]+B1[numeroDuBateau].taille][B1[numeroDuBateau].tabY[0]]=' ';   ///Suppression de l'icone du bateau sur l'ancienne dernière case.
            }
            if(choixDeplacement==4 && deplacementHaut==0) ///Si le joueur choisit d'aller à droite alors qu'il ne peut pas :
            {
                choixDeplacementValide=0;

                ///Permet de nettoyer la zone d'affichage de texte :
                gotoligcol(33,0);   ///Va au début de la zone de texte.
                for(i=0; i<11; i++) ///Pour les 20 lignes :
                {
                    for(j=0; j<15; j++)    ///Et les 120 colonnes de la console :
                    {
                        printf("        ");    ///Afficher des espaces sur toutes la ligne.
                    }
                    printf("\n");   ///Recommence sur la ligne en dessous.
                }
                gotoligcol(33,0);   ///Revient au début de la zone de texte.

                printf("\tVous ne pouvez pas aller en haut !\n\n");
                printf("\tVeuillez choisir une nouvelle direction :\n\n");

            }
        }
    }


    ///SI C'EST LE TOUR DU JOUEUR 2 (FONCTIONNE):
    if(*indiceJoueur==2)
    {
        while(deplacementImpossible==1)
        {
            while (test==0)
            {
                /// L'utilisateur rentre la ligne et la colonne du bateau à déplacer :
                printf("\t\tS%clectionnez la ligne : ", 130);
                scanf(" %c", &charLigne);
                ligne=charLigne-97;
                printf("\t\tS%clectionnez la colonne : ", 130);
                scanf("%d", &colonne);

                ///Vérification que la case séléctionnée contienne un bateau :
                if (tabJoueur1[ligne][colonne]==' ' || tabJoueur1[ligne][colonne]=='X')
                {
                    test=0;

                    ///Permet de nettoyer la zone d'affichage de texte :
                    gotoligcol(33,0);   ///Va au début de la zone de texte.
                    for(i=0; i<11; i++) ///Pour les 20 lignes :
                    {
                        for(j=0; j<15; j++)    ///Et les 120 colonnes de la console :
                        {
                            printf("        ");    ///Afficher des espaces sur toutes la ligne.
                        }
                        printf("\n");   ///Recommence sur la ligne en dessous.
                    }
                    gotoligcol(33,0);   ///Revient au début de la zone de texte

                    printf("\tLa case est invalide, veuillez saisir de nouvelles coordonn%ces :\n", 130);
                }
                else
                {
                    test=1;
                }
            }

            ///Parcours des coordonnées des bateaux afin de trouver une correspondance :
            for (i=0; i<10; i++)  ///Pour i allant de 0 à 10 :
            {
                for (j=0; j<7; j++)   ///Et j allant de 0 à 7 :
                {
                    if ((B2[i].tabX[j])==ligne && (B2[i].tabY[j])==colonne) ///Si les coordonnées d'un bateau sont les mêmes que les coordonnées entrées :
                    {
                        numeroDuBateau=i ;
                        j=7;    ///alors on sort de la boucle de j.
                        i=10;    ///et on sort de la boucle de i.
                    }
                }
            }

            ///Tests pour savoir comment on peut déplacer le bateau :
            ///(On utilisera désormais B2[numeroDuBateau] et on jouera avec les tabX et tabY)

            tailleEffective=(B2[numeroDuBateau].taille)-1;

            ///Si le bateau est horizontal (testé et FONCTIONNE) :
            if(B2[numeroDuBateau].orientation==0)
            {
                deplacementHaut=0;  ///Le déplacement en haut est impossible.
                deplacementBas=0;   ///Le déplacement en bas est impossible.

                ///déplacement à gauche :
                if(B2[numeroDuBateau].tabY[0]==0)   ///si la coordonnée Y de la première case du bateau est égale à 0 :
                {
                    deplacementGauche=0;    ///alors le déplacement à gauche est impossible.
                }

                else
                {
                    if(tabJoueur1[B2[numeroDuBateau].tabX[0]][B2[numeroDuBateau].tabY[0]-1]!=' ') ///Si la case précédant la première case du bateau n'est pas libre :
                    {
                        deplacementGauche=0;    ///Le déplacement à gauche est impossible.
                    }

                    else
                    {
                        deplacementGauche=1;
                    }
                }

                ///déplacement à droite :
                if(B2[numeroDuBateau].tabY[tailleEffective]==14)  ///si la coordonnée Y de la dernière case du bateau est égale à 14 :
                {
                    deplacementDroite=0;     ///alors le déplacement à droite est impossible.

                }
                else
                {
                    if(tabJoueur1[B2[numeroDuBateau].tabX[0]][B2[numeroDuBateau].tabY[tailleEffective]+1]!=' ') ///Si la case suivant la dernière case du bateau n'est pas libre :
                    {
                        deplacementDroite=0;    ///Le déplacement à droite est impossible.

                    }

                    else
                    {
                        deplacementDroite=1;

                    }
                }

                ///Test pour savoir si le bateau est touché :
                for(j=0; j<=tailleEffective; j++)
                {
                    if(tabJoueur1[B2[numeroDuBateau].tabX[0]][B2[numeroDuBateau].tabY[0]+j]=='X')   ///Si le bateau contient un X :
                    {
                        deplacementHaut=0;  ///Le déplacement en haut est impossible.
                        deplacementBas=0;   ///Le déplacement en bas est impossible.
                        deplacementGauche=0;    ///alors le déplacement à gauche est impossible.
                        deplacementDroite=0;     ///alors le déplacement à droite est impossible.
                    }
                }

            }

            ///Si le bateau est vertical (testé et FONCTIONNE) :
            if(B2[numeroDuBateau].orientation==1)
            {
                deplacementGauche=0;  ///Le déplacement en haut est impossible.
                deplacementDroite=0;   ///Le déplacement en bas est impossible.


                ///déplacement en haut :
                if(B2[numeroDuBateau].tabX[0]==0)   ///si la coordonnée X de la première case du bateau est égale à 0 :
                {
                    deplacementHaut=0;    ///alors le déplacement en haut est impossible.

                }

                else
                {
                    if(tabJoueur1[B2[numeroDuBateau].tabX[0]-1][B2[numeroDuBateau].tabY[0]]!=' ') ///Si la case précédant la première case du bateau n'est pas libre :
                    {
                        deplacementHaut=0;    ///Le déplacement en haut est impossible.

                    }

                    else
                    {
                        deplacementHaut=1;

                    }
                }

                ///déplacement en bas :
                if(B2[numeroDuBateau].tabX[tailleEffective]==14)  ///si la coordonnée X de la dernière case du bateau est égale à 14 :
                {
                    deplacementBas=0;     ///alors le déplacement en bas est impossible.

                }
                else
                {
                    if(tabJoueur1[B2[numeroDuBateau].tabX[tailleEffective]+1][B2[numeroDuBateau].tabY[0]]!=' ') ///Si la case suivant la dernière case du bateau n'est pas libre :
                    {
                        deplacementBas=0;    ///Le déplacement en bas est impossible.

                    }

                    else
                    {
                        deplacementBas=1;

                    }
                }

                ///Test pour savoir si le bateau est touché :
                for(j=0; j<=tailleEffective; j++)
                {
                    if(tabJoueur1[B2[numeroDuBateau].tabX[0]+j][B2[numeroDuBateau].tabY[0]]=='X')
                    {
                        deplacementHaut=0;  ///Le déplacement en haut est impossible.
                        deplacementBas=0;   ///Le déplacement en bas est impossible.
                        deplacementGauche=0;    ///alors le déplacement à gauche est impossible.
                        deplacementDroite=0;     ///alors le déplacement à droite est impossible.
                    }
                }
            }

            ///Si le bateau est à la fois horizontal et vertical (cas des sous-marins, testé et FONCTIONNE) :
            if(B2[numeroDuBateau].orientation==2)
            {

                ///déplacement à gauche :
                if(B2[numeroDuBateau].tabY[0]==0)   ///si la coordonnée Y de la première case du bateau est égale à 0 :
                {
                    deplacementGauche=0;    ///alors le déplacement à gauche est impossible.

                }

                else
                {
                    if(tabJoueur1[B2[numeroDuBateau].tabX[0]][B2[numeroDuBateau].tabY[0]-1]!=' ') ///Si la case précédant la première case du bateau n'est pas libre :
                    {
                        deplacementGauche=0;    ///Le déplacement à gauche est impossible.

                    }

                    else
                    {
                        deplacementGauche=1;

                    }
                }

                ///déplacement à droite :
                if(B2[numeroDuBateau].tabY[tailleEffective]==14)  ///si la coordonnée Y de la dernière case du bateau est égale à 14 :
                {
                    deplacementDroite=0;     ///alors le déplacement à droite est impossible.

                }
                else
                {
                    if(tabJoueur1[B2[numeroDuBateau].tabX[0]][B2[numeroDuBateau].tabY[tailleEffective]+1]!=' ') ///Si la case suivant la dernière case du bateau n'est pas libre :
                    {
                        deplacementDroite=0;    ///Le déplacement à droite est impossible.

                    }

                    else
                    {
                        deplacementDroite=1;

                    }
                }

                ///déplacement en haut :
                if(B2[numeroDuBateau].tabX[0]==0)   ///si la coordonnée X de la première case du bateau est égale à 0 :
                {
                    deplacementHaut=0;    ///alors le déplacement en haut est impossible.

                }

                else
                {
                    if(tabJoueur1[B2[numeroDuBateau].tabX[0]-1][B2[numeroDuBateau].tabY[0]]!=' ') ///Si la case précédant la première case du bateau n'est pas libre :
                    {
                        deplacementHaut=0;    ///Le déplacement en haut est impossible.

                    }

                    else
                    {
                        deplacementHaut=1;

                    }
                }

                ///déplacement en bas :
                if(B2[numeroDuBateau].tabX[tailleEffective]==14)  ///si la coordonnée X de la dernière case du bateau est égale à 14 :
                {
                    deplacementBas=0;     ///alors le déplacement en bas est impossible.

                }
                else
                {
                    if(tabJoueur1[B2[numeroDuBateau].tabX[tailleEffective]+1][B2[numeroDuBateau].tabY[0]]!=' ') ///Si la case suivant la dernière case du bateau n'est pas libre :
                    {
                        deplacementBas=0;    ///Le déplacement en bas est impossible.

                    }

                    else
                    {
                        deplacementBas=1;

                    }
                }

                ///Test pour savoir si le bateau est touché :
                if(tabJoueur1[B2[numeroDuBateau].tabX[0]][B2[numeroDuBateau].tabY[0]]=='X')
                {
                    deplacementHaut=0;  ///Le déplacement en haut est impossible.
                    deplacementBas=0;   ///Le déplacement en bas est impossible.
                    deplacementGauche=0;    ///alors le déplacement à gauche est impossible.
                    deplacementDroite=0;     ///alors le déplacement à droite est impossible.
                }
            }


            ///Demande à l'utilisateur de la direction souhaitée :

            if(deplacementDroite==0 && deplacementGauche==0 && deplacementBas==0 && deplacementHaut==0) ///Si le déplacement n'est possible dans aucune direction :
            {
                ///Permet de nettoyer la zone d'affichage de texte :
                gotoligcol(33,0);   ///Va au début de la zone de texte.
                for(i=0; i<11; i++) ///Pour les 20 lignes :
                {
                    for(j=0; j<15; j++)    ///Et les 120 colonnes de la console :
                    {
                        printf("        ");    ///Afficher des espaces sur toutes la ligne.
                    }
                    printf("\n");   ///Recommence sur la ligne en dessous.
                }
                gotoligcol(33,0);   ///Revient au début de la zone de texte.

                printf("\tVous ne pouvez pas d%cplacer ce bateau ! Veuillez en choisir un autre :\n\n", 130);
                deplacementImpossible=1; ///On met déplacement impossible à 1.
                test=0; ///On met le test à 0 pour pouvoir entrer de nouvelles coordonnées.
            }
            else
            {
                deplacementImpossible=0; ///On met déplacement impossible à 0.
            }


            ///Phrase personalisée en fonction du type de bateau :
            if(deplacementImpossible==0)
            {
                if(B2[numeroDuBateau].type==1)  ///Si le bateau séléctionné est un cuirassé :
                {
                    printf("\n\tDans quelle direction voulez-vous d%cplacer ce Cuirass%c ?\n", 130, 130);
                }
                if(B2[numeroDuBateau].type==2)  ///Si le bateau séléctionné est un croiseur :
                {
                    printf("\n\tDans quelle direction voulez-vous d%cplacer ce croiseur ?\n", 130);
                }
                if(B2[numeroDuBateau].type==3)  ///Si le bateau séléctionné est un destroyer :
                {
                    printf("\n\tDans quelle direction voulez-vous d%cplacer ce destroyer ?\n", 130);
                }
                if(B2[numeroDuBateau].type==4)  ///Si le bateau séléctionné est un sous-marins :
                {
                    printf("\n\tDans quelle direction voulez-vous d%cplacer ce sous-marin ?\n", 130);
                }
            }



        }



        ///DEPLACEMENT PUR DES BATEAUX :

        ///Si le joueur a choisi de déplacer le bateau à droite (testé et FONCTIONNE) :
        while(choixDeplacementValide==0)
        {
            ///Affichage personalisé en fonction des déplacement possibles :
            if(deplacementDroite==1)
            {
                printf("\tTapez 1 pour aller %c Droite.\n", 133);
                deplacementImpossible=0;
            }
            if(deplacementGauche==1)
            {
                printf("\tTapez 2 pour aller %c Gauche.\n", 133);
                deplacementImpossible=0;
            }
            if(deplacementBas==1)
            {
                printf("\tTapez 3 pour aller en Bas.\n");
                deplacementImpossible=0;
            }
            if(deplacementHaut==1)
            {
                printf("\tTapez 4 pour aller en Haut.\n");
                deplacementImpossible=0;
            }

            printf("\n\t\tChoix : ");

            scanf("%d",&choixDeplacement);  ///Saisie du choix de l'utilisateur.

            if(choixDeplacement==1 && deplacementDroite==1)
            {
                choixDeplacementValide=1;
                for(i=0; i<B2[numeroDuBateau].taille; i++)  ///Pour toutes les cases du bateau :
                {
                    ///décalage vers la droite des cases du tableau de char correspondantes au bateau séléctionné :
                    tabJoueur1[B2[numeroDuBateau].tabX[i]][B2[numeroDuBateau].tabY[i]+1]=tabJoueur1[B2[numeroDuBateau].tabX[i]][B2[numeroDuBateau].tabY[i]];
                    B2[numeroDuBateau].tabY[i]+=1;  ///Incrémentation de 1 des coordonnées des colonnes du bateau (ATTENTION : respecter cet ordre sinon ça ne marche pas).
                }
                tabJoueur1[B2[numeroDuBateau].tabX[0]][B2[numeroDuBateau].tabY[0]-1]=' ';   ///Suppression de l'icone du bateau sur l'ancienne première case.
            }
            if(choixDeplacement==1 && deplacementDroite==0) ///Si le joueur choisit d'aller à droite alors qu'il ne peut pas :
            {
                choixDeplacementValide=0;

                ///Permet de nettoyer la zone d'affichage de texte :
                gotoligcol(33,0);   ///Va au début de la zone de texte.
                for(i=0; i<11; i++) ///Pour les 20 lignes :
                {
                    for(j=0; j<15; j++)    ///Et les 120 colonnes de la console :
                    {
                        printf("        ");    ///Afficher des espaces sur toutes la ligne.
                    }
                    printf("\n");   ///Recommence sur la ligne en dessous.
                }
                gotoligcol(33,0);   ///Revient au début de la zone de texte.

                printf("\tVous ne pouvez pas aller %c droite !\n\n", 133);
                printf("\tVeuillez choisir une nouvelle direction :\n\n");

            }

            ///Si le joueur a choisi de déplacer le bateau à gauche (testé et FONCTIONNE) :
            if(choixDeplacement==2 && deplacementGauche==1)
            {
                choixDeplacementValide=1;

                for(i=0; i<B2[numeroDuBateau].taille; i++)  ///Pour toutes les cases du bateau :
                {
                    ///décalage vers la gauche des cases du tableau de char correspondantes au bateau séléctionné :
                    tabJoueur1[B2[numeroDuBateau].tabX[i]][B2[numeroDuBateau].tabY[i]-1]=tabJoueur1[B2[numeroDuBateau].tabX[i]][B2[numeroDuBateau].tabY[i]];
                    B2[numeroDuBateau].tabY[i]-=1;  ///Incrémentation de -1 des coordonnées des colonnes du bateau (ATTENTION : respecter cet ordre sinon ça ne marche pas).
                }
                tabJoueur1[B2[numeroDuBateau].tabX[0]][B2[numeroDuBateau].tabY[0]+B2[numeroDuBateau].taille]=' ';   ///Suppression de l'icone du bateau sur l'ancienne dernière case.
            }
            if(choixDeplacement==2 && deplacementGauche==0) ///Si le joueur choisit d'aller à droite alors qu'il ne peut pas :
            {
                choixDeplacementValide=0;

                ///Permet de nettoyer la zone d'affichage de texte :
                gotoligcol(33,0);   ///Va au début de la zone de texte.
                for(i=0; i<11; i++) ///Pour les 20 lignes :
                {
                    for(j=0; j<15; j++)    ///Et les 120 colonnes de la console :
                    {
                        printf("        ");    ///Afficher des espaces sur toutes la ligne.
                    }
                    printf("\n");   ///Recommence sur la ligne en dessous.
                }
                gotoligcol(33,0);   ///Revient au début de la zone de texte.

                printf("\tVous ne pouvez pas aller %c gauche !\n\n", 133);
                printf("\tVeuillez choisir une nouvelle direction :\n\n");

            }

            ///Si le joueur a choisi de déplacer le bateau en bas (testé et FONCTIONNE) :
            if(choixDeplacement==3 && deplacementBas==1)
            {
                choixDeplacementValide=1;

                for(i=0; i<B2[numeroDuBateau].taille; i++)  ///Pour toutes les cases du bateau :
                {
                    ///décalage vers le bas des cases du tableau de char correspondantes au bateau séléctionné :
                    tabJoueur1[B2[numeroDuBateau].tabX[i]+1][B2[numeroDuBateau].tabY[i]]=tabJoueur1[B2[numeroDuBateau].tabX[i]][B2[numeroDuBateau].tabY[i]];
                    B2[numeroDuBateau].tabX[i]+=1;  ///Incrémentation de 1 des coordonnées des colonnes du bateau (ATTENTION : respecter cet ordre sinon ça ne marche pas).
                }
                tabJoueur1[B2[numeroDuBateau].tabX[0]-1][B2[numeroDuBateau].tabY[0]]=' ';   ///Suppression de l'icone du bateau sur l'ancienne première case.
            }
            if(choixDeplacement==3 && deplacementBas==0) ///Si le joueur choisit d'aller à droite alors qu'il ne peut pas :
            {
                choixDeplacementValide=0;

                ///Permet de nettoyer la zone d'affichage de texte :
                gotoligcol(33,0);   ///Va au début de la zone de texte.
                for(i=0; i<11; i++) ///Pour les 20 lignes :
                {
                    for(j=0; j<15; j++)    ///Et les 120 colonnes de la console :
                    {
                        printf("        ");    ///Afficher des espaces sur toutes la ligne.
                    }
                    printf("\n");   ///Recommence sur la ligne en dessous.
                }
                gotoligcol(33,0);   ///Revient au début de la zone de texte.

                printf("\tVous ne pouvez pas aller en bas !\n\n");
                printf("\tVeuillez choisir une nouvelle direction :\n\n");

            }

            ///Si le joueur a choisi de déplacer le bateau en haut (testé et FONCTIONNE) :
            if(choixDeplacement==4 && deplacementHaut==1)
            {
                choixDeplacementValide=1;

                for(i=0; i<B2[numeroDuBateau].taille; i++)  ///Pour toutes les cases du bateau :
                {
                    ///décalage vers le haut des cases du tableau de char correspondantes au bateau séléctionné :
                    tabJoueur1[B2[numeroDuBateau].tabX[i]-1][B2[numeroDuBateau].tabY[i]]=tabJoueur1[B2[numeroDuBateau].tabX[i]][B2[numeroDuBateau].tabY[i]];
                    B2[numeroDuBateau].tabX[i]-=1;  ///Incrémentation de -1 des coordonnées des colonnes du bateau (ATTENTION : respecter cet ordre sinon ça ne marche pas).
                }
                tabJoueur1[B2[numeroDuBateau].tabX[0]+B2[numeroDuBateau].taille][B2[numeroDuBateau].tabY[0]]=' ';   ///Suppression de l'icone du bateau sur l'ancienne dernière case.
            }
            if(choixDeplacement==4 && deplacementHaut==0) ///Si le joueur choisit d'aller à droite alors qu'il ne peut pas :
            {
                choixDeplacementValide=0;

                ///Permet de nettoyer la zone d'affichage de texte :
                gotoligcol(33,0);   ///Va au début de la zone de texte.
                for(i=0; i<11; i++) ///Pour les 20 lignes :
                {
                    for(j=0; j<15; j++)    ///Et les 120 colonnes de la console :
                    {
                        printf("        ");    ///Afficher des espaces sur toutes la ligne.
                    }
                    printf("\n");   ///Recommence sur la ligne en dessous.
                }
                gotoligcol(33,0);   ///Revient au début de la zone de texte.

                printf("\tVous ne pouvez pas aller en haut !\n\n");
                printf("\tVeuillez choisir une nouvelle direction :\n\n");

            }
        }
    }


}

