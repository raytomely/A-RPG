//Projet Rabidja - SDL 2.0
//Partie2_06Rabidja_LvlEditor
//map.c

#include "map.h"


void loadMap(char *name)
{
    int x, y;
    FILE *fp;

    fp = fopen(name, "rb");

    /* Si on ne peut pas ouvrir le fichier, on quitte */
    if (fp == NULL)
    {
        printf("Failed to open map %s\n", name);
        exit(1);
    }

    /* Lit les données du fichier dans la map */

	/* Lit les coordonnées de début du joueur */
	fscanf(fp, "%d", &map.beginx);
	fscanf(fp, "%d", &map.beginy);

	/* Read the number of the tileset */
	fscanf(fp, "%d", &map.tilesetAffiche);


    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            /* On lit le numéro de la tile et on le copie dans notre tableau */
            fscanf(fp, "%d", &map.tileAction[y][x]);
        }
    }

    //Deuxième couche de tiles
    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            /* On lit le numéro de la tile et on le copie dans notre tableau */
            fscanf(fp, "%d", &map.tileBackground[y][x]);
        }
    }

	//Troisième couche de tiles
	for (y = 0; y < MAX_MAP_Y; y++)
	{
		for (x = 0; x < MAX_MAP_X; x++)
		{
			/* On lit le numéro de la tile et on le copie dans notre tableau */
			fscanf(fp, "%d", &map.tileForeground[y][x]);
		}
	}

	//Couche des collisions
	for (y = 0; y < MAX_MAP_Y; y++)
	{
		for (x = 0; x < MAX_MAP_X; x++)
		{
			/* On lit le numéro de la tile et on le copie dans notre tableau */
			fscanf(fp, "%d", &map.tileCollisions[y][x]);
		}
	}

	//On charge les variables supplémentaires
	fscanf(fp, "%d", &jeu.warpUp);
	fscanf(fp, "%d", &jeu.warpDown);
	fscanf(fp, "%d", &jeu.warpLeft);
	fscanf(fp, "%d", &jeu.warpRight);

	for (x = 0; x < 10; x++)
    {
        fscanf(fp, "%d", &jeu.warpSP[x].value);
    }
    for (x = 0; x < 20; x++)
    {
        fscanf(fp, "%d", &jeu.pnj[x].type);
        fscanf(fp, "%d", &jeu.pnj[x].text);
        fscanf(fp, "%d", &jeu.pnj[x].quest);
    }
    for (x = 0; x < 20; x++)
    {
        fscanf(fp, "%d", &jeu.chest[x].type);
    }
    fscanf(fp, "%d", &jeu.loot);
    fscanf(fp, "%d", &jeu.weather);
    fscanf(fp, "%d", &jeu.cinematics);
    fscanf(fp, "%d", &jeu.cinematics_condition);
    fscanf(fp, "%d", &jeu.musicNumber);
	for (x = 0; x < 10; x++)
    {
        fscanf(fp, "%d", &jeu.button[x].type);
    }
    for (x = 0; x < 10; x++)
    {
        fscanf(fp, "%d", &jeu.trap[x].type);
    }


    /* On change ces coordonnées pour qu'on puisse scroller et éditer la map
	au maximum */

	map.maxX = MAX_MAP_X * TILE_SIZE;
	map.maxY = MAX_MAP_Y * TILE_SIZE;


	/* Remet à 0 les coordonnées de départ de la map */

	map.startX = map.startY = 0;

    /* Remet à 0 les coordonnées de départ de la map */
    map.startX = map.startY = 0;

    /* Et on referme le fichier */
    fclose(fp);

}


void saveMap(char *name)
{
	int x, y;
	FILE *fp;

	fp = fopen(name, "wb");

	/* Si on ne peut pas charger la map, on quitte */

	if (fp == NULL)
	{
		printf("Failed to open map %s\n", name);

		exit(1);
	}

	/* Sauve les coordonnées du début du niveau */
    fprintf(fp, "%d ", map.beginx);
    fprintf(fp, "%d ", map.beginy);

    /* Sauve le numéro du tileset */
    fprintf(fp, "%d ", map.tilesetAffiche);

    /* Sauvegarde la map : couche 1 */

	for (y=0;y<MAX_MAP_Y;y++)
	{
		for (x=0;x<MAX_MAP_X;x++)
		{
			fprintf(fp, "%d ", map.tileAction[y][x]);
		}

		fprintf(fp, "\n");
	}

	/* Sauvegarde la map : couche 2 */
    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            fprintf(fp, "%d ", map.tileBackground[y][x]);
        }

        fprintf(fp, "\n");
    }

    /* Sauvegarde la map : couche 3 */
    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            fprintf(fp, "%d ", map.tileForeground[y][x]);
        }

        fprintf(fp, "\n");
    }

    /* Sauvegarde la map : couche des collisions */
    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            fprintf(fp, "%d ", map.tileCollisions[y][x]);
        }

        fprintf(fp, "\n");
    }

    //Sauvegarde des variables supplémentaires pour gérer la map
    fprintf(fp, "%d ", jeu.warpUp);
    fprintf(fp, "%d ", jeu.warpDown);
    fprintf(fp, "%d ", jeu.warpLeft);
    fprintf(fp, "%d ", jeu.warpRight);

    for (x = 0; x < 10; x++)
    {
        fprintf(fp, "%d ", jeu.warpSP[x].value);
    }

    for (x = 0; x < 20; x++)
    {
        fprintf(fp, "%d ", jeu.pnj[x].type);
        fprintf(fp, "%d ", jeu.pnj[x].text);
        fprintf(fp, "%d ", jeu.pnj[x].quest);
    }

    for (x = 0; x < 20; x++)
    {
        fprintf(fp, "%d ", jeu.chest[x].type);
    }

	fprintf(fp, "%d ", jeu.loot);
	fprintf(fp, "%d ", jeu.weather);
	fprintf(fp, "%d ", jeu.cinematics);
	fprintf(fp, "%d ", jeu.cinematics_condition);
	fprintf(fp, "%d ", jeu.musicNumber);

    for (x = 0; x < 10; x++)
    {
        fprintf(fp, "%d ", jeu.button[x].type);
    }

    for (x = 0; x < 10; x++)
    {
        fprintf(fp, "%d ", jeu.trap[x].type);
    }

	// On referme le fichier
	fclose(fp);
}


void reinitMap()
{
	int x, y;

    /* On réinitialise les coordonnées du début du niveau */
    map.beginx = 0;
    map.beginy = 0;

    /* On réinitialise le numéro du tileset */
    map.tilesetAffiche = 1;


    /* Remplit la map de 0 (3 couches) */
    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            map.tileAction[y][x] = 0;
        }
    }

    //Deuxième couche de tiles
    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            map.tileBackground[y][x] = 0;
        }
    }

	//Troisième couche de tiles
	for (y = 0; y < MAX_MAP_Y; y++)
	{
		for (x = 0; x < MAX_MAP_X; x++)
		{
			map.tileForeground[y][x] = 0;
		}
	}

	//Couche des collisions
	for (y = 0; y < MAX_MAP_Y; y++)
	{
		for (x = 0; x < MAX_MAP_X; x++)
		{
			map.tileCollisions[y][x] = 0;
		}
	}

	jeu.warpUp = jeu.warpDown = jeu.warpLeft = jeu.warpRight = 0;
	for (x = 0; x < 10; x++)
    {
        jeu.warpSP[x].value = 0;
    }
    for (x = 0; x < 20; x++)
    {
        jeu.pnj[x].type = 0;
        jeu.pnj[x].text = 0;
        jeu.pnj[x].quest = 0;
    }
    for (x = 0; x < 20; x++)
    {
        jeu.chest[x].type = 0;
    }
	jeu.loot = jeu.weather = 0;
	jeu.cinematics = jeu.cinematics_condition = 0;
	jeu.musicNumber = 1;
	for (x = 0; x < 10; x++)
    {
        jeu.button[x].type = 0;
    }
    for (x = 0; x < 10; x++)
    {
        jeu.trap[x].type = 0;
    }

}


void drawMap(int layerAffichee, int transparence)
{
    int x, y, mapX, x1, x2, mapY, y1, y2, xsource, ysource, a;

    /* On initialise mapX à la 1ère colonne qu'on doit blitter.
    Celle-ci correspond au x de la map (en pixels) divisés par la taille d'une tile (32)
    pour obtenir la bonne colonne de notre map
    Exemple : si x du début de la map = 1026, on fait 1026 / 32
    et on sait qu'on doit commencer par afficher la 32eme colonne de tiles de notre map */
    mapX = map.startX / TILE_SIZE;

    /* Coordonnées de départ pour l'affichage de la map : permet
    de déterminer à quels coordonnées blitter la 1ère colonne de tiles au pixel près
    (par exemple, si la 1ère colonne n'est visible qu'en partie, on devra commencer à blitter
    hors écran, donc avoir des coordonnées négatives - d'où le -1). */
    x1 = (map.startX % TILE_SIZE) * -1;

    /* Calcul des coordonnées de la fin de la map : jusqu'où doit-on blitter ?
    Logiquement, on doit aller à x1 (départ) + SCREEN_WIDTH (la largeur de l'écran).
    Mais si on a commencé à blitter en dehors de l'écran la première colonne, il
    va falloir rajouter une autre colonne de tiles sinon on va avoir des pixels
    blancs. C'est ce que fait : x1 == 0 ? 0 : TILE_SIZE qu'on pourrait traduire par:
    if(x1 != 0)
        x2 = x1 + SCREEN_WIDTH + TILE_SIZE , mais forcément, c'est plus long ;)*/
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    /* On fait exactement pareil pour calculer y */
    mapY = map.startY / TILE_SIZE;
    y1 = (map.startY % TILE_SIZE) * -1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    //Layer 1 :
    if(layerAffichee == 1)
    {
        /* Dessine la carte en commençant par startX et startY */

        /* On dessine ligne par ligne en commençant par y1 (0) jusqu'à y2 (480)
        A chaque fois, on rajoute TILE_SIZE (donc 32), car on descend d'une ligne
        de tile (qui fait 32 pixels de hauteur) */
        for (y = y1; y < y2; y += TILE_SIZE)
        {
            /* A chaque début de ligne, on réinitialise mapX qui contient la colonne
            (0 au début puisqu'on ne scrolle pas) */
            mapX = map.startX / TILE_SIZE;

            /* A chaque colonne de tile, on dessine la bonne tile en allant
            de x = 0 à x = 640 */
            for (x = x1; x < x2; x += TILE_SIZE)
            {

                /* Suivant le numéro de notre tile, on découpe le tileset (a = le numéro
                de la tile */
                a = map.tileAction[mapY][mapX];

                /* Calcul pour obtenir son y (pour un tileset de 10 tiles
                par ligne, d'où le 10 */
                ysource = a / 10 * TILE_SIZE;
                /* Et son x */
                xsource = a % 10 * TILE_SIZE;

                /* Fonction qui blitte la bonne tile au bon endroit */
                if(transparence == 1)
                    drawTile(map.tileSetTransparent, x, y + 32, xsource, ysource);
                else
                    drawTile(map.tileSet, x, y + 32, xsource, ysource);

                mapX++;
            }

            mapY++;
        }
    }

    mapX = map.startX / TILE_SIZE;
    mapY = map.startY / TILE_SIZE;

    //Layer 2 :
    if(layerAffichee == 2 )
    {
        //Deuxième couche de tiles ;)
        for (y = y1; y < y2; y += TILE_SIZE)
        {
            mapX = map.startX / TILE_SIZE;

            for (x = x1; x < x2; x += TILE_SIZE)
            {
                a = map.tileBackground[mapY][mapX];
                ysource = a / 10 * TILE_SIZE;
                xsource = a % 10 * TILE_SIZE;
                if(transparence == 1)
                    drawTile(map.tileSetTransparent, x, y + 32, xsource, ysource);
                else
                    drawTile(map.tileSet, x, y + 32, xsource, ysource);
                mapX++;
            }
            mapY++;
        }

    }

    //Layer 3 :
    if(layerAffichee == 3)
    {
        //Troisième couche de tiles ;)
        for (y = y1; y < y2; y += TILE_SIZE)
        {
            mapX = map.startX / TILE_SIZE;

            for (x = x1; x < x2; x += TILE_SIZE)
            {
                a = map.tileForeground[mapY][mapX];
                ysource = a / 10 * TILE_SIZE;
                xsource = a % 10 * TILE_SIZE;
                if(transparence == 1)
                    drawTile(map.tileSetTransparent, x, y + 32, xsource, ysource);
                else
                    drawTile(map.tileSet, x, y + 32, xsource, ysource);
                mapX++;
            }
            mapY++;
        }

    }

    //Layer 3 :
    if(layerAffichee == 4)
    {
        //Couche des tiles de collision
        for (y = y1; y < y2; y += TILE_SIZE)
        {
            mapX = map.startX / TILE_SIZE;

            for (x = x1; x < x2; x += TILE_SIZE)
            {
                a = map.tileCollisions[mapY][mapX];
                ysource = a / 10 * TILE_SIZE;
                xsource = a % 10 * TILE_SIZE;
                drawTile(map.tileSetSpec, x, y + 32, xsource, ysource);
                mapX++;
            }
            mapY++;
        }

    }
}


void drawSelectedTile(){

	int xsource, ysource;

	// On affiche la tile sélectionnée
    ysource = cursor.tileID / 10 * TILE_SIZE;
    xsource = cursor.tileID % 10 * TILE_SIZE;

    if(input.layerDrawn == 5)
        drawTile(map.tileSetSpec, 682, 275, xsource, ysource);
    else
        drawTile(map.tileSet, 682, 275, xsource, ysource);
}
