//Projet Rabidja - SDL 2.0
//Partie2_06Rabidja_LvlEditor
//main.c

#include "main.h"


int main(int argc, char *argv[])
{
	unsigned int frameLimit = SDL_GetTicks() + 16;
	int go;

   	/* Initialisation de la SDL */

	init("Level Editor SDL2, Action-RPG v.2.1 - www.meruvia.fr - 06/2015");

	/* Affichage des 3 layers */
    input.layerDrawn = 4;

	/* Chargement des ressources (graphismes, sons) */
	loadGame();

	/* Appelle la fonction cleanup à la fin du programme */

	atexit(cleanup);

	go = 1;


	/* Boucle infinie, principale, du jeu */

	while (go == 1)
	{

		/* On prend on compte les input (clavier, joystick... */
		getInput();

		/* On met à jour le jeu */
		if(jeu.messageBox == 1)
            updateMessageBox();
        else if(jeu.doMessageBoxAction == 1)
            doMessageBoxAction();
        else
            update();

		/* On affiche tout */
		draw();

		/* Gestion des 60 fps (1000ms/60 = 16.6 -> 16 */
		delay(frameLimit);
		frameLimit = SDL_GetTicks() + 16;

	}

	/* Exit */
	exit(0);
}

