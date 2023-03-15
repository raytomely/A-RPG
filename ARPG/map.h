
#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>


// Structures pour les A-RPGs
typedef struct { int type, text, quest; } PNJ;
typedef struct { int type; } CHEST;
typedef struct { int value; } WARPSPE;
typedef struct { int type; } BUTTON;
typedef struct { int type; } TRAP;
typedef struct { int x, y; } POINT;

//Constructeur
void map_init(void);

//Destructeur
void map_free(void);

//Accesseurs
int map_getBeginX(void);
int map_getBeginY(void);
int map_getStartX(void);
int map_getStartY(void);
int map_getMaxX(void);
int map_getMaxY(void);
int map_getTile(int y, int x);
int map_getLevel(void);
int map_getNombreMonstres(void);
int map_getWarpUp(void);
int map_getWarpDown(void);
int map_getWarpLeft(void);
int map_getWarpRight(void);
int map_getWarpSP(int number);
int map_getWarpDirection(void);
int map_getWarp_coming_from_x(void);
int map_getWarp_coming_from_y(void);

//Mutateurs
void map_setLevel(int valeur);
void map_setStartX(int valeur);
void map_setStartY(int valeur);
void map_setTile(int y, int x, int valeur);
void map_setNombreMonstres(int valeur);
void map_setWarpDirection(int valeur);
void map_setWarp_coming_from_x(int valeur);
void map_setWarp_coming_from_y(int valeur);

//Fonctions
void map_loadMap(char* filename);
void map_drawMap(int layer, SDL_Surface* surface);
void map_changeLevel(void);
void map_testDefilement(void);

#endif
