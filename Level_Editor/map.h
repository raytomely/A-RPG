//Projet Rabidja - SDL 2.0
//Partie2_06Rabidja_LvlEditor
//map.h

#define _CRT_SECURE_NO_WARNINGS /* Pour �viter les warnings d�s � l'ins�curit� de la
                                   fonction fopen lors de la compilation avec l'option C++ */

#ifndef DEF_MAP
#define DEF_MAP

#include "structs.h"

/* Prototypes des fonctions utilis�es */
extern void drawImage(SDL_Texture *, int, int);
extern void drawTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy);

extern Gestion jeu;
extern Map map;
extern Cursor cursor;
extern Input input;

#endif