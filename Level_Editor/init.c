//Projet Rabidja - SDL 2.0
//Partie2_06Rabidja_LvlEditor
//init.c

#include "init.h"


void init(char *title)
{
	// Initialise SDL Video
	jeu.screen = SDL_CreateWindow(title,
		                          SDL_WINDOWPOS_CENTERED,
								  SDL_WINDOWPOS_CENTERED,
								  1020, 720,
								  SDL_WINDOW_SHOWN);

	jeu.renderer = SDL_CreateRenderer(jeu.screen, -1, SDL_RENDERER_PRESENTVSYNC);

    if (jeu.screen == NULL || jeu.renderer == NULL)
        {
            printf("Impossible d'initialiser le mode écran à %d x %d: %s\n", 1020,
				                                                    720, SDL_GetError());
            exit(1);
        }

	//Initialisation du chargement des images png avec la SDL 2.0 - Voir les commentaires du chapitre 9
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image n'a pu être initialisée! SDL_image Error: %s\n", IMG_GetError() );
		exit(1);
	}

		/* Initialise SDL_TTF */
	if (TTF_Init() < 0)
	{
		printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());

		exit(1);
	}

	/* Chargement de la police */
	font = loadFont("font/GenBasB.ttf", 22);

	//On commence par le level 1
    jeu.level = 1;
}



void loadGame(void)
{
    //On crée un tableau de 120 caractères pour contenir le nom de notre fichier
    char file[120];

    /* On charge la map */
    sprintf(file, "map/map%d.txt", jeu.level);
    loadMap(file);

    if(file == NULL)
    {
        printf("Unable to load map : %d", jeu.level);
        exit(1);
    }

    /* Si le background est déjà chargé, on ne le recharge pas */
    if (map.background == NULL)
        map.background = loadImage("graphics/background.png");

    //Chargement du fond de l'editeur s'il n'est pas déjà chargé
    if (map.fond == NULL)
        map.fond = loadImage("graphics/editeur.png");

    //Chargement des onglets
    if (map.onglets == NULL)
        map.onglets = loadImage("graphics/onglets.png");

    //Chargement de l'icône indiquant le point de départ du niveau (Rabidja)
    if (map.startpoint == NULL)
        map.startpoint = loadImage("graphics/startpoint.png");

    //Chargement de la messagebox si nécessaire
    if (map.messageBox == NULL)
        map.messageBox = loadImage("graphics/messagebox.png");

	// Chargement de la grille
	if (jeu.grille32 == NULL)
        jeu.grille32 = loadImage("graphics/Grille_32.png");

	// On charge les images de selection
    if (jeu.select_Img == NULL)
    {
        jeu.select_Img = loadImage("graphics/Selection.png");
    }
	if (jeu.selectZone_Img == NULL)
    {
        jeu.selectZone_Img = loadImage("graphics/SelectZone.png");
    }

	//On charge les images de selection
    if (jeu.information_Img == NULL)
    {
        jeu.information_Img = loadImage("graphics/Information.png");
    }

    //On charge le tileset spécial
    //On décharge le tileset précédent et on charge celui de la map, si nécessaire
    if (map.tileSetSpec == NULL)
    {
        map.tileSetSpec = loadImage("graphics/tilesspec.png");
    }

    //On décharge le tileset précédent et on charge celui de la map, si nécessaire
    if (map.tileSet != NULL)
    {
        SDL_DestroyTexture(map.tileSet);
    }

    sprintf(file, "graphics/tileset%d.png", map.tilesetAffiche);
    map.tileSet = loadImage(file);

    //Version transparente pour la surimpression
    if (map.tileSetTransparent != NULL)
    {
        SDL_DestroyTexture(map.tileSetTransparent);
    }

    sprintf(file, "graphics/tileset%dtransp.png", map.tilesetAffiche);
    map.tileSetTransparent = loadImage(file);

    map.tilesetPart = 0;
    jeu.placeBegin = 0;
    //jeu.message = 0;
    jeu.message_timer = DUREE_MESSAGE;
	//sprintf(jeu.messageText, "No message");

	//Variables pour la gestion des A-RPG
	jeu.afficheWarpSP = jeu.affichePNJ = jeu.afficheChest = jeu.afficheButton = jeu.afficheTrap = 0;

	jeu.targetLevel = jeu.level;

}

void reloadTileset()
{
    char file[120];

    //On décharge le tileset précédent et on charge celui de la map, si nécessaire
    if (map.tileSet != NULL)
    {
        SDL_DestroyTexture(map.tileSet);
    }


    sprintf(file, "graphics/tileset%d.png", map.tilesetAffiche);
    map.tileSet = loadImage(file);

    //Version transparente pour la surimpression
    if (map.tileSetTransparent != NULL)
    {
        SDL_DestroyTexture(map.tileSetTransparent);
    }

    sprintf(file, "graphics/tileset%dtransp.png", map.tilesetAffiche);
    map.tileSetTransparent = loadImage(file);

}

void cleanup()
{

    /* Libère l'image du background */

	if (map.background != NULL)
	{
		SDL_DestroyTexture(map.background);
	}

	if (map.fond != NULL)
	{
		SDL_DestroyTexture(map.fond);
	}

	if (map.startpoint != NULL)
	{
		SDL_DestroyTexture(map.startpoint);
	}

	if (map.messageBox != NULL)
	{
		SDL_DestroyTexture(map.messageBox);
	}

	/* Libère l'image du tileset */

	if (map.tileSet != NULL)
	{
		SDL_DestroyTexture(map.tileSet);
	}

	if (map.tileSetTransparent != NULL)
    {
        SDL_DestroyTexture(map.tileSetTransparent);
    }

	if (map.tileSetSpec != NULL)
	{
		SDL_DestroyTexture(map.tileSetSpec);
	}

	if (map.onglets != NULL)
	{
		SDL_DestroyTexture(map.onglets);
	}

	if (jeu.grille32 != NULL){
		SDL_DestroyTexture(jeu.grille32);
	}

	if (jeu.select_Img != NULL)
    {
        SDL_DestroyTexture(jeu.select_Img);
    }
	if (jeu.selectZone_Img != NULL)
    {
        SDL_DestroyTexture(jeu.selectZone_Img);
    }
	if (jeu.information_Img != NULL)
    {
        SDL_DestroyTexture(jeu.information_Img);
    }

	/* Close the font */
    closeFont(font);

    /* Close SDL_TTF */
    TTF_Quit();

	/* Quitte la SDL */
	SDL_Quit();

}


