#include "main.h"


int main(int argc, char *argv[])
{
    SDL_Surface *bmpSample = NULL, *screen = NULL;
    //SDL_Event event;
    SDL_Rect bmpPos;

    bmpPos.x = 0;
    bmpPos.y = 0;

    SDL_Init(SDL_INIT_VIDEO);

    /* load icon before SDL_SetVideoMode */
    SDL_WM_SetIcon(SDL_LoadBMP("cb.bmp"), NULL);

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

    /* load Bitmap image in a surface */
    bmpSample = SDL_LoadBMP("cb.bmp");

    SDL_WM_SetCaption("A-RPG", NULL);

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    SDL_BlitSurface(bmpSample, NULL, screen, &bmpPos);
    SDL_Flip(screen);

    //Instanciation des classes
    input_init();
    map_init();
    player_init();

    //On commence au premier niveau
    map_setLevel(1);
    map_changeLevel();

    //On initialise le player
    player_initialize();
    player_setGold(100);

    int main_loop = 1;

    //SDL_EnableKeyRepeat(400, 30);

    while (main_loop)
    {
        input_gestionInputs(screen, &main_loop);

        //Updates
        update();

        // Dessin - draw
        draw(screen);

        sleep();
    }

    SDL_FreeSurface(bmpSample); /* free the surface */
    map_free();
    player_free();
    return EXIT_SUCCESS;;
}


//Fonction de mise à jour du jeu : gère la logique du jeu
void update()
{
    //On met à jour le player
    player_update();
}


//Fonction de dessin du jeu : dessine tous les éléments
void draw(SDL_Surface* surface)
{
    //On efface tout
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));

    // Affiche la map de tiles : layer 2 (couche du fond)
    map_drawMap(2, surface);

    // Affiche la map de tiles : layer 1 (couche active : sol, etc.)
    map_drawMap(1, surface);

    // Affiche le joueur
    player_draw(surface);

    // Affiche la map de tiles : layer 3 (couche en foreground / devant)
    map_drawMap(3, surface);

    SDL_Flip(surface);
}
