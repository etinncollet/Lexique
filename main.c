/**
* \file main.c
* \author Etienne Collet Lionel Rajon
* \brief DM d'Algo des arbre
* Université gustave Eiffel
*/
#include "main.h"


/**
* verifie les options placées après l'executable\n
* renvoie entre 1 et 5 si les option son bonne et que le fichier existe sinon 0
**/
int verif_option(int argc, char **argv){
    int i;
    FILE *fichier;
    char option[5][4] = {"-l", "-s", "-r", "-S", "-h"};
    for(i = 0; i < 5; i++){
        if(argv[1][0] == option[i][0] && argv[1][1] == option[i][1] && argv[1][2] == option[i][2]){
            if((i + 1) == 5){
                affiche_aide_option(stderr);
                return 0;
            }
            if(argc < 3){
                affiche_err(1);
                return 0;
            }
            if(i == 2){
                if(argc < 4){
                    affiche_err(1);
                    return 0;
                }
                fichier = fopen(argv[3], "r");
                if(fichier == NULL){
                    fprintf(stderr, "\nLe fichier en argument: '%s' n'est pas dans le repertoire\n", argv[3]);
                    return 0;
                }
                fclose(fichier);
                return i + 1;

            }
            if(argc >= 4){
                affiche_err(0);
                return 0;
            }
            fichier = fopen(argv[2], "r");
            if(fichier == NULL){
                fprintf(stderr, "\nLe fichier en argument: '%s' n'est pas dans le repertoire\n\n", argv[2]);
                return 0;
            }
            fclose(fichier);
            return i + 1;
        }
    }
    fprintf(stderr, "\nL'option '%s' n'existe pas\n\t", argv[1]);
    fprintf(stderr, "Utiliser l'option -h pour avoir plus de precision\n\n");
    return 0;
}


/**
* fait l'option -l\n
* prend en parametre le nom du fichier et l'adresse d'un pointeur sur un arbre lexical
* renvoie 0 en cas d'erreur sinon 1
*/
int affiche_lexique(char *chaine, Arbre *arbre){
    char mots_aff[514];
    FILE *regarde;
    regarde = fopen(chaine, "r");
    if(!lit_fichier(arbre, regarde)){
        return 0;
    }
    fclose(regarde);
    fprintf(stderr, "voila les mots qui sont dans le fichier '%s' :\n\n", chaine);
    ressort_mot((*arbre), mots_aff, 0, stderr);
    return 1;
}


/**
* Gère l'interface graphique
*/
int menu(){
    int tst;
    while(1){
        if((tst = dans_menu()) == 7 || tst == -1){
            break;
        }else{
            switch(tst){
            case 1:
                if(!affiche_graphique()){
                    return 0;
                }
                break;
            case 2:
                if(!sauv_lexi_graphique()){
                    return 0;
                }
                break;
            case 3:
                if(!recherche_graphique()){
                    return 0;
                }
                break;
            case 4:
                if(!sauv_dico_graphique()){
                    return 0;
                }
                break;
            case 5:
                if(!ouvre_fichier()){
                    return 0;
                }
                break;
            case 6:
                affiche_aide_menu(stderr);
                break;
            default:
                break;
            }
        }
    }
    return 0;
}


/**
* Gère l'executable quand il a des arguments\n
* Renvoie 0 en cas d'erreur sinon 1
*/
int avec_option(char **chaine, int nbr, Arbre arbre){
    int tst;
    char *dictionaire = NULL, *lexique = NULL;
    tst = verif_option(nbr, chaine);
    if(tst == 0){
        return 0;
    }else{
        if(tst == 3){
            nom_fichier(chaine[3], &lexique, &dictionaire);
        }else{
            nom_fichier(chaine[2], &lexique, &dictionaire);
        }
        if(tst != 4){
            if(!telecharge(&arbre, dictionaire)){
                return 0;
            }
        }else{
            if(!sauvegarde_dico(chaine[2], &arbre, dictionaire)){
                return 0;
            }
        }
    }
    if(tst == 1){
        if(!affiche_lexique(chaine[2], &arbre)){
            return 0;
        }
        fprintf(stderr, "\n");
    }else if(tst == 2){
        if(!sauvegarde_lexique(chaine[2], &arbre, lexique)){
            return 0;
        }
    }else if(tst == 3){
        if(!recherche_mot(chaine[2], chaine[3], &arbre)){
            return 0;
        }
    }
    libere_lexique(arbre);
    free(dictionaire);
    free(lexique);
    arbre = NULL;
    return 1;
}


/**main du programme*/
int main(int argc, char **argv){
    Arbre arbre = NULL;

    if(argc != 1){
        if(!avec_option(argv, argc, arbre)){
            libere_lexique(arbre);
            return 0;
        }
    }else{
        menu();
    }
	return 0;
}
