#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//-----------------------------------------------------------------------------------//
//|CET BIBLIOTHEQUE TOF_INTERMEDIAIRE.h , EST FAITE POUR GENERER DES ID ELEVE UNIQUE|//
//-----------------------------------------------------------------------------------//

#define tailleBlocTOF_sauv 25 // Le nombre d'enregistrements maximal d'un bloc TOF_sauv
/*************************************** Declaration de la structure de fichier TOF_sauv *******************************************/

/* Structure d'enregistrement */
typedef struct Tenreg_TOF_sauv
{
    // La cle dans notre cas , le fichier de l'annee courante sera idEleve
    int idEleve;
    //-------------------------
    int supp;
    //-------------------------
} Tenreg_TOF_sauv;

/* Structure de bloc */
typedef struct Tbloc_TOF_sauv
{
    Tenreg_TOF_sauv tab[tailleBlocTOF_sauv];
    int nb; // nombre d'enregistrements dans le bloc
} Tbloc_TOF_sauv;

/* Structure du buffer */
typedef struct Tbloc_TOF_sauv Buffer_TOF_sauv;

/* Structure de l'entete du fichier */
typedef struct Entete_TOF_sauv
{
    int nbBloc;  // Nombre de blocs dans le fichier
    int nbEnreg; // Nombre d'enregistrements dans le fichier
    int nbSupp;  // Nombre d'enregistrements supprimer dans le fichier
} Entete_TOF_sauv;

typedef struct TOF_sauv
{
    FILE *fichier;
    Entete_TOF_sauv entete;
} TOF_sauv;

//------------------------------------------------------------------------------------------------------------//

TOF_sauv *Ouvrir_TOF_sauv(const char nomFichier[], char mode)
{
    TOF_sauv *f = (struct TOF_sauv *)malloc(sizeof(TOF_sauv));
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
            f->entete.nbBloc = 0; // initialisation de l'ent�te dans la structure
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

/* Procedure de fermeture d'un fichier TOF_sauv */

void Fermer_TOF_sauv(TOF_sauv *f)
{
    rewind(f->fichier);                                           // positionne le curseur au debut du fichier
    fwrite(&(f->entete), sizeof(Entete_TOF_sauv), 1, f->fichier); // sauvegarde l'entete en debut du fichier
    fclose(f->fichier);                                           // ferme le fichier
    free(f);                                                      // libere l'espace memoire occupe par la structure
}
//------------------------------------------------------------------------------------------------------------//

/* Procedure de lecture d'un bloc TOF_sauv */

void LireDir_TOF_sauv(TOF_sauv *f, int Num_Bloc, Buffer_TOF_sauv *buf)
{
    if (Num_Bloc <= f->entete.nbBloc)
    {
        fseek(f->fichier, sizeof(Entete_TOF_sauv) + Num_Bloc * sizeof(Tbloc_TOF_sauv), SEEK_SET);
        fread(buf, sizeof(Tbloc_TOF_sauv), 1, f->fichier);
    }
}

//------------------------------------------------------------------------------------------------------------//

/* Procedure d'ecriture d'un bloc methode TOF_sauv */

void EcrireDir_TOF_sauv(TOF_sauv *f, int Num_Bloc, Buffer_TOF_sauv *buf)
{
    if (Num_Bloc <= (f->entete).nbBloc)
    {
        fseek(f->fichier, sizeof(Entete_TOF_sauv) + Num_Bloc * sizeof(Tbloc_TOF_sauv), SEEK_SET);
        fwrite(buf, sizeof(Tbloc_TOF_sauv), 1, f->fichier);
    }
}
//------------------------------------------------------------------------------------------------------------//

/* Fonction de lecture de l'entete methode TOF_sauv */

// lorsque i=1 ====> lecture du nombre de blocs
// lorsque i=2 ====> lecture du nombre d'enregistrement

int entete_TOF_sauv(TOF_sauv *f, int i)
{
    if (i == 1)
        return (f->entete).nbBloc;
    else if (i == 2)
        return (f->entete).nbEnreg;
    else
        return -1;
}
//------------------------------------------------------------------------------------------------------------//
/* Procedure de modification de l'entete methode TOF_sauv */
/* lorsque i=1 ====> modification du nombre de blocs
   lorsque i=2 ====> modification du nombre d'enregistrement */

void Aff_entete_TOF_sauv(TOF_sauv *f, int i, int val)
{
    if (i == 1)
        (f->entete).nbBloc = val;
    else if (i == 2)
        (f->entete).nbEnreg = val;
}
//------------------------------------------------------------------------------------------------------------//

int Alloc_bloc_TOF_sauv(TOF_sauv *f)
{
    Aff_entete_TOF_sauv(f, 1, entete_TOF_sauv(f, 1) + 1);
    return entete_TOF_sauv(f, 1) - 1;
}

//------------------------------------------------------------------------------------------------------------//
bool RechDicho_TOF_sauv(TOF_sauv *f, int idEleve, int *i, int *j)
{
    if (entete_TOF_sauv(f, 1) <= 0)
    {
        *i = 0;
        *j = 0;
        return false;
    }
    Buffer_TOF_sauv buf;
    bool trouv = false, stop = false;

    int infB = 0, supB = entete_TOF_sauv(f, 1) - 1; // les numeros des blocs sup et inf de la recherche externe
    int infE, supE;                                 // les positions des enregistrements sup et inf de la recherche interne
    /* Traitement du cas ou le fichier est vide */
    /* Recherche externe */
    while (infB <= supB && !trouv && !stop)
    {
        *i = (infB + supB) / 2; // le numero du bloc du milieu
        LireDir_TOF_sauv(f, *i, &buf);
        if (buf.tab[0].idEleve <= idEleve && idEleve <= buf.tab[buf.nb - 1].idEleve)
        {
            /* Recherche interne */
            infE = 0;          // le premier enregistrement du bloc
            supE = buf.nb - 1; // le dernier enregistrement du bloc
            while (infE <= supE && !trouv)
            {
                *j = (infE + supE) / 2; // l'indice de l'enregistrement du milieu
                if (buf.tab[*j].idEleve == idEleve)
                    trouv = true;
                else
                {
                    if (buf.tab[*j].idEleve > idEleve)
                        supE = *j - 1;
                    if (buf.tab[*j].idEleve < idEleve)
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
            if (buf.tab[0].idEleve > idEleve)
                supB = *i - 1;
            if (idEleve > buf.tab[buf.nb - 1].idEleve)
                infB = *i + 1;
        }
    }
    if (infB > supB && idEleve < buf.tab[0].idEleve) // le numero recherche est plus petite que
        *j = 0;                                      // tous les numeros qui existent dans le fichier

    if (infB > supB && idEleve > buf.tab[buf.nb - 1].idEleve) // le numero recherche est plus grande que
    {                                                         // tous les numeros qui existent dans le fichier

        if (buf.nb == tailleBlocTOF_sauv) // le dernier bloc est plein
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
/* module d'insertion dans le fichier TOF_sauv */

bool Insertion_TOF_sauv(TOF_sauv *f, Tenreg_TOF_sauv enreg)
{
    //---------------------
    int i = 0, j = 0;
    Buffer_TOF_sauv buff;
    Tenreg_TOF_sauv x;
    bool continu = true;
    //---------------------
    if (entete_TOF_sauv(f, 1) < 0)
        return false;
    //---------------------
    if (entete_TOF_sauv(f, 1) == 0)
    {
        buff.tab[0] = enreg;
        buff.nb = 1;
        EcrireDir_TOF_sauv(f, 0, &buff);
        Aff_entete_TOF_sauv(f, 1, entete_TOF_sauv(f, 1) + 1);
        Aff_entete_TOF_sauv(f, 2, entete_TOF_sauv(f, 2) + 1);
        return true;
    }
    //---------------------
    // On commence par rechercher l'enregistrement pour localiser l'emplacement (i,j)
    // on doit etre inserer l'enregistrement s'il n'existe pas encore dans le fichier
    if (RechDicho_TOF_sauv(f, enreg.idEleve, &i, &j))
        return false;
    // la cle existe deja dans le fichier et on ne peut pas le reinserer

    // la cle n'existe pas dans le fichier, il faut l'inserer a l'emplacement (i,j)

    while (continu && i < entete_TOF_sauv(f, 1))
    {
        LireDir_TOF_sauv(f, i, &buff);
        x = buff.tab[buff.nb - 1]; // sauvegarder le dernier enregistrement du bloc

        /* Decalages intra-bloc */
        for (int k = buff.nb - 1; k > j; k--)
            buff.tab[k] = buff.tab[k - 1];

        buff.tab[j] = enreg;

        if (buff.nb < tailleBlocTOF_sauv) // si le bloc n'est pas plein, on remet x dans permier indice libre du bloc
        {
            buff.nb++;
            if (j == buff.nb - 1) // le nouvel enregistrement est le dernier enregistrement du fichier
                buff.tab[buff.nb - 2] = x;
            else // le nouvel enregistrement est inserer entre deux enregistrements
                buff.tab[buff.nb - 1] = x;
            EcrireDir_TOF_sauv(f, i, &buff);
            continu = false;
        }
        else // si le bloc est plein, x doit etre inserer dans un nouveau bloc i+1 a la position 0
        {
            EcrireDir_TOF_sauv(f, i, &buff);
            i++;
            j = 0;
            enreg = x; // l'enregistrement qui doit etre inserer a l'emplacement (i,0)
        }
    }
    // si on depasse la fin de fichier, on rajoute un nouveau bloc contenant un seul enregistrement
    if (i >= entete_TOF_sauv(f, 1))
    {
        buff.tab[0] = enreg;
        buff.nb = 1;
        EcrireDir_TOF_sauv(f, Alloc_bloc_TOF_sauv(f), &buff);
    }

    Aff_entete_TOF_sauv(f, 2, entete_TOF_sauv(f, 2) + 1);
    // incrementer le champ de l'entete qui contient le nombre d'enregistrements
    return true;
}

//------------------------------------------------------------------------------------------------------------//

bool suppression_TOF_sauv(TOF_sauv *f, int idEleve)
{
    Buffer_TOF_sauv buff;
    int i = 0, j = 0;
    if (RechDicho_TOF_sauv(f, idEleve, &i, &j))
    {
        LireDir_TOF_sauv(f, i, &buff);
        buff.tab[j].supp = true;
        EcrireDir_TOF_sauv(f, i, &buff);
        f->entete.nbSupp++;
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------------------------------------//

void Affichage_TOF_sauv(TOF_sauv *f)
{
    Buffer_TOF_sauv buffer;

    printf("\n\t***************************************\n");
    printf("\t          AFFICHAGE FICHIER              ");
    printf("\n\t***************************************\n");
    for (int i = 0; i < entete_TOF_sauv(f, 1); i++)
    {
        LireDir_TOF_sauv(f, i, &buffer);                  // lire le bloc dans buffer
        printf("\n\tBloc num %d\tNB=%d\n", i, buffer.nb); // Afficher le num du bloc et le nombre d'enr qu'il contient
        for (int j = 0; j < buffer.nb; j++)
        { // Afficher les enregistrements du buffer
            printf("id Eleve : %d\n", buffer.tab[j].idEleve);
        }
        printf("\n\t---------------------------------------\n");
    }
}