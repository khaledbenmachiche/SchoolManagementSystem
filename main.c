#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "bib_TBOF_ARCHIVAGE.h"

void menu_intro()
{
    system("cls");
    system("Color 2");
    printf("--------------------------------------------------------------------------- \n");
    printf("|       -ESI-          ECOLE SUPERIEUR D'INFORMATIQUE          -ESI-      |\n");
    printf("|                                                                         |\n");
    printf("|                    TP N*1 ~Gestion de la scolarite~ TP N*1              |\n");
    printf("|                                                                         |\n");
    printf("|  BINOME N*11:                                                           |\n");
    printf("|  BAZOULA CERINE.                                            -SFSD-      |\n");
    printf("|  BENMACHICHE KHALED.                                                    |\n");
    printf("|                                                           SEMESTRE -1-  |\n");
    printf("---------------------------------------------------------------------------\n");
}
int menu_1()
{
    system("cls");
    system("Color 2");
    printf("--------------------------------------------------------------------------------- \n");
    printf("|                MENU PRINCIPALE, CHOISISSEZ UNE OPTION                         |\n");
    printf("-------------------------------------------------------------------------------- \n");
    printf("|                                                                               |\n");
    printf("|     >>[1]  Creation de fichier des informations scolaires des eleves -TOVC-   |\n");
    printf("|     >>[2]  Reponse de la question 3.b.i et des remarques sur le TP            |\n");
    printf("|     >>[3]  QUITTER LE PROGRAMME                                               |\n");
    printf("|                                                                               |\n");
    printf("--------------------------------------------------------------------------------- \n");
    printf("\n");
    int choix;
    printf("-->>Entrez votre choix ic : ");
    scanf("%d", &choix);
    return choix;
}

int menu_Reponce_remarque()
{
    printf("************************************-REMARQUES ET REPONSE DE LA QUESTION -3.b.i-************************************************************************************\n");
    printf("| -----------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
    printf("|>>>La question -3.b.i- :                                                                                                                                          |\n");
    printf("|L'INDEX DANS CE CAS EST UN INDEX DENSE.                                                                                                                           |\n");
    printf("|LA CLE SERA LA MOYENNE DE L'ETUDIANT DE L'ANNEE EN QUESTION.                                                                                                      |\n");
    printf("|PAR EXAMPLE DANS L'INDEX 1 , LA CLE SERA LA MOYENNE DE L'ETUDIANT SUR CET ANNEE.                                                                                  |\n");
    printf("|------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
    printf("|>>>Remarque:                                                                                                                                                      |\n");
    printf("|POUR UN SEULE ARCHIVE SUR 5 ANS IL Y'AURA POUR TOUT LES ETUDIANTS 5 INDEX , POUR LA 1ER, 2EM , 3EM , 4EM , 5EM ANNEE.                                             |\n");
    printf("|POUR LE PRESCOLAIRE ON VAS PAS FAIRE UN INDEX CAR TOUT LES ETUDIANTS VONT AVOIR UNE MOYENNE 20/20 , ON OPTIMISE LES RESOURCES.                                    |\n");
    printf("********************************************************************************************************************************************************************\n");
}

int menu_choix_fichier()
{
    system("cls");
    system("Color 2");
    printf("----------------------------------------------------------------------- \n");
    printf("|                MENU PRINCIPALE, CHOISISSEZ UNE OPTION                |\n");
    printf("----------------------------------------------------------------------- \n");
    printf("|                                                                      |\n");
    printf("|        CHOISISSEZ L'OPERATIONS QUE VOULER FAIRE :                    |\n");
    printf("|         >>[1] Les Operations sur le fichier -TOVC-                   |\n");
    printf("|         >>[2] Creation de fichier archive -T~OF-                     |\n");
    printf("|                                                                      |\n");
    printf("----------------------------------------------------------------------- \n");
    printf("\n");
    int choix;
    printf("-->>Entrez l'operation que vous avez choisit : ");
    scanf("%d", &choix);
    return choix;
}

int menu_operation_TOVC()
{
    system("cls");
    system("Color 2");
    printf("----------------------------------------------------------------------- \n");
    printf("|                MENU PRINCIPALE, CHOISISSEZ UNE OPTION                |\n");
    printf("----------------------------------------------------------------------- \n");
    printf("|                                                                      |\n");
    printf("|   CHOISISSEZ L'OPERATIONS QUE VOULER FAIRE SUR FICHIER -TOVC- :      |\n");
    printf("|         >>[1] RECHERCHE d'un eleve.                                  |\n");
    printf("|         >>[2] RECHERCHE par numero d'enregistrement d'eleve.         |\n");
    printf("|         >>[3] INSERTION d'un nouveau eleve.                          |\n");
    printf("|         >>[4] SUPPRISSION d'un eleve.                                |\n");
    printf("|         >>[5] SUPPRISSION par position.                              |\n");
    printf("|         >>[6] MISE A JOUR les informations personnelles d'un eleve.  |\n");
    printf("|                                                                      |\n");
    printf("----------------------------------------------------------------------- \n");
    printf("\n");
    int choix;
    printf("-->>Entrez l'operation que vous avez choisit : ");
    scanf("%d", &choix);
    return choix;
}
int menu_choix_mise_a_jour()
{
    system("cls");
    system("Color 2");
    printf("----------------------------------------------------------------------- \n");
    printf("|                MENU PRINCIPALE, CHOISISSEZ UNE OPTION                |\n");
    printf("----------------------------------------------------------------------- \n");
    printf("|                                                                      |\n");
    printf("|        CHOISISSEZ L'OPERATIONS QUE VOULER FAIRE :                    |\n");
    printf("|         >>[1] M-J-R de NOM.                                          |\n");
    printf("|         >>[2] M-J-R de PRENOM.                                       |\n");
    printf("|         >>[3] M-J-R de GENRE.                                        |\n");
    printf("|         >>[4] M-J-R de BULTIN.                                       |\n");
    printf("|         >>[5] M-J-R de IDCLASSE.                                     |\n");
    printf("|         >>[6] M-J-R de tout les informations.                        |\n");
    printf("|                                                                      |\n");
    printf("----------------------------------------------------------------------- \n");
    printf("\n");
    int choix;
    printf("-->>Entrez l'operation que vous avez choisit : ");
    scanf("%d", &choix);
    return choix;
}
int menu_2()
{
    system("cls");
    system("Color 2");
    printf("----------------------------------------------------------------------- \n");
    printf("|                MENU PRINCIPALE, CHOISISSEZ UNE OPTION                |\n");
    printf("----------------------------------------------------------------------- \n");
    printf("|                                                                      |\n");
    printf("|        CHOISISSEZ L'OPERATIONS QUE VOULER FAIRE :                    |\n");
    printf("|         >>[1] Les Operations sur le fichier -T~OF-                   |\n");
    printf("|         >>[2] les Operations de Transfert.                           |\n");
    printf("|                                                                      |\n");
    printf("----------------------------------------------------------------------- \n");
    printf("\n");
    int choix;
    printf("-->>Entrez l'operation que vous avez choisit : ");
    scanf("%d", &choix);
    return choix;
}

int menu_operation_Transfert()
{
    system("cls");
    system("Color 2");
    printf("----------------------------------------------------------------------- \n");
    printf("|                MENU PRINCIPALE, CHOISISSEZ UNE OPTION                |\n");
    printf("----------------------------------------------------------------------- \n");
    printf("|                                                                      |\n");
    printf("|        CHOISISSEZ L'OPERATIONS QUE VOULER FAIRE :                    |\n");
    printf("|         >>[1] Transfert d'un eleve de cette ecole a une autre.       |\n");
    printf("|         >>[2] Recevoir un eleve d'une autre ecole.                   |\n");
    printf("|                                                                      |\n");
    printf("----------------------------------------------------------------------- \n");
    printf("\n");
    int choix;
    printf("-->>Entrez l'operation que vous avez choisit : ");
    scanf("%d", &choix);
    return choix;
}

int menu_opertion_TOF()
{
    system("cls");
    system("Color 2");
    printf("----------------------------------------------------------------------- \n");
    printf("|                MENU PRINCIPALE, CHOISISSEZ UNE OPTION                |\n");
    printf("----------------------------------------------------------------------- \n");
    printf("|                                                                      |\n");
    printf("|  CHOISISSEZ L'OPERATIONS QUE VOULER FAIRE SUR FICHIER ARCHIVE T~OF:  |\n");
    printf("|         >>[1] INSERTION d'un eleve dans L'archive T~OF.              |\n");
    printf("|         >>[2] SUPPRISSION d'un eleve de l'archive T~OF.              |\n");
    printf("|         >>[3] RECHRECHE par intervalle dans une annee.(R-a-I)        |\n");
    printf("|         >>[4] Lister les eleves ayant obtenu une moyenne--           |\n");
    printf("|               --superieure a 12 sur les 5 annees par R-a-I           |\n");
    printf("|                                                                      |\n");
    printf("----------------------------------------------------------------------- \n");
    printf("\n");
    int choix;
    printf("-->>Entrez l'operation que vous avez choisit : ");
    scanf("%d", &choix);
    return choix;
}
int menu_choix_fichier_R_A_I()
{
    system("cls");
    system("Color 2");
    printf("----------------------------------------------------------------------- \n");
    printf("|                MENU PRINCIPALE, CHOISISSEZ UNE OPTION                |\n");
    printf("----------------------------------------------------------------------- \n");
    printf("|                                                                      |\n");
    printf("|  CHOISISSEZ LE FICHIER T~OF POUR FAIRE LA RECHERCHE PAR INTERVALLE:  |\n");
    printf("|         >>[1] LE FICHIER 1 DE L'ANNEE 1 DE LA SIMULATION.            |\n");
    printf("|         >>[2] LE FICHIER 2 DE L'ANNEE 2 DE LA SIMULATION.            |\n");
    printf("|         >>[3] LE FICHIER 3 DE L'ANNEE 3 DE LA SIMULATION.            |\n");
    printf("|         >>[4] LE FICHIER 4 DE L'ANNEE 4 DE LA SIMULATION.            |\n");
    printf("|         >>[5] LE FICHIER 5 DE L'ANNEE 5 DE LA SIMULATION.            |\n");
    printf("|                                                                      |\n");
    printf("----------------------------------------------------------------------- \n");
    printf("\n");
    int choix_fichier;
    printf("-->>Entrez le numero du fichier que vous avez choisit : ");
    scanf("%d", &choix_fichier);
    return choix_fichier;
}

void type_donnee()
{
    printf("|************************************************************************************|\n");
    printf("|  SUPPRIMER |  IDELEVE    |  IDCLASSE   | nomPrenomGenre    |       BULTIN          |\n");
    printf("|  (1 byte)  |  (4 bytes)  |  (3 bytes)  | (taille variable) |  (taille variable)    |\n");
    printf("|************************************************************************************|\n");
}

void Quite_programme()
{
    printf("**************************************************************\n");
    printf("| .                           .                         .    |\n");
    printf("|     .     ESI        @      .    #        2CP      .       |\n");
    printf("| ?      . _____________________________________ .           |\n");
    printf("|          |   0        1     0     1       0   |     =      |\n");
    printf("|. . . . . |      1         MERCI         0     | . . . . . .|\n");
    printf("|          |  1     0     1    0       1      1 |            |\n");
    printf("|          |____________________________________|     $      |\n");
    printf("|   *     .                   .                   .          |\n");
    printf("|      .     SFSD   &         .        2023-2022    .        |\n");
    printf("|   .                          .   !                    .    |\n");
    printf("*************************************************************\n");
}

int main()
{ /*ESPACE POUR LES VARIABLES DE PROGRAMME PRINCIPAL*/
    //-----------------------------------
    TOVC *fTOVC1 = NULL,
         *fTOVC2 = NULL;
    //-----------------------------------
    TOF_index *fIndex1 = NULL,
              *fIndex2 = NULL,
              *fIndex3 = NULL,
              *fIndex4 = NULL,
              *fIndex5 = NULL;
    //-----------------------------------
    TOF_sauv *fsauv;
    //-----------------------------------
    TBOF *fArchive1 = NULL,
         *fArchive2 = NULL;
    //-----------------------------------
    FILE *f = NULL;
    //-----------------------------------
    Tenreg_TBOF engArchive;
    enregEleve eleve;
    //-----------------------------------
    char nom[MAX_NOM_PRENOM],
        prenom[MAX_NOM_PRENOM],
        idClasse[sizeID_Classe + 1],
        idEleve[sizeID_Eleve + 1],
        bultin[50],
        donneEleve[100];
    //-----------------------------------
    char *strEleve = NULL,
         *nomPrenomGenre = NULL;
    //-----------------------------------
    char genre = '\0';
    //-----------------------------------
    int pos_i = 0,
        pos_j = 0,
        position = 0,
        ans = 0,
        ID_ELEVE = 0,
        tmp = 0;
    //-----------------------------------
    float min = 0,
          max = 0,
          moyenneInf = 0;
    //-----------------------------------
    //-------------------------------------------------------------------------------//
    char ch,
        reponse_M_A_J = 'y';
    int creation_TOVC, choix_fichier, choix_operation_TOVC, choix_mise_a_jour, choix_menu_2, choix_opertion_TOF, choix_operation_Transfert;
    //------------------------------------------------------------------------------//
    menu_intro();
    printf("\n");
    printf("\n");
    printf("press charactere key to continue......");
    scanf("%s", &ch);

    /*varibale pour les programme*/
    creation_TOVC = menu_1();
    type_donnee();
    printf("press charactere key to continue......");
    scanf("%s", &ch);

    switch (creation_TOVC) // Creation de fichier des informations scolaires des eleves -TOVC- /QUITE
    {
    case 1:
        system("cls");
        printf("--------------------------------------------------------------------------------------------- \n");
        printf("|              CREATION DE FICHIER DES INFORMATIONS SCOLAIRES DES ELEVES -TOVC-            |\n");
        printf("-------------------------------------------------------------------------------------------- \n");
        /* ---------------------------------LE PROGRAMME DE LA CREATION DE -TOVC-*--------------------------------------------------------*/
        fTOVC1 = Ouvrir_TOVC("./ecole1/Dossier_Des_Annees/FICHIER_TOVC1", 'N');
        chargementInitialTOVC(fTOVC1);
        printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR BLOC]<<<\n\n");
        Affichage_TOVC(fTOVC1);
        printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE]<<<\n\n");
        affichageParEnregTOVC(fTOVC1);
        printf("\n\npress charactere key to continue......");
        scanf("%s", &ch);
        // il faut faire affichage ici pour montrer que le fichier a ete cree
        //---------------------------------------------------------------------------------------------------------------------------------//
        choix_fichier = menu_choix_fichier();
        switch (choix_fichier)
        {
        case 1: // Les Operations sur le fichier -TOVC-
            choix_operation_TOVC = menu_operation_TOVC();
            switch (choix_operation_TOVC)
            {
            case 1: // RECHERCHE D'UN ELEVE
                system("cls");
                printf("--------------------------------------------------------------------------------------------- \n");
                printf("|                        RECHRECHE D'UN ELEVE DANS LE FICHIER -TOVC                        |\n");
                printf("-------------------------------------------------------------------------------------------- \n");
                /*       LE PROGRAMME DE LA RECHRECHE D'UN ELEVE DANS TOVC*/
                printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR BLOC]<<<\n\n");
                Affichage_TOVC(fTOVC1);
                printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE]<<<\n\n");
                affichageParEnregTOVC(fTOVC1);
                printf(">>> ENTRER LES CLEs DE RECHERCHE : \n");
                printf(">>> ENTRER L'ID CLASSE : ");
                scanf("%s", idClasse);
                printf("\n>>> ENTRER LE NOM :");
                scanf("%s", nom);
                toUpperCase(nom);
                printf("\n>>> ENTRER LE PRENOM :");
                scanf("%s", prenom);
                toUpperCase(prenom);
                if (rechercheTOVC(fTOVC1, idClasse, prenom, nom, &pos_i, &pos_j))
                {
                    printf("ELEVE TROUVER, LA POSITION DE L'ELEVE APRES LA RECHERCHE DANS LE FICHIER TOVC EST --> [i , j] = [%d ; %d]\n\n", pos_i, pos_j);
                }
                else
                {
                    printf("ELEVE NON TROUVER , LA POSITION DE L'INSERTION --> [i , j] = [%d ; %d]\n\n", pos_i, pos_j);
                }
                Fermer_TOVC(fTOVC1);
                //---------------------------------------------------//
                printf("\n\npress charactere key to continue......");
                scanf("%s", &ch);
                break;

            case 2:
                system("cls");
                printf("--------------------------------------------------------------------------------------------- \n");
                printf("|            RECHRECHE PAR NUMERO D'ENREGISTREMENT D'UN ELEVE DANS LE FICHIER -TOVC         |\n");
                printf("-------------------------------------------------------------------------------------------- \n");
                /*       LE PROGRAMME DE RECHRECHE PAR NUMERO D'ENREGISTREMENT D'UN ELEVE DANS LE FICHIER -TOVC   */
                printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR BLOC]<<<\n\n");
                Affichage_TOVC(fTOVC1);
                printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE]<<<\n\n");
                affichageParEnregTOVC(fTOVC1);
                printf("\n\n>>> ENTRER LA POSITION DE L'ELEVE QUE VOUS VOULEZ CHANGER SAVOIR SA POSITION DANS LE FICHIER TOVC ");
                printf("\n\n>>> Position : ");
                scanf("%d", &position);
                if (rechercheTOVCParEnreg(fTOVC1, position, &pos_i, &pos_j))
                {
                    printf("ELEVE TROUVER, LA POSITION DE L'ELEVE APRES LA RECHERCHE DANS LE FICHIER TOVC EST --> [i , j] = [%d ; %d]\n\n", pos_i, pos_j);
                }
                else
                {
                    printf("ELEVE NON TROUVER , LA POSITION DE L'INSERTION --> [i , j] = [%d ; %d]\n\n", pos_i, pos_j);
                }
                Fermer_TOVC(fTOVC1);
                //---------------------------------------------------//
                printf("\n\npress charactere key to continue......");
                scanf("%s", &ch);
                break;

            case 3: // INSERTION D'UN ELEVE
                system("cls");
                printf("--------------------------------------------------------------------------------------------- \n");
                printf("|                        INSERTION D'UN ELEVE DANS LE FICHIER -TOVC                         |\n");
                printf("-------------------------------------------------------------------------------------------- \n");
                /*       LE PROGRAMME DE L'INSERTION D'UN ELEVE DANS TOVC*/
                printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR BLOC]<<<\n\n");
                Affichage_TOVC(fTOVC1);
                printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE]<<<\n\n");
                affichageParEnregTOVC(fTOVC1);
                //-------------------------------------------------
                memset(nom, '\0', MAX_NOM_PRENOM * sizeof(char));
                memset(prenom, '\0', MAX_NOM_PRENOM * sizeof(char));
                //-------------------------------------------------
                printf(">>> ENTRER LES CLEs DE RECHERCHE POUR INSERER : \n\n");
                printf(">>> ENTRER ANNEE COURANTE DE L'ELEVE A INSERER : ");
                scanf("%d", &ans);
                printf("\n>>> ENTRER LE NOM : ");
                scanf("%s", nom);
                toUpperCase(nom);
                printf("\n>>> ENTRER LE PRENOM : ");
                scanf("%s", prenom);
                toUpperCase(prenom);
                printf("\n>>> ENTRER LE GENRE : ");
                scanf("%s", &genre);
                nomPrenomGenre = creerNomPrenomGenre(nom, prenom, genre);
                fsauv = Ouvrir_TOF_sauv("SAUVGARDE_ID_ELEVE", 'A');
                if (fsauv == NULL)
                {
                    Fermer_TOVC(fTOVC1);
                    exit(EXIT_FAILURE);
                }
                //-------------------------------------
                eleve.supp = '0';
                eleve.idEleve = IdEleveGenerator(fsauv);
                eleve.idClasse = genererIdClasse(ans + '0');
                eleve.nomPrenomGenre = nomPrenomGenre;
                eleve.bultin = bultinGenerator(ans + '0');
                //-------------------------------------------------
                strEleve = ConvertionEnregEleveChaine(eleve);
                libererEleve(eleve);
                if (insertionTOVC(fTOVC1, &strEleve))
                {
                    printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR BLOC APRES L'INSERTION]<<<\n\n");
                    Affichage_TOVC(fTOVC1);
                    printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE APRES L'INSERTION]<<<\n\n");
                    affichageParEnregTOVC(fTOVC1);
                }
                else
                {
                    printf("\n\nL'ELEVE QUE VOUS VOULEZ INSERER EXISTE DEJA DANS LE FICHIER");
                }
                Fermer_TOF_sauv(fsauv);
                Fermer_TOVC(fTOVC1);
                //---------------------------------------------------//
                printf("\n\npress charactere key to continue......");
                scanf("%s", &ch);
                break;

            case 4: // SUPPRISSION D'UN ELEVE
                system("cls");
                printf("--------------------------------------------------------------------------------------------- \n");
                printf("|                        SUPPRISSON D'UN ELEVE DANS LE FICHIER -TOVC                         |\n");
                printf("----------------------------------------------------------------------------------------------- \n");
                /*       LE PROGRAMME DE LA SUPPRISSION D'UN ELEVE DANS TOVC*/
                printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR BLOC]<<<\n\n");
                Affichage_TOVC(fTOVC1);
                printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE]<<<\n\n");
                affichageParEnregTOVC(fTOVC1);
                printf(">>> ENTRER LES CLEs DE RECHERCHE : \n");
                printf(">>> ENTRER L'ID CLASSE : ");
                scanf("%s", idClasse);
                printf("\n>>> ENTRER LE NOM :");
                scanf("%s", nom);
                toUpperCase(nom);
                printf("\n>>> ENTRER LE PRENOM :");
                scanf("%s", prenom);
                toUpperCase(prenom);
                if (suppressionTOVC(fTOVC1, nom, prenom, idClasse))
                {
                    printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR BLOC APRES LA SUPPRESSION]<<<\n\n");
                    Affichage_TOVC(fTOVC1);
                    printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE APRES LA SUPPRESSION]<<<\n\n");
                    affichageParEnregTOVC(fTOVC1);
                }
                else
                {
                    printf("\n\n>>>L'ELEVE QUE VOUS VOULEZ SUPPRIMER N'EXISTE PAS DANS LE FICHIER TOVC DE L'ANNEE COURANTE<<<");
                }
                Fermer_TOVC(fTOVC1);
                //---------------------------------------------------//
                printf("\n\npress charactere key to continue......");
                scanf("%s", &ch);
                break;

            case 5: // SUPPRISSION PAR POSTION.
                system("cls");
                printf("--------------------------------------------------------------------------------------------- \n");
                printf("|                        SUPPRISSON PAR POSTION DANS -TOVC                         |\n");
                printf("----------------------------------------------------------------------------------------------- \n");
                /*       LE PROGRAMME DE LA SUPPRISSION D'UN ELEVE PAR LA POSTION DANS LE FICHIER TOVC DANS TOVC*/
                printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR BLOC]<<<\n\n");
                Affichage_TOVC(fTOVC1);
                printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE]<<<\n\n");
                affichageParEnregTOVC(fTOVC1);
                printf("\n\n>>> ENTRER LA POSITION DE L'ELEVE QUE VOUS VOULEZ CHANGER SAVOIR SA POSITION DANS LE FICHIER TOVC ");
                printf("\n\n>>> Position : ");
                scanf("%d", &position);
                if (rechercheTOVCParEnreg(fTOVC1, position, &pos_i, &pos_j))
                {
                    if (suppressionTOVC_ParPosition(fTOVC1, pos_i, pos_j))
                    {
                        printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR BLOC APRES LA SUPPRESSION]<<<\n\n");
                        Affichage_TOVC(fTOVC1);
                        printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE APRES LA SUPPRESSION]<<<\n\n");
                        affichageParEnregTOVC(fTOVC1);
                    }
                    else
                    {
                        printf(">>>ECHEC DANS LA SUPPRESSION PAR POSTION DANS LE FICHIER<<<");
                    }
                }
                else
                {
                    printf("\n\n>>>ELEVE NON TROUVER<<<\n\n");
                }
                Fermer_TOVC(fTOVC1);
                printf("\n\npress charactere key to continue......");
                scanf("%s", &ch);
                printf("\n\npress charactere key to continue......");
                scanf("%s", &ch);
                break;

            case 6: // MISE A JOUR DES INFORMATION PERSONNELLES
                while (reponse_M_A_J == 'y')
                {
                    choix_mise_a_jour = menu_choix_mise_a_jour();
                    switch (choix_mise_a_jour)
                    {
                    case 1: // M-A-J DE NOM
                        system("cls");
                        printf("--------------------------------------------------------------------------------------------- \n");
                        printf("|                         MISE A JOUR DE NOM D'ELEVE DANS TOVC                               |\n");
                        printf("----------------------------------------------------------------------------------------------- \n");

                        /* LE PROGRAMME DE MISE A JOUR DE NOM D'ELEVE*/
                        printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR BLOC]<<<\n\n");
                        Affichage_TOVC(fTOVC1);
                        printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE]<<<\n\n");
                        affichageParEnregTOVC(fTOVC1);
                        printf("\n\n>>> ENTRER LA POSITION DE L'ELEVE QUE VOUS VOULEZ CHANGER , DANS LE FICHIER TOVC COURANT");
                        printf("\n\n>>> Position : ");
                        scanf("%d", &position);
                        printf("\n\n>>> ENTRER LE NOUVEAU NOM : ");
                        scanf("%s", nom);
                        toUpperCase(nom);
                        pos_i = 0;
                        pos_j = 0;
                        if (rechercheTOVCParEnreg(fTOVC1, position, &pos_i, &pos_j))
                        {
                            strEleve = recupererEnregTOVC(fTOVC1, pos_i, pos_j);
                            nomPrenomGenre = getNomPrenomGenre(strEleve);
                            changerNom(&nomPrenomGenre, nom);
                            changerNomPrenomGenre(&strEleve, nomPrenomGenre);
                            libererString(nomPrenomGenre);
                            if (miseJourTOVCParPosition(fTOVC1, pos_i, pos_j, strEleve))
                            {
                                printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR BLOC APRES LA MISE A JOUR]<<<\n\n");
                                Affichage_TOVC(fTOVC1);
                                printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE APRES LA MISE A JOUR]<<<\n\n");
                                affichageParEnregTOVC(fTOVC1);
                            }
                            else
                            {
                                printf("\n\nECHEC DANS LA MISE A JOUR DE L'ELEVE");
                            }
                        }
                        else
                        {
                            printf("LE FICHIER NE CONTIENT PAS UN ELEVE(ENREGISTREMENT) AVEC CET POSITION !");
                        }
                        //---------------------------------------------------//
                        printf("\n\npress charactere key to continue......");
                        scanf("%s", &ch);
                        break;

                    case 2: // M-A-J DE PRENOM
                        system("cls");
                        printf("--------------------------------------------------------------------------------------------- \n");
                        printf("|                         MISE A JOUR DE PRENOM D'ELEVE DANS TOVC                            |\n");
                        printf("----------------------------------------------------------------------------------------------- \n");
                        /* LE PROGRAMME DE MISE A JOUR DE PRENOM D'ELEVE*/
                        printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR BLOC]<<<\n\n");
                        Affichage_TOVC(fTOVC1);
                        printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE]<<<\n\n");
                        affichageParEnregTOVC(fTOVC1);
                        printf("\n\n>>> ENTRER LA POSITION DE L'ELEVE QUE VOUS VOULEZ CHANGER , DANS LE FICHIER TOVC COURANT");
                        printf("\n\n>>> Position : ");
                        scanf("%d", &position);
                        printf("\n\n>>> ENTRER LE NOUVEAU  PRENOM: ");
                        scanf("%s", prenom);
                        toUpperCase(prenom);
                        pos_i = 0;
                        pos_j = 0;
                        if (rechercheTOVCParEnreg(fTOVC1, position, &pos_i, &pos_j))
                        {
                            strEleve = recupererEnregTOVC(fTOVC1, pos_i, pos_j);
                            nomPrenomGenre = getNomPrenomGenre(strEleve);
                            changerPrenom(&nomPrenomGenre, prenom);
                            changerNomPrenomGenre(&strEleve, nomPrenomGenre);
                            libererString(nomPrenomGenre);
                            if (miseJourTOVCParPosition(fTOVC1, pos_i, pos_j, strEleve))
                            {
                                printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR BLOC APRES LA MISE A JOUR]<<<\n\n");
                                Affichage_TOVC(fTOVC1);
                                printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE APRES LA MISE A JOUR]<<<\n\n");
                                affichageParEnregTOVC(fTOVC1);
                            }
                            else
                            {
                                printf("\n\nECHEC DANS LA MISE A JOUR DE L'ELEVE");
                            }
                        }
                        else
                        {
                            printf("LE FICHIER NE CONTIENT PAS UN ELEVE(ENREGISTREMENT) AVEC CET POSITION !");
                        }
                        //---------------------------------------------------//
                        printf("\n\npress charactere key to continue......");
                        scanf("%s", &ch);
                        break;

                    case 3: // M-A-J DE GENRE
                        system("cls");
                        printf("--------------------------------------------------------------------------------------------- \n");
                        printf("|                         MISE A JOUR DE GENRE D'ELEVE DANS TOVC                            |\n");
                        printf("----------------------------------------------------------------------------------------------- \n");
                        /* LE PROGRAMME DE MISE A JOUR DE GENRE D'ELEVE*/
                        printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR BLOC]<<<\n\n");
                        Affichage_TOVC(fTOVC1);
                        printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE]<<<\n\n");
                        affichageParEnregTOVC(fTOVC1);
                        printf("\n\n>>> ENTRER LA POSITION DE L'ELEVE QUE VOUS VOULEZ CHANGER , DANS LE FICHIER TOVC COURANT");
                        printf("\n\n>>> Position : ");
                        scanf("%d", &position);
                        printf("\n\n>>> ENTRER LE NOUVEAU GENRE: ");
                        scanf("%s", &genre);
                        pos_i = 0;
                        pos_j = 0;
                        if (rechercheTOVCParEnreg(fTOVC1, position, &pos_i, &pos_j))
                        {
                            strEleve = recupererEnregTOVC(fTOVC1, pos_i, pos_j);
                            nomPrenomGenre = getNomPrenomGenre(strEleve);
                            changerGenre(nomPrenomGenre, genre);
                            changerNomPrenomGenre(&strEleve, nomPrenomGenre);
                            libererString(nomPrenomGenre);
                            if (miseJourTOVCParPosition(fTOVC1, pos_i, pos_j, strEleve))
                            {
                                printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR BLOC APRES LA MISE A JOUR]<<<\n\n");
                                Affichage_TOVC(fTOVC1);
                                printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE APRES LA MISE A JOUR]<<<\n\n");
                                affichageParEnregTOVC(fTOVC1);
                            }
                            else
                            {
                                printf("\n\nECHEC DANS LA MISE A JOUR DE L'ELEVE");
                            }
                        }
                        else
                        {
                            printf("LE FICHIER NE CONTIENT PAS UN ELEVE(ENREGISTREMENT) AVEC CET POSITION !");
                        }
                        //---------------------------------------------------//
                        printf("\n\npress charactere key to continue......");
                        scanf("%s", &ch);
                        break;

                    case 4: // M-A-J DE BULTIIN
                        system("cls");
                        printf("--------------------------------------------------------------------------------------------- \n");
                        printf("|                         MISE A JOUR DE BULTIN D'ELEVE DANS TOVC                            |\n");
                        printf("----------------------------------------------------------------------------------------------- \n");
                        /* LE PROGRAMME DE MISE A JOUR DE BULTIN D'ELEVE*/
                        printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR BLOC]<<<\n\n");
                        Affichage_TOVC(fTOVC1);
                        printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE]<<<\n\n");
                        affichageParEnregTOVC(fTOVC1);
                        printf("\n\n>>> ENTRER LA POSITION DE L'ELEVE QUE VOUS VOULEZ CHANGER , DANS LE FICHIER TOVC COURANT");
                        printf("\n\n>>> Position : ");
                        scanf("%d", &position);
                        printf("\n\nAVANT D'ENTRER LE NOUVEAUT SVP RESPECTER LE FORMAT : NOTE1|NOTE2|NOTE3|NOTE4....");
                        printf("\n\n>>> ENTRER LE NOUVEAU BULTIN: ");
                        scanf("%s", bultin);
                        pos_i = 0;
                        pos_j = 0;
                        if (rechercheTOVCParEnreg(fTOVC1, position, &pos_i, &pos_j))
                        {
                            strEleve = recupererEnregTOVC(fTOVC1, pos_i, pos_j);
                            changerBultin(&strEleve, bultin);
                            if (miseJourTOVCParPosition(fTOVC1, pos_i, pos_j, strEleve))
                            {
                                printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR BLOC APRES LA MISE A JOUR]<<<\n\n");
                                Affichage_TOVC(fTOVC1);
                                printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE APRES LA MISE A JOUR]<<<\n\n");
                                affichageParEnregTOVC(fTOVC1);
                            }
                            else
                            {
                                printf("\n\nECHEC DANS LA MISE A JOUR DE L'ELEVE");
                            }
                        }
                        else
                        {
                            printf("\n\nLE FICHIER NE CONTIENT PAS UN ELEVE(ENREGISTREMENT) AVEC CET POSITION !");
                        }
                        //---------------------------------------------------//
                        printf("\n\npress charactere key to continue......");
                        scanf("%s", &ch);
                        break;

                    case 5: // M-A-J DE IDCALSSE
                        system("cls");
                        printf("--------------------------------------------------------------------------------------------- \n");
                        printf("|                         MISE A JOUR DE IDCLASSE D'ELEVE DANS TOVC                          |\n");
                        printf("----------------------------------------------------------------------------------------------- \n");
                        /* LE PROGRAMME DE MISE A JOUR DE IDCLASSE D'ELEVE*/
                        printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR BLOC]<<<\n\n");
                        Affichage_TOVC(fTOVC1);
                        printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE]<<<\n\n");
                        affichageParEnregTOVC(fTOVC1);
                        printf("\n\n>>> ENTRER LA POSITION DE L'ELEVE QUE VOUS VOULEZ CHANGER , DANS LE FICHIER TOVC COURANT");
                        printf("\n\n>>> Position : ");
                        scanf("%d", &position);
                        printf("\n\n>>> ENTRER LE NOUVEAU ID CLASSE: ");
                        scanf("%s", idClasse);
                        pos_i = 0;
                        pos_j = 0;
                        if (rechercheTOVCParEnreg(fTOVC1, position, &pos_i, &pos_j))
                        {
                            strEleve = recupererEnregTOVC(fTOVC1, pos_i, pos_j);
                            changerIdClasse(strEleve, idClasse);

                            if (miseJourTOVCParPosition(fTOVC1, pos_i, pos_j, strEleve))
                            {
                                printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR BLOC APRES LA MISE A JOUR]<<<\n\n");
                                Affichage_TOVC(fTOVC1);
                                printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE APRES LA MISE A JOUR]<<<\n\n");
                                affichageParEnregTOVC(fTOVC1);
                            }
                            else
                            {
                                printf("\n\nECHEC DANS LA MISE A JOUR DE L'ELEVE");
                            }
                        }
                        else
                        {
                            printf("\n\nLE FICHIER NE CONTIENT PAS UN ELEVE(ENREGISTREMENT) AVEC CET POSITION !");
                        }
                        //---------------------------------------------------//
                        printf("\n\npress charactere key to continue......");
                        scanf("%s", &ch);
                        break;

                    case 6: // M-A-J DE TOUT LES INFORMATION.
                        system("cls");
                        printf("--------------------------------------------------------------------------------------------- \n");
                        printf("|                         MISE A JOUR DE TOUT LES INFORMATION DANS TOVC                      |\n");
                        printf("----------------------------------------------------------------------------------------------- \n");
                        /* LE PROGRAMME DE MISE A JOUR DE TOUT LES INFORMATION.*/
                        printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR BLOC]<<<\n\n");
                        Affichage_TOVC(fTOVC1);
                        printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE]<<<\n\n");
                        affichageParEnregTOVC(fTOVC1);
                        printf("\n\n>>> ENTRER LA POSITION DE L'ELEVE QUE VOUS VOULEZ CHANGER , DANS LE FICHIER TOVC COURANT");
                        printf("\n\n>>> Position : ");
                        scanf("%d", &position);
                        printf("\n\nAVANT D'ENTRER LE NOUVEAUT SVP RESPECTER LE FORMAT : NOTE1|NOTE2|NOTE3|NOTE4....");
                        printf("\n\n>>> ENTRER LES NOUVELLES ID ELEVE DE L'ETUDIANT : ");
                        scanf("%s", idEleve);
                        printf("\n\n>>> ENTRER LES NOUVELLES ID CLASSE DE L'ETUDIANT : ");
                        scanf("%s", idClasse);
                        printf("\n>>> ENTRER LE NOM : ");
                        scanf("%s", nom);
                        toUpperCase(nom);
                        printf("\n>>> ENTRER LE PRENOM : ");
                        scanf("%s", prenom);
                        toUpperCase(prenom);
                        printf("\n>>> ENTRER LE GENRE : ");
                        scanf("%s", &genre);
                        nomPrenomGenre = creerNomPrenomGenre(nom, prenom, genre);
                        printf("\n\nAVANT D'ENTRER LE NOUVEAUT SVP RESPECTER LE FORMAT : NOTE1|NOTE2|NOTE3|NOTE4....");
                        printf("\n\n>>> ENTRER LE NOUVEAU BULTIN: ");
                        scanf("%s", bultin);
                        eleve.supp = '0';
                        eleve.idEleve = idEleve;
                        eleve.idClasse = idClasse;
                        eleve.nomPrenomGenre = nomPrenomGenre;
                        eleve.bultin = bultin;
                        strEleve = ConvertionEnregEleveChaine(eleve);
                        libererString(nomPrenomGenre);
                        if (miseJourTOVC(fTOVC1, position, strEleve))
                        {
                            printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR BLOC APRES LA MISE A JOUR]<<<\n\n");
                            Affichage_TOVC(fTOVC1);
                            printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE APRES LA MISE A JOUR]<<<\n\n");
                            affichageParEnregTOVC(fTOVC1);
                        }
                        else
                        {
                            printf("\n\nECHEC DANS LA MISE A JOUR DE L'ELEVE");
                        }
                        //---------------------------------------------------//
                        printf("\n\npress charactere key to continue......");
                        scanf("%s", &ch);
                        break;
                    }
                    printf("Est que vous voulez modifier un autre champ (y/n) : ");
                    scanf("%s", &reponse_M_A_J);
                }
                Fermer_TOVC(fTOVC1);
            }
            break;

            //----------------------------------------------------------------------------------------------------------------------------------------//
        case 2: // la creation de l'archive de T~OF
            printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ANNEE COURANTE PAR ELEVE]<<<\n\n");
            affichageParEnregTOVC(fTOVC1);
            fArchive1 = Ouvrir_TBOF("./ecole1/FICHIER_ARCHIVE_TBOF", 'N');
            archiveCreationTBOF(&fTOVC1, fArchive1, '1');
            Affichage_TBOF(fArchive1);
            printf("\n\npress charactere key to continue......");
            scanf("%s", &ch);
            choix_menu_2 = menu_2();
            switch (choix_menu_2)
            {
            case 1: // Les Operations sur le fichier -T~OF-
                choix_opertion_TOF = menu_opertion_TOF();
                switch (choix_opertion_TOF)
                {
                case 1: // INSERTION dans L'archive T~OF.
                    system("cls");
                    printf("--------------------------------------------------------------------------------------------- \n");
                    printf("|                        INSERTION DANS d'UN ELEVE L'ARCHIVE T~OF                            |\n");
                    printf("----------------------------------------------------------------------------------------------- \n");
                    /* LE PROGRAMME INSERTION d'un eleve de l'archive T~OF*/
                    //----------------------------------------------------------------------------------
                    printf("\n\n-------------->>>[AFFICHAGE LE FICHIER D'ARCHIVE 1 T~OF]<<<------------------\n\n");
                    Affichage_TBOF(fArchive1);
                    //----------------------------------------------------------------------------------
                    printf("\n\n>>> ENTRER LES DONNEES QUE VOUS VOULEZ ARCHIVER");
                    //------------------------------------------------
                    printf("\n\n>>>ID ELEVE : ");
                    scanf("%d", &engArchive.idEleve);
                    printf("\n\n>>>NOM : ");
                    scanf("%s", engArchive.nom);
                    printf("\n\n>>>PRENOM : ");
                    scanf("%s", engArchive.prenom);
                    printf("\n\n>>>NOMRE DE REDOUBLE : ");
                    scanf("%d", &(engArchive.redouble));
                    printf("L'ANNEE COURANTE DE L'ETUDIANT : ");
                    scanf("%d", &engArchive.anneeCourante);
                    if (engArchive.anneeCourante == 5)
                    {
                        printf("\n\n>>>ENTRER [1] SI L'ETUDIANT A FINI CES 5ANS\n");
                        printf(">>>ENTRER [0] SI IL N'A PAS ENCORE FINI CES 5ANS\n");
                        printf("\n\n>>>VOTRE CHOIX : ");
                        scanf("%d", &tmp);
                        if (tmp)
                            engArchive.fini = true;
                        else
                            engArchive.fini = false;
                    }
                    else
                    {
                        engArchive.fini = false;
                    }
                    for (int i = 0; i <= engArchive.anneeCourante; i++)
                    {
                        if (i == 0)
                            engArchive.tabMoyenne[0] = 20;
                        else
                        {
                            printf("\n\n>>> ENTRER LA MOYENNE DE L'ANNEE %d", i);
                            printf("\n\n>>>MOYENNE %d : ", i);
                            scanf("%f", &(engArchive.tabMoyenne[i]));
                        }
                    }
                    //------------------------------------------------
                    insertionTBOF(fArchive1, engArchive);
                    printf("\n\n-------------->>>[AFFICHAGE LE FICHIER D'ARCHIVE T~OF]<<<------------------\n\n");
                    Affichage_TBOF(fArchive1);
                    Fermer_TBOF(fArchive1);
                    //---------------------------------------------------//
                    printf("\n\npress charactere key to continue......");
                    scanf("%s", &ch);
                    break;

                case 2: // SUPPRISSION d'un eleve de l'archive T~OF.
                    system("cls");
                    printf("--------------------------------------------------------------------------------------------- \n");
                    printf("|                    SUPPRISSION DANS d'UN ELEVE L'ARCHIVE T~OF                              |\n");
                    printf("----------------------------------------------------------------------------------------------- \n");
                    /* LE PROGRAMME SUPPRISSION d'un eleve de l'archive T~OF*/
                    printf("\n\n-------------->>>[AFFICHAGE LE FICHIER D'ARCHIVE 1 T~OF]<<<------------------\n\n");
                    Affichage_TBOF(fArchive1);
                    // ---------------------------------------------------//
                    printf(">>> ENTREZ ID-ELEVE D'ELEVE QUE VOULEZ SUPPRIMEZ : ");
                    scanf("%d", &ID_ELEVE);
                    supprimerTBOF(fArchive1, ID_ELEVE);
                    printf("\n\n-------------->>>[AFFICHAGE LE FICHIER D'ARCHIVE T~OF]<<<------------------\n\n");
                    Affichage_TBOF(fArchive1);
                    Fermer_TBOF(fArchive1);
                    printf("\n\npress charactere key to continue......");
                    scanf("%s", &ch);
                    break;

                case 3: // RECHRECHE par intervalle dans une annee.(R-a-I)
                    system("cls");
                    printf("--------------------------------------------------------------------------------------------- \n");
                    printf("|                   RECHRECHE PAR INTERVALLE DANS UNE ANNEE.(R-a-I)                          |\n");
                    printf("----------------------------------------------------------------------------------------------- \n");
                    /* LE PROGRAMME RECHRECHE PAR INTERVALLE DANS UNE ANNEE.(R-a-I)*/
                    printf("\n\n-------------->>>[AFFICHAGE LE FICHIER D'ARCHIVE 1 T~OF]<<<------------------\n\n");
                    Affichage_TBOF(fArchive1);
                    creationIndexArchive(fArchive1, &fIndex1, &fIndex2, &fIndex3, &fIndex4, &fIndex5);
                    printf("\n\n--------------------------------------------------------------------------------------------- \n\n");
                    printf("\n\npress charactere key to continue......");
                    scanf("%s", &ch);
                    choix_fichier = menu_choix_fichier_R_A_I();
                    printf("\n\n>>>ENTRER LE MIN DE CET RECHERCHE<<<");
                    printf("\n\n>>>MIN : ");
                    scanf("%f", &min);
                    printf("\n\n>>>ENTRER LE MAX DE CET RECHERCHE<<<");
                    printf("\n\n>>>MAX : ");
                    scanf("%f", &max);
                    switch (choix_fichier)
                    {
                    case 1:
                        rechechreParIntervalle(fIndex1, min, max); // recherchre par intervalle dans le fichier 1 de l'annee 1 de la simulation
                        break;

                    case 2:
                        rechechreParIntervalle(fIndex2, min, max); // recherchre par intervalle dans le fichier 2 de l'annee 2 de la simulation

                    case 3:
                        rechechreParIntervalle(fIndex3, min, max); // recherchre par intervalle dans le fichier 3 de l'annee 3 de la simulation
                        break;

                    case 4:
                        rechechreParIntervalle(fIndex4, min, max); // recherchre par intervalle dans le fichier 4 de l'annee 4 de la simulation
                        break;

                    case 5:
                        rechechreParIntervalle(fIndex5, min, max); // recherchre par intervalle dans le fichier 5 de l'annee 5 de la simulation
                        break;
                    }
                    //---------------------------------------------------//
                    f = fopen("./RECHERCHE_PAR_INTERVALLE_RESULTAT.txt", "r");
                    if (f == NULL)
                        exit(EXIT_FAILURE);
                    printf("\n\n>>>LE RESULTAT DE LA RECHERCHE PAR INTERVALLE : \n\n");
                    printFile(f);
                    printf("\n\n>>>>VOUS POUVEZ AUSSI CONSULTER LES RESULTATS DE LA RECHERCHE DANS LE FICHIER TEXTE<<<<\n\n");
                    fclose(f);
                    Fermer_TBOF(fArchive1);
                    Fermer_TOF_index(fIndex1);
                    Fermer_TOF_index(fIndex2);
                    Fermer_TOF_index(fIndex3);
                    Fermer_TOF_index(fIndex4);
                    Fermer_TOF_index(fIndex5);
                    //---------------------------------------------------//
                    printf("\n\npress charactere key to continue......");
                    scanf("%s", &ch);
                    break;

                case 4:
                    system("cls");
                    printf("--------------------------------------------------------------------------------------------- \n");
                    printf("|    LISTER LES ELEVES AYANT OBTENU UNE MOYENNE SUPERIEURE A 12 SUR LES 5 ANNEES PAR R-a-I    |\n");
                    printf("--------------------------------------------------------------------------------------------- \n");
                    /* LE PROGRAMME RECHRECHE PAR INTERVALLE DANS UNE ANNEE.(R-a-I)*/
                    printf("\n\n>>> ENTRER LA VALEUR MINIMALE : "); // POUR LA QUESTION 4.B ON DOIT ENTRER 12
                    scanf("%f", &moyenneInf);
                    listerElevesSuppMoy(fArchive1, moyenneInf);
                    f = fopen("./QUESTION_4B_RESULTAT.txt", "r");
                    if (f == NULL)
                        exit(EXIT_FAILURE);
                    printf("\n\n>>>LE RESULTAT DE LA RECHERCHE PAR INTERVALLE : \n\n");
                    printFile(f);
                    printf("\n\n>>>>VOUS POUVEZ AUSSI CONSULTER LES RESULTATS DE LA RECHERCHE DANS LE FICHIER TEXTE<<<<\n\n");
                    fclose(f);
                    Fermer_TBOF(fArchive1);
                    //---------------------------------------------------//
                    printf("\n\npress charactere key to continue......");
                    scanf("%s", &ch);
                    break;
                }
                break; // cace-1-

            case 2: // les Operations de Transfert.
                choix_operation_Transfert = menu_operation_Transfert();
                switch (choix_operation_Transfert)
                {
                case 1: // TRANSFER D'UN ELEVE DE CETTE ECOLE UNE AUTRE.
                    system("cls");
                    printf("--------------------------------------------------------------------------------------------- \n");
                    printf("|                    TRANSFERT D'UN ELEVE DE CETTE ECOLE A UNE AUTRE                         |\n");
                    printf("--------------------------------------------------------------------------------------------- \n");
                    /* LE PROGRAMME TRANSFERT D'UN ELEVE DE CETTE ECOLE A UNE AUTRE*/
                    // ecole 1 --> ecole 2
                    printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ECOLE 1 DE L'ANNEE COURANTE PAR ELEVE]<<<\n\n");
                    affichageParEnregTOVC(fTOVC1);
                    printf("\n\n-------------->>>[AFFICHAGE LE FICHIER D'ARCHIVE 1 T~OF]<<<------------------\n\n");
                    Affichage_TBOF(fArchive1);
                    //------------------------------------------------------------------------------
                    innitArray(schoolYear, nombreAns);
                    innitArray(schoolSalle, nombreSalle);
                    fTOVC2 = Ouvrir_TOVC("./ecole2/Dossier_Des_Annees/FICHIER_TOVC1", 'N');
                    printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ECOLE 2 DE L'ANNEE COURANTE PAR ELEVE]<<<\n\n");
                    chargementInitialTOVC(fTOVC2);
                    affichageParEnregTOVC(fTOVC2);
                    //------------------------------------------------------------------------------
                    fArchive2 = Ouvrir_TBOF("./ecole2/FICHIER_ARCHIVE_TBOF", 'N');
                    archiveCreationTBOF(&fTOVC2, fArchive2, '2');
                    printf("\n\n-------------->>>[AFFICHAGE LE FICHIER D'ARCHIVE 2 T~OF]<<<------------------\n\n");
                    Affichage_TBOF(fArchive2);
                    fTOVC1 = Ouvrir_TOVC("./ecole1/Dossier_Des_Annees/FICHIER_TOVC6", 'A');
                    fTOVC2 = Ouvrir_TOVC("./ecole2/Dossier_Des_Annees/FICHIER_TOVC6", 'A');
                    printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ECOLE 1 DE L'ANNEE COURANTE PAR ELEVE APRES LE DEROULEMENT DES 5ANS]<<<\n\n");
                    affichageParEnregTOVC(fTOVC1);
                    printf("\n\n>>>ENTRER LES DONNEES DE L'ELEVE QUI VA FAIRE LE TRANSFERT [ID CLASSE , NOM , PRENOM]");
                    printf("\n\n>>>ENTRER L'ID CLASSE :");
                    scanf("%s", idClasse);
                    printf("\n\n>>>ENTRER NOM :");
                    scanf("%s", nom);
                    printf("\n\n>>>ENTRER PRENOM :");
                    scanf("%s", prenom);

                    if (transfert(fTOVC1, fTOVC2, fArchive1, fArchive2, idClasse, nom, prenom))
                    {
                        printf("\n\n-------------------------------------------------------------------------------------\n\n");
                        printf("\n\n|                 >>>          LE RESULTAT DU TRANSFERT        <<<                   |\n\n");
                        printf("\n\n-------------------------------------------------------------------------------------\n\n");
                        printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ECOLE 1 DE L'ANNEE COURANTE PAR ELEVE]<<<\n\n");
                        affichageParEnregTOVC(fTOVC1);
                        printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ECOLE 2 DE L'ANNEE COURANTE PAR ELEVE]<<<\n\n");
                        affichageParEnregTOVC(fTOVC2);
                        printf("\n\n-------------->>>[AFFICHAGE LE FICHIER D'ARCHIVE 1 T~OF]<<<------------------\n\n");
                        Affichage_TBOF(fArchive1);
                        printf("\n\n-------------->>>[AFFICHAGE LE FICHIER D'ARCHIVE 2 T~OF]<<<------------------\n\n");
                        Affichage_TBOF(fArchive2);
                    }
                    else
                    {
                        printf(">>>>UNE ERROR DANS LE TRANSFERT DE L'ETUDIANT<<<<");
                    }
                    Fermer_TBOF(fArchive1);
                    Fermer_TBOF(fArchive2);
                    Fermer_TOVC(fTOVC1);
                    Fermer_TOVC(fTOVC2);
                    //---------------------------------------------------//
                    printf("\n\npress charactere key to continue......");
                    scanf("%s", &ch);
                    break;

                case 2: // RECEVOIR UN ELEVE D'UNE AUTRE ECOLE
                    system("cls");
                    printf("--------------------------------------------------------------------------------------------- \n");
                    printf("|                         RECEVOIR UN ELEVE D'UNE AUTRE ECOLE                                |\n");
                    printf("--------------------------------------------------------------------------------------------- \n");
                    /* LE PROGRAMME TRANSFERT D'UN ELEVE DE CETTE ECOLE A UNE AUTRE*/
                    // ecole 2 --> ecole 1
                    printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ECOLE 1 DE L'ANNEE COURANTE PAR ELEVE]<<<\n\n");
                    affichageParEnregTOVC(fTOVC1);
                    printf("\n\n-------------->>>[AFFICHAGE LE FICHIER D'ARCHIVE 1 T~OF]<<<------------------\n\n");
                    Affichage_TBOF(fArchive1);
                    //------------------------------------------------------------------------------
                    innitArray(schoolYear, nombreAns);
                    innitArray(schoolSalle, nombreSalle);
                    fTOVC2 = Ouvrir_TOVC("./ecole2/Dossier_Des_Annees/FICHIER_TOVC1", 'N');
                    printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ECOLE 2 DE L'ANNEE COURANTE PAR ELEVE]<<<\n\n");
                    chargementInitialTOVC(fTOVC2);
                    affichageParEnregTOVC(fTOVC2);
                    //------------------------------------------------------------------------------
                    fArchive2 = Ouvrir_TBOF("./ecole2/FICHIER_ARCHIVE_TBOF", 'N');
                    archiveCreationTBOF(&fTOVC2, fArchive2, '2');
                    printf("\n\n-------------->>>[AFFICHAGE LE FICHIER D'ARCHIVE 2 T~OF]<<<------------------\n\n");
                    Affichage_TBOF(fArchive2);
                    fTOVC1 = Ouvrir_TOVC("./ecole1/Dossier_Des_Annees/FICHIER_TOVC6", 'A');
                    fTOVC2 = Ouvrir_TOVC("./ecole2/Dossier_Des_Annees/FICHIER_TOVC6", 'A');
                    printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ECOLE 1 DE L'ANNEE COURANTE PAR ELEVE APRES LE DEROULEMENT DES 5ANS]<<<\n\n");
                    affichageParEnregTOVC(fTOVC2);
                    printf("\n\n>>>ENTRER LES DONNEES DE L'ELEVE QUI VA FAIRE LE TRANSFERT [ID CLASSE , NOM , PRENOM]");
                    printf("\n\n>>>ENTRER L'ID CLASSE :");
                    scanf("%s", idClasse);
                    printf("\n\n>>>ENTRER NOM :");
                    scanf("%s", nom);
                    printf("\n\n>>>ENTRER PRENOM :");
                    scanf("%s", prenom);

                    transfert(fTOVC2, fTOVC1, fArchive2, fArchive1, idClasse, nom, prenom);
                    printf("\n\n-------------------------------------------------------------------------------------\n\n");
                    printf("\n\n|                 >>>          LE RESULTAT DU TRANSFERT        <<<                   |\n\n");
                    printf("\n\n-------------------------------------------------------------------------------------\n\n");
                    printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ECOLE 1 DE L'ANNEE COURANTE PAR ELEVE]<<<\n\n");
                    affichageParEnregTOVC(fTOVC1);
                    printf("\n\n>>>[L'AFFICHAGE DU FICHIER TOVC DE L'ECOLE 2 DE L'ANNEE COURANTE PAR ELEVE]<<<\n\n");
                    affichageParEnregTOVC(fTOVC2);
                    printf("\n\n-------------->>>[AFFICHAGE LE FICHIER D'ARCHIVE 1 T~OF]<<<------------------\n\n");
                    Affichage_TBOF(fArchive1);
                    printf("\n\n-------------->>>[AFFICHAGE LE FICHIER D'ARCHIVE 2 T~OF]<<<------------------\n\n");
                    Affichage_TBOF(fArchive2);
                    Fermer_TBOF(fArchive1);
                    Fermer_TOVC(fTOVC1);
                    Fermer_TBOF(fArchive2);
                    Fermer_TOVC(fTOVC2);
                    //---------------------------------------------------//
                    printf("\n\npress charactere key to continue......");
                    scanf("%s", &ch);
                    break;
                }
                break; // CASE -2-
            }
            break;
        }
        break;
    case 2:
        system("cls");
        menu_Reponce_remarque();
        break;
    case 3: // QUITTER LE PROGRAMME
        //--la fonction de quite--
        system("cls");
        Quite_programme();
        scanf("%s", &ch);
        break;
    }
}
