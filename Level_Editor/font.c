//Projet Rabidja - SDL 2.0
//Partie2_06Rabidja_LvlEditor
//font.c

 #include "font.h"

TTF_Font *loadFont(char *name, int size)
{
	/* Use SDL_TTF to load the font at the specified size */
	TTF_Font *font = TTF_OpenFont(name, size);

	if (font == NULL)
	{
		printf("Failed to open Font %s: %s\n", name, TTF_GetError());
		exit(1);
	}

	return font;
}


void closeFont(TTF_Font *font)
{
	/* Close the font once we're done with it */

	if (font != NULL)
	{
		TTF_CloseFont(font);
	}
}


void drawString(char *text, int x, int y, TTF_Font *font, int r, int g, int b, int a)
{
	SDL_Rect dest;
	SDL_Surface *surface; //Pour écrire le texte
	SDL_Texture *texture; //Pour convertir la surface en texture
	SDL_Color foregroundColor;

	/* On choisit d'écrire le texte en noir (RGBA) */
	foregroundColor.r = r;
	foregroundColor.g = g;
	foregroundColor.b = b;
	foregroundColor.a = a;


	/* On utilise SDL_TTF pour générer une SDL_Surface à partir d'une chaîne de caractères (string) */
	   surface = TTF_RenderUTF8_Blended(font, text, foregroundColor);

	if (surface != NULL)
	{
		/* NOUS MODIFIONS QUELQUE PEU NOTRE CODE POUR PROFITER DE LA MEMOIRE GRAPHIQUE
		   QUI GERE LES TEXTURES  */
		// Conversion de l'image en texture
		texture = SDL_CreateTextureFromSurface(jeu.renderer, surface);

		// On se débarrasse du pointeur vers une surface
		/* On libère la SDL_Surface temporaire (pour éviter les fuites de mémoire - cf. chapitre
		   dédié) */
		SDL_FreeSurface(surface);
		surface = NULL;

	    // On dessine cette texture à l'écran
	    dest.x = x;
	    dest.y = y;

		SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
		SDL_RenderCopy(jeu.renderer, texture, NULL, &dest);

		//On supprime la texture
		SDL_DestroyTexture(texture);

	}
	else
	{
		printf("La chaine n'a pu être écrite %s: %s\n", text, TTF_GetError());

		exit(0);
	}
}
