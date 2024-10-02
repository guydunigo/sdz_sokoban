/* inclusion guard */
#ifndef __JEU_H__
#define __JEU_H__

#include "constantes.h"
#include <SDL/SDL.h>

void jouer(SDL_Surface *ecran);

void deplacerJoueur(char carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos,
                    char direction);

char isPlayerStuck(char carte[][NB_BLOCS_HAUTEUR], SDL_Rect *new_pos);

char isCaisseStuck(char carte[][NB_BLOCS_HAUTEUR], SDL_Rect *new_pos);

void deplacerCaisse(char carte[][NB_BLOCS_HAUTEUR], SDL_Rect *old_pos,
                    SDL_Rect *new_pos);

#endif /* __JEU_H__ */
