/**
* \file main.c
* \author Etienne Collet Lionel Rajon
* \brief DM d'Algo des arbre
* Université gustave Eiffel
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ncurses.h>

/**
* Structure des noeud de l'arbre lexical
*/
typedef struct lexique {
	char lettre;
	struct lexique * freredroit;
	struct lexique * fils;
	struct lexique * freregauche;
} Elem, *Arbre;


Arbre alloux_lettre(char caractere);


void libere_lexique(Arbre a);


int ajoute_mot(Arbre *a, char *mots, int i);


void affiche_arbre(Arbre a);


int ressort_mot(Arbre a, char mots[], int i, FILE *sortie);


int recherche(Arbre a, char *mot, int i);
