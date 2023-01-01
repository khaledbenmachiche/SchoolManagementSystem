#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bib_TOVC.h"
#include "INDEX_ARCHIVE.h"
//----------------------------BIBLOTHEQUE POUR MANIPULER LE FICHIER ARCHIVE---------------------------------------------//

//---------------------------------------------------------------------------------------------------------------------//
#define tailleBlocTBOF 25
#define MAX_NOM_PRENOM 30
//-------------------------

/*************************************** Declaration de la structure de fichier TBOF *******************************************/

/* Structure d'enregistrement */
typedef struct Tenreg_TBOF
{
    // La cle dans notre cas , l'archivage sera idEleve
    int idEleve;
    //-------------------------
    char nom[MAX_NOM_PRENOM];
    char prenom[MAX_NOM_PRENOM];
    int anneeCourante;
    bool fini;
    int redouble;
    float tabMoyenne[nombreAns];
    //-------------------------
} Tenreg_TBOF;
//------------------------------------------------------------------------------------------------------------//
/* Structure de bloc */
typedef struct Tbloc_TBOF
{
    Tenreg_TBOF tab[tailleBlocTBOF];
    int nb; // nombre d'enregistrements dans le bloc
} Tbloc_TBOF;
//------------------------------------------------------------------------------------------------------------//
/* Structure du buffer */
typedef struct Tbloc_TBOF Buffer_TBOF;
//------------------------------------------------------------------------------------------------------------//
/* Structure de l'entete du fichier */
typedef struct Entete_TBOF
{
    int nbBloc;  // Nombre de blocs dans le fichier
    int nbEnreg; // Nombre d'enregistrements dans le fichier
} Entete_TBOF;
//------------------------------------------------------------------------------------------------------------//
typedef struct TBOF
{
    FILE *fichier;
    Entete_TBOF entete;
} TBOF;

/**************************************** Implementation du modele de fichier TBOF ****************************************/

/* Fonction d'ouverture ou creation d'un fichier TBOF */

TBOF *Ouvrir_TBOF(const char nomFichier[], char mode)
{
    TBOF *f = (struct TBOF *)malloc(sizeof(TBOF));
    if ((mode == 'A') || (mode == 'a'))
    {
        f->fichier = fopen(nomFichier, "rb+"); // ouvrir un fichier existant
        if (f->fichier == NULL)
        {
            free(f);
            return NULL;
        }
        else
            fread(&(f->entete), sizeof(f->entete), 1, f->fichier); // chargement de l'ent�te dans la structure
    }
    else if ((mode == 'N') || (mode == 'n'))
    {
        f->fichier = fopen(nomFichier, "wb+"); // ouvrir un nouveau fichier
        if (f->fichier == NULL)
        {
            free(f);
            return NULL;
        }
        else
        {
            f->entete.nbBloc = 0; // initialisation de l'entete dans la structure
            f->entete.nbEnreg = 0;
        }
    }
    else
    {
        free(f);
        return NULL;
    }
    return f;
}

//------------------------------------------------------------------------------------------------------------//
/* Procedure de fermeture d'un fichier TBOF */

void Fermer_TBOF(TBOF *f)
{
    rewind(f->fichier);                                       // positionne le curseur au debut du fichier
    fwrite(&(f->entete), sizeof(Entete_TBOF), 1, f->fichier); // sauvegarde l'entete en debut du fichier
    fclose(f->fichier);                                       // ferme le fichier
    free(f);                                                  // libere l'espace memoire occupe par la structure
}

//------------------------------------------------------------------------------------------------------------//
/* Procedure de lecture d'un bloc TOF */

void LireDir_TBOF(TBOF *f, int Num_Bloc, Buffer_TBOF *buf)
{
    if (Num_Bloc <= f->entete.nbBloc)
    {
        fseek(f->fichier, sizeof(Entete_TBOF) + Num_Bloc * sizeof(Tbloc_TBOF), SEEK_SET);
        fread(buf, sizeof(Tbloc_TBOF), 1, f->fichier);
    }
}

//------------------------------------------------------------------------------------------------------------//

/* Procedure d'ecriture d'un bloc methode TOF */

void EcrireDir_TBOF(TBOF *f, int Num_Bloc, Buffer_TBOF *buf)
{
    if (Num_Bloc <= f->entete.nbBloc)
    {
        fseek(f->fichier, sizeof(Entete_TBOF) + Num_Bloc * sizeof(Tbloc_TBOF), SEEK_SET);
        fwrite(buf, sizeof(Tbloc_TBOF), 1, f->fichier);
    }
}

//------------------------------------------------------------------------------------------------------------//

/* Fonction de lecture de l'entete methode TBOF */
/* lorsque i=1 ====> lecture du nombre de blocs
   lorsque i=2 ====> lecture du nombre d'enregistrement */

int entete_TBOF(TBOF *f, int i)
{
    if (i == 1)
        return (f->entete).nbBloc;
    else if (i == 2)
        return (f->entete).nbEnreg;
    else
        return -1;
}

//------------------------------------------------------------------------------------------------------------//

/* Procedure de modification de l'entete methode TBOF */
/* lorsque i=1 ====> modification du nombre de blocs
   lorsque i=2 ====> modification du nombre d'enregistrement */

void Aff_entete_TBOF(TBOF *f, int i, int val)
{
    if (i == 1)
        (f->entete).nbBloc = val;
    else if (i == 2)
        (f->entete).nbEnreg = val;
}
//------------------------------------------------------------------------------------------------------------//

bool RechercheTBOF(int cleIdEleve, TBOF *f, int *i, int *j)
{
    *i = 0;
    Buffer_TBOF buff;
    while (*i < entete_TBOF(f, 1))
    {
        LireDir_TBOF(f, *i, &buff);
        for (*j = 0; *j < buff.nb; (*j)++)
        {
            if (buff.tab[*j].idEleve == cleIdEleve)
                return true;
        }
        (*i)++;
    }
    return false;
}

//------------------------------------------------------------------------------------------------------------//

bool insertionTBOF(TBOF *f, Tenreg_TBOF enreg)
{
    int i, j;
    Buffer_TBOF buff;
    if (entete_TBOF(f, 1) < 0)
        return false;

    if (entete_TBOF(f, 1) > 0)
    {
        LireDir_TBOF(f, entete_TBOF(f, 1) - 1, &buff);
        if (buff.nb < tailleBlocTBOF && buff.nb > 0)
        {
            buff.tab[buff.nb] = enreg;
            buff.nb++;
            EcrireDir_TBOF(f, entete_TBOF(f, 1) - 1, &buff);
        }
        else
        {
            buff.tab[0] = enreg;
            buff.nb = 1;
            Aff_entete_TBOF(f, 1, entete_TBOF(f, 1) + 1); // incremetation du nombre d'enregistrement dans le fichier
            EcrireDir_TBOF(f, entete_TBOF(f, 1) - 1, &buff);
        }
    }
    else if (entete_TBOF(f, 1) == 0)
    {
        buff.tab[0] = enreg;
        buff.nb = 1;
        EcrireDir_TBOF(f, 0, &buff);
        Aff_entete_TBOF(f, 1, entete_TBOF(f, 1) + 1); // incremetation du nombre d'enregistrement dans le fichier
    }
    Aff_entete_TBOF(f, 2, entete_TBOF(f, 2) + 1); // incremetation du nombre d'enregistrement dans le fichier
    return true;
}

//------------------------------------------------------------------------------------------------------------//

bool supprimerTBOF(TBOF *f, int cle)
{
    int i, j;
    Buffer_TBOF buff;
    Tenreg_TBOF e;
    if (!RechercheTBOF(cle, f, &i, &j))
        return false;

    if (i != entete_TBOF(f, 1))
    {
        LireDir_TBOF(f, entete_TBOF(f, 1) - 1, &buff);
        e = buff.tab[buff.nb - 1];
        buff.nb--;
        if (buff.nb > 0)
            EcrireDir_TBOF(f, entete_TBOF(f, 1) - 1, &buff);
        else
            Aff_entete_TBOF(f, 1, entete_TBOF(f, 1) - 1);

        LireDir_TBOF(f, i, &buff);
        buff.tab[j] = e;
        EcrireDir_TBOF(f, i, &buff);
    }
    else
    {
        LireDir_TBOF(f, i, &buff);
        buff.tab[j] = buff.tab[buff.nb - 1];
        buff.nb--;
        if (buff.nb > 0)
            EcrireDir_TBOF(f, i, &buff);
        else
            Aff_entete_TBOF(f, 1, entete_TBOF(f, 1) - 1);
    }
    Aff_entete_TBOF(f, 2, entete_TBOF(f, 2) - 1); // decremetation du nombre d'enregistrement dans le fichier
    return true;
}
//------------------------------------------------------------------------------------------------------------//
void Affichage_TBOF(TBOF *f)
{
    Buffer_TBOF buffer;
    printf("\n\t***************************************\n");
    printf("\t          AFFICHAGE FICHIER TBOF");
    printf("\n\t***************************************\n");
    for (int i = 0; i < entete_TBOF(f, 1); i++)
    {
        LireDir_TBOF(f, i, &buffer);                      // lire le bloc dans buffer
        printf("\n\tBloc num %d\tNB=%d\n", i, buffer.nb); // Afficher le num du bloc et le nombre d'enr qu'il contient
        for (int j = 0; j < buffer.nb; j++)
        { // Afficher les enregistrements du buffer
            printf("\n\n\tID Eleve=%04d\tNOM:%s--PRENOM:%s\t  Annee courante : %d\t", buffer.tab[j].idEleve, buffer.tab[j].nom, buffer.tab[j].prenom, buffer.tab[j].anneeCourante);
            // printf("|\t%s-%s-%c", buffer.tab[i].nom, buffer.tab[i].prenom, buffer.tab[i].genre);
            printf("\tredouble : %d\t", buffer.tab[j].redouble);
            for (int cpt = 0; cpt <= buffer.tab[j].anneeCourante; cpt++)
            {
                printf("|%.2f", buffer.tab[j].tabMoyenne[cpt]);
            }
            if (buffer.tab[j].fini)
                printf("\tGraduated.");
            printf("\n\n");
        }

        printf("\n\t---------------------------------------\n");
    }
}
//------------------------------------------------------------------------------------------------------------//
float calculMoyenne(char *bultin)
{
    float moyenne = 0;
    int nbrNote = 0;
    char *note = allouerString(1);
    note[0] = '\0';
    for (int i = 0; i <= strlen(bultin); i++)
    {
        if (bultin[i] != '|')
        {
            stringCharAppend(&note, bultin[i]);
        }
        else
        {
            moyenne += stringToFloat(note);
            libererString(note);
            note = NULL;
            note = allouerString(1);
            note[0] = '\0';
            nbrNote++;
        }
    }
    if (note != NULL)
        libererString(note);
    moyenne /= (float)nbrNote;
    return moyenne;
}
//------------------------------------------------------------------------------------------------------------//
//------------------GENERER NOM ET PRENOM APARTIR D'UN FICHIER TEXTE EN REVERSE-------------------------------//
//------------------------------------------------------------------------------------------------------------//
void reverseStr(char *str)
{
    // on va utiliser la fonction dans la fonction recupererNomPrenomEnReverse
    int len = strlen(str); // la taille de la chaine;
    char temp;

    for (int i = 0; i < len / 2; i++)
    {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}
//------------------------------------------------------------------------------------------------------------//
bool recupererNomPrenomEnReverse(FILE *f, int position, char **str)
{
    //----------------------------
    if (f == NULL)
        exit(EXIT_FAILURE);
    char c = '\0';
    int cpt = 0; // cpt pour trouver la position correct.
    //----------------------------
    fseek(f, 0, SEEK_END);
    int length = ftell(f);  // La taille du fichier
    fseek(f, -1, SEEK_CUR); // pour que f pointe sur le dernier chacter diffrenet a EOF(FIN DE FICHIER)
    while (length > 0)
    {
        c = fgetc(f);
        if (c != ',')
            stringCharAppend(str, c);
        else
        {
            if (cpt == position)
            {
                // si c'est la position on a recuperer la chaine en inverse
                // on doit utiliser reverseStr pour obtenir la chaine correct
                reverseStr(*str);
                return true;
            }
            cpt++;
            libererString(*str);
            *str = allouerString(1);
            (*str)[0] = '\0';
        }
        fseek(f, -2, SEEK_CUR);
        length--;
    }
    if (*str != NULL)
    {
        libererString(*str);
        *str = NULL;
    }
}
//------------------------------------------------------------------------------------------------------------//
char *generateNomPrenomEnReverse(bool *prenomChecker, bool *nomChecker)
{
    // on vas generer les noms , prenoms des eleves prescolaire de la fin des fichiers text noms, prenoms
    //  de la fin jusqu'au debut car les noms , prenoms du debut sont deja utiliser pour la construction
    // du fichier innitialle TOVC
    //----------------------------
    int randomPrenom = Random((nombreEleve * nombreAns) - 1, 0), randomNom = Random((nombreEleve * nombreAns) - 1, 0);
    FILE *f1 = fopen("prenomAlgeriens.txt", "r"), *f2 = fopen("nomAlgeriens.txt", "r");
    if (f1 == NULL || f2 == NULL)
        exit(EXIT_FAILURE);
    //----------------------------
    while (prenomChecker[randomPrenom] || nomChecker[randomNom]) // on verfier si le prenom est deja utiliser ou pas
    {
        if (prenomChecker[randomPrenom])
            randomPrenom = Random(nombreEleve * nombreAns - 1, 0);
        if (nomChecker[randomNom])
            randomNom = Random(nombreEleve * nombreAns - 1, 0);
    }
    prenomChecker[randomPrenom] = true;
    nomChecker[randomNom] = true;
    char *prenom = allouerString(1), *nom = allouerString(1);
    // allouez un espace memoire pour le liberer a la fin de l'execution du programme
    if (prenom == NULL || nom == NULL)
        exit(EXIT_FAILURE);
    prenom[0] = '\0';
    nom[0] = '\0';

    recupererNomPrenomEnReverse(f1, randomPrenom, &prenom);
    recupererNomPrenomEnReverse(f2, randomNom, &nom);
    stringCharAppend(&nom, '-');
    char *nomPrenom = stringStringAppend(nom, prenom);
    //----------------------------
    // on libere la memoire allouer dans la fonction
    libererString(nom);
    libererString(prenom);
    fclose(f1);
    fclose(f2);
    //----------------------------
    return nomPrenom;
}
//------------------------------------------------------------------------------------------------------------//
//---------------------------------LE DEROULEMENT DES 5 ANNEES----------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//

void archiveCreationTBOF(TOVC **fTOVC1, TBOF *fTBOF, char ecole)
{
    // on a ajouter char ecole , pour la fonction de transfer car on doit avoir deux ecole
    TOVC *fTOVC2 = NULL;
    if (nombreAns <= 0)
        exit(EXIT_FAILURE);
    //----------------------------
    // le chemin relative du premier fichier
    char relativePathFichier[] = "./ecole1/Dossier_Des_Annees/FICHIER_TOVC2";
    if (ecole == '2')
        strcpy(relativePathFichier, "./ecole2/Dossier_Des_Annees/FICHIER_TOVC2");
    else if (ecole != '2' && ecole != '1')
        return;
    //----------------------------
    char *strEleve = NULL;
    int size = strlen(relativePathFichier);
    float moyenne = 0;
    int pos_i, pos_j;
    int pos_x, pos_y;
    int ans = 0;
    bool prenomChecker[nombreEleve * nombreAns] = {false}, nomChecker[nombreEleve * nombreAns] = {false};
    Tenreg_TBOF eleveArchive;
    enregEleve eleve;
    Buffer_TBOF buffTBOF;
    char *nom = NULL, *prenom = NULL;
    TOF_sauv *fsauv = Ouvrir_TOF_sauv("SAUVGARDE_ID_ELEVE", 'A');
    for (int i = 0; i < nombreAns - 1; i++)
    {
        fTOVC2 = Ouvrir_TOVC(relativePathFichier, 'N');
        for (int j = 1; j <= entete_TOVC(*fTOVC1, 2); j++)
        {
            if (rechercheTOVCParEnreg(*fTOVC1, j, &pos_i, &pos_j))
            {
                strEleve = recupererEnregTOVC(*fTOVC1, pos_i, pos_j); // on recupere l'enregistrement dans strEleve
                eleve = getEleve(strEleve);
                if (eleve.supp == '0') // on verifie si l'etudiant est supprimer dans le fichier courant TOVC
                {
                    eleveArchive.idEleve = stringToInt(eleve.idEleve);
                    ans = stringToInt(eleve.idClasse) / (int)pow(10, sizeID_Classe - 1);
                    tabMoyenneInit(eleveArchive.tabMoyenne, nombreAns);     // on initiallise le tableau de moyenne avec des moyennes supperieure a 10.
                    seperateNomPrenom(eleve.nomPrenomGenre, &nom, &prenom); // on recupere le nom et le prenom
                    strcpy(eleveArchive.nom, nom);
                    strcpy(eleveArchive.prenom, prenom);
                    libererString(nom);
                    libererString(prenom);
                    eleveArchive.redouble = 0; // on initialise redouble a 0 , il n'a jamais redoubler.
                    eleveArchive.anneeCourante = ans;
                    if (eleve.idClasse[0] == '0')
                    {
                        // Si l'etudiant est en prescolaire La moyenne est toujours 20/20
                        eleveArchive.tabMoyenne[0] = 20;
                        moyenne = 20;
                    }
                    else
                    {
                        // sinon on calcul la moyenne de l'eleve avec la fonction calculMoyenne
                        moyenne = calculMoyenne(eleve.bultin);
                        eleveArchive.tabMoyenne[ans] = moyenne;
                    }

                    //------------------------------------------------------------------
                    if (moyenne >= 10 && eleve.idClasse[0] != '5')
                    {
                        // Si moyenne >= 10 , et il est pas en 5em annee
                        // on incremente la classe , et l'annee de l'eleve donc le changement de idClasse.
                        // on genere un nouveau bultin qui va etre inserer dans le fichier TOVC de l'annee prochaine
                        // et on mis fini a false car l'eleve n'a pas encore finis les etudes dans notre ecoles
                        incrementIdClasse(eleve.idClasse);
                        changerIdClasse(strEleve, eleve.idClasse);
                        char *newBultin = bultinGenerator(eleve.idClasse[0]);
                        changerBultin(&strEleve, newBultin);
                        libererString(newBultin);
                        newBultin = NULL;
                        // on insere l'etudiant avec ces donnee de l'annee prochaine dans le fichier TOVC de l'annee prochaine
                        insertionTOVC(fTOVC2, &strEleve);
                        // strEleve vas etre libere dans le module insertionTOVC
                        if (strEleve != NULL)
                        {
                            libererString(strEleve);
                            strEleve = NULL;
                        }
                        eleveArchive.fini = false;
                    }
                    else if (moyenne >= 10 && eleve.idClasse[0] == '5')
                    {
                        // Si moyenne >= 10 et il est on 5em annee , donc il a terminer toute les 6 annees dans notre ecoles.
                        // Alors fini <-- true
                        // on insere pas l'etudiant dans le fichier TOVC de l'annee prochaine car l'annee prochaine il sera au college!
                        eleveArchive.fini = true;
                    }
                    else if (moyenne < 10)
                    {
                        // Si moyenne < 10 , dans les deux cas , il va redoubler
                        // donc on genere un nouveau bultin , mais sans changer sa classe et annee , car il a redoubler
                        char *newBultin = bultinGenerator(eleve.idClasse[0]);
                        changerBultin(&strEleve, newBultin);
                        libererString(newBultin);
                        insertionTOVC(fTOVC2, &strEleve);
                        // strEleve vas etre libere dans le module insertionTOVC
                        eleveArchive.fini = false;
                    }
                    //------------------------------------------------------------------

                    if (RechercheTBOF(eleveArchive.idEleve, fTBOF, &pos_x, &pos_y))
                    {
                        // Si l'etudiant existe deja dans le fichier Archive on fait juste une mise a jour des moyenne , redouble si il a redoubler ,L'annee courante et fini --
                        LireDir_TBOF(fTBOF, pos_x, &buffTBOF);
                        if (moyenne < 10)
                            buffTBOF.tab[pos_y].redouble++;
                        buffTBOF.tab[pos_y].tabMoyenne[ans] = eleveArchive.tabMoyenne[ans];
                        buffTBOF.tab[pos_y].anneeCourante = ans;
                        buffTBOF.tab[pos_y].fini = eleveArchive.fini;
                        EcrireDir_TBOF(fTBOF, pos_x, &buffTBOF);
                    }
                    else
                    {
                        // Si il n'existe pas on insere l'eleve dans l'archive
                        if (moyenne < 10)
                            eleveArchive.redouble++;
                        insertionTBOF(fTBOF, eleveArchive);
                    }
                    if (strEleve != NULL)
                    {
                        libererString(strEleve);
                        strEleve = NULL;
                    }
                }
                libererEleve(eleve);
            }
        }
        // a la fin d'une annee les eleves en prescolaire vont passer a l'annee prochaine donc on doit
        // generer des nouveaus eleves qui vont etre en prescolaire l'annee suivantes (i+1)
        // les 5em annee qui ont eu plus que 10 , il vont quitter l'ecole
        for (int cpt = 0; cpt < nombreEleve; cpt++)
        {
            eleve.supp = '0';
            eleve.idEleve = IdEleveGenerator(fsauv);
            eleve.idClasse = genererIdClasse('0');
            eleve.nomPrenomGenre = generateNomPrenomEnReverse(prenomChecker, nomChecker);
            eleve.bultin = bultinGenerator('0');
            strEleve = ConvertionEnregEleveChaine(eleve);
            insertionTOVC(fTOVC2, &strEleve);
            if (strEleve != NULL)
            {
                libererString(strEleve);
                strEleve = NULL;
            }
            libererEleve(eleve);
        }
        // A chaque fois on ferme les fichiers quand a ouvrit
        //--------------------------------------------------
        Fermer_TOVC(*fTOVC1);
        *fTOVC1 = fTOVC2;
        //--------------------------------------------------
        // on incremente le chemin relative du prochain fichier , on incremente le dernier character
        relativePathFichier[size - 1] = (char)((int)relativePathFichier[size - 1] + 1);
    }
    //-------------------------
    Fermer_TOF_sauv(fsauv);
    Fermer_TOVC(fTOVC2);
    //-------------------------
}
//|******************************************LE COUT DE L'ARCHIVAGE*****************************************************************************//
//|---------------------------------------------------------------------------------------------------------------------------------------------|//
//| LE COUT DE L'ARCHIVAGE :                                                                                                                    |//
//| ON DOIT CALCULET LE MEILLEUR CAS ET LE PIRE CAS                                                                                             |//
//| ON CALCUL LE COUT DES FONCTIONS UTILISER DANS LA FONCTIONS DU CREATION ARCHIVE                                                              |//
//|-------------------------------------                                                                                                        |//
//|LE COUT DE RECHERCHE_TOVC_PAR_ENREG:                                                                                                         |//
//|LE PIRE CAS : NombreBlocTOVC ACCES                                                                                                           |//
//|LE MEILLEUR CAS : 1 ACCES                                                                                                                    |//
//|------------------------------------                                                                                                         |//
//|LE COUT DE INSERTION_TOVC :                                                                                                                  |//
//|LE PIRE CAS : (NombreBlocTOVC + 1) ACCES                                                                                                     |//
//|LE MEILLEUR CAS : 1 ACCES                                                                                                                    |//
//|-------------------------------------                                                                                                        |//
//|LE COUT RECUPERR enregTOVC:                                                                                                                  |//
//|PIRE CAS : 1 ACCES                                                                                                                           |//
//|MEILLEUR CAS : 0 ACCES                                                                                                                       |//
//|-------------------------------------                                                                                                        |//
//|LE COUT RECHERCHE TBOF:                                                                                                                      |//               
//|LE PIRE CAS : NbrblocTBOF                                                                                                                    |// 
//|LE MEILLEUR CAS:0 ACCES SI LE FICHIER                                                                                                        |// 
//|-------------------------------------                                                                                                        |// 
//|LE COUT DE INSERTION TBOF:                                                                                                                   |// 
//|LE PIRE CAS : 1 ACCES                                                                                                                        |// 
//|LE MEILLEUR CAS : 2 ACCES                                                                                                                    |// 
//|----------------------------------------                                                                                                     |// 
//|LE COUT DE LA CREATION DE L'ARCHIVE , SUR LES 5ANS                                                                                           |// 
//|LE PIRE CAS : [(NombreBlocTOVC + (NombreBlocTOVC + 1) + (NombreBlocTOVC + 1) * NOMBRE_ELEVE) * NombreBlocTOVC * (NOMBRE_ANS - 1)] ACCES      |//     
//|              =  [ 2 * NombreBlocTOVC + 1 + (NombreBlocTOVC + 1) * NOMBRE_ELEVE) * NombreBlocTOVC * (NOMBRE_ANS - 1)]                        |//
//| LE MEILLEUR CAS : [(1 + NOMBRE_ELEVE) * NOMBRE_BLOC_TOVC * (NOMBRE_ANS - 1)] ACCES                                                          |//
//**********************************************************************************************************************************************//
//---------------------------------------------------------------------------------------------------------------------------------------------//
bool creationIndexArchive(TBOF *fArchive, TOF_index **f1, TOF_index **f2, TOF_index **f3, TOF_index **f4, TOF_index **f5)
{
    //------------------------------------------------------------
    *f1 = Ouvrir_TOF_index("./ecole1/Index_Archive/indexArchive1", 'N');
    *f2 = Ouvrir_TOF_index("./ecole1/Index_Archive/indexArchive2", 'N');
    *f3 = Ouvrir_TOF_index("./ecole1/Index_Archive/indexArchive3", 'N');
    *f4 = Ouvrir_TOF_index("./ecole1/Index_Archive/indexArchive4", 'N');
    *f5 = Ouvrir_TOF_index("./ecole1/Index_Archive/indexArchive5", 'N');
    if (*f1 == NULL || *f2 == NULL || *f3 == NULL || *f4 == NULL || *f5 == NULL)
        exit(EXIT_FAILURE);
    //------------------------------------------------------------
    //--------LES DECLARTIONS------------//
    //--------------------------
    Buffer_TBOF buffArchive;
    Tenreg_TOF_index enreg;
    //--------------------------
    for (int i = 0; i < entete_TBOF(fArchive, 1); i++)
    {
        LireDir_TBOF(fArchive, i, &buffArchive);
        for (int j = 0; j < buffArchive.nb; j++)
        {
            if (buffArchive.tab[j].anneeCourante != 0)
            {
                for (int cpt = 1; cpt <= buffArchive.tab[j].anneeCourante; cpt++)
                {
                    enreg.supp = 0;
                    enreg.idEleve = buffArchive.tab[j].idEleve;
                    enreg.pos_i = i;
                    enreg.pos_j = j;
                    enreg.moyenne = buffArchive.tab[j].tabMoyenne[cpt];
                    insererDansLesIndexes(*f1, *f2, *f3, *f4, *f5, cpt, enreg);
                }
            }
        }
    }
}
//------------------------------------------------------------------------------------------------------------//
bool rechechreParIntervalle(TOF_index *f, float min, float max)
{
    //--------LES DECLARTIONS------------//
    //--------------------------
    int i = 0,
        j = 0,
        cpt = 0;
    Buffer_TOF_index buff;
    // fOut est un pointeur vers un fichier qui vas contenir les resultats de cet fonction --listerElevesSuppMoy--
    // Dans le menu on va demander si l'utilisateur veut consulter le fichier text directement avec un editeur text , ou bien afficher le fichier sur la console.
    FILE *fOut = fopen("RECHERCHE_PAR_INTERVALLE_RESULTAT.txt", "w");
    if (fOut == NULL)
        exit(EXIT_FAILURE);
    //--------------------------
    if (f->entete.nbBloc <= 0)
        return false;

    RechDicho_TOF_index(f, min, &i, &j);
    int sauv = i;
    if (min < max && min <= 20 && max <= 20)
    {
        fprintf(fOut, "\nLa recherche par intervalle des enregistremens dans l'intervalle [%.2f,%.2f] : \n\n", min, max);
        while (i < entete_TOF_index(f, 1))
        {
            LireDir_TOF_index(f, i, &buff);
            if (i != sauv)
                j = 0;

            if (buff.tab[j].moyenne <= max)
            {
                while (j < buff.nb)
                {
                    if (buff.tab[j].moyenne <= max)
                    {
                        fprintf(fOut, "ELEVE %d:\tIDELEVE : %04d\tmoyenne : %.2f\n", cpt, buff.tab[j].idEleve, buff.tab[j].moyenne);
                        j++;
                        cpt++;
                    } // if -2-
                    else
                    {
                        fclose(fOut);
                        return false;
                    } // else -2-
                }     // while de j
            }
            i++;
        } // boucle while
        fclose(fOut);
        return true;
    } // condition if -1-
    else
    {
        fprintf(fOut, "L'intervalle choisis est errone\n");
        fclose(fOut);
        return false;
    } // else -1-
}
//------------------------------------------------------------------------------------------------------------//
// cet fonction
// return true si tout les valeur de tableau sont supperieure a une valeur inf
// return false si au moin il existe un seule element dans le tableau qui est inferieure a cet valeur
bool toutSupperieur(float borneInf, float *arr, int taille)
{
    for (int i = 0; i < taille; i++)
    {
        if (arr[i] < borneInf)
            return false;
    }
    return true;
}
//------------------------------------------------------------------------------------------------------------//
//----------LA QUESTION 4.B , LISTER LES ELEVES QUI ON EU UNE MOYENNE SUPPEREURE A 12 SUR LES 5 ANNEES--------//
bool listerElevesSuppMoy(TBOF *fArchive, float moyenneInf)
{
    //---------------------------------------------------
    Buffer_TBOF buff;
    int x = 1;
    // fOut est un pointeur vers un fichier qui vas contenir les resultats de cet fonction --listerElevesSuppMoy--
    // Dans le menu on va demander si l'utilisateur veut consulter le fichier text directement avec un editeur text , ou bien afficher le fichier sur la console.
    FILE *fOut = fopen("QUESTION_4B_RESULTAT.txt", "w");
    //---------------------------------------------------
    if (fOut == NULL)
        exit(EXIT_FAILURE);
    if (entete_TBOF(fArchive, 1) <= 0)
        return false;

    fprintf(fOut, "Les eleves qu'il ont eu une moyenne supperieure à %.2f dans tout les annees de scolarsation dans notres ecoles \n\n", moyenneInf);
    for (int i = 0; i < entete_TBOF(fArchive, 1); i++)
    {
        LireDir_TBOF(fArchive, i, &buff);
        for (int j = 0; j < buff.nb; j++)
        {
            if (buff.tab[j].anneeCourante == 5 && buff.tab[j].redouble != 0)
            {
                if (toutSupperieur(moyenneInf, buff.tab[j].tabMoyenne, 6))
                {
                    fprintf(fOut, "ELEVE%d --- ID Eleve = %04d\t", x, buff.tab[j].idEleve);
                    for (int cpt = 0; cpt <= buff.tab[j].anneeCourante; cpt++)
                    {
                        fprintf(fOut, "|%.2f", buff.tab[j].tabMoyenne[cpt]);
                    }
                    fprintf(fOut, "\n");
                    x++;
                }
            }
        }
    }
    if (x == 1) // SI x reste a 1 donc aucun eleves a eu la moyenne "MoyenneInf" , sur els 5 annees ,
    {
        fclose(fOut);
        fOut = fopen("QUESTION_4B_RESULTAT.txt", "w");
        if (fOut == NULL)
            exit(EXIT_FAILURE);
        fprintf(fOut, "AUCUN ELEVE A EU PLUS QUE %.2f !", moyenneInf);
    }
    fclose(fOut);
    return true;
}
//------------------------------------------------------------------------------------------------------------//
//---------------------L'OPERATION DE TRANFERT D'UN ELEVE D'UNE ECOLE 1 a UNE ECOLE 2 -----------------------//
bool recevoirEleve(TOVC *fTOVC, TBOF *fArchive, Tenreg_TBOF eng, char *strEleve)
{
    TOF_sauv *fsauv = Ouvrir_TOF_sauv("SAUVGARDE_ID_ELEVE", 'A');
    if (strEleve == NULL || fTOVC == NULL || fArchive == NULL || fsauv == NULL)
        exit(EXIT_FAILURE);

    if (strEleve[0] != '0') // l'eleve est supprimer
        return false;

    enregEleve eleve = getEleve(strEleve);
    libererString(strEleve);
    char ans = eleve.idClasse[0];
    libererString(eleve.idClasse);
    // on genere le nouvaux idClasse de l'eleve , une nouvelle classe
    eleve.idClasse = genererIdClasse(ans);
    libererString(eleve.idEleve);
    // on genere un nouvaux idClasse de l'eleve dans les cas ou il peut etre des id eleve commune dans les deux ecoles
    eleve.idEleve = IdEleveGenerator(fsauv);
    Fermer_TOF_sauv(fsauv);

    strEleve = ConvertionEnregEleveChaine(eleve);
    libererEleve(eleve);
    if (insertionTOVC(fTOVC, &strEleve))
    {
        // on insere l'etudiant avec sont bultin de l'annee passer dans le fichier courant dans l'ecole2
        // si l'insertion dans le fichier TOVC est terminer est terminer avec successer on inserse l'eleve avec ces donnees archive dans l'archive de l'ecole 2
        if (insertionTBOF(fArchive, eng))
            return true;
        else
            return false;
        // si insertion dans le fichier TOVC et dans l'archive est terminer avec successer, recevoirEleve return true
    }
    return false;
    // l'etudiant deja exist dans le fichier de l'annee courante
    // l'etudiant deja exist dans le fichier Archive.
}
//------------------------------------------------------------------------------------------------------------//
bool transmettreEleve(TOVC *fTOVC, TBOF *fArchive, char *idClasse, char *nom, char *prenom, Tenreg_TBOF *ArchiveData, char **strEleve)
{
    int pos_i, pos_j;
    Buffer_TBOF buff;
    if (fTOVC == NULL && fArchive == NULL)
        exit(EXIT_FAILURE);
    // on cherche l'eleve qui vas faire le transfaire dans l'archive si on le trouve on continue , sinon return false(transmettreEleve failed)
    if (!rechercheTOVC(fTOVC, nom, prenom, idClasse, &pos_i, &pos_j))
        return false; // l'etudiant que vous voulez transferer n'existe pas.

    *strEleve = recupererEnregTOVC(fTOVC, pos_i, pos_j);
    suppressionTOVC_ParPosition(fTOVC, pos_i, pos_j);
    char *idEleve = getIdEleve(*strEleve);
    pos_i = 0;
    pos_j = 0;
    // on cherche l'eleve qui vas faire le transfaire dans l'archive si on le trouve
    //, on recupere ces donnee archiver pour les transmettre pour une autre ecole
    if (RechercheTBOF(stringToInt(idEleve), fArchive, &pos_i, &pos_j))
    {
        LireDir_TBOF(fArchive, pos_i, &buff);
        *ArchiveData = buff.tab[pos_j];
        supprimerTBOF(fArchive, stringToInt(idEleve));
        libererString(idEleve);
        return true;
    }
    // si on trouve pas notre etudiant return false il n'est pas dans l'archive!
    return false;
}
//------------------------------------------------------------------------------------------------------------//
int transfert(TOVC *fTOVC1, TOVC *fTOVC2, TBOF *fArchive1, TBOF *fArchive2, char *idClasse, char *nom, char *prenom)
{
    //-------------------
    // Les Parametre de la fonction
    // fTOVC1 : le fichier de l'annee courante de l'ecole 1 ,l'etudiant est initiallement dans ce fichier
    // fArchive1 : le fichier archive de l'ecole 1 , l'etudiant est initiallement dans cet archive
    // L'eleve vas etre transferer vers une 2eme ecole , donc ces donnees vont etre transferer vers fichierCourant2 et fichier Archive 2 de la 2em ecoles
    // fTOVC2 : le fichier de l'annee courante de l'ecole 2 , les donnees de l'annee cournante d'etudiant vont etre transferer ici
    // fArchive2 : Le fichier archive de l'ecole 2 , les donnees d'etudiant archivee dans archive 1 vont etre transferer vers cet archive
    //-------------------
    int pos_i, pos_j;
    Buffer_TBOF buff;
    Tenreg_TBOF enreg;
    char *strEleve;
    //-------------------
    if (transmettreEleve(fTOVC1, fArchive1, idClasse, nom, prenom, &enreg, &strEleve))
    {
        if (recevoirEleve(fTOVC2, fArchive2, enreg, strEleve))
            return true;
        else
            return false;
    }
    else
        return false;

    // on doit generer un nouveau idEleve.
}
//------------------------------------------------------------------------------------------------------------//
void toUpperCase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = str[i] - 32;
        }
    }
}
//------------------------------------------------------------------------------------------------------------//
void innitArray(int *arr, int taille)
{
    for (int i = 0; i < taille; i++)
        arr[i] = 0;
}
//------------------------------------------------------------------------------------------------------------//
// cet fonction ecrit le contenu fichier text sur la console
void printFile(FILE *f)
{
    if (f == NULL)
        exit(EXIT_FAILURE);

    char c = '\0';

    c = fgetc(f);
    while (c != EOF)
    {
        printf("%c", c);
        c = fgetc(f);
    }
}
//------------------------------------------------------------------------------------------------------------//