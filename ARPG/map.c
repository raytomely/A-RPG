#include "map.h"
#include "util.h"


//Num�ro du tileset � utiliser
int tilesetAffiche;

/* Coordonn�es de d�part du h�ros, lorsqu'il commence le niveau */
int beginx, beginy;

/* Coordonn�es de d�but, lorsqu'on doit dessiner la map */
int startX, startY;

/* Coordonn�es max de fin de la map */
int maxX, maxY;

/* Tableau � double dimension repr�sentant la map de tiles */
int tile[80][80];

//Deuxi�me couche de tiles
int tile2[80][80];

//Troisi�me couche de tiles
int tile3[80][80];

//Quatri�me couche de tiles pour les collisions
int tile4[80][80];

/* Timer et num�ro du tileset � afficher pour animer la map */
int mapTimer, tileSetNumber;

//Num�ro du niveau en cours
int level;

//Variable pour testDefilement()
int testdefil;

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

//Pour g�rer les warps
int warpDirection;
int warp_coming_from_x;
int warp_coming_from_y;

//Tilesets
SDL_Surface* tileSet1;
SDL_Surface* tileSet1B;

//Nombre max de monstres � l'�cran
int nombreMonstres;

//Police de caract�res
//sf::Font font;

//HUD (Informations affich�es � l'�cran, comme le nombre de coeurs, la magie, etc.)
SDL_Surface* HUD;
SDL_Surface* HUDHearts;
SDL_Surface* HUDMagic;
float HUDtimer;
int HUDDirection;


//******************/
/* Constantes */
//******************/

// Taille de la fen�tre : 800x480 pixels
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

/* Taille maxi de la map : 400 x 150 tiles */
const int MAX_MAP_X = 80;
const int MAX_MAP_Y = 80;

/* Taille d'une tile (32 x 32 pixels) */
const int TILE_SIZE = 32;

/* Constante pour l'animation */
const int TIME_BETWEEN_2_FRAMES = 20;

//Nombre max de monstres g�r�s
const int MONSTRES_MAX = 50;

//Directions
extern const int DOWN;
extern const int UP;
extern const int RIGHT;
extern const int LEFT;


//*************************/
/* VALEURS DES TILES */
//************************/

const int TILE_MONSTRE_DEBUT = 20;
const int TILE_MONSTRE_FIN = 39;


//Constructeur
void map_init(void)
{
    //Chargement des ressources graphiques
    //Chargement des 2 tilesets n�1
    if (!(tileSet1 = IMG_Load("graphics/tileset1.png")))
    {
        // Erreur
        printf("Erreur durant le chargement de l'image du tileset 1.");
    }
    else
        convert_surface_alpha(&tileSet1);

    if (!(tileSet1B = IMG_Load("graphics/tileset1b.png")))
    {
        // Erreur
        printf("Erreur durant le chargement de l'image du tileset 1b.");
    }
    else
        convert_surface_alpha(&tileSet1B);

    //Chargement de la police Gentium
    /*if (!font.loadFromFile("font/GenBasB.ttf"))
    {
    // Erreur
    cout << "Erreur durant le chargement de la police." << endl;
    }

    //Chargement du HUD
    if (!HUDTexture.loadFromFile("graphics/HUD.png"))
    {
    // Erreur
    cout << "Erreur durant le chargement de l'image du HUD." << endl;
    }
    else
    HUD.setTexture(HUDTexture);

    if (!HUDMagicTexture.loadFromFile("graphics/energy.png"))
    {
    // Erreur
    cout << "Erreur durant le chargement de l'image du HUD Magic." << endl;
    }
    else
    HUDMagic.setTexture(HUDMagicTexture);

    if (!HUDHeartsTexture.loadFromFile("graphics/life.png"))
    {
    // Erreur
    cout << "Erreur durant le chargement de l'image du HUD Vies." << endl;
    }
    else
    HUDHearts.setTexture(HUDHeartsTexture);*/


    //Autres variables
    mapTimer = TIME_BETWEEN_2_FRAMES * 3;
    tileSetNumber = 0;
    testdefil = 0;
    level = 1;
    startX = startY = 0;
    warpDirection = warp_coming_from_x = warp_coming_from_y = 0;
    HUDtimer = 3;
    HUDDirection = DOWN;
}


//Destructeur
void map_free(void)
{
    SDL_FreeSurface(tileSet1);
    SDL_FreeSurface(tileSet1B);
}


//Accesseurs
int map_getBeginX(void) { return beginx; }
int map_getBeginY(void) { return beginy; }
int map_getStartX(void) { return startX; }
int map_getStartY(void) { return startY; }
int map_getMaxX(void) { return maxX; }
int map_getMaxY(void) { return maxY; }
int map_getTile(int y, int x) { return tile4[y][x]; }
int map_getLevel(void) { return level; }
int map_getNombreMonstres(void) { return nombreMonstres; }
int map_getWarpUp(void) { return warpUp; }
int map_getWarpDown(void) { return warpDown; }
int map_getWarpLeft(void) { return warpLeft; }
int map_getWarpRight(void) { return warpRight; }
int map_getWarpSP(int number) { return warpSP[number].value; }
int map_getWarpDirection(void) { return warpDirection; }
int map_getWarp_coming_from_x(void) { return warp_coming_from_x; }
int map_getWarp_coming_from_y(void) { return warp_coming_from_y; }


//Mutateurs
void map_setLevel(int valeur) { level = valeur; }
void map_setStartX(int valeur) { startX = valeur; }
void map_setStartY(int valeur) { startY = valeur; }
void map_setTile(int y, int x, int valeur) { tile[y][x] = valeur; }
void map_setNombreMonstres(int valeur) { nombreMonstres = valeur; }
void map_setWarpDirection(int valeur) { warpDirection = valeur; }
void map_setWarp_coming_from_x(int valeur) { warp_coming_from_x = valeur; }
void map_setWarp_coming_from_y(int valeur) { warp_coming_from_y = valeur; }


//Fonctions

void map_changeLevel(void)
{
    char filename[100];
    sprintf(filename,"map/map%d.txt",level);
    map_loadMap(filename);
}


void map_drawMap(int layer, SDL_Surface* surface)
{
    int x, y, mapX, x1, x2, mapY, y1, y2, xsource, ysource, a;
    SDL_Rect image_size, image_pos;

    /* On initialise mapX � la 1�re colonne qu'on doit blitter.
    Celle-ci correspond au x de la map (en pixels) divis�s par la taille d'une tile (32)
    pour obtenir la bonne colonne de notre map
    Exemple : si x du d�but de la map = 1026, on fait 1026 / 32
    et on sait qu'on doit commencer par afficher la 32eme colonne de tiles de notre map */
    mapX = startX / TILE_SIZE;

    /* Coordonn�es de d�part pour l'affichage de la map : permet
    de d�terminer � quels coordonn�es blitter la 1�re colonne de tiles au pixel pr�s
    (par exemple, si la 1�re colonne n'est visible qu'en partie, on devra commencer � blitter
    hors �cran, donc avoir des coordonn�es n�gatives - d'o� le -1). */
    x1 = (startX % TILE_SIZE) * -1;

    /* Calcul des coordonn�es de la fin de la map : jusqu'o� doit-on blitter ?
    Logiquement, on doit aller � x1 (d�part) + SCREEN_WIDTH (la largeur de l'�cran).
    Mais si on a commenc� � blitter en dehors de l'�cran la premi�re colonne, il
    va falloir rajouter une autre colonne de tiles sinon on va avoir des pixels
    blancs. C'est ce que fait : x1 == 0 ? 0 : TILE_SIZE qu'on pourrait traduire par:
    if(x1 != 0)
    x2 = x1 + SCREEN_WIDTH + TILE_SIZE , mais forc�ment, c'est plus long ;)*/
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    /* On fait exactement pareil pour calculer y */
    mapY = startY / TILE_SIZE;
    y1 = (startY % TILE_SIZE) * -1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);


    //On met en place un timer pour animer la map
    if (mapTimer <= 0)
    {
        if (tileSetNumber == 0)
        {
            tileSetNumber = 1;
            mapTimer = TIME_BETWEEN_2_FRAMES * 3;
        }
        else
        {
            tileSetNumber = 0;
            mapTimer = TIME_BETWEEN_2_FRAMES * 3;
        }

    }
    else
    mapTimer--;


    /* Dessine la carte en commen�ant par startX et startY */

    /* On dessine ligne par ligne en commen�ant par y1 (0) jusqu'� y2 (480)
    A chaque fois, on rajoute TILE_SIZE (donc 32), car on descend d'une ligne
    de tile (qui fait 32 pixels de hauteur) */
    if (layer == 1)
    {
        for (y = y1; y < y2; y += TILE_SIZE)
        {
            /* A chaque d�but de ligne, on r�initialise mapX qui contient la colonne
            (0 au d�but puisqu'on ne scrolle pas) */
            mapX = startX / TILE_SIZE;

            /* A chaque colonne de tile, on dessine la bonne tile en allant
            de x = 0 � x = 640 */
            for (x = x1; x < x2; x += TILE_SIZE)
            {
                /* Suivant le num�ro de notre tile, on d�coupe le tileset (a = le num�ro
                de la tile */
                a = tile[mapY][mapX];

                /* Calcul pour obtenir son y (pour un tileset de 10 tiles
                par ligne, d'o� le 10 */
                ysource = a / 10 * TILE_SIZE;
                /* Et son x */
                xsource = a % 10 * TILE_SIZE;

                /* Fonction qui blitte la bonne tile au bon endroit suivant le timer */
                if (tileSetNumber == 0)
                {
                    image_size.x = xsource; image_size.y = ysource;
                    image_size.w = TILE_SIZE; image_size.h = TILE_SIZE;
                    image_pos.x = x; image_pos.y = y;
                    SDL_BlitSurface(tileSet1, &image_size, surface, &image_pos);
                }
                else
                {
                    image_size.x = xsource; image_size.y = ysource;
                    image_size.w = TILE_SIZE; image_size.h = TILE_SIZE;
                    image_pos.x = x; image_pos.y = y;
                    SDL_BlitSurface(tileSet1B, &image_size, surface, &image_pos);
                }

                mapX++;
            }

            mapY++;
        }
    }

    else if (layer == 2)
    {
        //Deuxi�me couche de tiles ;)
        for (y = y1; y < y2; y += TILE_SIZE)
        {
            mapX = startX / TILE_SIZE;

            for (x = x1; x < x2; x += TILE_SIZE)
            {
                /* Suivant le num�ro de notre tile, on d�coupe le tileset (a = le num�ro
                de la tile */
                a = tile2[mapY][mapX];

                /* Calcul pour obtenir son y (pour un tileset de 10 tiles
                par ligne, d'o� le 10 */
                ysource = a / 10 * TILE_SIZE;
                /* Et son x */
                xsource = a % 10 * TILE_SIZE;

                /* Fonction qui blitte la bonne tile au bon endroit suivant le timer */
                if (tileSetNumber == 0)
                {
                    image_size.x = xsource; image_size.y = ysource;
                    image_size.w = TILE_SIZE; image_size.h = TILE_SIZE;
                    image_pos.x = x; image_pos.y = y;
                    SDL_BlitSurface(tileSet1, &image_size, surface, &image_pos);
                }
                else
                {
                    image_size.x = xsource; image_size.y = ysource;
                    image_size.w = TILE_SIZE; image_size.h = TILE_SIZE;
                    image_pos.x = x; image_pos.y = y;
                    SDL_BlitSurface(tileSet1B, &image_size, surface, &image_pos);
                }

                mapX++;
            }

            mapY++;
        }
    }

    else if (layer == 3)
    {
        //Troisi�me couche de tiles ;)
        for (y = y1; y < y2; y += TILE_SIZE)
        {
            mapX = startX / TILE_SIZE;

            for (x = x1; x < x2; x += TILE_SIZE)
            {
                /* Suivant le num�ro de notre tile, on d�coupe le tileset (a = le num�ro
                de la tile */
                a = tile3[mapY][mapX];

                /* Calcul pour obtenir son y (pour un tileset de 10 tiles
                par ligne, d'o� le 10 */
                ysource = a / 10 * TILE_SIZE;
                /* Et son x */
                xsource = a % 10 * TILE_SIZE;

                /* Fonction qui blitte la bonne tile au bon endroit suivant le timer */
                if (tileSetNumber == 0)
                {
                    image_size.x = xsource; image_size.y = ysource;
                    image_size.w = TILE_SIZE; image_size.h = TILE_SIZE;
                    image_pos.x = x; image_pos.y = y;
                    SDL_BlitSurface(tileSet1, &image_size, surface, &image_pos);
                }
                else
                {
                    image_size.x = xsource; image_size.y = ysource;
                    image_size.w = TILE_SIZE; image_size.h = TILE_SIZE;
                    image_pos.x = x; image_pos.y = y;
                    SDL_BlitSurface(tileSet1B, &image_size, surface, &image_pos);
                }

                mapX++;
            }

            mapY++;
        }
    }
}



void map_testDefilement(void)
{
    //Test de d�filement de la map


    //On commence � faire d�filer vers la droite (valeur == 0)
    if (testdefil == 0)
    {
        //Tant que le d�but du blittage de la map est inf�rieur aux coordonn�es
        //en X de la fin de la map (- la largeur de l'�cran pour ne pas afficher
        //du noir), on fait d�filer la map.
        if (startX < maxX - SCREEN_WIDTH)
            //Vous pouvez changer cette valeur pour faire d�filer la map plus ou moins vite
            startX += 2;
        else
            testdefil = 1;
    }
    //Une fois au bout, on fait d�filer vers le bas (valeur == 1)
    else if (testdefil == 1)
    {
        if (startY < maxY - SCREEN_HEIGHT)
            //Vous pouvez changer cette valeur pour faire d�filer la map plus ou moins vite
            startY += 2;
        else
            testdefil = 2;
    }
    //Une fois en bas, on fait d�filer vers la gauche (valeur == 2)
    else if (testdefil == 2)
    {
        if (startX > 0)
            //Vous pouvez changer cette valeur pour faire d�filer la map plus ou moins vite
            startX -= 2;
        else
            testdefil = 3;
    }
    //Puis on remonte au point de d�part (valeur == 3) et on recommence
    else if (testdefil == 3)
    {
        if (startY > 0)
            //Vous pouvez changer cette valeur pour faire d�filer la map plus ou moins vite
            startY -= 2;
        else
            testdefil = 0;
    }
}



void map_loadMap(char* filename)
{
    //On cr�e un flux (stream) pour lire notre fichier
    //x et y nous serviront pour les boucles ci-dessous
    FILE* file;
    int x = 0;
    int y = 0;

    //On r�initialise maxX et maxY qui nous permettront de
    //d�terminer la taille de notre map
    maxX = 0;
    maxY = 0;

    //On cr�e un vecteur en 2 dimensions (un vecteur de vecteurs, quoi)
    //vector < vector < int > > lignes;
    int lignes[500][120];

    //On cr�e des cha�nes de caract�res temporaires
    char char_temp[1], str_temp[10];

    //On ouvre le fichier
    file = fopen(filename, "r");

    //Si on �choue, on fait une erreur
    if (!file)
    {
        printf("Erreur de chargement du fichier.\n");
        exit(1);
    }

    int column_index = 0, row_index = 0, str_index = 0;
    while (fread(char_temp, sizeof(char), 1, file))
    {
        str_temp[str_index] = char_temp[0];
        str_index ++;

        if (char_temp[0] == ' ')
        {
            str_temp[str_index] = '\0';
            str_index = 0;
            if(str_temp[0] != '\0')
                lignes[row_index][column_index] = atoi(str_temp);
            column_index ++;
        }
        else if (char_temp[0] == '\n')
        {
            row_index ++;
            str_index = 0;
            column_index = 0;
        }
    }
    lignes[row_index][column_index] = atoi(str_temp);
    //On ferme le fichier
    fclose(file);

    //On va maintenant remplir les variables de notre classe � l'aide de notre vecteur
    //� 2 dimensions temporaire.
    //On commence par r�cup�rer les 3 premi�res valeurs de la 1�re ligne (0)
    //qui sont les valeurs de d�part du h�ros et du tileset � afficher
    beginx = lignes[0][0];

    beginy = lignes[0][1];

    tilesetAffiche = lignes[0][2];

    //On charge ensuite la premi�re ligne individuellement car elle contient + de donn�es
    //(d�calage de 3 num�ros � cause des 3 pr�c�dents)
    for (x = 3; x < MAX_MAP_X + 3; x++)
    {
        tile[y][x - 3] = lignes[y][x];
    }

    //Puis on charge le reste du tableau de tiles pour la couche 1.
    //On boucle jusqu'� MAX_MAP_Y et MAX_MAP_X, soit les dimensions
    //maxi de la map (400 x 150 tiles, pour rappel)
    for (y = 1; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            //On copie la valeur de notre vecteur temporaire
            //dans notre tableau � deux dimensions
            tile[y][x] = lignes[y][x];

            //On d�tecte si la tile n'est pas vide
            if (tile[y][x] > 0)
            {
                //Si c'est la cas, on augmente la valeur de maxX ou
                //maxY car la map n'est pas encore finie.
                if (x > maxX)
                {
                    maxX = x;
                }

                if (y > maxY)
                {
                    maxY = y;
                }
            }
        }
    }

    //On fait la m�me chose pour la seconde couche de tiles :
    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            tile2[y][x] = lignes[y + MAX_MAP_Y][x];
        }
    }

    //Puis pour la troisi�me :
    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            tile3[y][x] = lignes[y + MAX_MAP_Y * 2][x];
        }
    }

    //Et enfin pour la quatri�me (la couche des collisions
    //et des tiles sp�ciales) :
    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            tile4[y][x] = lignes[y + MAX_MAP_Y * 3][x];
        }
    }



    //On charge les variables suppl�mentaires
    y = MAX_MAP_Y * 4;

    warpUp = lignes[y][0];
    warpDown = lignes[y][1];
    warpLeft = lignes[y][2];
    warpRight = lignes[y][3];

    int i;
    for (i = 0; i < 10; i++)
    {
        warpSP[i].value = lignes[y][i + 4];
    }

    for (i = 0; i < 20; i++)
    {
        pnj[i].type = lignes[y][14 + i * 3];
        pnj[i].text = lignes[y][15 + i * 3];
        pnj[i].quest = lignes[y][16 + i * 3];
    }

    for (i = 0; i < 20; i++)
    {
        chest[i].type = lignes[y][74 + i];
    }

    loot = lignes[y][94];
    weather = lignes[y][95];
    cinematics = lignes[y][96];
    cinematics_condition = lignes[y][97];
    musicNumber = lignes[y][98];

    for (i = 0; i < 10; i++)
    {
        button[i].type = lignes[y][99 + i];
    }

    for (i = 0; i < 10; i++)
    {
        trap[i].type = lignes[y][109 + i];
    }


    //On convertit les dimensions max de notre map en pixels, en ajoutant
    //1 (car on commence � la ligne/colonne 0) et en multipliant par la valeur
    //en pixels d'une tile (32 pixels).
    maxX = (maxX + 1) * TILE_SIZE;
    maxY = (maxY + 1) * TILE_SIZE;
}
