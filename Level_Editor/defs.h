//Projet Rabidja - SDL 2.0
//Partie2_06Rabidja_LvlEditor
//defs.h

#ifndef DEF_DEFS
#define DEF_DEFS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

/* On inclut les libs supplémentaires */
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h >

/* Taille de la fenêtre / résolution en plein écran */
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

/* Valeur RGB pour la transparence (canal alpha) */
#define TRANS_R 255
#define TRANS_G 0
#define TRANS_B 255

/* Taille maxi de la map : */
#define MAX_MAP_X 80
#define MAX_MAP_Y 80

/* Taille d'une tile (32 x 32 pixels) */
#define TILE_SIZE 32

/* N° de la tile transparente */
#define BLANK_TILE 0

/* MAX_TILES = numéro de la dernière tile */
#define MAX_TILES 330

 //Nombre maximum de levels
 #define LEVEL_MAX   41

 //Nombre max de tilesets
 #define MAX_TILESETS   1

 //Durée des messages
 #define DUREE_MESSAGE   60

 //Action à effectuer après la message box
 #define LOAD 1
 #define SAVE 2
 #define LEVELUP 3
 #define LEVELDOWN 4
 #define RESET 5
 #define PASTE 6
 #define QUIT 7
 #define CHANGELEVEL 8


#endif
