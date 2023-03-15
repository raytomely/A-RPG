#include "tools.h"


/*
 * Ajoute une colonne vide après à la position données
 * et décale tout le reste vers la droite
 */
void addEmptyColumn(int xPos){

    int x, y;

	// On part le la fin vers la colonne cible
	for (x = MAX_MAP_X-1 ; x >= xPos ; x--)
    {
        for (y = 0; y < MAX_MAP_Y; y++)
        {
            if(x > xPos){
				// On décale chaque Tile vers la droite
				map.tileBackground[y][x] = map.tileBackground[y][x-1];
				map.tileAction[y][x] = map.tileAction[y][x-1];
				map.tileForeground[y][x] = map.tileForeground[y][x-1];
			}else{
				// On met une Tile vide à l'endroit d'insertion
				map.tileBackground[y][x] = 0;
				map.tileAction[y][x] = 0;
				map.tileForeground[y][x] = 0;
			}
        }
    }
}

/*
 * Supprime une colonne à la position données
 * et décale tout le reste vers la gauche
 */
void deleteColumn(int xPos){

    int x, y;

	for (x = xPos ; x < MAX_MAP_X ; x++)
    {
        for (y = 0; y < MAX_MAP_Y; y++)
        {
            if(x < MAX_MAP_X-2){
				// On décale chaque Tile vers la gauche
				map.tileBackground[y][x] = map.tileBackground[y][x+1];
				map.tileAction[y][x] = map.tileAction[y][x+1];
				map.tileForeground[y][x] = map.tileForeground[y][x+1];
			}else{
				// On met une Tile vide à la fin
				map.tileBackground[y][x] = 0;
				map.tileAction[y][x] = 0;
				map.tileForeground[y][x] = 0;
			}
        }
    }
}


/*
 * Ajoute une ligne vide après à la position données
 * et décale tout le reste vers le bas
 */
void addEmptyRow(int yPos){

    int x, y;

	// On part le la fin vers la ligne cible
	for (y = MAX_MAP_Y-1 ; y >= yPos ; y--)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            if(y > yPos){
				// On décale chaque Tile vers le bas
				map.tileBackground[y][x] = map.tileBackground[y-1][x];
				map.tileAction[y][x] = map.tileAction[y-1][x];
				map.tileForeground[y][x] = map.tileForeground[y-1][x];
			}else{
				// On met une Tile vide à l'endroit d'insertion
				map.tileBackground[y][x] = 0;
				map.tileAction[y][x] = 0;
				map.tileForeground[y][x] = 0;
			}
        }
    }
}

/*
 * Supprime une ligne à la position données
 * et décale tout le reste vers le haut
 */
void deleteRow(int yPos){

    int x, y;

	for (y = yPos ; y < MAX_MAP_Y ; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            if(x < MAX_MAP_Y-2){
				// On décale chaque Tile vers la gauche
				map.tileBackground[y][x] = map.tileBackground[y+1][x];
				map.tileAction[y][x] = map.tileAction[y+1][x];
				map.tileForeground[y][x] = map.tileForeground[y+1][x];
			}else{
				// On met une Tile vide à la fin
				map.tileBackground[y][x] = 0;
				map.tileAction[y][x] = 0;
				map.tileForeground[y][x] = 0;
			}
        }
    }
}


// Remplie la zone passée en paramètre avec la Tile active
void fillWith(int xStart, int yStart, int xEnd, int yEnd){

    int x, y;

	for (y = yStart ; y <= yEnd ; y++)
    {
        for (x = xStart; x <= xEnd; x++)
        {
			// En fonction de la couche active
			if ( input.layerDrawn == 1 ){
				map.tileAction[y-1][x] = cursor.tileID; 		// -1 à cause des onglets
			}
			else if ( input.layerDrawn == 2 ){
				map.tileBackground[y-1][x] = cursor.tileID;
			}
			else if ( input.layerDrawn == 3 ){
				map.tileForeground[y-1][x] = cursor.tileID;
			}
        }
    }
}

