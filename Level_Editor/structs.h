//Projet Rabidja - SDL 2.0
//Partie2_06Rabidja_LvlEditor
//structs.h


#define _CRT_SECURE_NO_WARNINGS /*Pour éviter les warnings dûs à l'insécurité de la
                                  fonction sprintf lors de la compilation avec l'option c++ */


#ifndef DEF_STRUCTS
#define DEF_STRUCTS

#include "defs.h"

/* Structures qui seront utilisées pour gérer le jeu */

/* Structure pour les A-RPGs */
typedef struct PNJ
{
	int type, text, quest;

} PNJ;


typedef struct CHEST
{
	int type;

} CHEST;


typedef struct WARPSPE
{
	int value;

} WARPSPE;


typedef struct BUTTON
{
	int type;

} BUTTON;


typedef struct TRAP
{
	int type;

} TRAP;


/* Structure pour gérer l'input (clavier puis joystick) */

typedef struct Input
{
	int left, right, up, down, add, remove;
	int previous, next, load, save, copy, reinit;
	int copyMap, pasteMap;
	int mouseX, mouseY;
	int leveldown, levelup;
	int changeLevel;
	int layerDrawn, changeLayer;
	int Tactileleft, Tactileright, Tactileup, Tactiledown;

	// Ajout/Suppression de lignes/colonnes
	int addColumn, deleteColumn, addRow, deleteRow, fillWith;

	// Cestion du Copy/Paste
	int shortcutCopy, shortcutPaste;
	int ctrl;

} Input;


/* Structure pour gérer le niveau (à compléter plus tard) */

typedef struct Gestion
{

    SDL_Window *screen;
	SDL_Renderer *renderer;

	// Gestion de la grille
	SDL_Texture *grille32;
	int displayGrille;

	// Information sur les fonctionnalités
	SDL_Texture *information_Img;
	int displayInformation;

	int level;
	int targetLevel;
	int placeBegin;

	int message, message_timer; //Vaut 1 s'il y a un message à afficher
	char messageText[200];

	//Boite de dialogue
	int messageBox, messageBoxResult, doMessageBoxAction, messageBoxAction;
	char messageBoxText[200];

	// Gestion de la sélection
	SDL_Texture *select_Img;
	SDL_Texture *selectZone_Img;
	int selectActivated, selectZoneActivated;
	int selectFirstX, selectFirstY, selectLastX, selectLastY;
	int zoneMemFromX, zoneMemFromY, zoneMemToX, zoneMemToY;
	int zoneMemFromX_CP, zoneMemFromY_CP, zoneMemToX_CP, zoneMemToY_CP;
	int selectCopyTab[MAX_MAP_Y][MAX_MAP_X];

	//Gestion A-RPG
	int afficheWarpSP, affichePNJ, afficheChest, afficheButton, afficheTrap;

	//Nouvelles variables pour les A-RPG
	int warpUp, warpDown, warpLeft, warpRight;
	WARPSPE warpSP[10];
	PNJ pnj[20];
	CHEST chest[20];
	int loot, weather;
	int cinematics, cinematics_condition;
	int musicNumber;
	BUTTON button[10];
	TRAP trap[10];

} Gestion;


/* Structure pour gérer la map à afficher (à compléter plus tard) */

typedef struct Map
{

	SDL_Texture *background, *tileSet, *tileSetTransparent, *tileSetSpec, *fond, *startpoint, *onglets, *messageBox;

    //Numéro du tileset à utiliser
	int tilesetAffiche;

	//Numero de la partie du tileset à afficher à droite
	int tilesetPart;

	/* Coordonnées de départ du héros, lorsqu'il commence le niveau */
	int beginx, beginy;

	/* Coordonnées de début, lorsqu'on doit dessiner la map */
	int startX, startY;

	/* Coordonnées max de fin de la map */
	int maxX, maxY;

	/* Tableau à double dimension représentant la map de tiles */
	int tileAction[MAX_MAP_Y][MAX_MAP_X];

	//Deuxième couche de tiles
    int tileBackground[MAX_MAP_Y][MAX_MAP_X];

    //Deuxième couche de tiles
    int tileForeground[MAX_MAP_Y][MAX_MAP_X];

    //Couche de tiles pour les collisions
    int tileCollisions[MAX_MAP_Y][MAX_MAP_X];

} Map;


typedef struct Cursor
{
	int x, y, tileID;
} Cursor;

#endif




