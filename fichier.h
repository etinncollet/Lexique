/**
* \file main.c
* \author Etienne Collet Lionel Rajon
* \brief DM d'Algo des arbre
* Université gustave Eiffel
*/
#include "arbre.h"


int nom_fichier(char *origine, char **lexique, char **dico);


void sauvegarde_arbre(Arbre a, FILE * fichier);


int reconstruit_fichier(Arbre *a, FILE * fichier);


int lit_fichier(Arbre *a, FILE *fichier);


int telecharge(Arbre *arbre, char *dictionaire);


int sauvegarde_dico(char *chaine, Arbre *arbre, char *dictionaire);


int sauvegarde_lexique(char *chaine, Arbre *arbre, char *lexique);
