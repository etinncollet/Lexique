/**
* \file main.c
* \author Etienne Collet Lionel Rajon
* \brief DM d'Algo des arbre
* Université gustave Eiffel
*/
#include "fichier.h"


/**
* copie la chaine origine de taille "taille" dans la chaine "destination"
* en commançant à l'indice "depart" de "destination"
*/
void copie_chaine(char *origine, char *destination, int taille, int depart){
    int i;
    assert(taille > 0);
    assert(depart >= 0);
    for(i = 0; i < taille; i++){
        destination[depart + i] = origine[i];
    }
}


/**
* donne la taille de chaîne en incluant le \0
*/
int taille_chaine(char *chaine){
    int compte;
    assert(chaine != NULL);
    compte = 0;
    while(chaine[compte] != '\0'){
        compte += 1;
    }
    return compte + 1;;
}


/**
* permet de ressortir les trois noms de fichier possible
*/
int nom_fichier(char *origine, char **lexique, char **dico){
    int taille;
    char extention[2][5] = {".LEX", ".DIC"};
    assert(origine != NULL);

    taille = taille_chaine(origine);
    (*dico) = (char *)calloc(taille + 4, sizeof(char));
    (*lexique) = (char *)calloc(taille + 4, sizeof(char));

    if((*dico) == NULL || (*lexique) == NULL){
        fprintf(stderr, "Il y a eu un probleme d'allocation ( fichier.c -> nom_fichier )\n");
        return 0;
    }

    copie_chaine(origine, (*dico), taille, 0);
    copie_chaine(origine, (*lexique), taille, 0);

	copie_chaine(extention[1], (*dico), 4, taille - 1);
    copie_chaine(extention[0], (*lexique), 4, taille - 1);

    return 1;
}


/**
* sauvegarde l'arbre en argument dans le fichier "fichier"
*/
void sauvegarde_arbre(Arbre a, FILE * fichier){
    assert(fichier != NULL);
    if(a != NULL){
        if(a -> lettre == '\0'){
            fprintf(fichier, "\n");
        }else{
            fprintf(fichier, "%c", a -> lettre);
        }
        sauvegarde_arbre(a->freregauche, fichier);
        sauvegarde_arbre(a->fils, fichier);
        sauvegarde_arbre(a->freredroit, fichier);
    }else{
        fprintf(fichier, " ");
    }
}


/**
* prend un fichier.DIC en parametre et reconstruit l'arbre de lexique qu'il represente
*/
int reconstruit_fichier(Arbre *a, FILE * fichier){
    char caractere;
    Arbre nouv = NULL;
    assert(fichier != NULL);
    caractere = fgetc(fichier);
    if(caractere == EOF){
        return 1;
    }
    if(caractere == ' '){
        return 1;
    }
    if(caractere == '\n'){
        caractere = '\0';
    }
    nouv = alloux_lettre( caractere );
    if(nouv == NULL){
        fprintf(stderr, "erreur d'allocation ( fichier.c -> reconstruit_fichier)\n");
        return 0;
    }
    (*a) = nouv;
    return reconstruit_fichier(&((*a) -> freregauche), fichier) &&
            reconstruit_fichier(&((*a) -> fils), fichier) &&
            reconstruit_fichier(&((*a) -> freredroit), fichier);
}


/**
* lit le fichier et rentre chaque mots dans l'arbre lexical
*/
int lit_fichier(Arbre *a, FILE *fichier){
    char caractere, mots[513];
    int i = 0;
    assert(fichier != NULL);
    do{
        caractere = fgetc(fichier);
        if(caractere == '\0' || caractere == ' ' || caractere == '\n' || caractere == EOF || i == 512){
            if(i == 0){
                continue;
            }
            mots[i] = '\0';
            if(!ajoute_mot(a, mots, 0)){
                return 0;
            }
            i = 0;
        }else{
            mots[i] = caractere;
            i += 1;
        }
    }while(caractere != EOF);
    return 1;
}


/**
* verifie si un fichier .DIC existe si oui il construit l'arbre qu'il contient
* renvoie 0 en cas d'erreur sinon 1
*/
int telecharge(Arbre *arbre, char *dictionaire){
    FILE *regarde;
    regarde = fopen(dictionaire, "r");
    if(regarde != NULL){
        if(reconstruit_fichier(arbre, regarde) == 0){
            return 0;
        }
        /*fprintf(stderr, "/existe/\n");*/
        fclose(regarde);
    }
    return 1;
}


/**
* fait l'option -S
* renvoie 0 en cas de'erreur sinon 1
*/
int sauvegarde_dico(char *chaine, Arbre *arbre, char *dictionaire){
    FILE *regarde;
    /*fprintf(stderr, "/-S/\n");*/
    regarde = fopen(chaine, "r");
    if(!lit_fichier(arbre, regarde)){
        return 0;
    }
    fclose(regarde);
    /*affiche_arbre((*arbre));*/
    regarde = fopen(dictionaire, "w");
    if(regarde == NULL){
        fprintf(stderr, "erreur de fichier (main.c -> main)\n");
        return 0;
    }
    sauvegarde_arbre((*arbre), regarde);
    fclose(regarde);
    return 1;
}


/**
* fait l'option -s
* renvoie 0 en cas d'erreur sinon 1
*/
int sauvegarde_lexique(char *chaine, Arbre *arbre, char *lexique){
    char mots_aff[514];
    FILE *regarde;
    /*fprintf(stderr, "/-s/\n");*/

    regarde = fopen(chaine, "r");
    if(!lit_fichier(arbre, regarde)){
        return 0;
    }
    fclose(regarde);
    regarde = fopen(lexique, "w");
    if(regarde == NULL){
        fprintf(stderr, "erreur de fichier (main.c -> main)\n");
        return 0;
    }
    ressort_mot((*arbre), mots_aff, 0, regarde);
    fclose(regarde);
    return 1;
}
