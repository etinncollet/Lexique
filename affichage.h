/**
* \file main.c
* \author Etienne Collet Lionel Rajon
* \brief DM d'Algo des arbre
* Université gustave Eiffel
*/
#include "fichier.h"


void affiche_aide_option(FILE *sortie);


void affiche_err(int i);


void efface_menu(int x, int y);


void affiche_menu();


int dans_menu();


void ouverture_fichier();


int affiche_graphique();


int sauv_lexi_graphique();


int sauv_dico_graphique();


int ouvre_fichier();


void affiche_aide_menu(FILE *sortie);


int recherche_mot(char *mots, char *fichier, Arbre *a);


int recherche_graphique();
