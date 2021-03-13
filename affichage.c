/**
* \file main.c
* \author Etienne Collet Lionel Rajon
* \brief DM d'Algo des arbre
* Université gustave Eiffel
*/
#include "affichage.h"

/**
* donne le nombre de partie du menu
*/
#define NB_OPTION 7

/**
* affiche le man
*/
void affiche_aide_option(FILE *sortie){
    fprintf(sortie, "SYNOPSIS:\n\tLexique [ -options ] [ args ... ]\n\n");
    fprintf(sortie, "DESCRIPTION:\n\tl'objectif est de manipuler des lexique\n\n");
    fprintf(sortie, "OPTIONS:\n\t-l fichier\n\t Affiche tous les mots du fichier dans l'ordre alphabetique\n");
    fprintf(sortie, "\n\t-s fichier\n\tSauvegarde les mots du fichier dans un fichier.LEX\n");
    fprintf(sortie, "\n\t-r Mot fichier\n\tIndique si Mot apparaît dans le fichier\n");
    fprintf(sortie, "\n\t-S fichier\n\tSauvegarde l'arbre dans un fichier.DIC\n\n");
    fprintf(sortie, "Auteur:\n\tEtienne Collet et Lionel Rajon\n");
    fprintf(sortie, "\n\t\t22/02/2021\n");
}

/**
* affiche la documentation dans le menu
*/
void affiche_aide_menu(FILE *sortie){
    fprintf(sortie, "DESCRIPTION:\n\tl'objectif est de manipuler des lexique\n\n");
    fprintf(sortie, "OPTIONS:\n\tafficher un lexique\n\t Affiche tout les mots du fichier dans l'ordre alphabetique\n");
    fprintf(sortie, "\n\tsauvegarder un lexique\n\tSauvegarde les mots du fichier dans un fichier.LEX\n");
    fprintf(sortie, "\n\trechercher un mot\n\tIndique si Mot apparaît dans le fichier\n");
    fprintf(sortie, "\n\tsauvegarder un arbre lexical\n\tSauvegarde l'arbre dans un fichier.DIC\n\n");
    fprintf(sortie, "\n\tQuitter\n\tQuitte le programme\n\n");
    fprintf(sortie, "Auteur:\n\tEtienne Collet et Lionel Rajon\n");
    fprintf(sortie, "\n\t\t22/02/2021\n");

    fprintf(stderr, "appuyer sur une touche pour quitter\n");
    getchar();
    getchar();
}

/**
* affiche qu'il y a trop d'argument si i vaut 0
* sinon affiche qu'il n'y en a pas assez
*/
void affiche_err(int i){
    if(i){
        fprintf(stderr, "\nIl manque des arguments,\n\t");
    }else{
        fprintf(stderr, "\nIl y a trop d'arguments,\n\t");
    }
    fprintf(stderr, "Utiliser l'option -h pour avoir plus de precision\n\n");
}


/**
* affiche le menu avec la zone choisie en surbrillance
* nbr designe l'element selectionné
*/
void affiche_menu() {
    int i;
    char chaine[NB_OPTION][50] = {
    "afficher un lexique",
    "sauvegarder un lexique",
    "rechercher un mot",
    "sauvegarder un arbre lexical",
    "Ouvrir un fichier",
    "Option",
    "Quitter"
    };
    for (i = 0; i < NB_OPTION; i++) {
        fprintf(stderr, "%d -  %s\n", i+1, chaine[i]);
    }
    fprintf(stderr, "entrer le nombre correspondant à l'action que vous voulez faire : ");
}


/**
* permet de manipuler le menu et renvoie lequel des choix est validé
*/
int dans_menu(){
    char nbr;
    int sys;
    while (1) {
        sys=system("clear");
        if (sys==-1)
			return 0;
        affiche_menu();
        if(EOF == scanf("%c", &nbr)){
            return -1;
        }
        if(nbr > '0' && nbr < '8'){
            return nbr - '0';
        }
    }
}


/**
* demande quel fichier ont veux utiliser et le renvoie en parametre
*/
int demande_fichier(char *fichier){
    FILE *regarde;
    int retour;
    retour=scanf("%100s", fichier);
    if (retour==-1){
		return 0;
	}
    regarde = fopen(fichier, "r");
    if(regarde == NULL){
        fprintf(stderr, "Ce fichier n'existe pas dans ce repertoire : %s\n", fichier);
        return 0;
    }
    fclose(regarde);
    return 1;
}


/**
* affiche la liste des mots du lexique
*/
int affiche_graphique(){
    char fichier[100], *dictionaire, *lexique, mots[514];
    Arbre arbre;
    FILE *regarde;
    while(1){
        fprintf(stderr, "Affichage du lexique\nentrer le caractere '.' pour revenir au menu\n");
        fprintf(stderr, "entrer le nom du fichier : ");

        if(!demande_fichier(fichier)){
            continue;
        }

        if(fichier[0] == '.'){
            return 1;
        }

        nom_fichier(fichier, &lexique, &dictionaire);
        if(!telecharge(&arbre, dictionaire)){
                return 0;
        }
        regarde = fopen(fichier, "r");
        if(!lit_fichier(&arbre, regarde)){
            return 0;
        }
        fclose(regarde);
        if(!ressort_mot(arbre, mots, 0, stderr)){
            return 0;
        }
        fprintf(stderr, "appuyer sur une entrer pour revenir au menu\n");
        getchar();
        getchar();
        libere_lexique(arbre);
        free(dictionaire);
        free(lexique);
        break;
    }
    return 1;
}


/**
* Affiche si la sauvegarde du lexique à bien été fait 
*/
int sauv_lexi_graphique(){
    char fichier[100], *dictionaire, *lexique;
    Arbre arbre = NULL;
    while(1){
        fprintf(stderr, "Sauvegarde du lexique\nentrer le caractere '.' pour revenir au menu\n");
        fprintf(stderr, "entrer le nom du fichier : ");
        if(!demande_fichier(fichier)){
            continue;
        }
        if(fichier[0] == '.'){
            return 1;
        }
        nom_fichier(fichier, &lexique, &dictionaire);
        if(!telecharge(&arbre, dictionaire)){
                return 0;
        }
        if(!sauvegarde_lexique(fichier, &arbre, lexique)){
            return 0;
        }
        break;
    }
    fprintf(stderr, "l'operation a reussi\n");
    fprintf(stderr, "appuyer sur une touche pour revenir au menu\n");
    getchar();
    getchar();
    libere_lexique(arbre);
    free(dictionaire);
    free(lexique);
    return 1;
}


/**
* Affiche si la sauvegarde du dictionnaire à bien été fait 
*/
int sauv_dico_graphique(){
    char fichier[100], *dictionaire, *lexique;
    Arbre arbre = NULL;
    while(1){
        fprintf(stderr, "Sauvegarde de l'arbre\nentrer le caractere '.' pour revenir au menu\n");
        fprintf(stderr, "entrer le nom du fichier : ");
        if(!demande_fichier(fichier)){
            continue;
        }
        if(fichier[0] == '.'){
            return 1;
        }
        nom_fichier(fichier, &lexique, &dictionaire);
        if(!telecharge(&arbre, dictionaire)){
                return 0;
        }
        if(!sauvegarde_dico(fichier, &arbre, dictionaire)){
            return 0;
        }
        break;
    }
    fprintf(stderr, "l'operation à reussi\n");
    fprintf(stderr, "appuyer sur une touche pour revenir au menu\n");
    getchar();
    getchar();
    libere_lexique(arbre);
    free(dictionaire);
    free(lexique);
    return 1;
}


/**
* Demande le nom du fichier à ouvrir et affiche si il a bien été ouvert
*/
int ouvre_fichier(){
    char fichier[100], caractere;
    int retour;
    FILE *regarde;
    fprintf(stderr, "entrer le nom du fichier à ouvrir : ");
    retour =scanf("%100s", fichier);
    if ( retour ==-1){
		return 0;
	}
    regarde = fopen(fichier, "r");
    if(regarde == NULL){
        fprintf(stderr, "voulez-vous cree ce fichier (appuyer sur Y pour oui sinon non) : ");
        getchar();
        caractere = getchar();
        if(caractere == 'Y'){
            fprintf(stderr, "le fichier a bien ete cree\n");
            regarde = fopen(fichier, "w");
            fclose(regarde);
        }
        fprintf(stderr, "appuyer sur une touche pour revenir au menu\n");
        getchar();
        getchar();
        return 1;
    }
    fprintf(stderr, "le fichier a bien ete ouvert\n%s\n", fichier);
    fprintf(stderr, "\n===============================\n");
    while(1){
        caractere = fgetc(regarde);
        if(caractere == EOF){
            break;
        }
        fprintf(stderr, "%c", caractere);
    }
    fprintf(stderr, "\n===============================\n");
    fclose(regarde);
    fprintf(stderr, "l'operation a reussi\n");
    fprintf(stderr, "appuyer sur une touche pour revenir au menu\n");
    getchar();
    getchar();
    return 1;
}


/**
* Fait appel à la fonction recherche et affiche si le mot
* est présent dans le fichier
*/
int recherche_mot(char *mots, char *fichier, Arbre *a){
	FILE *regarde = fopen(fichier, "r");
    assert(mots != NULL);
    assert(a != NULL);
    assert(fichier != NULL);

    
    if(!lit_fichier(a, regarde)){
        return 0;
    }
    fclose(regarde);
    if(recherche(*a, mots, 0)){
        fprintf(stderr, "le mot est dans le fichier\n");
    }else{
        fprintf(stderr, "le mot n'est pas dans le fichier\n");
    }
    return 1;
}


/**
* Demande quel mot est recherché et propose d'en chercher un autre 
* lorsque la recherche est terminé
*/
int recherche_graphique(){
    char fichier[100], *dictionaire, *lexique, mots[513];
    int retour;
    Arbre arbre = NULL;
    while(1){
        fprintf(stderr, "rechercher un mot\nentrer le caractere '.' pour revenir au menu\n");
        fprintf(stderr, "entrer le nom du fichier : ");
        if(!demande_fichier(fichier)){
            continue;
        }
        if(fichier[0] == '.'){
            return 1;
        }
        nom_fichier(fichier, &lexique, &dictionaire);
        if(!telecharge(&arbre, dictionaire)){
                return 0;
        }
        fprintf(stderr, "le lexique du fichier a bien ete extrait\n");
        while(1){
            fprintf(stderr, "quel mot cherchez vous : ");
            retour =scanf("%513s", mots);
            if ( retour == -1){
				return 0;
			}
            if(!recherche_mot(mots, fichier, &arbre)){
                return 0;
            }
            fprintf(stderr, "appuyer sur entrer pour chercher un autre mots ou\nune autre touche puis entrer pour revenir au menu\n");
            getchar();
            if(10 == getchar()){
                continue;
            }
            break;
        }
        break;
    }

    libere_lexique(arbre);
    free(dictionaire);
    free(lexique);
    return 1;
}
