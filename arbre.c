/**
* \file main.c
* \author Etienne Collet Lionel Rajon
* \brief DM d'Algo des arbre
* Université gustave Eiffel
*/
#include "arbre.h"

/*$
* alloue un bloc de la structure Elem
* initialise les pointeurs a null et la lettre avec l'argument
* renvoie l'adresse de la structure si tout c'est bien passer sinon Null
*/
Arbre alloux_lettre(char caractere){
	Arbre nouv = malloc(sizeof(Elem));
	if(NULL != nouv){
		nouv -> lettre = caractere;
		nouv -> freredroit = NULL;
		nouv -> fils = NULL;
		nouv -> freregauche = NULL;
	}
	return nouv;
}


/**
* libere tout l'arbre qui représente un lexique passé en parametre
*/
void libere_lexique(Arbre a){
	if(NULL != a){
		libere_lexique(a -> freregauche);
		libere_lexique(a -> fils);
		libere_lexique(a -> freredroit);
		free(a);
	}
}


/**
* fonction qui permet d'ajouter un mot
*/
int ajoute_mot(Arbre *a, char *mots, int i){
    Arbre tst, tmp;
    assert(mots != NULL);
    if(NULL == (*a)){
        if(mots[i] != '\0'){
            if((tst = alloux_lettre(mots[i])) == NULL){
                return 0;
            }
            (*a) = tst;
            return ajoute_mot( &((*a) -> fils), mots, i + 1);
        }
        if((tst = alloux_lettre(mots[i])) == NULL){
            return 0;
        }
        (*a) = tst;
        return 1;
    }

    if(mots[i] == '\0'){
        if((*a)->lettre == '\0'){
            return 1;
        }
        tmp = (*a);
        if((tst = alloux_lettre(mots[i])) == NULL){
            return 0;
        }
        (*a) = tst;
        tst -> freredroit = tmp;
        return 1;
    }

    if((*a)->lettre == '\0'){
        return ajoute_mot( &( (*a) -> freredroit), mots, i);
    }

    if(mots[i] == ((*a)->lettre)){
        return ajoute_mot( &( (*a) -> fils), mots, i + 1);
    }else if(mots[i] < ((*a)->lettre)){
        return ajoute_mot( &( (*a) -> freregauche), mots, i);
    }else{
        return ajoute_mot( &( (*a) -> freredroit), mots, i);
    }
}


/**
* affiche dans la sortie d'erreur l'arbre
* dans un parcours en profondeur prefixe
*/
void affiche_arbre(Arbre a){
    if(a != NULL){
        fprintf(stderr, ".%c.", a->lettre);
        affiche_arbre(a->freregauche);
        affiche_arbre(a->fils);
        affiche_arbre(a->freredroit);
    }
}


/**
* ressort les mots present dans un arbre dans l'ordre alphabetique
*/
int ressort_mot(Arbre a, char mots[], int i, FILE *sortie){
    assert(mots != NULL);
    assert(i >= 0);
    assert(sortie != NULL);
    if(a == NULL){
        return 1;
    }
    if(a->lettre == '\0'){
        mots[i] = (a -> lettre);
        fprintf(sortie, "%s\n", mots);
        ressort_mot(a -> freredroit, mots, i, sortie);
    }else{
        ressort_mot(a -> freregauche, mots, i, sortie);
        mots[i] = (a -> lettre);
        ressort_mot(a -> fils, mots, i + 1, sortie);
        ressort_mot(a -> freredroit, mots, i, sortie);
    }
    return 1;
}

/**
* renvoie 1 si le mot est présent dans le lexique sinon renvoie 0
*/
int recherche(Arbre a, char mot[],int i)
{
	assert(mot != NULL);
    assert(i >= 0);
	
    if (NULL == a)
        return 0;
        
    if (mot[i]=='\0' && (a->lettre) =='\0')
			return 1;
        
    if (a->lettre=='\0')
		return recherche(a->freredroit,mot,i);
		
    if (a->lettre == mot[i]){		
		 return recherche(a->fils,mot,i+1);
    }   
    
    if (a->lettre < mot[i])
        return recherche(a->freredroit, mot,i);
    return recherche(a->freregauche, mot,i);
}


