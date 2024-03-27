/* inclusion guard */
#ifndef __CONSTANTES_H__
#define __CONSTANTES_H__

#define TAILLE_BLOC         34
#define NB_BLOCS_LARGEUR    12
#define NB_BLOCS_HAUTEUR    12
#define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
#define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR
#define NB_BLOCS_TOTAL      NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR

enum {HAUT, BAS, GAUCHE, DROITE};
enum {VIDE, MUR, CAISSE, OBJECTIF, MARIO, CAISSE_OK};

#endif /* __CONSTANTES_H__ */
