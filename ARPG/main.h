#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>

#include "input.h"
#include "map.h"
#include "player.h"

#include "util.h"


//Fonctions
void update();
void draw(SDL_Surface* surface);


// Taille de la fenêtre : 800x480 pixels
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
