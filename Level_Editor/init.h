//Projet Rabidja - SDL 2.0
//Partie2_06Rabidja_LvlEditor
//init.h

#define _CRT_SECURE_NO_WARNINGS /*Pour éviter les warnings dûs à l'insécurité de la
                                  fonction sprintf lors de la compilation avec l'option c++ */

#ifndef DEF_INIT
#define DEF_INIT

#include "structs.h"

/* Prototypes des fonctions utilisées */
extern SDL_Texture *loadImage(char *name);
extern void loadMap(char *name);
extern TTF_Font *loadFont(char *, int);
extern void closeFont(TTF_Font *font);

extern Gestion jeu;
extern Map map;
extern TTF_Font *font;

#endif


