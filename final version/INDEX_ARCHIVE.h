#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//************************************-REMARQUES ET REPONSE DE LA QUESTION -3.B.i-***********************************************************************************//
//| -----------------------------------------------------------------------------------------------------------------------------------------------------------------|//
//|L'INDEX DANS CE CAS EST UN INDEX DENSE.                                                                                                                           |//
//|LA CLE SERA LA MOYENNE DE L'ETUDIANT DE L'ANNEE EN QUESTION.                                                                                                      |//
//|PAR EXAMPLE DANS L'INDEX 1 , LA CLE SERA LA MOYENNE DE L'ETUDIANT SUR CET ANNEE.                                                                                  |//
//|------------------------------------------------------------------------------------------------------------------------------------------------------------------|//
//|POUR UN SEULE ARCHIVE SUR 5 ANS IL Y'AURA POUR TOUT LES ETUDIANTS 5 INDEX , POUR LA 1ER, 2EM , 3EM , 4EM , 5EM ANNEE.                                             |//
//|POUR LE PRESCOLAIRE ON VAS PAS FAIRE UN INDEX CAR TOUT LES ETUDIANTS VONT AVOIR UNE MOYENNE 20/20 , ON OPTIMISE LES RESOURCES.                                    |//
//********************************************************************************************************************************************************************//

#define tailleBlocTOF_index 25 // Le nombre d'enregistrements maximal d'un bloc TOF_index

/*************************************** Declaration de la structure de fichier TOF_index *******************************************/

/* Structure d'enregistrement */
typedef struct Tenreg_TOF_index
{
    // La cle dans notre cas , l'archivage sera moyenne
    float moyenne;
    int idEleve;
    int pos_i;
    int pos_j;
    int supp;
    //-------------------------
} Tenreg_TOF_index;

/* Structure de bloc */
typedef struct Tbloc_TOF_index
{
    Tenreg_TOF_index tab[tailleBlocTOF_index];
    int nb; // nombre d'enregistrements dans le bloc
} Tbloc_TOF_index;

/* Structure du buffer */
typedef struct Tbloc_TOF_index Buffer_TOF_index;

/* Structure de l'entete du fichier */
typedef struct Entete_TOF_index
{
    int nbBloc; // Nombre de blocs dans le fichier
    int nbEnreg;
    int nbSuppression; // Nombre d'enregistrements dans le fichier
} Entete_TOF_index;

typedef struct TOF_index
{
    FILE *fichier;
    Entete_TOF_index entete;
} TOF_index;

//------------------------------------------------------------------------------------------------------------//

TOF_index *Ouvrir_TOF_index(const char nomFichier[], char mode)
{
    TOF_index *f = (struct TOF_index *)malloc(sizeof(TOF_index));
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
            return NULL;
        else
        {
            f->entete.nbBloc = 0; // initialisation de l'ent�te dans la structure
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

//------------------------------------------------------------------------------------------------------------//

/* Procedure de fermeture d'un fichier TOF_index */

void Fermer_TOF_index(TOF_index *f)
{
    rewind(f->fichier);                                            // positionne le curseur au debut du fichier
    fwrite(&(f->entete), sizeof(Entete_TOF_index), 1, f->fichier); // sauvegarde l'entete en debut du fichier
    fclose(f->fichier);                                            // ferme le fichier
    free(f);                                                       // libere l'espace memoire occupe par la structure
}
//------------------------------------------------------------------------------------------------------------//

/* Procedure de lecture d'un bloc TOF_index */

void LireDir_TOF_index(TOF_index *f, int Num_Bloc, Buffer_TOF_index *buf)
{
    if (Num_Bloc <= f->entete.nbBloc)
    {
        fseek(f->fichier, sizeof(Entete_TOF_index) + Num_Bloc * sizeof(Tbloc_TOF_index), SEEK_SET);
        fread(buf, sizeof(Tbloc_TOF_index), 1, f->fichier);
    }
}

//------------------------------------------------------------------------------------------------------------//

/* Procedure d'ecriture d'un bloc methode TOF_index */

void EcrireDir_TOF_index(TOF_index *f, int Num_Bloc, Buffer_TOF_index *buf)
{
    if (Num_Bloc <= (f->entete).nbBloc)
    {
        fseek(f->fichier, sizeof(Entete_TOF_index) + Num_Bloc * sizeof(Tbloc_TOF_index), SEEK_SET);
        fwrite(buf, sizeof(Tbloc_TOF_index), 1, f->fichier);
    }
}
//------------------------------------------------------------------------------------------------------------//

/* Fonction de lecture de l'entete methode TOF_index */

// lorsque i=1 ====> lecture du nombre de blocs
// lorsque i=2 ====> lecture du nombre d'enregistrement

int entete_TOF_index(TOF_index *f, int i)
{
    if (i == 1)
        return (f->entete).nbBloc;
    else if (i == 2)
        return (f->entete).nbEnreg;
    else if (i == 3)
        return (f->entete).nbSuppression;
    else
        return -1;
}
//------------------------------------------------------------------------------------------------------------//
/* Procedure de modification de l'entete methode TOF_index */
/* lorsque i=1 ====> modification du nombre de blocs
   lorsque i=2 ====> modification du nombre d'enregistrement */

void Aff_entete_TOF_index(TOF_index *f, int i, int val)
{
    if (i == 1)
        (f->entete).nbBloc = val;
    else if (i == 2)
        (f->entete).nbEnreg = val;
    else if (i == 3)
        (f->entete).nbSuppression = val;
}
//------------------------------------------------------------------------------------------------------------//

int Alloc_bloc_TOF_index(TOF_index *f)
{
    Aff_entete_TOF_index(f, 1, entete_TOF_index(f, 1) + 1);
    return entete_TOF_index(f, 1) - 1;
}

//------------------------------------------------------------------------------------------------------------//
bool RechDicho_TOF_index(TOF_index *f, float moyenne, int *i, int *j)
{
    if (entete_TOF_index(f, 1) <= 0)
    {
        *i = 0;
        *j = 0;
        return false;
    }
    Buffer_TOF_index buf;
    bool trouv = false, stop = false;

    int infB = 0, supB = entete_TOF_index(f, 1) - 1; // les numeros des blocs sup et inf de la recherche externe
    int infE, supE;                                  // les positions des enregistrements sup et inf de la recherche interne
    /* Traitement du cas ou le fichier est vide */
    /* Recherche externe */
    while (infB <= supB && !trouv && !stop)
    {
        *i = (infB + supB) / 2; // le numero du bloc du milieu
        LireDir_TOF_index(f, *i, &buf);
        if (buf.tab[0].moyenne <= moyenne && moyenne <= buf.tab[buf.nb - 1].moyenne)
        {
            /* Recherche interne */
            infE = 0;          // le premier enregistrement du bloc
            supE = buf.nb - 1; // le dernier enregistrement du bloc
            while (infE <= supE && !trouv)
            {
                *j = (infE + supE) / 2; // l'indice de l'enregistrement du milieu
                if (buf.tab[*j].moyenne == moyenne)
                    trouv = true;
                else
                {
                    if (buf.tab[*j].moyenne > moyenne)
                        supE = *j - 1;
                    if (buf.tab[*j].moyenne < moyenne)
                        infE = *j + 1;
                }
            }
            if (infE > supE) // le numero recherche n'existe pas dans le bloc
                *j = infE;   // la position ou il faut l'inseerer alors
            stop = true;
            /* Fin de la recherche interne */
        }
        else
        {
            if (buf.tab[0].moyenne > moyenne)
                supB = *i - 1;
            if (moyenne > buf.tab[buf.nb - 1].moyenne)
                infB = *i + 1;
        }
    }
    if (infB > supB && moyenne < buf.tab[0].moyenne) // le numero recherche est plus petite que
        *j = 0;                                      // tous les numeros qui existent dans le fichier

    if (infB > supB && moyenne > buf.tab[buf.nb - 1].moyenne) // le numero recherche est plus grande que
    {                                                         // tous les numeros qui existent dans le fichier

        if (buf.nb == tailleBlocTOF_index) // le dernier bloc est plein
        {
            *i = infB; // il faut inserer l'enregistrement dans un nouveau bloc
            *j = 0;
        }
        else             // le dernier bloc n'est pas encore plein
            *j = buf.nb; // il faut l'inserer dans le dernier bloc a la premiere position libre
    }
    /* Fin de la recherche externe */
    return trouv;
}
//------------------------------------------------------------------------------------------------------------//
/* module d'insertion dans le fichier TOF_index */
bool Insertion_TOF_index(TOF_index *f, Tenreg_TOF_index enreg)
{
    //---------------------
    Buffer_TOF_index buff;
    Tenreg_TOF_index x;
    bool continu = true;
    //---------------------
    if (entete_TOF_index(f, 1) < 0)
        return false;
    if (entete_TOF_index(f, 1) == 0)
    {
        buff.tab[0] = enreg;
        buff.nb = 1;
        EcrireDir_TOF_index(f, 0, &buff);
        Aff_entete_TOF_index(f, 1, entete_TOF_index(f, 1) + 1);
        Aff_entete_TOF_index(f, 2, entete_TOF_index(f, 2) + 1);
        return true;
    }
    int i = 0, j = 0;
    //---------------------
    // On commence par rechercher l'enregistrement pour localiser l'emplacement (i,j)
    // on doit etre inserer l'enregistrement s'il n'existe pas encore dans le fichier
    if (RechDicho_TOF_index(f, enreg.moyenne, &i, &j))
        return false;
    // la cle existe deja dans le fichier et on ne peut pas le reinserer
    // la cle n'existe pas dans le fichier, il faut l'inserer a l'emplacement (i,j)

    while (continu && i < entete_TOF_index(f, 1))
    {
        LireDir_TOF_index(f, i, &buff);
        x = buff.tab[buff.nb - 1]; // sauvegarder le dernier enregistrement du bloc

        /* Decalages intra-bloc */
        for (int k = buff.nb - 1; k > j; k--)
            buff.tab[k] = buff.tab[k - 1];

        buff.tab[j] = enreg;

        if (buff.nb < tailleBlocTOF_index) // si le bloc n'est pas plein, on remet x dans permier indice libre du bloc
        {
            buff.nb++;
            if (j == buff.nb - 1) // le nouvel enregistrement est le dernier enregistrement du fichier
                buff.tab[buff.nb - 2] = x;
            else // le nouvel enregistrement est inserer entre deux enregistrements
                buff.tab[buff.nb - 1] = x;
            EcrireDir_TOF_index(f, i, &buff);
            continu = false;
        }
        else // si le bloc est plein, x doit etre inserer dans un nouveau bloc i+1 a la position 0
        {
            EcrireDir_TOF_index(f, i, &buff);
            i++;
            j = 0;
            enreg = x; // l'enregistrement qui doit etre inserer a l'emplacement (i,0)
        }
    }
    // si on depasse la fin de fichier, on rajoute un nouveau bloc contenant un seul enregistrement
    if (i >= entete_TOF_index(f, 1))
    {
        buff.tab[0] = enreg;
        buff.nb = 1;
        EcrireDir_TOF_index(f, Alloc_bloc_TOF_index(f), &buff);
    }

    Aff_entete_TOF_index(f, 2, entete_TOF_index(f, 2) + 1);
    // incrementer le champ de l'entete qui contient le nombre d'enregistrements
    return true;
}
//------------------------------------------------------------------------------------------------------------//
bool suppression_TOF_index(TOF_index *f, Tenreg_TOF_index enreg)
{
    int i, j;
    Buffer_TOF_index buff;
    if (RechDicho_TOF_index(f, enreg.moyenne, &i, &j))
    {
        LireDir_TOF_index(f, i, &buff);
        buff.tab[j].supp = 1;
        EcrireDir_TOF_index(f, i, &buff);
        Aff_entete_TOF_index(f, 3, entete_TOF_index(f, 3) + 1);
        Aff_entete_TOF_index(f, 2, entete_TOF_index(f, 2) + 1);
    }
    return false;
}
//------------------------------------------------------------------------------------------------------------//
void Affichage_TOF_index(TOF_index *f)
{
    Buffer_TOF_index buffer;

    printf("\n\t***************************************\n");
    printf("\t          AFFICHAGE FICHIER INDEX");
    printf("\n\t***************************************\n");
    for (int i = 0; i < entete_TOF_index(f, 1); i++)
    {
        LireDir_TOF_index(f, i, &buffer);                 // lire le bloc dans buffer
        printf("\n\tBloc num %d\tNB=%d\n", i, buffer.nb); // Afficher le num du bloc et le nombre d'enr qu'il contient
        for (int j = 0; j < buffer.nb; j++)
        { // Afficher les enregistrements du buffer
            printf("idEleve : %d --- moyenne : %.2f --- (i , j) = (%d , %d)\n\n", buffer.tab[j].idEleve, buffer.tab[j].moyenne, buffer.tab[j].pos_i, buffer.tab[j].pos_j);
        }
        printf("\n\t---------------------------------------\n");
    }
}

void insererDansLesIndexes(TOF_index *f1, TOF_index *f2, TOF_index *f3, TOF_index *f4, TOF_index *f5, int ansCourant, Tenreg_TOF_index enreg)
{
    switch (ansCourant)
    {
    case 1:
        Insertion_TOF_index(f1, enreg);
        return;
    case 2:
        Insertion_TOF_index(f2, enreg);
        return;
    case 3:
        Insertion_TOF_index(f3, enreg);
        return;
    case 4:
        Insertion_TOF_index(f4, enreg);
        return;
    case 5:
        Insertion_TOF_index(f5, enreg);
        return;
    default:
        return;
    }
}