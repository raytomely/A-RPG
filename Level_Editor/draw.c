//Projet Rabidja - SDL 2.0
//Partie2_06Rabidja_LvlEditor
//draw.c

#include "draw.h"


void drawImage(SDL_Texture *image, int x, int y)
{
	SDL_Rect dest;

	/* Règle le rectangle à dessiner selon la taille de l'image source */

	dest.x = x;
	dest.y = y;

	/* Dessine l'image entière sur l'écran aux coordonnées x et y */
    SDL_QueryTexture(image, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(jeu.renderer, image, NULL, &dest);
}


// Blit une image dont les dimensions dépendent d'une variable
void drawImageScaled(SDL_Texture *image, int x, int y, int w, int h)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;

	/* Dessine l'image sur l'écran aux coordonnées x et y */
	SDL_RenderCopy(jeu.renderer, image, NULL, &dest);
}


void drawTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy)
{
    /* Rectangle de destination à dessiner */
	SDL_Rect dest;

	dest.x = destx;
	dest.y = desty;
	dest.w = TILE_SIZE;
	dest.h = TILE_SIZE;

	/* Rectangle source */
	SDL_Rect src;

	src.x = srcx;
	src.y = srcy;
	src.w = TILE_SIZE;
	src.h = TILE_SIZE;

	/* Dessine la tile choisie sur l'écran aux coordonnées x et y */

	SDL_RenderCopy(jeu.renderer, image, &src, &dest);
}

void drawTilePlus(SDL_Texture *image, int destx, int desty, int srcx, int srcy, int w, int h)
{
    /* Rectangle de destination à dessiner */
	SDL_Rect dest;

	dest.x = destx;
	dest.y = desty;
	dest.w = w;
	dest.h = h;

	/* Rectangle source */
	SDL_Rect src;

	src.x = srcx;
	src.y = srcy;
	src.w = w;
	src.h = h;

	/* Dessine la tile choisie sur l'écran aux coordonnées x et y */

	SDL_RenderCopy(jeu.renderer, image, &src, &dest);
}


void drawTileset()
{
    int srcy = (map.tilesetPart) * 6 * 32;

    if (input.layerDrawn == 5)
        drawTilePlus(map.tileSetSpec, 650, 42, 0, srcy, 320, 192);
    else
        drawTilePlus(map.tileSet, 650, 42, 0, srcy, 320, 192);
}


void drawMessageBox()
{
    char text[200];

    /* Enregistre les coordonnées de la souris */
    SDL_GetMouseState(&input.mouseX, &input.mouseY);

    /* On récupère les coordonnées de la souris */
    cursor.x = input.mouseX;
	cursor.y = input.mouseY;

    /* Affiche la boîte de dialogue */
    drawImage(map.messageBox, 300, 180);

    //Affiche le message
    sprintf(text, "%s", jeu.messageBoxText);
    drawString(text, 390, 220, font, 255, 255, 255, 255);

    //Affiche YES / NO
    if (cursor.x > 450 && cursor.x < 490
            && cursor.y > 280 && cursor.y < 310)
    {
        drawString("YES", 450, 280, font, 255, 255, 0, 255);
    }
    else
        drawString("YES", 450, 280, font, 255, 255, 255, 255);

    if (cursor.x > 550 && cursor.x < 590
            && cursor.y > 280 && cursor.y < 310)
    {
        drawString("NO", 550, 280, font, 255, 255, 0, 255);
    }
    else
        drawString("NO", 550, 280, font, 255, 255, 255, 255);


}


void draw(void)
{

    char text[100];
    int i;

    /* Affiche le background aux coordonnées (0,0) */
    drawImage(map.background, 0, 32);

    /* Affiche la map de tiles */
    if(input.layerDrawn == 1)
    {
        //On les affiche dans le bon ordre ;)
        drawMap(2, 1);
        drawMap(1, 0);
        drawMap(3, 1);
    }
    else if(input.layerDrawn == 2)
    {
        //On les affiche dans le bon ordre ;)
        drawMap(2, 0);
        drawMap(1, 1);
        drawMap(3, 1);
    }
    else if(input.layerDrawn == 3)
    {
        //On les affiche dans le bon ordre ;)
        drawMap(2, 1);
        drawMap(1, 1);
        drawMap(3, 0);
    }
    else if(input.layerDrawn == 4)
    {
        //On les affiche dans le bon ordre ;)
        drawMap(2, 0);
        drawMap(1, 0);
        drawMap(3, 0);
    }
    else if(input.layerDrawn == 5)
    {
        //On les affiche dans le bon ordre ;)
        drawMap(2, 0);
        drawMap(1, 0);
        drawMap(3, 0);
        //Puis la couche des collisions
        drawMap(4, 0);
    }


	// On affiche la selection
	if(jeu.selectActivated){
		drawImage(jeu.select_Img, (jeu.selectFirstX * TILE_SIZE) - map.startX, (jeu.selectFirstY * TILE_SIZE) - map.startY);
	}
	// Ou la zone de sélection
	else if(jeu.selectZoneActivated){
		int posX, posY, sizeW, sizeH;
		// En fonction de la selection la plus en haut à gauche
		if(jeu.selectFirstX <= jeu.selectLastX){
			posX = (jeu.selectFirstX * TILE_SIZE) - map.startX;
			sizeW = abs(jeu.selectFirstX - (jeu.selectLastX + 1)) * TILE_SIZE;
		}else{
			posX = (jeu.selectLastX * TILE_SIZE) - map.startX;
			sizeW = abs(jeu.selectLastX - (jeu.selectFirstX + 1)) * TILE_SIZE;
		}
		if(jeu.selectFirstY <= jeu.selectLastY){
			posY = (jeu.selectFirstY * TILE_SIZE) - map.startY;
			sizeH = abs(jeu.selectFirstY - (jeu.selectLastY + 1)) * TILE_SIZE;
		}else{
			posY = (jeu.selectLastY * TILE_SIZE) - map.startY;
			sizeH = abs(jeu.selectLastY - (jeu.selectFirstY + 1)) * TILE_SIZE;
		}
		// On dessine la zone avec la bonne dimension
		drawImageScaled(jeu.selectZone_Img, posX, posY, sizeW, sizeH);
	}


    /* Affiche le fond de l'éditeur aux coordonnées (0,0) */
    drawImage(map.fond, 0, 0);

	// Affiche la Tile sélectionnée
	drawSelectedTile();

    /* Affiche le numero de la layer (couche) affichée */
    if(input.layerDrawn == 5)
    {
        //Dernier jaune
        for(i = 0; i < 3; i++)
        {
            int srcx = (i * 96);
            drawTilePlus(map.onglets, i * 96, 0, srcx, 0, 96, 32);
        }
        drawTilePlus(map.onglets, 3 * 96, 0, 6 * 96, 0, 96, 32);
        drawTilePlus(map.onglets, 4 * 96, 0, 9 * 96, 0, 96, 32);
        sprintf(text, "Lvl %d: Collisions / Tiles speciales", jeu.level);
    }
    else if(input.layerDrawn == 4)
    {
        //Dernier jaune
        for(i = 0; i < 3; i++)
        {
            int srcx = (i * 96);
            drawTilePlus(map.onglets, i * 96, 0, srcx, 0, 96, 32);
        }
        drawTilePlus(map.onglets, 3 * 96, 0, 7 * 96, 0, 96, 32);
        drawTilePlus(map.onglets, 4 * 96, 0, 8 * 96, 0, 96, 32);
        sprintf(text, "Lvl %d: Resultat - Pas de modifs", jeu.level);
    }
    else if(input.layerDrawn == 1)
    {
        int srcx = 96 * 3;
        drawTilePlus(map.onglets, 0, 0, srcx, 0, 96, 32);

        for(i = 0; i < 2; i++)
        {
            srcx = (i * 96) + 96;
            drawTilePlus(map.onglets, i * 96 + 96, 0, srcx, 0, 96, 32);
        }
        drawTilePlus(map.onglets, 3 * 96, 0, 6 * 96, 0, 96, 32);
        drawTilePlus(map.onglets, 4 * 96, 0, 8 * 96, 0, 96, 32);
        sprintf(text, "Lvl %d : Action", jeu.level);
    }
    else if(input.layerDrawn == 2)
    {
        drawTilePlus(map.onglets, 0, 0, 0, 0, 96, 32);
        drawTilePlus(map.onglets, 96, 0, 96 * 4, 0, 96, 32);
        drawTilePlus(map.onglets, 96 * 2, 0, 96 * 2, 0, 96, 32);
        drawTilePlus(map.onglets, 3 * 96, 0, 6 * 96, 0, 96, 32);
        drawTilePlus(map.onglets, 4 * 96, 0, 8 * 96, 0, 96, 32);
        sprintf(text, "Lvl %d: Background (derriere)", jeu.level);
    }
    else if(input.layerDrawn == 3)
    {
        int srcx = 96 * 5;
        drawTilePlus(map.onglets, 96 * 2, 0, srcx, 0, 96, 32);
        for(i = 0; i < 2; i++)
        {
            srcx = (i * 96);
            drawTilePlus(map.onglets, i * 96, 0, srcx, 0, 96, 32);
        }
        drawTilePlus(map.onglets, 3 * 96, 0, 6 * 96, 0, 96, 32);
        drawTilePlus(map.onglets, 4 * 96, 0, 8 * 96, 0, 96, 32);
        sprintf(text, "Lvl %d: Foreground (devant)", jeu.level);
    }


	// Affichage de la grille 32x32
	if(jeu.displayGrille){
		drawImage(jeu.grille32, -32, 32);
	}

	// Affiche la couche
    drawString(text, 10, 40, font, 0, 0, 0, 255);
    drawString(text, 8, 38, font, 255, 255, 255, 255);

    //Affiche le numéro du niveau
    sprintf(text, "Target level: %d", jeu.targetLevel);
    drawString(text, 655, 380, font, 0, 0, 0, 255);

    //Affiche les coordonnées de la souris
    sprintf(text, "Mouse (%d, %d)", cursor.x, cursor.y);
    drawString(text, 655, 492, font, 0, 0, 0, 255);

	//Affiche les coordonnées de la souris depuis le début du niveau, ainsi que les coordonnées de la Tile survolée
	sprintf(text, "(%d, %d - Tile: %d, %d)", cursor.x + map.startX, cursor.y + map.startY, (cursor.x + map.startX)/TILE_SIZE, (cursor.y + map.startY)/TILE_SIZE);
    drawString(text, 655, 515, font, 0, 0, 0, 255);

    //Affiche le numéro du tileset en cours
    sprintf(text, "Tileset number : %d", map.tilesetAffiche);
    drawString(text, 655, 415, font, 0, 0, 0, 255);

    //Affiche le texte pour placer le point de départ
    sprintf(text, "Choose Start Point");
    drawString(text, 655, 450, font, 0, 0, 0, 255);

    //Affiche le tilesetpart
    sprintf(text, "%d", map.tilesetPart);
    drawString(text, 993, 120, font, 0, 0, 0, 255);

	// Affiche le point de départ du niveau
    if(map.beginx - map.startX <= 610)
        drawImage(map.startpoint, map.beginx - map.startX, map.beginy - map.startY);

	// Affichage du message d'information
    if (jeu.displayInformation)
    {
		drawImage(jeu.information_Img, 0, 32);
    }

    //Affiche les messages s'il y en a
    if(jeu.message == 1)
    {
        sprintf(text, "%s", jeu.messageText);

        drawString(text, 660, 336, font, 0, 0, 0, 255);

        jeu.message_timer--;
        if(jeu.message_timer < 0)
        {
            jeu.message_timer = DUREE_MESSAGE;
            jeu.message = 0;
        }

    }

    //Affiche le message pour choisir le début du niveau
    if(jeu.placeBegin == 1 && jeu.message == 0)
    {
        sprintf(text, "Place start and hit +1!");
        drawString(text, 650, 325, font, 0, 0, 0, 255);
    }

    //Affiche le tileset à faire défiler à droite
    drawTileset();

    //Affiche la boite de dialogue, s'il y en a une
    if(jeu.messageBox == 1)
    {
        drawMessageBox();
    }

    //Affiche les variables pour les A-RPG
    drawVariables();


    /* Affiche l'écran */
    SDL_RenderPresent(jeu.renderer);

    /* Delai */
    SDL_Delay(1);
}


SDL_Texture *loadImage(char *name)
{
	/* Charge les images avec SDL Image dans une SDL_Surface */

	SDL_Surface *loadedImage = NULL;
	SDL_Texture *texture = NULL;
    loadedImage = IMG_Load(name);

	if (loadedImage != NULL)
	{
		// Conversion de l'image en texture
		texture = SDL_CreateTextureFromSurface(jeu.renderer, loadedImage);

		// On se débarrasse du pointeur vers une surface
		SDL_FreeSurface(loadedImage);
		loadedImage = NULL;
	}
	else
		printf("L'image n'a pas pu être chargée! SDL_Error :  %s\n", SDL_GetError());

		return texture;
}


void delay(unsigned int frameLimit)
{

    /* Gestion des 60 fps */

    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }

    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}


void drawVariables(void)
{
    char text[100];

    //Affiche les warps (coins de l'écran
    sprintf(text, "%d", jeu.warpUp);
    drawString(text, 85, 565, font, 0, 0, 0, 255);

    sprintf(text, "%d", jeu.warpDown);
    drawString(text, 85, 586, font, 0, 0, 0, 255);

    sprintf(text, "%d", jeu.warpRight);
    drawString(text, 85, 607, font, 0, 0, 0, 255);

    sprintf(text, "%d", jeu.warpLeft);
    drawString(text, 85, 626, font, 0, 0, 0, 255);

    //Warps Speciales
    sprintf(text, "%d", jeu.afficheWarpSP + 1);
    drawString(text, 98, 665, font, 0, 0, 0, 255);
    sprintf(text, "%d", jeu.warpSP[jeu.afficheWarpSP].value);
    drawString(text, 98, 685, font, 0, 0, 0, 255);

    //PNJ
    sprintf(text, "%d", jeu.affichePNJ + 1);
    drawString(text, 313, 548, font, 0, 0, 0, 255);
    sprintf(text, "%d", jeu.pnj[jeu.affichePNJ].type);
    drawString(text, 313, 569, font, 0, 0, 0, 255);
    sprintf(text, "%d", jeu.pnj[jeu.affichePNJ].text);
    drawString(text, 313, 589, font, 0, 0, 0, 255);
    sprintf(text, "%d", jeu.pnj[jeu.affichePNJ].quest);
    drawString(text, 313, 610, font, 0, 0, 0, 255);

    //Chests
    sprintf(text, "%d", jeu.afficheChest + 1);
    drawString(text, 322, 652, font, 0, 0, 0, 255);
    sprintf(text, "%d", jeu.chest[jeu.afficheChest].type);
    drawString(text, 310, 673, font, 0, 0, 0, 255);

    //Loot, weather
    sprintf(text, "%d", jeu.loot);
    drawString(text, 550, 549, font, 0, 0, 0, 255);

    sprintf(text, "%d", jeu.weather);
    drawString(text, 553, 570, font, 0, 0, 0, 255);

    //Cinematiques
    sprintf(text, "%d", jeu.cinematics);
    drawString(text, 550, 612, font, 0, 0, 0, 255);
    sprintf(text, "%d", jeu.cinematics_condition);
    drawString(text, 570, 632, font, 0, 0, 0, 255);

    //Musique
    sprintf(text, "%d", jeu.musicNumber);
    drawString(text, 550, 674, font, 0, 0, 0, 255);

    //Bouton / mécanisme
    sprintf(text, "%d", jeu.afficheButton + 1);
    drawString(text, 817, 549, font, 0, 0, 0, 255);
    sprintf(text, "%d", jeu.button[jeu.afficheButton].type);
    drawString(text, 817, 570, font, 0, 0, 0, 255);

    //Traps / pièges
    sprintf(text, "%d", jeu.afficheTrap + 1);
    drawString(text, 800, 612, font, 0, 0, 0, 255);
    sprintf(text, "%d", jeu.trap[jeu.afficheTrap].type);
    drawString(text, 800, 633, font, 0, 0, 0, 255);

}

