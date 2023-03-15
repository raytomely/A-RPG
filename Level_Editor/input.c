//Projet Rabidja - SDL 2.0
//Partie2_06Rabidja_LvlEditor
//input.c

#include "input.h"


void getInput(void)
{
    SDL_Event event;

    /* Keymapping : gère les appuis sur les touches et les enregistre
    dans la structure input */

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {

        case SDL_QUIT:
            jeu.messageBox = 1;
            sprintf(jeu.messageBoxText, "Do you want to quit?");
            jeu.messageBoxAction = QUIT;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                //case SDLK_ESCAPE:
                //	exit(0);
                //break;

            case SDLK_LEFT:
                input.left = 1;
                break;

            case SDLK_RIGHT:
                input.right = 1;
                break;

            case SDLK_UP:
                input.up = 1;
                break;

            case SDLK_DOWN:
                input.down = 1;
                break;

            /* La touche S sauvegardera */
            case SDLK_s:
                input.save = 1;
                break;

            /* La touche L chargera la map */
            case SDLK_l:
                input.load = 1;
                break;

            /* La touche DEL/Suppr réinitialisera la map */
            case SDLK_DELETE:
                input.reinit = 1;
                break;

            //Choix du niveau
            case SDLK_F1:
                input.changeLayer = 1;
                break;

            case SDLK_F2:
                input.leveldown = 1;
                break;

            case SDLK_F3:
                input.levelup = 1;
                break;


			// Gestion du Copy/Paste
			case SDLK_c:
				if(input.ctrl){
					input.shortcutCopy = 1;
				}
				break;
			case SDLK_v:
				if(input.ctrl){
					input.shortcutPaste = 1;
				}
				break;
			case SDLK_LCTRL:
			case SDLK_RCTRL:
				input.ctrl = 1;
				break;


            default:
                break;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                input.left = 0;
                break;

            case SDLK_RIGHT:
                input.right = 0;
                break;

            case SDLK_UP:
                input.up = 0;
                break;

            case SDLK_DOWN:
                input.down = 0;
                break;

			// Gestion du Copy/Paste
			case SDLK_LCTRL:
			case SDLK_RCTRL:
				input.ctrl = 0;
				input.shortcutCopy = 0;
				input.shortcutPaste = 0;
				break;

            default:
                break;
            }
            break;

        case SDL_FINGERUP:
        {
            input.add = 0;
        }
        break;

        case SDL_FINGERDOWN:
        {
            input.add = 1;
            input.mouseX = event.tfinger.x * 1020;
            input.mouseY = event.tfinger.y * 544;
        }
        break;


        case SDL_MOUSEBUTTONDOWN:
        {
            /* Enregistre les coordonnées de la souris */
            SDL_GetMouseState(&input.mouseX, &input.mouseY);

            switch(event.button.button)
            {
            // Le clic gauche de la souris ajoutera la tile en cours
            case SDL_BUTTON_LEFT:
                input.add = 1;
                break;

            // Le clic central de la souris effacera la tile sélectionnée
            case SDL_BUTTON_MIDDLE:
                input.remove = 1;
                break;

            // Le clic droit de la souris copiera la tile sélectionnée
            case SDL_BUTTON_RIGHT:
                input.copy = 1;
                break;
            }
        }
        break;


        case SDL_MOUSEWHEEL:
            //cas du SDL_BUTTON_WHEELUP
            if(event.button.x > 0)
                input.next = 1;
            //cas du SDL_BUTTON_WHEELDOWN
            else if(event.button.x < 0)
                input.previous = 1;
            break;

        case SDL_MOUSEBUTTONUP:
            switch(event.button.button)
            {
            case SDL_BUTTON_LEFT:
                input.add = 0;
                break;

            case SDL_BUTTON_MIDDLE:
                input.remove = 0;
                break;

            default:
                break;
            }
            break;


        }
    }




}


int buttonPressed(int x, int y, int w, int h)
{
      if (input.mouseX > x && input.mouseX < x+w
            && input.mouseY > y && input.mouseY < y+h)
        return 1;
      else
        return 0;
}


void updateMessageBox(void)
{
    //On réinitialise le résultat pour éviter les faux positifs
    jeu.messageBoxResult = 0;

    /* Enregistre les coordonnées de la souris */
    SDL_GetMouseState(&input.mouseX, &input.mouseY);

    /* On récupère les coordonnées de la souris */
    cursor.x = input.mouseX;
    cursor.y = input.mouseY;

    //Si on clique YES, on renvoie 1 (dans la variable jeu.messageBoxResult,
    //sinon 0 et on quitte la messageBox.
    if (input.add == 1)
    {
        if (cursor.x > 450 && cursor.x < 490
                && cursor.y > 280 && cursor.y < 310)
        {
            jeu.messageBoxResult = 1;
            jeu.messageBox = 0;
            jeu.doMessageBoxAction = 1;
        }
        else if (cursor.x > 550 && cursor.x < 590
                 && cursor.y > 280 && cursor.y < 310)
        {
            jeu.messageBoxResult = 0;
            jeu.messageBox = 0;
            jeu.doMessageBoxAction = 1;
        }
    }

}


void doMessageBoxAction(void)
{
    char file[120];

    switch (jeu.messageBoxAction)
    {

    case LEVELUP:
        if(jeu.messageBoxResult == 1)
        {
            sprintf(file, "map/map%d.txt", jeu.level);
            saveMap(file);

            jeu.message = 1;
            sprintf(jeu.messageText, "Map saved !");
        }
        jeu.level++;
        if (jeu.level > LEVEL_MAX )
            jeu.level = 1;
        loadGame();
        input.layerDrawn = 4;
        jeu.doMessageBoxAction = 0;
        break;


    case LEVELDOWN:
        if(jeu.messageBoxResult == 1)
        {
            sprintf(file, "map/map%d.txt", jeu.level);
            saveMap(file);

            jeu.message = 1;
            sprintf(jeu.messageText, "Map saved !");
        }
        jeu.level--;
        if (jeu.level < 1 )
            jeu.level = LEVEL_MAX;
        loadGame();
        input.layerDrawn = 4;
        jeu.doMessageBoxAction = 0;
        break;

    case CHANGELEVEL:
        if(jeu.messageBoxResult == 1)
        {
            sprintf(file, "map/map%d.txt", jeu.level);
            saveMap(file);

            jeu.message = 1;
            sprintf(jeu.messageText, "Map saved !");
        }
        jeu.level = jeu.targetLevel;
        if (jeu.level < 1 )
            jeu.level = 1;
        if(jeu.level > LEVEL_MAX)
            jeu.level = LEVEL_MAX;
        loadGame();
        input.layerDrawn = 4;
        jeu.doMessageBoxAction = 0;
        break;

    case SAVE:
        if(jeu.messageBoxResult == 1)
        {
            sprintf(file, "map/map%d.txt", jeu.level);
            saveMap(file);

            jeu.message = 1;
            sprintf(jeu.messageText, "Map saved !");
        }
        input.layerDrawn = 4;
        jeu.doMessageBoxAction = 0;
        break;

    case LOAD:
        if(jeu.messageBoxResult == 1)
        {
            sprintf(file, "map/map%d.txt", jeu.level);
            loadMap(file);

            jeu.message = 1;
            sprintf(jeu.messageText, "Map loaded !");
        }
        input.layerDrawn = 4;
        jeu.doMessageBoxAction = 0;
        break;


    case RESET:
        if(jeu.messageBoxResult == 1)
        {
            reinitMap();

            jeu.message = 1;
            sprintf(jeu.messageText, "Map reseted (but not saved) !");
        }
        input.layerDrawn = 4;
        jeu.doMessageBoxAction = 0;
        break;


    case PASTE:
        if(jeu.messageBoxResult == 1)
        {
            sprintf(file, "map/pastebin.txt");
            loadMap(file);

            jeu.message = 1;
            sprintf(jeu.messageText, "Map pasted (but not saved) !");
        }
        input.layerDrawn = 4;
        jeu.doMessageBoxAction = 0;
        break;


    case QUIT:
        if(jeu.messageBoxResult == 1)
        {
            exit(0);
        }
        input.layerDrawn = 4;
        jeu.doMessageBoxAction = 0;
        break;

    }

}


void update(void)
{
    char file[120];
    int x;
    int y;

    /* Enregistre les coordonnées de la souris */
    SDL_GetMouseState(&input.mouseX, &input.mouseY);

    /* On récupère les coordonnées de la souris */
    cursor.x = input.mouseX;
    cursor.y = input.mouseY;

	// Numéro de la Tile sous la souris
	int currentTileX = (map.startX + cursor.x) / TILE_SIZE;
	int currentTileY = ((map.startY + cursor.y) / TILE_SIZE);	// +1 pour les onglets


	// Ajout ou suppression de ligne/colonne
	if(jeu.selectActivated){
		if(input.addColumn){
			addEmptyColumn(jeu.selectFirstX);
			input.addColumn = 0;
			jeu.message = 1;
			sprintf(jeu.messageText, "Column added!");
		}else if(input.deleteColumn){
			deleteColumn(jeu.selectFirstX);
			input.deleteColumn = 0;
			jeu.message = 1;
			sprintf(jeu.messageText, "Column deleted!");
		}else if(input.addRow){
			addEmptyRow(jeu.selectFirstY-1);	// -1 pour les onglets
			input.addRow = 0;
			jeu.message = 1;
			sprintf(jeu.messageText, "Row added!");
		}else if(input.deleteRow){
			deleteRow(jeu.selectFirstY-1);	// -1 pour les onglets
			input.deleteRow = 0;
			jeu.message = 1;
			sprintf(jeu.messageText, "Row deleted!");
		}
	}

	// Remplissage d'une zone
	if(jeu.selectZoneActivated){
		if(input.fillWith){
			if(input.layerDrawn == 4 || input.layerDrawn == 5){
				jeu.message = 1;
				sprintf(jeu.messageText, "Choose a layer first!");
			}else{
				fillWith(jeu.zoneMemFromX, jeu.zoneMemFromY, jeu.zoneMemToX, jeu.zoneMemToY);
				input.fillWith = 0;
				jeu.message = 1;
				sprintf(jeu.messageText, "Area filled!");
			}
		}
	}

	// Gestion du Copy/Paste d'une sélection
	if(input.shortcutCopy){

		// Si une zone est selectionnée, on copie la zone
		if(jeu.selectZoneActivated){

			// Si on ne peut pas coller, on affiche un message d'avertissement
			if(input.layerDrawn == 4  || input.layerDrawn == 5){
				jeu.message = 1;
				sprintf(jeu.messageText, "Choose a layer first!");
			}else{

				// On vide le tableau
				for(x = 0 ; x < MAX_MAP_X ; x++){
					for(y = 0 ; y < MAX_MAP_Y ; y++){
						jeu.selectCopyTab[y][x] = 0;
					}
				}

				if(jeu.selectFirstX <= jeu.selectLastX){
					jeu.zoneMemFromX_CP = jeu.selectFirstX;
					jeu.zoneMemToX_CP = jeu.selectLastX;
				}else{
					jeu.zoneMemFromX_CP = jeu.selectLastX;
					jeu.zoneMemToX_CP = jeu.selectFirstX;
				}
				if(jeu.selectFirstY <= jeu.selectLastY){
					jeu.zoneMemFromY_CP = jeu.selectFirstY - 1;		// -1 à cause des onglets
					jeu.zoneMemToY_CP = jeu.selectLastY - 1;
				}else{
					jeu.zoneMemFromY_CP = jeu.selectLastY - 1;
					jeu.zoneMemToY_CP = jeu.selectFirstY - 1;
				}

				// Taille de la sélection
				int nbTileX = jeu.zoneMemToX_CP - jeu.zoneMemFromX_CP;
				int nbTileY = jeu.zoneMemToY_CP - jeu.zoneMemFromY_CP;

				// On mémorise les Tiles du calque actif
				for(x = 0 ; x <= nbTileX ; x++){
					for(y = 0 ; y <= nbTileY ; y++){
						if ( input.layerDrawn == 1 ){
							jeu.selectCopyTab[y][x] = map.tileAction[jeu.zoneMemFromY_CP + y][jeu.zoneMemFromX_CP + x];
						}
						else if ( input.layerDrawn == 2 ){
							jeu.selectCopyTab[y][x] = map.tileBackground[jeu.zoneMemFromY_CP + y][jeu.zoneMemFromX_CP + x];
						}
						else if ( input.layerDrawn == 3 ){
							jeu.selectCopyTab[y][x] = map.tileForeground[jeu.zoneMemFromY_CP + y][jeu.zoneMemFromX_CP + x];
						}
					}
				}
				jeu.message = 1;
				sprintf(jeu.messageText, "Area copied!");
			}
			input.shortcutCopy = 0;
		}

	}else if(input.shortcutPaste){

		// Si on ne peut pas coller, on affiche un message d'avertissement
		if(input.layerDrawn == 4  || input.layerDrawn == 5){
			jeu.message = 1;
			sprintf(jeu.messageText, "Choose a layer first!");
		}else{

			// Si une Tile est selectionnée
			if(jeu.selectActivated){

				// Taille de la sélection
				int nbTileX = jeu.zoneMemToX_CP - jeu.zoneMemFromX_CP;
				int nbTileY = jeu.zoneMemToY_CP - jeu.zoneMemFromY_CP;

				// On colle la zone copiée
				for(x = 0 ; x <= nbTileX ; x++){
					for(y = 0 ; y <= nbTileY ; y++){

						// En fonction de la couche active
						if ( input.layerDrawn == 1 ){
							map.tileAction[jeu.selectFirstY - 1 + y][jeu.selectFirstX + x] = jeu.selectCopyTab[y][x]; 		// -1 à cause des onglets
						}
						else if ( input.layerDrawn == 2 ){
							map.tileBackground[jeu.selectFirstY - 1 + y][jeu.selectFirstX + x] =jeu.selectCopyTab[y][x];
						}
						else if ( input.layerDrawn == 3 ){
							map.tileForeground[jeu.selectFirstY - 1 + y][jeu.selectFirstX + x] = jeu.selectCopyTab[y][x];
						}
					}
				}
				jeu.message = 1;
				sprintf(jeu.messageText, "Area pasted!");
			}
			input.shortcutPaste = 0;
		}
	}

    /* Gestion de notre scrolling du chapitre précédent */
    if (input.left == 1 || input.Tactileleft == 1)
    {
        map.startX -= TILE_SIZE;

        if (map.startX < 0)
        {
            map.startX = 0;
        }
    }

    else if (input.right == 1 || input.Tactileright == 1)
    {
        map.startX += TILE_SIZE;

        if (map.startX + SCREEN_WIDTH >= map.maxX)
        {
            map.startX = map.maxX - SCREEN_WIDTH;
        }
    }

    if (input.up == 1 || input.Tactileup == 1)
    {
        map.startY -= TILE_SIZE;

        if (map.startY < 0)
        {
            map.startY = 0;
        }
    }

    else if (input.down == 1 || input.Tactiledown == 1)
    {
        map.startY += TILE_SIZE;

        if (map.startY + SCREEN_HEIGHT >= map.maxY)
        {
            map.startY = map.maxY - SCREEN_HEIGHT;
        }
    }

    //Gestion du passage d'une map à l'autre
    if (input.levelup == 1)
    {
        jeu.messageBox = 1;
        sprintf(jeu.messageBoxText, "Do you want to save first?");
        jeu.messageBoxAction = LEVELUP;
        input.levelup = 0;
    }

    if (input.leveldown == 1)
    {
        jeu.messageBox = 1;
        sprintf(jeu.messageBoxText, "Do you want to save first?");
        jeu.messageBoxAction = LEVELDOWN;
        input.leveldown = 0;
    }
    if (input.levelup == 1)
    {
        jeu.messageBox = 1;
        sprintf(jeu.messageBoxText, "Do you want to save first?");
        jeu.messageBoxAction = LEVELUP;
        input.levelup = 0;
    }
    if (input.changeLevel == 1)
    {
        jeu.messageBox = 1;
        sprintf(jeu.messageBoxText, "Do you want to save first?");
        jeu.messageBoxAction = CHANGELEVEL;
        input.changeLevel = 0;
    }

    //On remet à 0 les inputs tactiles
    input.Tactileleft = input.Tactileright = input.Tactileup = input.Tactiledown = 0;

    /* Gestion de la copie de tile :
    on retrouve les coordonnées de la tile pointée par la souris et on remplace
    sa valeur par celle de la tile sélectionnée dans le curseur */

    if (input.add == 1)
    {
		// GESTION DE LA SELECTION
		// Si on presse CTRL et qu'on est dans la Map
		if(input.ctrl && cursor.x <= SCREEN_WIDTH){

			// Si la selection était déjà acitvée ET que le nouvelle selection est différente,
			// on active la zone de selection
			if(jeu.selectActivated == 1 && !(jeu.selectFirstX == currentTileX && jeu.selectFirstY == currentTileY)){

				jeu.selectZoneActivated = 1;
				jeu.selectActivated = 0;

				// On mémorise la zone de selection
				jeu.selectLastX = currentTileX;
				jeu.selectLastY = currentTileY;

				// Début et fin de la sélection
				if(jeu.selectFirstX <= jeu.selectLastX){
					jeu.zoneMemFromX = jeu.selectFirstX;
					jeu.zoneMemToX = jeu.selectLastX;
				}else{
					jeu.zoneMemFromX = jeu.selectLastX;
					jeu.zoneMemToX = jeu.selectFirstX;
				}
				if(jeu.selectFirstY <= jeu.selectLastY){
					jeu.zoneMemFromY = jeu.selectFirstY;		// -1 à cause des onglets
					jeu.zoneMemToY = jeu.selectLastY;
				}else{
					jeu.zoneMemFromY = jeu.selectLastY;
					jeu.zoneMemToY = jeu.selectFirstY;
				}

			}else{

				jeu.selectActivated = 1;
				jeu.selectZoneActivated = 0;

				// On mémorise la selection
				jeu.selectFirstX = currentTileX;
				jeu.selectFirstY = currentTileY;
				jeu.selectLastX = currentTileX;
				jeu.selectLastY = currentTileY;

			}

			input.add = 0;

		}else{

			// Dans la Map
			if(cursor.x < 641 && cursor.y < 544 && !jeu.displayInformation)
			{
				// On désactive la selection si c'est sur la Map (pas les onglets)
				if(cursor.y > TILE_SIZE){
					jeu.selectActivated = 0;
					jeu.selectZoneActivated = 0;
				}

				//Si on doit placer le début du niveau
				if (jeu.placeBegin == 1)
				{
					//Calcul pour obtenir la tile exacte
					map.beginx = ((map.startX + cursor.x) / TILE_SIZE) * TILE_SIZE;
					map.beginy = ((map.startY + cursor.y - 32) / TILE_SIZE) * TILE_SIZE;
				}

				//Sélection de la couche (layer)
				else if (cursor.x > 0 && cursor.x < 94
						 && cursor.y > 0 && cursor.y < 30)
				{
					input.layerDrawn = 1;
				}
				else if (cursor.x > 96 && cursor.x < 190
						 && cursor.y > 0 && cursor.y < 30)
				{
					input.layerDrawn = 2;
				}
				else if (cursor.x > 195 && cursor.x < 287
						 && cursor.y > 0 && cursor.y < 30)
				{
					input.layerDrawn = 3;
				}
				else if (cursor.x > 290 && cursor.x < 383
						 && cursor.y > 0 && cursor.y < 30)
				{
					input.layerDrawn = 4;
				}
				else if (cursor.x > 383 && cursor.x < 476
						 && cursor.y > 0 && cursor.y < 30)
				{
					input.layerDrawn = 5;
				}

				//Défilement de la map Haut / Bas
				else if (cursor.x > 555 && cursor.x < 587
						 && cursor.y > 0 && cursor.y < 32)
				{
					input.Tactileup = 1;
				}
				else if (cursor.x > 608 && cursor.x < 639
						 && cursor.y > 0 && cursor.y < 32)
				{
					input.Tactiledown = 1;
				}

				//Défilement de la map Gauche / Droite
				else if (cursor.x > 0 && cursor.x < 34
						 && cursor.y > 513 && cursor.y < 543)
				{
					input.Tactileleft = 1;
				}
				else if (cursor.x > 608 && cursor.x < 640
						 && cursor.y > 513 && cursor.y < 543)
				{
					input.Tactileright = 1;
				}

				//Sinon on copie
				else if (cursor.y < 512)
				{
					if ( input.layerDrawn == 1 )
						map.tileAction[(map.startY + cursor.y - 32) / TILE_SIZE][(map.startX + cursor.x) / TILE_SIZE] = cursor.tileID;
					else if ( input.layerDrawn == 2 )
						map.tileBackground[(map.startY + cursor.y - 32) / TILE_SIZE][(map.startX + cursor.x) / TILE_SIZE] = cursor.tileID;
					else if ( input.layerDrawn == 3 )
						map.tileForeground[(map.startY + cursor.y - 32) / TILE_SIZE][(map.startX + cursor.x) / TILE_SIZE] = cursor.tileID;
                    else if ( input.layerDrawn == 5 )
						map.tileCollisions[(map.startY + cursor.y - 32) / TILE_SIZE][(map.startX + cursor.x) / TILE_SIZE] = cursor.tileID;
				}
			}


			//Gestion des options à droite de la map
			else
			{
				//Choix d'un tile dans le tileset

				if(cursor.x >= 650 && cursor.x <= 970
						&& cursor.y >= 40 && cursor.y <= 240)
					cursor.tileID = ((cursor.y -42) / TILE_SIZE + ((map.tilesetPart) * 6))
									* 10 + (cursor.x - 650) / TILE_SIZE;

				//Ascenseur tileset
				else if (cursor.x > 983 && cursor.x < 1015
						 && cursor.y > 35 && cursor.y < 76)
				{
					if (map.tilesetPart >= 1)
						map.tilesetPart--;
				}
				else if (cursor.x > 983 && cursor.x < 1015
						 && cursor.y > 198 && cursor.y < 237)
				{
					if (map.tilesetPart < 5)
						map.tilesetPart++;
				}

				//Sélection de levels
				else if (cursor.x > 850 && cursor.x < 866
						 && cursor.y > 375 && cursor.y < 393)
				{
					jeu.targetLevel++;
					if(jeu.targetLevel < 1)
                        jeu.targetLevel = 1;
                    else if(jeu.targetLevel > LEVEL_MAX)
                        jeu.targetLevel = LEVEL_MAX;
				}
				else if (cursor.x > 870 && cursor.x < 888
						 && cursor.y > 375 && cursor.y < 393)
				{
					jeu.targetLevel--;
					if(jeu.targetLevel < 1)
                        jeu.targetLevel = 1;
                    else if(jeu.targetLevel > LEVEL_MAX)
                        jeu.targetLevel = LEVEL_MAX;
				}
				else if (cursor.x > 850 && cursor.x < 866
						 && cursor.y > 395 && cursor.y < 411)
				{
					jeu.targetLevel += 10;
					if(jeu.targetLevel < 1)
                        jeu.targetLevel = 1;
                    else if(jeu.targetLevel > LEVEL_MAX)
                        jeu.targetLevel = LEVEL_MAX;
				}
				else if (cursor.x > 870 && cursor.x < 888
						 && cursor.y > 395 && cursor.y < 411)
				{
					jeu.targetLevel -= 10;
					if(jeu.targetLevel < 1)
                        jeu.targetLevel = 1;
                    else if(jeu.targetLevel > LEVEL_MAX)
                        jeu.targetLevel = LEVEL_MAX;
				}
				else if (cursor.x > 895 && cursor.x < 925
						 && cursor.y > 377 && cursor.y < 408)
				{
					input.changeLevel = 1;
				}


				//Load
				else if (input.mouseX >= 763 && input.mouseX <= 863
						 && input.mouseY >= 289 && input.mouseY <= 321)
				{
					input.load = 1;
				}


				//Reset
				else if (input.mouseX >= 872 && input.mouseX <= 1012
						 && input.mouseY >= 291 && input.mouseY <= 320)
				{
					input.reinit = 1;
				}


				//Save
				else if (input.mouseX >= 764 && input.mouseX <= 863
						 && input.mouseY >= 248 && input.mouseY <= 281)
				{
					input.save = 1;
				}

				//Copy
				else if (input.mouseX >= 873 && input.mouseX <= 938
						 && input.mouseY >= 248 && input.mouseY <= 280)
				{
					input.copyMap = 1;
				}

				//Paste
				else if (input.mouseX >= 946 && input.mouseX <= 1012
						 && input.mouseY >= 248 && input.mouseY <= 280)
				{
					input.pasteMap = 1;
				}

				//Tileset + et -
				else if (input.mouseX >= 895 && input.mouseX <= 925
						 && input.mouseY >= 412 && input.mouseY <= 444)
				{
					map.tilesetAffiche--;
					if(map.tilesetAffiche < 1)
						map.tilesetAffiche = MAX_TILESETS;
					reloadTileset();
				}
				else if (input.mouseX >= 855 && input.mouseX <= 888
						 && input.mouseY >= 412 && input.mouseY <= 444)
				{
					map.tilesetAffiche++;
					if(map.tilesetAffiche > MAX_TILESETS)
						map.tilesetAffiche = 1;
					reloadTileset();
				}
				//Pour placer le début du niveau
				else if (input.mouseX >= 855 && input.mouseX <= 887
						 && input.mouseY >= 449 && input.mouseY <= 480)
				{
					if (jeu.placeBegin == 1)
						jeu.placeBegin = 0;
					else
						jeu.placeBegin = 1;
				}

				// Pour afficher la grille 32x32
				else if (input.mouseX >= 855 && input.mouseX <= 887
						 && input.mouseY >= 485 && input.mouseY <= 516)
				{
					jeu.displayGrille = !jeu.displayGrille;
				}

				// Pour ajouter une colonne
				else if (input.mouseX >= 940 && input.mouseX <= 972
						 && input.mouseY >= 378 && input.mouseY <= 408)
				{
					if(jeu.selectActivated){
						input.addColumn = 1;
					}
				}

				// Pour supprimer une colonne
				else if (input.mouseX >= 979 && input.mouseX <= 1010
						 && input.mouseY >= 378 && input.mouseY <= 408)
				{
					if(jeu.selectActivated){
						input.deleteColumn = 1;
					}
				}

				// Pour ajouter une ligne
				else if (input.mouseX >= 940 && input.mouseX <= 972
						 && input.mouseY >= 414 && input.mouseY <= 444)
				{
					if(jeu.selectActivated){
						input.addRow = 1;
					}
				}

				// Pour supprimer une ligne
				else if (input.mouseX >= 979 && input.mouseX <= 1010
						 && input.mouseY >= 414 && input.mouseY <= 444)
				{
					if(jeu.selectActivated){
						input.deleteRow = 1;
					}
				}

				// Pour remplir une zone avec la Tile active
				else if (input.mouseX >= 940 && input.mouseX <= 972
						 && input.mouseY >= 452 && input.mouseY <= 482)
				{
					if(jeu.selectZoneActivated){
						input.fillWith = 1;
					}
				}

				// Pour afficher/cacher de l'information
				else if (input.mouseX >= 979 && input.mouseX <= 1010
						 && input.mouseY >= 452 && input.mouseY <= 482)
				{
					jeu.displayInformation = !jeu.displayInformation;
				}

				//Gestion des variables pour le A-RPGs en bas

				//Warps
                else if(buttonPressed(130, 568, 20, 20) == 1)
                    jeu.warpUp++;
                else if(buttonPressed(153, 568, 20, 20) == 1)
                    jeu.warpUp--;
                else if(buttonPressed(176, 568, 20, 20) == 1)
                    jeu.warpUp += 10;
                else if(buttonPressed(199, 568, 20, 20) == 1)
                    jeu.warpUp -= 10;

                else if(buttonPressed(130, 590, 20, 20) == 1)
                    jeu.warpDown++;
                else if(buttonPressed(153, 590, 20, 20) == 1)
                    jeu.warpDown--;
                else if(buttonPressed(176, 590, 20, 20) == 1)
                    jeu.warpDown += 10;
                else if(buttonPressed(199, 590, 20, 20) == 1)
                    jeu.warpDown -= 10;

                else if(buttonPressed(130, 611, 20, 20) == 1)
                    jeu.warpRight++;
                else if(buttonPressed(153, 611, 20, 20) == 1)
                    jeu.warpRight--;
                else if(buttonPressed(176, 611, 20, 20) == 1)
                    jeu.warpRight += 10;
                else if(buttonPressed(199, 611, 20, 20) == 1)
                    jeu.warpRight -= 10;

                else if(buttonPressed(130, 631, 20, 20) == 1)
                    jeu.warpLeft++;
                else if(buttonPressed(153, 631, 20, 20) == 1)
                    jeu.warpLeft--;
                else if(buttonPressed(176, 631, 20, 20) == 1)
                    jeu.warpLeft += 10;
                else if(buttonPressed(199, 631, 20, 20) == 1)
                    jeu.warpLeft -= 10;

                //Special Warp number
                else if(buttonPressed(176, 670, 20, 20) == 1)
                {
                    if(jeu.afficheWarpSP < 9)
                        jeu.afficheWarpSP++;
                }

                else if(buttonPressed(199, 670, 20, 20) == 1)
                {
                    if(jeu.afficheWarpSP > 0)
                        jeu.afficheWarpSP--;
                }

                //Value of the special warp
                else if(buttonPressed(130, 693, 20, 20) == 1)
                    jeu.warpSP[jeu.afficheWarpSP].value++;
                else if(buttonPressed(153, 693, 20, 20) == 1)
                    jeu.warpSP[jeu.afficheWarpSP].value--;
                else if(buttonPressed(176, 693, 20, 20) == 1)
                    jeu.warpSP[jeu.afficheWarpSP].value += 10;
                else if(buttonPressed(199, 693, 20, 20) == 1)
                    jeu.warpSP[jeu.afficheWarpSP].value -= 10;


                //PNJ number
                else if(buttonPressed(359, 554, 20, 20) == 1)
                {
                    if(jeu.affichePNJ < 19)
                        jeu.affichePNJ++;
                }

                else if(buttonPressed(382, 554, 20, 20) == 1)
                {
                    if(jeu.affichePNJ > 0)
                        jeu.affichePNJ--;
                }
                else if(buttonPressed(405, 554, 20, 20) == 1)
                {
                    if(jeu.affichePNJ < 9)
                        jeu.affichePNJ += 10;
                }

                else if(buttonPressed(428, 554, 20, 20) == 1)
                {
                    if(jeu.affichePNJ > 9)
                        jeu.affichePNJ -= 10;
                }


                //Value of PNJ
                else if(buttonPressed(359, 575, 20, 20) == 1)
                    jeu.pnj[jeu.affichePNJ].type++;
                else if(buttonPressed(382, 575, 20, 20) == 1)
                    jeu.pnj[jeu.affichePNJ].type--;
                else if(buttonPressed(405, 575, 20, 20) == 1)
                    jeu.pnj[jeu.affichePNJ].type += 10;
                else if(buttonPressed(428, 575, 20, 20) == 1)
                    jeu.pnj[jeu.affichePNJ].type -= 10;

                else if(buttonPressed(359, 596, 20, 20) == 1)
                    jeu.pnj[jeu.affichePNJ].text++;
                else if(buttonPressed(382, 596, 20, 20) == 1)
                    jeu.pnj[jeu.affichePNJ].text--;
                else if(buttonPressed(405, 596, 20, 20) == 1)
                    jeu.pnj[jeu.affichePNJ].text += 10;
                else if(buttonPressed(428, 596, 20, 20) == 1)
                    jeu.pnj[jeu.affichePNJ].text -= 10;

                else if(buttonPressed(359, 617, 20, 20) == 1)
                    jeu.pnj[jeu.affichePNJ].quest++;
                else if(buttonPressed(382, 617, 20, 20) == 1)
                    jeu.pnj[jeu.affichePNJ].quest--;
                else if(buttonPressed(405, 617, 20, 20) == 1)
                    jeu.pnj[jeu.affichePNJ].quest += 10;
                else if(buttonPressed(428, 617, 20, 20) == 1)
                    jeu.pnj[jeu.affichePNJ].quest -= 10;

                //Chest Number
                else if(buttonPressed(359, 655, 20, 20) == 1)
                {
                    if(jeu.afficheChest < 19)
                        jeu.afficheChest++;
                }

                else if(buttonPressed(382, 655, 20, 20) == 1)
                {
                    if(jeu.afficheChest > 0)
                        jeu.afficheChest--;
                }
                else if(buttonPressed(405, 655, 20, 20) == 1)
                {
                    if(jeu.afficheChest < 9)
                        jeu.afficheChest += 10;
                }

                else if(buttonPressed(428, 655, 20, 20) == 1)
                {
                    if(jeu.afficheChest > 9)
                        jeu.afficheChest -= 10;
                }

                //Chest's value
                else if(buttonPressed(359, 678, 20, 20) == 1)
                    jeu.chest[jeu.afficheChest].type++;
                else if(buttonPressed(382, 678, 20, 20) == 1)
                    jeu.chest[jeu.afficheChest].type--;
                else if(buttonPressed(405, 678, 20, 20) == 1)
                    jeu.chest[jeu.afficheChest].type += 10;
                else if(buttonPressed(428, 678, 20, 20) == 1)
                    jeu.chest[jeu.afficheChest].type -= 10;


                //Loot
                else if(buttonPressed(610, 554, 20, 20) == 1)
                    jeu.loot++;
                else if(buttonPressed(632, 554, 20, 20) == 1)
                    jeu.loot--;
                else if(buttonPressed(656, 554, 20, 20) == 1)
                    jeu.loot += 10;
                else if(buttonPressed(678, 554, 20, 20) == 1)
                    jeu.loot -= 10;


                //Weather
                else if(buttonPressed(656, 573, 20, 20) == 1)
                    jeu.weather++;
                else if(buttonPressed(678, 573, 20, 20) == 1)
                    jeu.weather--;

                //Cinematiques
                else if(buttonPressed(610, 613, 20, 20) == 1)
                    jeu.cinematics++;
                else if(buttonPressed(632, 613, 20, 20) == 1)
                    jeu.cinematics--;
                else if(buttonPressed(656, 613, 20, 20) == 1)
                    jeu.cinematics += 10;
                else if(buttonPressed(678, 613, 20, 20) == 1)
                    jeu.cinematics -= 10;

                else if(buttonPressed(610, 635, 20, 20) == 1)
                    jeu.cinematics_condition++;
                else if(buttonPressed(632, 635, 20, 20) == 1)
                    jeu.cinematics_condition--;
                else if(buttonPressed(656, 635, 20, 20) == 1)
                    jeu.cinematics_condition += 10;
                else if(buttonPressed(678, 635, 20, 20) == 1)
                    jeu.cinematics_condition -= 10;

                //Musiques
                else if(buttonPressed(656, 676, 20, 20) == 1)
                    jeu.musicNumber++;
                else if(buttonPressed(678, 676, 20, 20) == 1)
                    jeu.musicNumber--;


                //Button
                else if(buttonPressed(863, 551, 20, 20) == 1)
                {
                    if(jeu.afficheButton < 9)
                        jeu.afficheButton++;
                }

                else if(buttonPressed(886, 551, 20, 20) == 1)
                {
                    if(jeu.afficheButton > 0)
                        jeu.afficheButton--;
                }

                //Value of the buttons
                else if(buttonPressed(863, 574, 20, 20) == 1)
                    jeu.button[jeu.afficheButton].type++;
                else if(buttonPressed(886, 574, 20, 20) == 1)
                    jeu.button[jeu.afficheButton].type--;
                else if(buttonPressed(910, 574, 20, 20) == 1)
                    jeu.button[jeu.afficheButton].type += 10;
                else if(buttonPressed(932, 574, 20, 20) == 1)
                    jeu.button[jeu.afficheButton].type -= 10;


                //Traps
                else if(buttonPressed(863, 613, 20, 20) == 1)
                {
                    if(jeu.afficheTrap < 9)
                        jeu.afficheTrap++;
                }

                else if(buttonPressed(886, 613, 20, 20) == 1)
                {
                    if(jeu.afficheTrap > 0)
                        jeu.afficheTrap--;
                }

                //Value of the traps
                else if(buttonPressed(863, 635, 20, 20) == 1)
                    jeu.trap[jeu.afficheTrap].type++;
                else if(buttonPressed(886, 635, 20, 20) == 1)
                    jeu.trap[jeu.afficheTrap].type--;
                else if(buttonPressed(910, 635, 20, 20) == 1)
                    jeu.trap[jeu.afficheTrap].type += 10;
                else if(buttonPressed(932, 635, 20, 20) == 1)
                    jeu.trap[jeu.afficheTrap].type -= 10;



				input.add = 0;
			}
		}
    }

    /* Même fonctionnement, sauf qu'on réinitialise la tile pointée en lui donnant
       la valeur BLANK_TILE (0 par défaut) */

    else if (input.remove == 1)
    {
        if(cursor.x < 641)
        {
            if ( input.layerDrawn == 1 )
                map.tileAction[(map.startY + cursor.y - 32) / TILE_SIZE][(map.startX + cursor.x) / TILE_SIZE] = BLANK_TILE;
            else if ( input.layerDrawn == 2 )
                map.tileBackground[(map.startY + cursor.y - 32) / TILE_SIZE][(map.startX + cursor.x) / TILE_SIZE] = BLANK_TILE;
            else if ( input.layerDrawn == 3 )
                map.tileForeground[(map.startY + cursor.y - 32) / TILE_SIZE][(map.startX + cursor.x) / TILE_SIZE] = BLANK_TILE;
            else if ( input.layerDrawn == 5 )
                map.tileCollisions[(map.startY + cursor.y - 32) / TILE_SIZE][(map.startX + cursor.x) / TILE_SIZE] = BLANK_TILE;

            cursor.tileID = 0;
        }

    }

    /* On fait défiler les tiles dans un sens ou dans l'autre */
    if (input.previous == 1)
    {
        cursor.tileID--;

        if (cursor.tileID < 0)
        {
            cursor.tileID = MAX_TILES;
        }
        else if (cursor.tileID > MAX_TILES)
        {
            cursor.tileID = 0;
        }


        input.previous = 0;
    }

    if (input.next == 1)
    {
        cursor.tileID++;

        if (cursor.tileID < 0)
        {
            cursor.tileID = MAX_TILES - 1;
        }
        else if (cursor.tileID > MAX_TILES)
        {
            cursor.tileID = 0;
        }

        input.next = 0;
    }

    /* On copie le numéro de la tile pointée dans le curseur pour qu'il affiche et colle
    désormais cette tile */
    if (input.copy == 1)
    {

		// On reset la sélection
		jeu.selectActivated = 0;
		jeu.selectZoneActivated = 0;

        if(cursor.x < 641)
        {
            if ( input.layerDrawn == 1 )
                cursor.tileID = map.tileAction[(map.startY + cursor.y - 32) / TILE_SIZE] [(map.startX + cursor.x) / TILE_SIZE];
            else if ( input.layerDrawn == 2 )
                cursor.tileID = map.tileBackground[(map.startY + cursor.y - 32) / TILE_SIZE] [(map.startX + cursor.x) / TILE_SIZE];
            else if ( input.layerDrawn == 3 )
                cursor.tileID = map.tileForeground[(map.startY + cursor.y - 32) / TILE_SIZE] [(map.startX + cursor.x) / TILE_SIZE];
            else if ( input.layerDrawn == 5 )
                cursor.tileID = map.tileCollisions[(map.startY + cursor.y - 32) / TILE_SIZE] [(map.startX + cursor.x) / TILE_SIZE];

            input.copy = 0;
        }
    }

    /* Pour réinitialiser la map, on appelle la fonction reinitMap puis on recharge la map */
    if (input.reinit == 1)
    {
        jeu.messageBox = 1;
        sprintf(jeu.messageBoxText, "Do you want to reset?");
        jeu.messageBoxAction = RESET;

        input.reinit = 0;
    }

    /* Sauvegarde la map (cf. plus loin) */
    if (input.save == 1)
    {
        jeu.messageBox = 1;
        sprintf(jeu.messageBoxText, "Do you want to save?");
        jeu.messageBoxAction = SAVE;

        input.save = 0;
    }

    /* Charge la map (notre bonne vieille fonction ;) ) */
    if (input.load == 1)
    {
        jeu.messageBox = 1;
        sprintf(jeu.messageBoxText, "Do you want to reload?");
        jeu.messageBoxAction = LOAD;

        input.load = 0;
    }

    /* Copie la map dans le fichier pastebin.txt */
    if (input.copyMap == 1)
    {
        sprintf(file, "map/pastebin.txt");
        saveMap(file);

        jeu.message = 1;
        sprintf(jeu.messageText, "Map copied !");

        input.copyMap = 0;
    }

    /* Colle la map depuis pastebin.txt */
    if (input.pasteMap == 1)
    {
        jeu.messageBox = 1;
        sprintf(jeu.messageBoxText, "Do you want to paste?");
        jeu.messageBoxAction = PASTE;

        input.pasteMap = 0;
    }

    if (input.changeLayer == 1)
    {
        input.layerDrawn++;
        if ( input.layerDrawn > 5 )
            input.layerDrawn = 1;

        input.changeLayer = 0;
    }

    /* On rajoute un délai entre 2 tours de boucle pour que le scrolling soit moins rapide */
    if (input.left == 1 || input.right == 1 || input.up == 1 || input.down == 1 ||
            input.Tactileleft == 1 || input.Tactileright == 1 || input.Tactileup == 1 || input.Tactiledown == 1)
    {
        SDL_Delay(10);
    }

}

