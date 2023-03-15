//Projet Rabidja - SDL 2.0
//Partie2_06Rabidja_LvlEditor
//structs.h


#define _CRT_SECURE_NO_WARNINGS /*Pour �viter les warnings d�s � l'ins�curit� de la
                                  fonction sprintf lors de la compilation avec l'option c++ */


#ifndef DEF_STRUCTS
#define DEF_STRUCTS

#include "defs.h"

/* Structures qui seront utilis�es pour g�rer le jeu */

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


/* Structure pour g�rer l'input (clavier puis joystick) */

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


/* Structure pour g�rer le niveau (� compl�ter plus tard) */

typedef struct Gestion
{

    SDL_Window *screen;
	SDL_Renderer *renderer;

	// Gestion de la grille
	SDL_Texture *grille32;
	int displayGrille;

	// Information sur les fonctionnalit�s
	SDL_Texture *information_Img;
	int displayInformation;

	int level;
	int targetLevel;
	int placeBegin;

	int message, message_timer; //Vaut 1 s'il y a un message � afficher
	char messageText[200];

	//Boite de dialogue
	int messageBox, messageBoxResult, doMessageBoxAction, messageBoxAction;
	char messageBoxText[200];

	// Gestion de la s�lection
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


/* Structure pour g�rer la map � afficher (� compl�ter plus tard) */

typedef struct Map
{

	SDL_Texture *background, *tileSet, *tileSetTransparent, *tileSetSpec, *fond, *startpoint, *onglets, *messageBox;

    //Num�ro du tileset � utiliser
	int tilesetAffiche;

	//Numero de la partie du tileset � afficher � droite
	int tilesetPart;

	/* Coordonn�es de d�part du h�ros, lorsqu'il commence le niveau */
	int beginx, beginy;

	/* Coordonn�es de d�but, lorsqu'on doit dessiner la map */
	int startX, startY;

	/* Coordonn�es max de fin de la map */
	int maxX, maxY;

	/* Tableau � double dimension repr�sentant la map de tiles */
	int tileAction[MAX_MAP_Y][MAX_MAP_X];

	//Deuxi�me couche de tiles
    int tileBackground[MAX_MAP_Y][MAX_MAP_X];

    //Deuxi�me couche de tiles
    int tileForeground[MAX_MAP_Y][MAX_MAP_X];

    //Couche de tiles pour les collisions
    int tileCollisions[MAX_MAP_Y][MAX_MAP_X];

} Map;


typedef struct Cursor
{
	int x, y, tileID;
} Cursor;

#endif




