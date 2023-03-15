#include "input.h"


//Variables de la classe en accès privé
SDL_Event event;
Button button;

//Enum pour les boutons
enum { up, down, right, left, attack, run, enter, magic };


//Constructeur
void input_init(void)
{
    button.left = button.right = button.up = button.down = button.run =
    button.attack = button.enter = button.magie = 0;
}


//Accesseur
Button input_getButton(void){ return button; }


//Mutateur
void input_setButton(int bouton, int etat)
{
    switch (bouton)
    {
        case up:
            button.up = etat;
            break;

        case down:
            button.down = etat;
            break;

        case right:
            button.right = etat;
            break;

        case left:
            button.left = etat;
            break;

        case attack:
            button.attack = etat;
            break;

        case run:
            button.run = etat;
            break;

        case magic:
            button.magie = etat;
            break;

        case enter:
            button.enter = etat;
            break;
    }
}


//Fonctions
void input_gestionInputs(SDL_Surface *surface, int *main_loop)
{
    //Pour l'instant, on ne gère que le clavier.
    //On gèrera les joysticks plus tard, s'il y en a
    //un de branché.
    //Pour l'instant, cette fonction n'est donc pas indispensable.
    input_getInput(surface, main_loop);
}


void input_getInput(SDL_Surface *surface, int *main_loop)
{
    // Tant qu'il y a des évènements à traiter...
    while (SDL_PollEvent(&event))
    {
        // on regarde le type de l'évènement...
        switch (event.type)
        {
            // On ferme la fenêtre
            case SDL_QUIT:
                *main_loop = 0;
                break;

            // Touche pressée
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) // La touche qui a été pressée
                {
                    case SDLK_ESCAPE: // Echap
                        *main_loop = 0;
                        break;

                    case SDLK_x:
                        button.run = 1;
                        break;

                    case SDLK_c:
                        button.magie = 1;
                        break;

                    case SDLK_v:
                        button.attack = 1;
                        break;

                    case SDLK_LEFT:
                        button.left = 1;
                        break;

                    case SDLK_RIGHT:
                        button.right = 1;
                        break;

                    case SDLK_DOWN:
                        button.down = 1;
                        break;

                    case SDLK_UP:
                        button.up = 1;
                        break;

                    case SDLK_RETURN:
                        button.enter = 1;
                        break;

                    default:
                        break;
                }
                break;

            // Touche relâchée
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                    case SDLK_x:
                        button.run = 0;
                        break;

                    case SDLK_c:
                        button.magie = 0;
                        break;

                    case SDLK_v:
                        button.attack = 0;
                        break;

                    case SDLK_LEFT:
                        button.left = 0;
                        break;

                    case SDLK_RIGHT:
                        button.right = 0;
                        break;

                    case SDLK_DOWN:
                        button.down = 0;
                        break;

                    case SDLK_UP:
                        button.up = 0;
                        break;

                    case SDLK_RETURN:
                        button.enter = 0;
                        break;

                    default:
                        break;
                }
                break;

            // on ne traite pas les autres types d'évènements
            default:
                break;
        }
    }
}
