/* inclusion guard */
#ifndef __FICHIERS_H__
#define __FICHIERS_H__

#include "constantes.h"

// Un niveau est stocké sur une seule ligne comme on lit du texte en français :
// 1. de gauche à droite
// 2. de la première ligne à la dernière

char chargerNiveau(char niveau[][NB_BLOCS_HAUTEUR]);

char sauvegarderNiveau(char niveau[][NB_BLOCS_HAUTEUR]);

#endif /* __FICHIERS_H__ */
