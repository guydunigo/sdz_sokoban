#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "fichiers.h"

char chargerNiveau(char niveau[][NB_BLOCS_HAUTEUR])
{

    FILE* fichier = fopen("niveaux.lvl", "r");
    if (fichier == NULL)
        return 0;

    char ligneFichier[NB_BLOCS_TOTAL + 1] = {0};
    fgets(ligneFichier, NB_BLOCS_TOTAL + 1, fichier);

    for (int j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
    {
        for (int i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
        {
            switch (ligneFichier[j * NB_BLOCS_HAUTEUR + i])
            {
            case '0':
                niveau[i][j] = 0;
                break;
            case '1':
                niveau[i][j] = 1;
                break;
            case '2':
                niveau[i][j] = 2;
                break;
            case '3':
                niveau[i][j] = 3;
                break;
            case '4':
                niveau[i][j] = 4;
                break;
            }
        }
    }

    fclose(fichier);
    return 1;
}

// All chars + line feed + null
#define LEVEL_STRING_LENGTH NB_BLOCS_TOTAL + 2
char sauvegarderNiveau(char niveau[][NB_BLOCS_HAUTEUR]) {
    FILE *fichier = fopen("niveaux.lvl", "a");
    if (fichier == NULL) {
        return 0;
    }

    char tmp[LEVEL_STRING_LENGTH] = {'0'};

    for (int j = 0; j < NB_BLOCS_HAUTEUR; j++) {
        for (int i = 0; i < NB_BLOCS_LARGEUR ; i++) {
            tmp[j*NB_BLOCS_HAUTEUR+i] = '0' + niveau[i][j] % 10;
        }
    }

    tmp[NB_BLOCS_TOTAL] = '\n';
    fputs(tmp, fichier);

    fclose(fichier);
    return 1;
}
