//Projet Rabidja - SDL 2.0
//Partie2_06Rabidja_LvlEditor
//input.h

#define _CRT_SECURE_NO_WARNINGS /*Pour éviter les warnings dûs à l'insécurité de la
                                  fonction sprintf lors de la compilation avec l'option c++ */

#ifndef DEF_INPUT
#define DEF_INPUT

#include "structs.h"

/* Prototypes des fonctions utilisées */
extern void loadMap(char *name);
extern void reinitMap();
extern void saveMap(char *name);
extern void loadGame(void);
extern void reloadTileset();

// Ajout/Suppression de lignes/colonnes
extern void addEmptyColumn(int);
extern void deleteColumn(int);
extern void addEmptyRow(int);
extern void deleteRow(int);
extern void fillWith(int, int, int, int);

extern Input input;
extern Map map;
extern Gestion jeu;
extern Cursor cursor;

#endif
