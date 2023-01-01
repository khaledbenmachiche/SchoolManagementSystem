#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "TOF_intermediaire.h"

//-------------------BILBLIOTHEQUE POUR MANIPUTLER LES FICHIER TOVC DE L'ANNEE COURANTE----------------------/

//---------------------------------------------LES CONSTANTES-------------------------------------------------------------------//
#define tailleBlocTOVC 150 // La nombre de characteres dans un bloc du Fichier TOVC.
#define sizeID_Eleve 4
// par example : 7654
#define sizeID_Classe 3
// par example : 108 , eleve en premier annee Dans la salle 8
#define sizeAns 1
// si 1<=nombreAns<=9 ==> sizeAns=1 ,sinon si 10<=nombreAns<=99 ==> sizeAns = 2 ...

//-----------------------------------------------------------------------------------------------------------------------------------//

#define nombreEleve 50 // par ans donc le nombre d'eleve total c'est nombreAns*nombreEleve
#define nombreAns 6
#define nombreSalle 24
#define delimiteurEnreg '$'
#define delimiteurBloc '@'

//----------------------------------------------LES ENREGISTREMENT-------------------------------------------------------------------//
typedef struct enregEleve // on va contcatiner les champs de la structure pour construire une chaine
{
    char supp;            // 0 ou 1 , donc la taille de ce champ est egale a 1
    char *idEleve;        // idEleve est de taille sizeID_Eleve // on a ajouter un 1 pour reserver un espace pour le caractere '\0'
    char *idClasse;       // idClasse est de taille sizeID_CLASSE
    char *nomPrenomGenre; // nom-Prenom est de taille variable
    char *bultin;         // bultin est de taille variable
    //|**********************************************************************************|//
    //|  SUPPRIMER |  IDELEVE    |  IDCLASSE   | nomPrenomGenre    |       BULTIN        |//
    //|  (1 byte)  |  (4 bytes)  |  (3 bytes)  | (taille variable) |  (taille variable)  |//
    //|**********************************************************************************|//
} enregEleve;

typedef struct Tbloc_TOVC // structure pour les bloc de TOVC
{
    char chaine[tailleBlocTOVC + 1];
} Tbloc_TOVC;

typedef struct Tbloc_TOVC Buffer_TOVC;

typedef struct Entete_TOVC // entete de TOVC
{
    int nbBloc;  // Nombre de blocs dans le fichier
    int nbEnreg; // Nombre d'enregistrements dans le fichier
    int nbSuppression;
} Entete_TOVC;

typedef struct TOVC
{
    FILE *fichier;
    Entete_TOVC entete;
} TOVC;
//-----------------------------------------------------------------------------------------------------------------------//
//---------------------------------IMPLEMENTATION DU MODULE DE FICHIER TOVC---------------------------------------------//

//-|1|--FONCTION D'OUVERTURE OU CREATION D'UN FICHIER TOVC
TOVC *Ouvrir_TOVC(const char nomFichier[], char mode)
{
    TOVC *f = (struct TOVC *)malloc(sizeof(TOVC));
    if ((mode == 'A') || (mode == 'a'))
    {
        f->fichier = fopen(nomFichier, "rb+"); // ouvrir un fichier existant
        if (f->fichier == NULL)
        {
            free(f);
            return NULL;
        }
        else
            fread(&(f->entete), sizeof(f->entete), 1, f->fichier); // chargement de l'entete dans la structure
    }
    else if ((mode == 'N') || (mode == 'n'))
    {
        f->fichier = fopen(nomFichier, "wb+"); // ouvrir un nouveau fichier
        if (f->fichier == NULL)
            return NULL;
        else
        {
            f->entete.nbBloc = 0; // initialisation de l'entete dans la structure
            f->entete.nbEnreg = 0;
            f->entete.nbSuppression = 0;
        }
    }
    else
    {
        free(f);
        return NULL;
    }
    return f;
}
/****************************************************************/
//-|2|--FONCTION POUR FERMER LE FICHIER

void Fermer_TOVC(TOVC *f)
{
    rewind(f->fichier);                                       // positionne le curseur au debut du fichier
    fwrite(&(f->entete), sizeof(Entete_TOVC), 1, f->fichier); // sauvegarde l'entete en debut du fichier
    fclose(f->fichier);                                       // ferme le fichier
    free(f);                                                  // libere l'espace memoire occupe par la structure
}

/*****************************************************************/
//-|3|--PROCEDURE DE LECTURE D'UN BLOC

void LireDir_TOVC(TOVC *f, int Num_Bloc, Buffer_TOVC *buf)
{
    if (Num_Bloc <= (f->entete).nbBloc)
    {
        fseek(f->fichier, sizeof(Entete_TOVC) + (Num_Bloc) * sizeof(Tbloc_TOVC), SEEK_SET);
        fread(buf, sizeof(Tbloc_TOVC), 1, f->fichier);
    }
}

/******************************************************************/
//-|4|--PROCEDURE D'ECRITURE D'UN BLOC METHODE TOVC

void EcrireDir_TOVC(TOVC *f, int Num_Bloc, Buffer_TOVC *buf)
{
    if (Num_Bloc <= (f->entete).nbBloc)
    {
        fseek(f->fichier, sizeof(Entete_TOVC) + (Num_Bloc) * sizeof(Tbloc_TOVC), SEEK_SET);
        fwrite(buf, sizeof(Tbloc_TOVC), 1, f->fichier);
    }
}

/*******************************************************************/
//-|5|--FONCTION DE LECTURE DE L'ENTETE METHODE TOVC

int entete_TOVC(TOVC *f, int i)
{
    if (i == 1) /*lorsque i=1 ====> lecture du nombre de blocs*/
        return (f->entete).nbBloc;
    else if (i == 2) /*lorsque i=2 ====> lecture du nombre d'enregistrement*/
        return (f->entete).nbEnreg;
    else if (i == 3) /*lorsque i=3 ====> lecture du nombre d'enregi supprime*/
        return (f->entete).nbSuppression;
    else
        return -1;
}

/*********************************************************************/
//-|6|--PROCEDURE DE MODIFICATION DE L'ENTETE METHODE TOVC

void Aff_entete_TOVC(TOVC *f, int i, int val)
{
    if (i == 1) /*lorsque i=1 ====> modification du nombre de blocs*/
        (f->entete).nbBloc = val;
    else if (i == 2) /*lorsque i=2 ====> modification du nombre d'enregistrement */
        (f->entete).nbEnreg = val;
    else if (i == 3) /*lorsque i=3 ====> modification du nombre d'enregi supprime*/
        (f->entete).nbSuppression = val;
}

//-----------------------------------------------------------------------------------------------------------------------//
//----------------------------------MANIPULATION DES CHAINE DE CHARACTERES----------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------//
//---POUR CET TP ON VA UTILISER DES ALLOCATIONS DYNAMIQUE POUR LES CHAINES DE CHARACTERS--------------------------------//
//---ET CHAQUE APRES CHAQUE ALLOCATION , ET QUAND ON A TERMINER AVEC LA CHAINE ON LIBERE L'ESPACE MEMOIRE ALLOUER-------//
//----------------------------------------------------------------------------------------------------------------------//
/*--1--*/
void libererString(char *str)
// on utilise uniquement cet module pour liberer les chaines qui ont etait creer par des allocation memoire (par les fonction malloc , calloc , realloc)
{
    free(str);
}
/*********************************************************************/
/*--2--*/
char *allouerString(int size)
{
    // allouer un espace memoire pour stocker une chaine de character du taille size
    return (char *)malloc(size * sizeof(char));
}
/*********************************************************************/
/*--3--*/
char *reAllouerString(char *str, int size)
{
    // UNE FONCTION POUR REALLOUER UNE CHAINE DE CHARACTER POINTER PAR str , POUR AUGMENTEZ OU DIMUNUEZ LA TAILLE DE LA CHAINE ALLOUEZ PRECEDAMENT
    return (char *)realloc(str, size * sizeof(char));
}

//--------------------------QUELQUE OPERATION SUR LES CHAINES DE CARACTERE--------------------------------//

/*--1--*/
void stringCharAppend(char **str, char c)
{
    if (*str == NULL)
        return;
    int size = strlen(*str) + 1 + 1;
    // La taille de la chaine result du concatenation // length + 1 [pour'\0'] + 1 [le character a concatiner]
    char *tmp = reAllouerString(*str, size);
    // faire une reallocation memoire afin d'ajouter une case a la chaine pour quelle soit suffisanate pour ajjour le character
    // on verifier si l'allocation memoire etait faite ou pas
    if (tmp == NULL)
    {
        libererString(*str);
        exit(EXIT_FAILURE);
    }
    else
    {
        *str = tmp;
        (*str)[size - 2] = c;
        (*str)[size - 1] = '\0';
    }
    tmp = NULL;
}

/*********************************************************************/
/*--2--*/
char *stringStringAppend(char *str1, char *str2)
{
    int size = strlen(str1) + strlen(str2) + 1; // La taille de la chaine result du concatenation
    char *result = allouerString(size);         // Allouer un espace memoire de taille size pour la chaine result
    if (result == NULL)                         // on verifier si l'allocation memoire etait faite ou pas
        exit(EXIT_FAILURE);
    for (int i = 0; i < strlen(str1); i++) // copier str1 dans result
    {
        result[i] = str1[i];
    }
    for (int i = 0; i < strlen(str2); i++) // copier str2 dans result
    {
        result[strlen(str1) + i] = str2[i];
    }
    result[size - 1] = '\0';
    return result;
}

/*********************************************************************/
/*--3--*/
char *intToString(int nombre, int taille)
{
    int sauv, len = 0; //-Len- c'est la longueur d'integer
    char *result = allouerString(taille + 1);
    if (result == NULL)
        return NULL;
    result[0] = '\0';
    sauv = nombre;
    if (sauv != 0)
    {
        while (sauv > 0)
        {
            len++;
            sauv /= 10;
        }
    }
    else
    {
        len = 1;
    }
    char str[taille + 1];
    str[0] = '\0';
    sprintf(str, "%d", nombre);
    if (taille - len != 0)
    {
        for (int i = 0; i < (taille - len); i++)
        {
            strcat(result, "0");
        }
    }
    strcat(result, str);
    // on libere pas str car il va se libirer automatiquement a la fin de l'execution du module
    return result;
}

/*********************************************************************/
/*--4--*/

int stringToInt(char *str)
{
    char *strEnd = NULL;
    // 10 <==> La  base 10
    int result = (int)strtol(str, &strEnd, 10);
    if (strEnd == NULL)
        exit(EXIT_FAILURE);
    return result;
}

/*********************************************************************/
/*--5--*/

float stringToFloat(char *str)
{
    char *strEnd = NULL;
    float result = strtof(str, &strEnd);
    if (strEnd == NULL)
        exit(EXIT_FAILURE);

    return result;
}

//------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------QUESTION-1---------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//
int Random(int upper, int lower)
{
    return ((rand() % (upper - lower + 1)) + lower); // fonction random
}

//------------------------------------------------------------------------------------------------------------//

//----------------------------
int schoolYear[nombreAns];
int schoolSalle[nombreSalle];
//----------------------------

char *IdEleveGenerator(TOF_sauv *f)
{
    int IdEleve;
    Tenreg_TOF_sauv enreg;
    do
    {
        IdEleve = Random(9999, 0);
        enreg.idEleve = IdEleve;
        enreg.supp = false;
    } while (!Insertion_TOF_sauv(f, enreg));
    return intToString(IdEleve, sizeID_Eleve);
}

//------------------------------------------------------------------------------------------------------------//
char *IdClasseGenerator()
{
    int minSalle = 0, maxSalle = 0, randomYear = 0, randomSalle = 0;
    int promoParClasse = (nombreSalle / nombreAns), eleveParClasse = (nombreEleve / promoParClasse);

    if (eleveParClasse == 0)
        eleveParClasse = nombreEleve;

    if (nombreEleve % nombreSalle != 0)
    {
        eleveParClasse += (nombreEleve % promoParClasse);
    }
    while (true)
    {
        randomYear = Random(nombreAns - 1, 0);
        // on verifier si la promo de cet annee gener aleatoirement est pleine
        if (schoolYear[randomYear] <= nombreEleve)
        {
            schoolYear[randomYear]++;
            minSalle = randomYear * promoParClasse + 1;
            maxSalle = minSalle + promoParClasse - 1;
            while (true)
            {
                randomSalle = Random(maxSalle, minSalle);
                if (schoolSalle[randomSalle] <= eleveParClasse)
                {
                    schoolSalle[randomSalle]++;
                    break;
                }
            }
            break;
        }
    }
    char *strRandomYear = intToString(randomYear, sizeAns), *strRandomSalle = intToString(randomSalle, 2);
    // 3 = 2 + 1, 2 car le nombre de position pour la salle c'est 2--[01, 02 , 03 ... , 98 , 99]--
    char *ID_Classe = stringStringAppend(strRandomYear, strRandomSalle);
    libererString(strRandomYear);
    libererString(strRandomSalle);
    return ID_Classe;
}

//------------------------------------------------------------------------------------------------------------//
bool recupererNomPrenomFichier(FILE *f, int position, char **str) // Le fichier already opened
{
    if (f == NULL)
        exit(EXIT_FAILURE);

    char c = '\0';
    int cpt = 0;
    fseek(f, 0, SEEK_SET);
    do
    {
        c = fgetc(f);
        if (c != ',')
            stringCharAppend(str, c);
        else
        {
            if (cpt == position)
                return true;
            cpt++;
            libererString(*str);
            *str = allouerString(1);
            (*str)[0] = '\0';
        }

    } while (c != EOF);
    return false;
}

//------------------------------------------------------------------------------------------------------------//
char *nomPrenomGenerator(FILE *f1, FILE *f2, bool *prenomChecker, bool *nomChecker)
{
    int randomPrenom = Random((nombreEleve * nombreAns) - 1, 0), randomNom = Random((nombreEleve * nombreAns) - 1, 0);

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

    recupererNomPrenomFichier(f1, randomPrenom, &prenom);
    recupererNomPrenomFichier(f2, randomNom, &nom);

    stringCharAppend(&nom, '-');
    char *nomPrenom = stringStringAppend(nom, prenom);
    libererString(nom);
    libererString(prenom);
    return nomPrenom; // return name , Prenom + genre on doit separer le le surnom et le genre pour
}

//------------------------------------------------------------------------------------------------------------//

char *noteRandom()
{
    int note = Random(20, 0);
    char *virgule[3] = {".25", ".5", ".75"};
    char *strNote = NULL, *tmp = NULL;
    if (note == 20)
    {
        strNote = intToString(note, 2);
        return strNote;
    }
    else if (note >= 10)
    {
        strNote = intToString(note, 2);
    }
    else
    {
        strNote = intToString(note, 1);
    }

    tmp = stringStringAppend(strNote, virgule[Random(2, 0)]);
    free(strNote);
    strNote = tmp;
    tmp = NULL;
    return strNote;
}

//------------------------------------------------------------------------------------------------------------//

int nombreMatiere(char ans)
{
    FILE *f = fopen("matiere.txt", "r");

    if (f == NULL)
        exit(EXIT_FAILURE);

    char c = '\0';
    int nbrMatiere = 0;
    bool checker = false;
    do
    {
        c = fgetc(f);
        // on verifier si on a trouver la ligne de l'annee quand doit compter le nombre de matiere
        if (!checker)
        {
            if (c == ans)
                checker = true;
        }
        else if (checker)
        {
            if (c == ',')
            {
                // chaque , une Matiere donc on increment nbrMatiere
                nbrMatiere++;
            }
            if (c == '\n')
            {
                break;
            }
        }
    } while (c != EOF);
    nbrMatiere++; // on fait cet incremetation pour la faire dans le cas ou c == '\n' et le cas de c == EOF
    fclose(f);
    return nbrMatiere;
}
//------------------------------------------------------------------------------------------------------------//

char *bultinGenerator(char Ans)
{
    char *strNote = NULL,
         *bultin = NULL,
         *tmp = NULL;

    int nbrMatiere = nombreMatiere(Ans);

    if (nbrMatiere > 0)
    {
        bultin = allouerString(1);
        bultin[0] = '\0';
    }

    for (int i = 0; i < nbrMatiere; i++)
    {
        if (Ans == '0')
        {
            strNote = allouerString(strlen("20") + 1);
            strcpy(strNote, "20");
        }
        else
        {
            strNote = noteRandom();
        }
        stringCharAppend(&strNote, '|');
        tmp = stringStringAppend(bultin, strNote);
        libererString(strNote);
        libererString(bultin);
        bultin = tmp;
        tmp = NULL;
    }
    return bultin;
}

//------------------------------------------------------------------------------------------------------------//

char *ConvertionEnregEleveChaine(enregEleve eleve)
{
    //|**********************************************************************************|//
    //|  SUPPRIMER |  IDELEVE    |  IDCLASSE   | nomPrenomGenre    |       BULTIN        |//
    //|  (1 byte)  |  (4 bytes)  |  (3 bytes)  | (taille variable) |  (taille variable)  |//
    //|**********************************************************************************|//
    int clen =
        1 + 1 + 1 + sizeID_Eleve + sizeID_Classe + strlen(eleve.nomPrenomGenre) +
        strlen(eleve.bultin) + 1;

    char *strEnreg = allouerString(clen);
    memset(strEnreg, '\0', clen * sizeof(char));

    sprintf(strEnreg, "%c%s%s%s$%s@", eleve.supp, eleve.idEleve, eleve.idClasse, eleve.nomPrenomGenre, eleve.bultin);
    strEnreg[clen - 1] = '\0';
    return strEnreg;
}

//------------------------------------------------------------------------------------------------------------//
char *creerNomPrenomGenre(char *nom, char *prenom, char genre)
{
    int clen = strlen(nom) + strlen(prenom) + 1 + 1 + 1 + 1;
    char *str = allouerString(clen);
    memset(str, '\0', clen * sizeof(char));
    sprintf(str, "%s-%s-%c", nom, prenom, genre);
    return str;
}
//------------------------------------------------------------------------------------------------------------//

//-----------fonction pour recuperer des chaines de caracteres a partir d'une chaine de charactere qui est une concatination du plusieur chaine------------------//

char getSupp(char *strEleve)
{
    if (strEleve == NULL)
        return 0;

    return strEleve[0];
}
//------------------------------------------------------------------------------------------------------------//

char *getIdEleve(char *strEleve)
{
    if (strEleve == NULL)
        return NULL;
    char *idEleve = allouerString(sizeID_Eleve + 1);

    for (int i = 1; i < sizeID_Eleve + 1; i++)
    // on commence par i = 1 car strEleve[0] est pour stocker si la chaine et supprimer ou pas
    {
        idEleve[i - 1] = strEleve[i];
    }
    idEleve[sizeID_Eleve] = '\0';
    return idEleve;
}

//------------------------------------------------------------------------------------------------------------//

char *getIdClasse(char *strEleve)
{
    if (strEleve == NULL)
        return NULL;
    char *idClasse = allouerString(sizeID_Classe + 1);

    for (int i = sizeID_Eleve + 1; i < sizeID_Eleve + sizeID_Classe + 1; i++)
    // on commence par i = size_IdEleve + 1 car les cases d'avant sont pour stocker IdEleve et supp est pour stocker si la chaine et supprimer ou pas
    {
        idClasse[i - sizeID_Eleve - 1] = strEleve[i];
    }
    idClasse[sizeID_Classe] = '\0';
    return idClasse;
}

//------------------------------------------------------------------------------------------------------------//

char *getNomPrenomGenre(char *strEleve)
{
    if (strEleve == NULL)
        return NULL;
    char *nomPrenomGenre = allouerString(1);
    nomPrenomGenre[0] = '\0';
    int i = sizeID_Eleve + sizeID_Classe + 1;
    while (strEleve[i] != delimiteurEnreg)
    {
        stringCharAppend(&nomPrenomGenre, strEleve[i]);
        i++;
    }
    return nomPrenomGenre;
}

//------------------------------------------------------------------------------------------------------------//

void seperateNomPrenom(char *nomPrenomGenre, char **nom, char **prenom)
{
    if (nomPrenomGenre == NULL)
        return;
    int i = 0;
    (*nom) = allouerString(1);
    (*prenom) = allouerString(1);
    (*nom)[0] = '\0';
    (*prenom)[0] = '\0';
    while (i <= strlen(nomPrenomGenre) && nomPrenomGenre[i] != '-')
    {
        stringCharAppend(&*nom, nomPrenomGenre[i]);
        i++;
    }
    i++;
    while (i <= strlen(nomPrenomGenre) && nomPrenomGenre[i] != '-')
    {
        stringCharAppend(&*prenom, nomPrenomGenre[i]);
        i++;
    }
}

//------------------------------------------------------------------------------------------------------------//

char *getBultin(char *strEleve)
{
    if (strEleve == NULL)
        return NULL;
    char *bultin = allouerString(1);
    bultin[0] = '\0';
    int i = sizeID_Eleve + sizeID_Classe + 1;
    while (i < strlen(strEleve) && strEleve[i] != delimiteurEnreg)
    {
        i++;
    }
    i++;
    while (i < strlen(strEleve) && strEleve[i] != delimiteurBloc)
    {
        stringCharAppend(&bultin, strEleve[i]);
        i++;
    }
    return bultin;
}

//------------------------------------------------------------------------------------------------------------//

enregEleve getEleve(char *strEleve)
{
    enregEleve eleve;
    eleve.supp = getSupp(strEleve);
    eleve.idEleve = getIdEleve(strEleve);
    eleve.idClasse = getIdClasse(strEleve);
    eleve.nomPrenomGenre = getNomPrenomGenre(strEleve);
    eleve.bultin = getBultin(strEleve);
    return eleve;
}

//------------------------------------------------------------------------------------------------------------//

void libererEleve(enregEleve eleve)
{
    libererString(eleve.idEleve);
    libererString(eleve.idClasse);
    libererString(eleve.nomPrenomGenre);
    libererString(eleve.bultin);
}

//------------------------------------------------------------------------------------------------------------//

bool changerIdEleve(char *strEleve, char *newIdEleve) // modulle pour changer le Id de l'eleve
{
    if (strlen(newIdEleve) > sizeID_Eleve)
        return false;

    for (int i = 0; i < sizeID_Eleve; i++)
    {
        strEleve[i + 1] = newIdEleve[i];
    }
}

//------------------------------------------------------------------------------------------------------------//

bool changerIdClasse(char *strEleve, char *newIdClass) // module pour changer le Id de Classe
{
    if (strlen(newIdClass) > sizeID_Classe)
        return false;

    for (int i = 0; i < sizeID_Classe; i++)
    {
        strEleve[i + sizeID_Eleve + 1] = newIdClass[i];
    }
}

//------------------------------------------------------------------------------------------------------------//

void changerNom(char **nomPrenomGenre, char *newNom) // modulle pour changer le nom
{
    char genre = (*nomPrenomGenre)[strlen(*nomPrenomGenre) - 1];
    char *nom = NULL, *prenom = NULL;
    seperateNomPrenom(*nomPrenomGenre, &nom, &prenom);
    int size = strlen(newNom) + strlen(prenom) + 1 + 1 + 1; //'-' , '-','M ou N'
    char *tmp = reAllouerString(*nomPrenomGenre, size + 1);
    if (tmp == NULL)
    {
        free(*nomPrenomGenre);
        exit(EXIT_FAILURE);
    }
    else
        *nomPrenomGenre = tmp;
    tmp = NULL;
    memset(*nomPrenomGenre, '\0', size * sizeof(char));

    strcpy(*nomPrenomGenre, newNom);
    strcat(*nomPrenomGenre, "-");
    strcat(*nomPrenomGenre, prenom);
    (*nomPrenomGenre)[size - 2] = '-';
    (*nomPrenomGenre)[size - 1] = genre;
    (*nomPrenomGenre)[size] = '\0';
    libererString(nom);
    libererString(prenom);
}

//------------------------------------------------------------------------------------------------------------//

void changerPrenom(char **nomPrenomGenre, char *newPrenom) // module pour changer le prenom
{
    char genre = (*nomPrenomGenre)[strlen(*nomPrenomGenre) - 1];
    char *nom = NULL, *prenom = NULL;
    seperateNomPrenom(*nomPrenomGenre, &nom, &prenom);
    int size = strlen(nom) + strlen(newPrenom) + 1 + 1 + 1; //'-' , '-','M ou N'
    char *tmp = reAllouerString(*nomPrenomGenre, size + 1);
    if (tmp == NULL)
    {
        free(*nomPrenomGenre);
        exit(EXIT_FAILURE);
    }
    else
        *nomPrenomGenre = tmp;
    tmp = NULL;

    memset(*nomPrenomGenre, '\0', size * sizeof(char));
    strcpy(*nomPrenomGenre, nom);
    strcat(*nomPrenomGenre, "-");
    strcat(*nomPrenomGenre, newPrenom);
    (*nomPrenomGenre)[size - 2] = '-';
    (*nomPrenomGenre)[size - 1] = genre;
    (*nomPrenomGenre)[size] = '\0';
    libererString(nom);
    libererString(prenom);
}

//------------------------------------------------------------------------------------------------------------//

void changerGenre(char *nomPrenomGenre, char genre) // module pour changer le sexe d'etudiant
{
    if (strlen(nomPrenomGenre) > 0)
        nomPrenomGenre[strlen(nomPrenomGenre) - 1] = genre;
}

//------------------------------------------------------------------------------------------------------------//

void changerNomPrenomGenre(char **strEleve, char *newNomPrenomGenre)
{
    enregEleve eleve = getEleve(*strEleve);

    libererString(eleve.nomPrenomGenre);
    eleve.nomPrenomGenre = newNomPrenomGenre;
    libererString(*strEleve);
    *strEleve = ConvertionEnregEleveChaine(eleve);
    libererString(eleve.idEleve);
    libererString(eleve.idClasse);
    libererString(eleve.bultin);
}

//------------------------------------------------------------------------------------------------------------//

bool changerBultin(char **strEleve, char *newBultin) // module pour changer le Bultin
{
    enregEleve eleve = getEleve(*strEleve);
    libererString(eleve.bultin);
    eleve.bultin = newBultin;
    libererString(*strEleve);
    *strEleve = ConvertionEnregEleveChaine(eleve);
    libererString(eleve.idEleve);
    libererString(eleve.idClasse);
    libererString(eleve.nomPrenomGenre);
}
//---------------------------------------------------QUESTION-1----------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//
/*************************************LES MODULES DE BASE DANS UN FICHIER TOVC*********************************/
//------------------------------------------------------------------------------------------------------------//
//*-------------lA RECHERCHE DANS UN FICHIER TOVC ORDONER PAR RAPPORT AU IDclass , NOM , PRENOM--------------*/
bool rechercheTOVC(TOVC *f, char *cleNom, char *clePrenom, char *cleIDclass, int *i, int *j)
{
    int i1 = 0, j1 = 0, jsauv = 0, isauv = 0;
    Buffer_TOVC buff;
    memset(buff.chaine, '\0', (tailleBlocTOVC + 1) * sizeof(char));
    char *strEleve = allouerString(1),
         *IDclass = NULL,
         *NomPrenomGenre = NULL,
         *Nom = NULL,
         *Prenom = NULL,
         *PrenomGenre = NULL;
    char Supp = '\0';
    strEleve[0] = '\0';
    (*i) = 0;
    (*j) = 0;

    bool check = false;

    if (entete_TOVC(f, 1) > 0)
    {
        for (i1 = 0; i1 < entete_TOVC(f, 1); i1++)
        {
            LireDir_TOVC(f, i1, &buff);
            j1 = 0;
            while (j1 < strlen(buff.chaine))
            {
                if (check == false)
                {
                    isauv = i1;
                    jsauv = j1;
                }
                if (buff.chaine[j1] != delimiteurBloc)
                {
                    stringCharAppend(&strEleve, buff.chaine[j1]);
                    j1++;
                    check = true;
                }
                else
                {
                    check = false;
                    Supp = strEleve[0];
                    IDclass = getIdClasse(strEleve);
                    NomPrenomGenre = getNomPrenomGenre(strEleve);
                    seperateNomPrenom(NomPrenomGenre, &Nom, &Prenom);
                    libererString(NomPrenomGenre);
                    if (strcmp(IDclass, cleIDclass) == 0)
                    {
                        if (strcmp(Nom, cleNom) == 0)
                        {
                            if (strcmp(Prenom, clePrenom) == 0)
                            {
                                *i = isauv;
                                *j = jsauv;
                                if (Supp == '1')
                                {
                                    libererString(Prenom);
                                    libererString(Nom);
                                    libererString(IDclass);
                                    libererString(strEleve);
                                    return false;
                                }
                                else if (Supp == '0')
                                {
                                    libererString(Prenom);
                                    libererString(Nom);
                                    libererString(IDclass);
                                    libererString(strEleve);
                                    return true;
                                }
                            }
                            else if (strcmp(Prenom, clePrenom) > 0) // ca veut dire que Prenom > clePrenom
                            {
                                *i = isauv;
                                *j = jsauv;
                                libererString(Prenom);
                                libererString(Nom);
                                libererString(IDclass);
                                libererString(strEleve);
                                return false;
                            }
                        }
                        else if (strcmp(Nom, cleNom) > 0) // ca veut dire que Nom > cleNom
                        {
                            *i = isauv;
                            *j = jsauv;
                            libererString(Prenom);
                            libererString(Nom);
                            libererString(IDclass);
                            libererString(strEleve);
                            return false;
                        }
                    }                                         // if id class
                    else if (strcmp(IDclass, cleIDclass) > 0) // ca veut dire que IDclass > cleIDclass
                    {
                        *i = isauv;
                        *j = jsauv;
                        libererString(Prenom);
                        libererString(Nom);
                        libererString(IDclass);
                        libererString(strEleve);
                        return false;
                    }
                    j1++;
                    libererString(Prenom);
                    libererString(Nom);
                    libererString(IDclass);
                    libererString(strEleve);
                    strEleve = allouerString(1);
                    strEleve[0] = '\0';
                }
            }
        }
        libererString(strEleve);
        (*i) = i1;
        (*j) = j1;
        return false;
    }
}

//------------------------------------------------------------------------------------------------------------//

bool insererChaineFinTOVC(TOVC *f, char *strEleve)
{
    Buffer_TOVC buff;
    memset(buff.chaine, '\0', (tailleBlocTOVC + 1) * sizeof(char));
    int k = 0, sizeBuff = 0, espaceLibre = 0;

    if (entete_TOVC(f, 1) < 0)
        return false;

    if (entete_TOVC(f, 1) == 0)
    {
        Aff_entete_TOVC(f, 1, entete_TOVC(f, 1) + 1); // Alloc_bloc
        memset(buff.chaine, '\0', (tailleBlocTOVC + 1) * sizeof(char));
    }
    else if (entete_TOVC(f, 1) > 0)
        LireDir_TOVC(f, entete_TOVC(f, 1) - 1, &buff);

    espaceLibre = tailleBlocTOVC - strlen(buff.chaine);
    sizeBuff = strlen(buff.chaine);
    if (espaceLibre != 0)
    {
        if (strlen(buff.chaine) >= tailleBlocTOVC)
            return false;

        while (k < espaceLibre && sizeBuff <= tailleBlocTOVC)
        {
            buff.chaine[sizeBuff] = strEleve[k];
            sizeBuff++;
            k++;
        }
        EcrireDir_TOVC(f, entete_TOVC(f, 1) - 1, &buff);
        memset(buff.chaine, '\0', (tailleBlocTOVC + 1) * sizeof(char));
        sizeBuff = 0;
    }

    while (k < strlen(strEleve))
    {
        memset(buff.chaine, '\0', (tailleBlocTOVC + 1) * sizeof(char));
        sizeBuff = 0;

        for (int i = k; i < strlen(strEleve); i++)
        {
            if (strlen(buff.chaine) >= tailleBlocTOVC)
                break;
            buff.chaine[sizeBuff] = strEleve[i];
            sizeBuff++;
            k++;
        }

        buff.chaine[sizeBuff] = '\0';
        if (strlen(buff.chaine) >= tailleBlocTOVC)
        {
            EcrireDir_TOVC(f, entete_TOVC(f, 1), &buff);
            Aff_entete_TOVC(f, 1, entete_TOVC(f, 1) + 1);
            memset(buff.chaine, '\0', (tailleBlocTOVC + 1) * sizeof(char));
            sizeBuff = 0;
        }
    }
    if (strlen(buff.chaine) > 0)
    {
        EcrireDir_TOVC(f, entete_TOVC(f, 1), &buff);
        Aff_entete_TOVC(f, 1, entete_TOVC(f, 1) + 1);
    }
    libererString(strEleve);
    return true;
}

//------------------------------------------------------------------------------------------------------------//

char *recupererStringTOVC(TOVC *f, int pos_i, int pos_j, int taille)
{
    if (entete_TOVC(f, 1) <= 0)
        return NULL;
    if (taille <= 0)
        return NULL;

    Buffer_TOVC buff;
    int buffSize = 0;
    memset(buff.chaine, '\0', (tailleBlocTOVC + 1) * sizeof(char));

    int j = pos_j, cpt = 0;
    char *result = allouerString(1);
    result[0] = '\0';
    for (int i = pos_i; i < entete_TOVC(f, 1); i++)
    {
        LireDir_TOVC(f, i, &buff);
        if (i == pos_i)
            j = pos_j;
        else
            j = 0;
        buffSize = strlen(buff.chaine);
        while (j < buffSize)
        {
            stringCharAppend(&result, buff.chaine[j]);
            j++;
            cpt++;
            if (cpt == taille)
            {
                return result;
            }
        }
    }
    return result;
}

//------------------------------------------------------------------------------------------------------------//

bool recupererEndTOVC(TOVC *f, int size, char **result)
{
    Buffer_TOVC buff;
    memset(buff.chaine, '\0', (tailleBlocTOVC + 1) * sizeof(char));

    if (entete_TOVC(f, 1) <= 0)
        return false;

    if (size <= 0)
        return false;

    // calculate pos_i and pos_j
    int tmp = size;
    int pos_i = entete_TOVC(f, 1) - 1, pos_j;
    while (pos_i >= 0)
    {
        LireDir_TOVC(f, pos_i, &buff);
        while (true)
        {
            pos_j = strlen(buff.chaine) - tmp;
            tmp -= strlen(buff.chaine);

            if (pos_j < 0)
            {
                pos_i--;
                break;
            }
            else
            {
                *result = recupererStringTOVC(f, pos_i, pos_j, size + 1);
                return true;
            }
        }
    }
    return true;
}

//------------------------------------------------------------------------------------------------------------//
//-------------------------------INSERTION D'UN NOUVEAU ELEVE DANS UN FICHIER TOVC----------------------------//

bool insertionTOVC(TOVC *f, char **strEleve)
{
    if (entete_TOVC(f, 1) < 0)
        return false;
    // dans le cas ou le fichier est vide
    if (entete_TOVC(f, 1) == 0)
    {
        insererChaineFinTOVC(f, *strEleve);
        *strEleve = NULL;
        // on libere pas strEleve car va etre liberer dans insererChaineFinTOVC
        Aff_entete_TOVC(f, 2, entete_TOVC(f, 2) + 1);
        return true;
    }
    char *idClasse = getIdClasse(*strEleve),
         *tmp = getNomPrenomGenre(*strEleve),
         *prenom = NULL,
         *nom = NULL,
         *strFin = NULL;

    seperateNomPrenom(tmp, &nom, &prenom);
    libererString(tmp);
    tmp = NULL;

    Buffer_TOVC buff;
    memset(buff.chaine, '\0', (tailleBlocTOVC + 1) * sizeof(char));

    int i = 0, j = 0, cpt = 0, size = strlen(*strEleve); // size la taille de la chaine a inserer

    // on cherche si l'enregistrement exist deja ou pas si il n'exist pas on commence l'insertion.
    if (!rechercheTOVC(f, nom, prenom, idClasse, &i, &j))
    {
        //----------------------
        // on libere les chaines allouer juste pour la recherche
        libererString(idClasse);
        idClasse = NULL;
        libererString(prenom);
        prenom = NULL;
        libererString(nom);
        nom = NULL;
        //----------------------
        // si l'enregistrement doit etre dans un nouveau bloc on ajoute un nouveau bloc au fichier TOVC
        if (i >= entete_TOVC(f, 1))
        {
            insererChaineFinTOVC(f, *strEleve);
            // on libere pas strEleve car va etre liberer dans insererChaineFinTOVC
            *strEleve = NULL;
            Aff_entete_TOVC(f, 2, entete_TOVC(f, 2) + 1);
            return true;
        }

        LireDir_TOVC(f, entete_TOVC(f, 1) - 1, &buff);
        int tailleSauv = strlen(*strEleve) - (tailleBlocTOVC - strlen(buff.chaine));
        // si la valeur tailleSauv est inferieure a 0 alors il y'a un espace pour inserer l'enregistrement sans ajouter un nouveau bloc
        // sinon si tailleSauv on doit recuperer la chaine qui va etre dans un nouveau dans une chaine strFin
        if (tailleSauv > 0)
        {
            recupererEndTOVC(f, tailleSauv, &strFin);
        }

        memset(buff.chaine, '\0', (tailleBlocTOVC + 1) * sizeof(char));
        // **les decalages** //
        while (i < entete_TOVC(f, 1))
        {
            LireDir_TOVC(f, i, &buff);
            while (cpt < strlen(*strEleve))
            {
                // si cpt = 0 , on sauvgarde dans tmp une chaine de de taille size la taille de la chaine quand doit inserer
                if (cpt == 0)
                {
                    tmp = recupererStringTOVC(f, i, j, size);
                    if (tmp != NULL && tmp[0] == '\0')
                    {
                        // si on recupere un chaine de charactere vide
                        libererString(tmp);
                        tmp = NULL;
                    }
                }
                if (j < tailleBlocTOVC)
                {
                    buff.chaine[j] = (*strEleve)[cpt];
                    buff.chaine[++j] = '\0';
                    // j++;
                    cpt++;
                }
                else
                {
                    EcrireDir_TOVC(f, i, &buff);
                    memset(buff.chaine, '\0', (tailleBlocTOVC + 1) * sizeof(char));
                    i++;
                    j = 0;
                    break;
                }

                if (cpt >= strlen(*strEleve))
                {
                    if (*strEleve != NULL)
                    {
                        libererString(*strEleve);
                        *strEleve = NULL;
                    }
                    *strEleve = tmp;
                    cpt = 0;
                    if (tmp == NULL)
                    {
                        // si tmp est NULL on a traiter le derniere bloc on doit inserer cet bloc
                        EcrireDir_TOVC(f, i, &buff);

                        if (*strEleve != NULL)
                        {
                            libererString(*strEleve);
                            *strEleve = NULL;
                        }
                        Aff_entete_TOVC(f, 2, entete_TOVC(f, 2) + 1);
                        return true;
                    }
                }
            }
        }
        // apres les decalages sont terminer et tailleSauv > 0 , donc on doit inserer strFin quand a recuperer au debut.
        // dans le cas ou tailleSauv <= 0 , l'insertion est terminer.
        if (tailleSauv > 0)
        {
            insererChaineFinTOVC(f, strFin);
            // strFin va etre liberer dans le module insererChaineFinTOVC.
            strFin = NULL;
            if (*strEleve != NULL)
            {
                libererString(*strEleve);
                *strEleve = NULL;
            }
            if (tmp != NULL)
            {
                libererString(tmp);
                tmp = NULL;
            }
            Aff_entete_TOVC(f, 2, entete_TOVC(f, 2) + 1);
            return true;
        }
        if (*strEleve != NULL)
        {
            libererString(*strEleve);
            *strEleve = NULL;
        }
        if (tmp != NULL)
        {
            libererString(tmp);
            tmp = NULL;
        }
        return true;
    }
    //-------------------------------------------------------
    // on libere les chaines allouer juste pour la recherche
    if (idClasse != NULL)
        libererString(idClasse);
    if (prenom != NULL)
        libererString(prenom);
    if (nom != NULL)
        libererString(nom);
    if (*strEleve != NULL)
    {
        libererString(*strEleve);
        *strEleve = NULL;
    }
    //-------------------------------------------------------
    return false;
    // A la fin d'execution de l'insertion strEleve la chaine inserer sera liberer donc on libere pas la chaine dans le main
}

//------------------------------------------------------------------------------------------------------------//
//*-----------------------------------------LA REORGANIZATION DANS UN FICHIER TOVC---------------------------//
void reorganizationTOVC(TOVC *f)
{
    Buffer_TOVC buff1, buff2;

    memset(buff1.chaine, '\0', (tailleBlocTOVC + 1) * sizeof(char));
    memset(buff2.chaine, '\0', (tailleBlocTOVC + 1) * sizeof(char));
    int j1 = 0, j2 = 0, i2 = 0;
    bool check = true, supp = false;
    Entete_TOVC entete = {0, 0, f->entete.nbSuppression};

    if (entete_TOVC(f, 1) <= 0)
        return;

    for (int i1 = 0; i1 < entete_TOVC(f, 1); i1++)
    {
        LireDir_TOVC(f, i1, &buff1);
        j1 = 0;
        while (j1 < strlen(buff1.chaine)) // va iterer dans la chaine du buff1
        {
            if (check)
            {
                if (buff1.chaine[j1] == '0')
                {
                    supp = false;
                    entete.nbEnreg++;
                }
                else if (buff1.chaine[j1] == '1')
                {
                    supp = true;
                    entete.nbSuppression--;
                }
                check = false;
            }
            if (buff1.chaine[j1] == delimiteurBloc)
            {
                if (!supp)
                {
                    buff2.chaine[j2] = buff1.chaine[j1];
                    j2++;
                }
                j1++;
                check = true;
                supp = false;
            }
            else if (!supp)
            {
                if (strlen(buff2.chaine) >= tailleBlocTOVC)
                {
                    EcrireDir_TOVC(f, i2, &buff2);
                    memset(buff2.chaine, '\0', (tailleBlocTOVC + 1) * sizeof(char));
                    j2 = 0;
                    i2++;
                    entete.nbBloc++;
                }
                buff2.chaine[j2] = buff1.chaine[j1];
                j1++;
                j2++;
            }
            else if (supp)
                j1++;
        }
    }
    if (strlen(buff2.chaine) > 0)
    {
        EcrireDir_TOVC(f, i2, &buff2);
        entete.nbBloc++;
    }
    f->entete = entete;
}

//------------------------------------------------------------------------------------------------------------//
//*-----------LE CHARGEMENT INITIAL DE FICHIER TOVC DE L'ANNEE COURANTE RANDOMIZED FICHIER TOVC--------------//
void chargementInitialTOVC(TOVC *f)
{
    if (f == NULL)
        exit(EXIT_FAILURE);
    enregEleve eleve;
    char *strEleve = NULL;
    // direct hashing tables
    bool prenomChecker[nombreEleve * nombreAns] = {false};
    bool nomChecker[nombreEleve * nombreAns] = {false};
    FILE *f1 = fopen("prenomAlgeriens.txt", "r"), *f2 = fopen("nomAlgeriens.txt", "r");
    TOF_sauv *fsauv = Ouvrir_TOF_sauv("SAUVGARDE_ID_ELEVE", 'N'); // un fichier pour sauvgarder idEleve
    if (f1 == NULL || f2 == NULL || fsauv == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < nombreAns * nombreEleve; i++)
    {
        eleve.supp = '0';
        eleve.idEleve = IdEleveGenerator(fsauv);
        eleve.idClasse = IdClasseGenerator();
        eleve.nomPrenomGenre = nomPrenomGenerator(f1, f2, prenomChecker, nomChecker);
        eleve.bultin = bultinGenerator(eleve.idClasse[0]);
        strEleve = ConvertionEnregEleveChaine(eleve);
        libererEleve(eleve);
        insertionTOVC(f, &strEleve);
    }
    fclose(f1);
    fclose(f2);
    Fermer_TOF_sauv(fsauv);
}

//------------------------------------------------------------------------------------------------------------//

bool rechercheTOVCParEnreg(TOVC *f, int position, int *i, int *j)
{
    Buffer_TOVC buff;
    memset(buff.chaine, '\0', (tailleBlocTOVC + 1) * sizeof(char));
    int isauv = 0, jsauv = 0, cpt = 0;
    bool check = true, supp = false;

    if (entete_TOVC(f, 1) <= 0)
        return false;

    for (*i = 0; (*i) < entete_TOVC(f, 1); (*i)++)
    {
        LireDir_TOVC(f, (*i), &buff);
        (*j) = 0;
        while (*j < strlen(buff.chaine)) // va iterer dans la chaine du buff1
        {
            if (check)
            {
                if (buff.chaine[*j] == '0')
                    supp = false;
                else if (buff.chaine[*j] == '1')
                {
                    supp = true;
                }
                check = false;
                jsauv = *j;
                isauv = *i;
            }
            if (buff.chaine[*j] == delimiteurBloc)
            {
                if (!supp)
                    cpt++;
                check = true;
                supp = false;
            }

            if (position == cpt)
            {
                (*j) = jsauv;
                (*i) = isauv;
                return true;
            }
            (*j)++;
        }
    }
    return true;
}

//------------------------------------------------------------------------------------------------------------//

char *recupererEnregTOVC(TOVC *f, int i, int j)
{
    Buffer_TOVC buff;
    memset(buff.chaine, '\0', (tailleBlocTOVC + 1) * sizeof(char));
    if (i >= entete_TOVC(f, 1))
        return NULL;

    char *result = allouerString(1);
    bool checker = true;
    result[0] = '\0';
    if (entete_TOVC(f, 1) > 0)
    {
        while (i < entete_TOVC(f, 1))
        {
            LireDir_TOVC(f, i, &buff);
            if (checker != true)
                j = 0;
            else
                checker = false;

            while (j < strlen(buff.chaine)) // va iterer dans la chaine du buff
            {
                stringCharAppend(&result, buff.chaine[j]);
                if (buff.chaine[j] == delimiteurBloc)
                {
                    return result;
                }
                j++;
            }
            i++;
        }
    }
    return result;
}
//------------------------------------------------------------------------------------------------------------//

bool suppressionTOVC_ParPosition(TOVC *f, int pos_i, int pos_j)
{
    if (pos_i > entete_TOVC(f, 1))
        return false;
    Buffer_TOVC buff;
    LireDir_TOVC(f, pos_i, &buff);
    if (pos_j >= strlen(buff.chaine))
        return false;
    char *strEleve = recupererEnregTOVC(f, pos_i, pos_j);
    //----on supprime id-Eleve du fichier TOF intermidiaire-----//
    //-----------------------------------------------------------
    TOF_sauv *fsauv = Ouvrir_TOF_sauv("SAUVGARDE_ID_ELEVE", 'A');
    char *idEleve = getIdEleve(strEleve);
    suppression_TOF_sauv(fsauv, stringToInt(idEleve));
    //-----------------------------------------------------------

    buff.chaine[pos_j] = '1';
    EcrireDir_TOVC(f, pos_i, &buff);
    Aff_entete_TOVC(f, 3, entete_TOVC(f, 3) + 1);
    Aff_entete_TOVC(f, 2, entete_TOVC(f, 2) - 1);
    if (entete_TOVC(f, 3) >= (nombreAns * nombreEleve) / 2)
        reorganizationTOVC(f);
    //-----------------------------------------------------------
    libererString(strEleve);
    libererString(idEleve);
    Fermer_TOF_sauv(fsauv);
    //------------------------------------------------------------
    return true;
}
//------------------------------------------------------------------------------------------------------------//
//-------------------------------------LA SUPPRESSION LOGIQUE DANS UN FICHIER TOVC----------------------------//
bool suppressionTOVC(TOVC *f, char *cleNom, char *clePrenom, char *cleIDclass)
{
    int i, j;
    Buffer_TOVC buff;
    memset(buff.chaine, '\0', (tailleBlocTOVC + 1) * sizeof(char));
    if (rechercheTOVC(f, cleNom, clePrenom, cleIDclass, &i, &j))
    {
        suppressionTOVC_ParPosition(f, i, j);
        return true;
    }
    return false;
}
//------------------------------------------------------------------------------------------------------------//
//*--------LA MISE A JOUR D'UN ENREGISTREMENT D'UNE POSTION i, DANS LE FICHIER TOVC-----------------//
bool miseJourTOVC(TOVC *f, int position, char *newStr)
{
    int pos_i = 0, pos_j = 0;
    if (rechercheTOVCParEnreg(f, position, &pos_i, &pos_j))
    {
        suppressionTOVC_ParPosition(f, pos_i, pos_j);
        insertionTOVC(f, &newStr);
        return true;
    }
    return false;
}
//------------------------------------------------------------------------------------------------------------//
bool miseJourTOVCParPosition(TOVC *f, int pos_i, int pos_j, char *newStr)
{
    // on utiliser cet fonction si on a utiliser la recherche , pour minimiser le cout du programme et eviter faire de recherche
    suppressionTOVC_ParPosition(f, pos_i, pos_j);
    if (insertionTOVC(f, &newStr))
        return true;
    return false;
}

//------------------------------------------------------------------------------------------------------------//
//-----------------------------------LES AFFICHAGES DE NOTRE FICHIER TOVC------------------------------------//
//------------------------------------------------------------------------------------------------------------//

void Affichage_TOVC(TOVC *f)
{
    Buffer_TOVC buff;
    printf("\nENTETE : %d\t%d\t%d\t\n", entete_TOVC(f, 1), entete_TOVC(f, 2), entete_TOVC(f, 3));

    for (int i = 0; i < entete_TOVC(f, 1); i++)
    {
        LireDir_TOVC(f, i, &buff);
        printf("\n\nbloc %d : %s \n\n", i, buff.chaine);
    }
}
//------------------------------------------------------------------------------------------------------------//
void affichageParEnregTOVC(TOVC *f)
{
    Buffer_TOVC buff;
    int j = 0, nbrEnreg = 1;
    char *strEleve = allouerString(1);
    strEleve[0] = '\0';
    enregEleve eleve;
    printf("\nENTETE : %d\t%d\t%d\t\n", entete_TOVC(f, 1), entete_TOVC(f, 2), entete_TOVC(f, 3));
    for (int i = 0; i < entete_TOVC(f, 1); i++)
    {
        LireDir_TOVC(f, i, &buff);
        j = 0;
        while (j <= strlen(buff.chaine))
        {
            if (buff.chaine[j] != delimiteurBloc)
            {
                stringCharAppend(&strEleve, buff.chaine[j]);
            }
            else
            {
                if (strEleve[0] == '0')
                {
                    eleve = getEleve(strEleve);
                    printf("\nELEVE %3d: ID eleve : %4s\tID classe : %3s\tNom-Prenom-Genre : %s\tbultin :%s \n",
                           nbrEnreg,
                           eleve.idEleve,
                           eleve.idClasse,
                           eleve.nomPrenomGenre,
                           eleve.bultin);
                    nbrEnreg++;
                    libererEleve(eleve);
                }
                libererString(strEleve);
                strEleve = allouerString(1);
                strEleve[0] = '\0';
            }
            j++;
        }
    }
    libererString(strEleve);
}
//------------------------------------------------------------------------------------------------------------//
float RandomFloat(float a, float b)
{
    // pour gener un float Random.
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}
//------------------------------------------------------------------------------------------------------------//
void incrementIdClasse(char *idClasse)
{
    int promoParClasse = (nombreSalle / nombreAns);
    int ID = stringToInt(idClasse);

    int ans = ID / 100;
    int classe = ID % 100;
    ans++;
    classe += promoParClasse;
    ID = ans * 100 + classe;
    char *newID = intToString(ID, sizeID_Classe);
    for (int i = 0; i < sizeID_Classe; i++)
        idClasse[i] = newID[i];
    libererString(newID);
    newID = NULL;
}
//------------------------------------------------------------------------------------------------------------//
void tabMoyenneInit(float *arr, int size)
{
    arr[0] = 20;
    for (int i = 1; i < size; i++)
    {
        // on initialise le tableau avec des notes superieure a 10 ensuite on ecrase les valeur dans les cas ou faut ecraser
        // sinon c'est les notes precedentes d'eleve
        arr[i] = RandomFloat(20, 10);
    }
}
//------------------------------------------------------------------------------------------------------------//
char *genererIdClasse(char ans) // cet fonction genere IdClasse Random en fonction de l'annee entrer
{
    int promoParClasse = nombreSalle / nombreAns;
    // pour convertir un character vers un int en fait char - '0'
    int minSalle = (ans - '0') * promoParClasse + 1;
    int maxSalle = minSalle + promoParClasse - 1;
    int randomSalle = Random(maxSalle, minSalle);
    char *strRandomSalle = intToString(randomSalle, 2);
    char *idClasse = allouerString(sizeID_Classe + 1);
    idClasse[0] = ans;
    idClasse[1] = strRandomSalle[0];
    idClasse[2] = strRandomSalle[1];
    idClasse[sizeID_Classe] = '\0';
    libererString(strRandomSalle);
    return idClasse;
}
//------------------------------------------------------------------------------------------------------------//