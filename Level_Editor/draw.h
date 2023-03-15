//Projet Rabidja - SDL 2.0
//Partie2_06Rabidja_LvlEditor
//draw.h

#ifndef DEF_DRAW
#define DEF_DRAW

#include "structs.h"

/* Prototypes des fonctions utilisées */
extern void drawMap(int layerAffichee, int transparence);
extern void drawSelectedTile(void);
extern void drawString(char *text, int x, int y, TTF_Font *font, int r, int g, int b, int a);
extern void drawVariables(void);

/* Structures globales */
extern Gestion jeu;
extern Map map;
extern Input input;
extern TTF_Font *font;
extern Cursor cursor;


#endif
