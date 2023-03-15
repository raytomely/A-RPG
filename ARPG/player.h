

#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>


//Constructeur
void player_init(void);

//Destructeur
void player_free(void);

//Accesseurs
int player_getX(void);
int player_getY(void);
int player_getW(void);
int player_getH(void);
float player_getDirX(void);
float player_getDirY(void);
int player_getOnGround(void);
int player_getLife(void);
int player_getGold(void);
int player_getDirection(void);
int player_getMagic(void);
int player_getNombreExplosions(void);
float player_getMP(void);
float player_getMPmax(void);

//Mutateurs
void player_setX(int valeur);
void player_setY(int valeur);
void player_setW(int valeur);
void player_setH(int valeur);
void player_setDirX(float valeur);
void player_setDirY(float valeur);
void player_setOnGround(int valeur);
void player_setTimerMort(int valeur);
void player_setGold(int valeur);
void player_setCheckpoint(int valeur);
void player_setMagic(int valeur);
void player_setNombreExplosions(int valeur);

//Fonctions
void player_initialize(void);
void player_reinitialize(void);
void player_draw(SDL_Surface* surface);
void player_update(void);
void player_centerScrolling(void);
void player_mapCollision(void);

#endif
