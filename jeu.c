#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"
#include "fichiers.h"
#include "jeu.h"

void jouer(SDL_Surface *ecran) {
    SDL_Surface *mario[4] = {NULL};
    SDL_Surface *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL,
                *marioActuel = NULL;
    SDL_Rect position, positionJoueur;
    SDL_Event event;

    int objectifsRestants = 0, i = 0, j = 0;
    char continuer = 1;
    char carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

    // Chargement de sprites.
    mur = IMG_Load("images/mur.jpg");
    caisse = IMG_Load("images/caisse.jpg");
    caisseOK = IMG_Load("images/caisse_ok.jpg");
    objectif = IMG_Load("images/objectif.png");
    mario[BAS] = IMG_Load("images/mario_bas.gif");
    mario[HAUT] = IMG_Load("images/mario_haut.gif");
    mario[GAUCHE] = IMG_Load("images/mario_gauche.gif");
    mario[DROITE] = IMG_Load("images/mario_droite.gif");

    marioActuel = mario[BAS];

    // Chargementdu niveau
    if (!chargerNiveau(carte))
        exit(EXIT_FAILURE);

    // Recherche de la position de Mario au départ
    for (i = 0; i < NB_BLOCS_LARGEUR; i++) {
        for (j = 0; j < NB_BLOCS_HAUTEUR; j++) {
            if (carte[i][j] == MARIO) {
                positionJoueur.x = i;
                positionJoueur.y = j;
                carte[i][j] = VIDE;
            }
        }
    }

    // Activation de la répétition des touches.
    SDL_EnableKeyRepeat(100, 100);

    while (continuer) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_UP:
                        marioActuel = mario[HAUT];
                        deplacerJoueur(carte, &positionJoueur, HAUT);
                        break;
                    case SDLK_DOWN:
                        marioActuel = mario[BAS];
                        deplacerJoueur(carte, &positionJoueur, BAS);
                        break;
                    case SDLK_LEFT:
                        marioActuel = mario[GAUCHE];
                        deplacerJoueur(carte, &positionJoueur, GAUCHE);
                        break;
                    case SDLK_RIGHT:
                        marioActuel = mario[DROITE];
                        deplacerJoueur(carte, &positionJoueur, DROITE);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }

        // Effacement de l'écran.
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

        // Placement des objets à l'écran.
        objectifsRestants = 0;

        for (i = 0; i < NB_BLOCS_LARGEUR; i++) {
            for (j = 0; j < NB_BLOCS_HAUTEUR; j++) {
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch (carte[i][j]) {
                    case MUR:
                        SDL_BlitSurface(mur, NULL, ecran, &position);
                        break;
                    case CAISSE:
                        SDL_BlitSurface(caisse, NULL, ecran, &position);
                        break;
                    case CAISSE_OK:
                        SDL_BlitSurface(caisseOK, NULL, ecran, &position);
                        break;
                    case OBJECTIF:
                        SDL_BlitSurface(objectif, NULL, ecran, &position);
                        objectifsRestants = 1;
                        break;
                }
            }
        }

        // Si on n'a trouvé aucun objectif sur la carte, c'est qu'on a gagné.
        if (!objectifsRestants)
            continuer = 0;

        // On place le joueur à la bonne position.
        position.x = positionJoueur.x * TAILLE_BLOC;
        position.y = positionJoueur.y * TAILLE_BLOC;
        SDL_BlitSurface(marioActuel, NULL, ecran, &position);

        SDL_Flip(ecran);
    }

    // Désactivation de la répétition des touches (remise à 0).
    SDL_EnableKeyRepeat(0, 0);

    // Libération des surfaces chargées
    SDL_FreeSurface(mur);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(caisseOK);
    SDL_FreeSurface(objectif);
    for (i = 0; i < 4; i++)
        SDL_FreeSurface(mario[i]);
}

void deplacerJoueur(char carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, char direction) {
    int x_modifier = 0, y_modifier = 0;
    switch (direction) {
        case HAUT:
            y_modifier = -1;
            break;
        case BAS:
            y_modifier = 1;
            break;
        case GAUCHE:
            x_modifier = -1;
            break;
        case DROITE:
            x_modifier = 1;
    }

    SDL_Rect new_pos, new_box_pos;
    new_pos.x = pos->x+x_modifier;
    new_pos.y = pos->y+y_modifier;
    new_box_pos.x = pos->x+x_modifier*2;
    new_box_pos.y = pos->y+y_modifier*2;

    // Si le joueur dépasse l'écran
    if (isStuck(carte, &new_pos))
        return;
    // Si on pousse une caisse :
    if (carte[new_pos.x][new_pos.y] == CAISSE || carte[new_pos.x][new_pos.y] == CAISSE_OK) {
        if (isStuck(carte, &new_box_pos))
            return;
        else
            deplacerCaisse(carte, &new_pos, &new_box_pos);
    }

    pos->x = new_pos.x;
    pos->y = new_pos.y;
}

char isStuck(char carte[][NB_BLOCS_HAUTEUR], SDL_Rect* new_pos) {
    // Bords de la carte ou mur
    return new_pos->x < 0 || new_pos->x >= NB_BLOCS_LARGEUR - 1
            || new_pos->y < 0 || new_pos->y >= NB_BLOCS_HAUTEUR - 1
            || carte[new_pos->x][new_pos->y] == MUR;
}

void deplacerCaisse(char carte[][NB_BLOCS_HAUTEUR], SDL_Rect *old_pos, SDL_Rect *new_pos) {
    char* old_case = carte[old_pos->x] + old_pos->y;
    char* new_case = carte[new_pos->x] + new_pos->y;

    if (*old_case == CAISSE || *old_case == CAISSE_OK) {
        *new_case = *new_case == OBJECTIF ? CAISSE_OK : CAISSE;
        *old_case = *old_case == CAISSE_OK ? OBJECTIF : VIDE;
    }
}
