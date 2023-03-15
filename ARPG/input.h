
#ifndef INPUT_H
#define INPUT_H

#include <SDL/SDL.h>

//Structures
typedef struct { int left, right, up, down, attack, run, enter, magie; }Button;

//Constructeur
void input_init(void);

//Accesseur
Button input_getButton(void);

//Mutateur
void input_setButton(int bouton, int etat);

//Fonctions
void input_gestionInputs(SDL_Surface *surface, int *main_loop);
void input_getInput(SDL_Surface *surface, int *main_loop);

#endif
