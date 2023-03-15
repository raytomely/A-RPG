//Projet Rabidja - SDL 2.0
//Partie2_06Rabidja_LvlEditor
//main.h

#ifndef DEF_MAIN
#define DEF_MAIN

#include "structs.h"

/* Prototypes des fonctions utilisées */

extern void init(char *);
extern void cleanup(void);
extern void getInput(void);
extern void draw(void);
extern void loadGame(void);
extern void delay(unsigned int frameLimit);

extern void update(void);
extern void updateMessageBox(void);
extern void doMessageBoxAction(void);

/* Déclaration des structures globales utilisées par le jeu */
Input input;
Gestion jeu;
Map map;

Cursor cursor;

/* Déclaration de notre police de caractères */
TTF_Font *font;

#endif
