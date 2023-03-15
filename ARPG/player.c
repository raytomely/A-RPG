
#include "player.h"
#include "map.h"
#include "input.h"
#include "util.h"


// Points de vie/sant� + chrono d'invicibilit�
int life, invincibleTimer;

//Magie
float MP, regainTime;
int MPmax;
int gold;

// Coordonn�es du sprite
int x, y;

// Largeur, hauteur du sprite
int h, w;

// Checkpoint pour le h�ros (actif ou non)
int checkpointActif;
// + coordonn�es de respawn (r�apparition)
int respawnX, respawnY;

// Variables utiles pour l'animation :
// Num�ro de la frame (= image) en cours + timer
int frameNumber, frameTimer, frameMax;
// Nombre max de frames, �tat du sprite et direction
// dans laquelle il se d�place (gauche / droite)
int etat, direction;
int isrunning;
int isAttacking;

// Variables utiles pour la gestion des collisions :
//Est-il sur le sol, chrono une fois mort
int timerMort;

//Vecteurs de d�placement temporaires avant d�tection
//des collisions avec la map
float dirX, dirY;
//Sauvegarde des coordonn�es de d�part
int saveX, saveY;

//Spritesheet du h�ros
SDL_Surface* hero;
SDL_Surface* sword;
SDL_Rect hero_pos, hero_size;

//Gestion de l'�p�e
int swordX, swordY;
int swordTimer;
int swordRotation;

//Gestion de la magie (boules de feu)
int magicNumber;

//Nombre d'explosions � l'�cran
int nombreExplosions;

//Num�ro de la warp sp�ciale emprunt�e
int numberSPE;


//******************/
/* Constantes */
//******************/

/* Taille maxi de la map : 80 x 80 tiles */
extern const int MAX_MAP_X;
extern const int MAX_MAP_Y;

/* Taille d'une tile (32 x 32 pixels) */
extern const int TILE_SIZE;

/* Constantes pour l'animation */
const int TIME_BETWEEN_2_FRAMES_PLAYER = 3;
const float TIME_BETWEEN_2_FRAMES_SWORD = 1;

/* Taille du sprite de notre h�ros (largeur = width et hauteur = heigth) */
const int PLAYER_WIDTH = 40;
const int PLAYER_HEIGTH = 48;

//Vitesse de d�placement en pixels du sprite
const int PLAYER_SPEED = 3;

//Valeurs attribu�es aux �tats/directions
const int IDLE = 0;
const int WALK = 1;

const int DEAD = 4;

const int DOWN = 0;
const int UP = 1;
const int LEFT = 2;
const int RIGHT = 3;


// Taille de la fen�tre : 800x480 pixels
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

//Constantes pour les limites de la cam�ra avant scrolling
const int LIMITE_X = 400;
const int LIMITE_Y = 220;
const int LIMITE_W = 100;
const int LIMITE_H = 80;

//Enum pour les boutons
enum { up, down, right, left, attack, run, enter, magie };

//Nombre max de levels
const int LEVEL_MAX = 2;

//Une enum pour la gestion du menu.
enum { START, PAUSE };

//Nombre max de shurikens � l'�cran
const int MAGIC_MAX = 6;


//*************************/
/* VALEURS DES TILES */
//************************/

const int MUR = 1;
const int SPE1 = 10;
const int SPE2 = 11;
const int SPE3 = 12;
const int SPE4 = 13;
const int SPE5 = 14;
const int SPE6 = 15;
const int SPE7 = 16;
const int SPE8 = 17;
const int SPE9 = 18;
const int SPE10 = 19;


//Constructeur

void player_init()
{
    //Chargement de la spritesheet du h�ros
    if (!(hero = IMG_Load("graphics/hero.png")))
    {
        // Erreur
        printf("Erreur durant le chargement du spritesheet du h�ros.");
    }
    else
    {
        convert_surface_alpha(&hero);
        SDL_SetColorKey(hero, SDL_SRCCOLORKEY, getpixel32(hero,0,0));
    }

    //Chargement du sprite de l'�p�e
    /*if (!(sword = loadFromFile("graphics/sword.png")))
    {
        // Erreur
        printf("Erreur durant le chargement du sprite de l'�p�e.");
    }
    else
    {
        convert_surface_alpha(&sword);
        SDL_SetColorKey(sword, SDL_SRCCOLORKEY, getpixel32(sword,0,0));
    }*/


    //Initialisation des variables :
    dirX = 0;
    dirY = 0;
    life = 3;
    invincibleTimer = 0;
    x = y = h = w = 0;
    checkpointActif = 0;
    respawnX = respawnY = 0;
    frameNumber = frameTimer = frameMax = 0;
    etat = direction = 0;
    timerMort = 0;
    dirX = dirY = 0;
    saveX = saveY = 0;

    MP = MPmax = 100;
    regainTime = 0.2f;

    swordTimer = 0;
    swordRotation = 0;
}


//Destructeur
void player_free(void)
{
    SDL_FreeSurface(hero);
    //SDL_FreeSurface(sword);
}


//Accesseurs
int player_getX(void) { return x; }
int player_getY(void) { return y; }
int player_getW(void) { return w; }
int player_getH(void) { return h; }
float player_getDirX(void) { return dirX; }
float player_getDirY(void) { return dirY; }
int player_getLife(void) { return life; }
int player_getGold(void) { return gold; }
int player_getDirection(void) { return direction; }
int player_getMagic(void) { return magicNumber; }
int player_getNombreExplosions(void) { return nombreExplosions; }
float player_getMP(void) { return MP; }
float player_getMPmax(void) { return MPmax; }


//Mutateurs
void player_setX(int valeur) { x = valeur; }
void player_setY(int valeur) { y = valeur; }
void player_setW(int valeur) { w = valeur; }
void player_setH(int valeur) { h = valeur; }
void player_setDirX(float valeur) { dirX = valeur; }
void player_setDirY(float valeur) { dirY = valeur; }
void player_setTimerMort(int valeur) { timerMort = valeur; }
void player_setGold(int valeur) { gold = valeur; }
void player_setCheckpoint(int valeur) { checkpointActif = valeur; }
void player_setMagic(int valeur) { magicNumber = valeur; }
void player_setNombreExplosions(int valeur) { nombreExplosions = valeur; }


//Fonctions
void player_initialize()
{
    //PV � 3 coeurs
    life = 3;

    //Timer d'invincibilit� � 0
    invincibleTimer = 0;

    //Indique l'�tat et la direction de notre h�ros
    direction = RIGHT;
    etat = IDLE;

    //Indique le num�ro de la frame o� commencer
    frameNumber = 0;

    //...la valeur de son chrono ou timer
    frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

    //... et son nombre de frames max (8 pour l'anim' IDLE
    // = ne fait rien)
    frameMax = 8;

    //On d�marre au d�but de la map
    x = map_getBeginX();
    y = map_getBeginY();

    //On recentre la cam�ra
    map_setStartX(map_getBeginX() - (SCREEN_WIDTH / 2));
    map_setStartY(map_getBeginY() - (SCREEN_HEIGHT / 2));

    /* Hauteur et largeur de notre h�ros */
    w = PLAYER_WIDTH;
    h = PLAYER_HEIGTH;

    //Variables n�cessaires au fonctionnement de la gestion des collisions
    timerMort = 0;
    isAttacking = 0;

    map_setWarpDirection(-1);
}


void player_draw(SDL_Surface *surface)
{
    /* Gestion du timer */
    // Si notre timer (un compte � rebours en fait) arrive � z�ro
    if (frameTimer <= 0)
    {
        //On le r�initialise
        frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

        //Et on incr�mente notre variable qui compte les frames de 1 pour passer � la suivante
        frameNumber++;

        //Mais si on d�passe la frame max, il faut revenir � la premi�re :
        if (frameNumber >= frameMax)
            frameNumber = 0;

    }
    //Sinon, on d�cr�mente notre timer
    else
    {
        if (etat != IDLE)
            frameTimer -= 1 + (isrunning * 2);
        else
            frameTimer--;
    }



    //On place le joueur correctement sur la map
    hero_pos.x = x - map_getStartX(); hero_pos.y = y - map_getStartY();


    //Pour conna�tre le X de la bonne frame � dessiner, il suffit de multiplier
    //la largeur du sprite par le num�ro de la frame � afficher -> 0 = 0; 1 = 40; 2 = 80...
    //On calcule le Y de la bonne frame � dessiner, selon la valeur de l'�tat du h�ros :
    //Aucun Mouvement (Idle) = 0, marche (walk) = 1, etc...
    //Tout cela en accord avec notre spritesheet, of course ;)

    //Si on a �t� touch� et qu'on est invincible
    if (invincibleTimer > 0)
    {
        //On fait clignoter le h�ros une frame sur deux
        //Pour �a, on calcule si le num�ro de la frame en
        //cours est un multiple de deux
        if (frameNumber % 2 == 0)
        {
            //Gestion du flip (retournement de l'image selon que le sprite regarde � droite ou � gauche)
            if (direction == RIGHT)
            {
                hero_size.x = frameNumber * w;
                hero_size.y = (etat * 3 * h + (direction - 1) * h + isAttacking * 6 * h);
                hero_size.w = w; hero_size.h = h;
                blit_flipped(hero, &hero_size, surface, &hero_pos);
            }
            else
            {
                hero_size.x = frameNumber * w;
                hero_size.y = (etat * 3 * h + direction * h + isAttacking * 6 * h);
                hero_size.w = w; hero_size.h = h;
                SDL_BlitSurface(hero, &hero_size, surface, &hero_pos);
            }
        }
        //Sinon, on ne dessine rien, pour le faire clignoter
    }

    //Sinon, on dessine normalement
    else
    {
        //Gestion du flip (retournement de l'image selon que le sprite regarde � droite ou � gauche)
        if (direction == RIGHT)
        {
            hero_size.x = frameNumber * w;
            hero_size.y = (etat * 3 * h + (direction - 1) * h + isAttacking * 6 * h);
            hero_size.w = w; hero_size.h = h;
            blit_flipped(hero, &hero_size, surface, &hero_pos);
        }
        else
        {
            hero_size.x = frameNumber * w;
            hero_size.y = (etat * 3 * h + direction * h + isAttacking * 6 * h);
            hero_size.w = w; hero_size.h = h;
            SDL_BlitSurface(hero, &hero_size, surface, &hero_pos);
        }
    }
}


void player_update()
{
    //On rajoute un timer au cas o� notre h�ros mourrait lamentablement en tombant dans un trou...
    //Si le timer vaut 0, c'est que tout va bien, sinon, on le d�cr�mente jusqu'� 0, et l�,
    //on r�initialise.
    //C'est pour �a qu'on ne g�re le joueur que si ce timer vaut 0.
    if (timerMort == 0)
    {
        //On g�re le timer de l'invincibilit�
        if (invincibleTimer > 0)
            invincibleTimer--;

        //On r�initialise nos vecteurs de d�placement, pour �viter que le perso
        //ne fonce de plus en plus vite pour atteindre la vitesse de la lumi�re ! ;)
        //Essayez de le d�sactiver pour voir !
        dirX = 0;
        dirY = 0;

        //Gestion de la course en appuyant sur la touche courir
        if (input_getButton().run)
            isrunning = 1;
        else
            isrunning = 0;

        //Voil�, au lieu de changer directement les coordonn�es du joueur, on passe par un vecteur
        //qui sera utilis� par la fonction mapCollision(), qui regardera si on peut ou pas d�placer
        //le joueur selon ce vecteur et changera les coordonn�es du player en fonction.
        if (input_getButton().left)
        {
            dirX -= PLAYER_SPEED + isrunning;
            //Et on indique qu'il va � gauche (pour le flip
            //de l'affichage, rappelez-vous).
            direction = LEFT;

            //Si ce n'�tait pas son �tat auparavant :
            if (etat != WALK)
            {
                //On enregistre l'anim' de la marche et on l'initialise � 0
                etat = WALK;
                frameNumber = 0;
                frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                frameMax = 8;
            }
        }

        //Si on d�tecte un appui sur la touche fl�ch�e droite
        else if (input_getButton().right)
        {
            //On augmente les coordonn�es en x du joueur
            dirX += PLAYER_SPEED + isrunning;
            //Et on indique qu'il va � droite (pour le flip
            //de l'affichage, rappelez-vous).
            direction = RIGHT;

            //Si ce n'�tait pas son �tat auparavant
            if (etat != WALK)
            {
                //On enregistre l'anim' de la marche et on l'initialise � 0
                etat = WALK;
                frameNumber = 0;
                frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                frameMax = 8;
            }
        }

        //Si on d�tecte un appui sur la touche fl�ch�e haut
        else if (input_getButton().up)
        {
            //On augmente les coordonn�es en x du joueur
            dirY -= PLAYER_SPEED + isrunning;
            //Et on indique qu'il va � droite (pour le flip
            //de l'affichage, rappelez-vous).
            direction = UP;

            //Si ce n'�tait pas son �tat auparavant
            if (etat != WALK)
            {
                //On enregistre l'anim' de la marche et on l'initialise � 0
                etat = WALK;
                frameNumber = 0;
                frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                frameMax = 8;
            }
        }

        //Si on d�tecte un appui sur la touche fl�ch�e bas
        else if (input_getButton().down)
        {
            //On augmente les coordonn�es en x du joueur
            dirY += PLAYER_SPEED + isrunning;
            //Et on indique qu'il va � droite (pour le flip
            //de l'affichage, rappelez-vous).
            direction = DOWN;

            //Si ce n'�tait pas son �tat auparavant
            if (etat != WALK)
            {
                //On enregistre l'anim' de la marche et on l'initialise � 0
                etat = WALK;
                frameNumber = 0;
                frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                frameMax = 8;
            }
        }

        //Si on n'appuie sur rien, on charge l'animation marquant l'inactivit� (Idle)
        else if (!input_getButton().right && !input_getButton().left &&
        !input_getButton().up && !input_getButton().down)
        {
            //On teste si le joueur n'�tait pas d�j� inactif, pour ne pas recharger l'animation
            //� chaque tour de boucle
            if (etat != IDLE)
            {
                //On enregistre l'anim' de l'inactivit� et on l'initialise � 0
                etat = IDLE;
                frameNumber = 0;
                frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
                frameMax = 8;
            }
        }
        //On rajoute notre fonction de d�tection des collisions qui va mettre �
        //jour les coordonn�es de notre h�ros.
        player_mapCollision();

        //On g�re le scrolling (fonction ci-dessous)
        player_centerScrolling();
    }

    //Gestion de la mort :
    //Si timerMort est diff�rent de 0, c'est qu'il faut r�initialiser le joueur.
    //On ignore alors ce qui pr�c�de et on joue cette boucle (un wait en fait) jusqu'� ce que
    // timerMort == 1. A ce moment-l�, on le d�cr�mente encore -> il vaut 0 et on r�initialise
    //le jeu avec notre bonne vieille fonction d'initialisation ;) !
    if (timerMort > 0)
    {
        timerMort--;

        if (timerMort == 0)
        {
            // Si on est mort, on r�initialise le niveau
            map_changeLevel();
            player_initialize();
        }
    }
}


void player_centerScrolling(void)
{
    // Nouveau scrolling � sous-bo�te limite :
    //Pour �viter les effets de saccades dus � une cam�ra qui se
    //centre automatiquement et constamment sur le joueur (ce qui
    //peut en rendre malade certains...), on cr�e une "bo�te" imaginaire
    //autour du joueur. Quand on d�passe un de ses bords (en haut, en bas,
    //� gauche ou � droite), on scrolle.
    //Mais l� encore, au lieu de centrer sur le joueur, on d�place simplement
    //la cam�ra jusqu'� arriver au joueur. On a chang� ici la valeur � 4 pixels
    //pour que le jeu soit plus rapide.
    int cxperso = x + w / 2;
    int cyperso = y + h / 2;
    int xlimmin = map_getStartX() + LIMITE_X;
    int xlimmax = xlimmin + LIMITE_W;
    int ylimmin = map_getStartY() + LIMITE_Y;
    int ylimmax = ylimmin + LIMITE_H;

    //Effet de retour en arri�re quand on est mort :
    //Si on est tr�s loin de la cam�ra, plus loin que le bord
    //de la map, on acc�l�re le scrolling :
    if (cxperso < map_getStartX())
    {
        map_setStartX(map_getStartX() - 30);
    }

    //Si on d�passe par la gauche, on recule la cam�ra
    else if (cxperso < xlimmin)
    {
        map_setStartX(map_getStartX() - 3 - isrunning);
    }

    //Effet de retour en avant quand on est mort (au
    //cas o� le joueur s'amuse � faire le niveau � rebours
    //apr�s une checkpoint) :
    //Si on est tr�s loin de la cam�ra, plus loin que le bord
    //de la map, on acc�l�re le scrolling :
    if (cxperso > map_getStartX() + SCREEN_WIDTH)
    {
        map_setStartX(map_getStartX() + 30);
    }

    //Si on d�passe par la droite, on avance la cam�ra
    else if (cxperso > xlimmax)
    {
        map_setStartX(map_getStartX() + 3 + isrunning);
    }

    //Si on arrive au bout de la map � gauche, on stoppe le scrolling
    if (map_getStartX() < 0)
    {
        map_setStartX(0);
    }

    //Si on arrive au bout de la map � droite, on stoppe le scrolling � la
    //valeur Max de la map - la moiti� d'un �cran (pour ne pas afficher du noir).
    else if (map_getStartX() + SCREEN_WIDTH >= map_getMaxX())
    {
        map_setStartX(map_getMaxX() - SCREEN_WIDTH);
    }

    //Si on d�passe par le haut, on remonte la cam�ra
    if (cyperso < ylimmin)
    {
        map_setStartY(map_getStartY() - 3 - isrunning);
    }

    //Si on d�passe par le bas, on descend la cam�ra
    if (cyperso > ylimmax)
    {
        map_setStartY(map_getStartY() + 3 + isrunning);
    }

    //Si on arrive au bout de la map en haut, on stoppe le scrolling
    if (map_getStartY() < 0)
    {
        map_setStartY(0);
    }

    //Si on arrive au bout de la map en bas, on stoppe le scrolling � la
    //valeur Max de la map - la moiti� d'un �cran (pour ne pas afficher du noir).
    else if (map_getStartY() + SCREEN_HEIGHT >= map_getMaxY())
    {
        map_setStartY(map_getMaxY() - SCREEN_HEIGHT);
    }
}


void player_mapCollision()
{
    int i, x1, x2, y1, y2, warp_tile;

    /* Ensuite, on va tester les mouvements horizontaux en premier
    (axe des X). On va se servir de i comme compteur pour notre boucle.
    En fait, on va d�couper notre sprite en blocs de tiles pour voir
    quelles tiles il est susceptible de recouvrir.
    On va donc commencer en donnant la valeur de Tile_Size � i pour qu'il
    teste la tile o� se trouve le x du joueur mais aussi la suivante SAUF
    dans le cas o� notre sprite serait inf�rieur � la taille d'une tile.
    Dans ce cas, on lui donnera la vraie valeur de la taille du sprite
    Et on testera ensuite 2 fois la m�me tile. Mais comme �a notre code
    sera op�rationnel quelle que soit la taille de nos sprites ! */

    if (h > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = h;


    //On lance alors une boucle for infinie car on l'interrompra selon
    //les r�sultats de nos calculs
    for (;;)
    {
        //On va calculer ici les coins de notre sprite � gauche et �
        //droite pour voir quelle tile ils touchent.
        x1 = (x + dirX) / TILE_SIZE;
        x2 = (x + dirX + w - 1) / TILE_SIZE;

        //M�me chose avec y, sauf qu'on va descendre au fur et � mesure
        //pour tester toute la hauteur de notre sprite, gr�ce � notre
        //fameuse variable i.
        y1 = (y) / TILE_SIZE;
        y2 = (y + i - 1) / TILE_SIZE;

        //De l�, on va tester les mouvements initi�s dans updatePlayer
        //gr�ce aux vecteurs dirX et dirY, tout en testant avant qu'on
        //se situe bien dans les limites de l'�cran.
        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            //Si on a un mouvement � droite
            if (dirX > 0)
            {
                //On v�rifie si les tiles recouvertes sont solides
                if (map_getTile(y1, x2) == MUR || map_getTile(y2, x2) == MUR)
                {
                    // Si c'est le cas, on place le joueur aussi pr�s que possible
                    // de ces tiles, en mettant � jour ses coordonn�es. Enfin, on
                    //r�initialise son vecteur d�placement (dirX).

                    x = x2 * TILE_SIZE;
                    x -= (w + 1);
                    dirX = 0;
                }
            }

            //M�me chose � gauche
            else if (dirX < 0)
            {
                if (map_getTile(y1, x1) == MUR || map_getTile(y2, x1) == MUR)
                {
                    x = (x1 + 1) * TILE_SIZE;
                    dirX = 0;
                }
            }
        }

        //On sort de la boucle si on a test� toutes les tiles le long de la hauteur du sprite.
        if (i == h)
        {
            break;
        }

        //Sinon, on teste les tiles sup�rieures en se limitant � la heuteur du sprite.
        i += TILE_SIZE;

        if (i > h)
        {
            i = h;
        }
    }


    //On recommence la m�me chose avec le mouvement vertical (axe des Y)
    if (w > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = w;


    for (;;)
    {
        x1 = (x) / TILE_SIZE;
        x2 = (x + i) / TILE_SIZE;

        y1 = (y + dirY) / TILE_SIZE;
        y2 = (y + dirY + h) / TILE_SIZE;

        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            if (dirY > 0)
            {
                // D�placement en bas
                if (map_getTile(y2, x1) == MUR || map_getTile(y2, x2) == MUR)
                {
                    //Si la tile est une tile solide, on y colle le joueur
                    y = y2 * TILE_SIZE;
                    y -= (h + 1);
                    dirY = 0;
                }

                else if (((warp_tile = map_getTile(y2, x1)) >= SPE1 && warp_tile <= SPE1) ||
                        ((warp_tile = map_getTile(y2, x2)) >= SPE1 && warp_tile <= SPE10))
                {
                    //On stoppe le joueur
                    y = 0;

                    //On teste si on doit warper en haut
                    if ((map_getWarpSP(warp_tile - 10) > 0))
                    {
                        //On enregistre la direction du warp et les coordonn�es du joueur
                        map_setWarpDirection(-1);
                        map_setWarp_coming_from_x(x);
                        map_setWarp_coming_from_y(y);

                        //On change de level
                        map_setLevel(map_getWarpSP(warp_tile - 10));
                        map_changeLevel();
                        player_reinitialize();
                    }
                }

            }

            else if (dirY < 0)
            {
                // D�placement vers le haut
                if (map_getTile(y1, x1) == MUR || map_getTile(y1, x2) == MUR)
                {
                    y = (y1 + 1) * TILE_SIZE;
                    dirY = 0;
                }

                else if (((warp_tile = map_getTile(y1, x1)) >= SPE1 && warp_tile <= SPE1) ||
                        ((warp_tile = map_getTile(y1, x2)) >= SPE1 && warp_tile <= SPE10))
                {
                    //On stoppe le joueur
                    y = 0;

                    //On teste si on doit warper en haut
                    if ((map_getWarpSP(warp_tile - 10) > 0))
                    {
                        //On enregistre la direction du warp et les coordonn�es du joueur
                        map_setWarpDirection(-1);
                        map_setWarp_coming_from_x(x);
                        map_setWarp_coming_from_y(y);

                        //On change de level
                        map_setLevel(map_getWarpSP(warp_tile - 10));
                        map_changeLevel();
                        player_reinitialize();
                    }
                }
            }
        }

        //On teste la largeur du sprite (m�me technique que pour la hauteur pr�c�demment)
        if (i == w)
        {
            break;
        }

        i += TILE_SIZE;

        if (i > w)
        {
            i = w;
        }
    }

    /* Maintenant, on applique les vecteurs de mouvement si le sprite n'est pas bloqu� */
    x += dirX;
    y += dirY;

    //Si on touche les bords de l'�cran,
    if (x < 0)
    {
        //On stoppe le joueur
        x = 0;
    }

    else if (x + w >= map_getMaxX())
    {
        //On stoppe le joueur
        x = map_getMaxX() - w;
    }

    else if (y < 0)
    {
        //On stoppe le joueur
        y = 0;
    }

    else if (y + h >= map_getMaxY())
    {
        //On stoppe le joueur
        y = map_getMaxY() - h;
    }

    //****GESTION DES WARPS DIRECTIONNEL****
    //Si on touche les bords de l'�cran, on warp au niveau indiqu�
    //si celui-ci est diff�rent de 0
    if (x <= 0)
    {
        //On stoppe le joueur
        x = 0;

        //On teste si on doit warper � gauche
        if (map_getWarpLeft() > 0)
        {
            //On enregistre la direction du warp et les coordonn�es du joueur
            map_setWarpDirection(LEFT);
            map_setWarp_coming_from_x(x);
            map_setWarp_coming_from_y(y);

            //On change de level
            map_setLevel(map_getWarpLeft());
            map_changeLevel();
            player_reinitialize();
        }
    }

    else if (x + w >= map_getMaxX())
    {
        //On stoppe le joueur
        x = map_getMaxX() - w;

        //On teste si on doit warper � droite
        if (map_getWarpRight() > 0)
        {
            //On enregistre la direction du warp et les coordonn�es du joueur
            map_setWarpDirection(RIGHT);
            map_setWarp_coming_from_x(x);
            map_setWarp_coming_from_y(y);

            //On change de level
            map_setLevel(map_getWarpRight());
            map_changeLevel();
            player_reinitialize();
        }
    }

    else if (y <= 0)
    {
        //On stoppe le joueur
        y = 0;

        //On teste si on doit warper en haut
        if (map_getWarpUp() > 0)
        {
            //On enregistre la direction du warp et les coordonn�es du joueur
            map_setWarpDirection(UP);
            map_setWarp_coming_from_x(x);
            map_setWarp_coming_from_y(y);

            //On change de level
            map_setLevel(map_getWarpUp());
            map_changeLevel();
            player_reinitialize();
        }
    }

    else if (y + h >= map_getMaxY())
    {
        //On stoppe le joueur
        y = map_getMaxY() - h;

        //On teste si on doit warper en bas
        if (map_getWarpDown() > 0)
        {
            //On enregistre la direction du warp et les coordonn�es du joueur
            map_setWarpDirection(DOWN);
            map_setWarp_coming_from_x(x);
            map_setWarp_coming_from_y(y);

            //On change de level
            map_setLevel(map_getWarpDown());
            map_changeLevel();
            player_reinitialize();
        }
    }
}


void player_reinitialize()
{
    // Coordonn�es de d�marrage de notre h�ros selon la direction de warp
    //Si on n'a pas warp�, alors on commence aux coordonn�es de d�part de la map
    if (map_getWarpDirection() == -1)
    {
        x = map_getBeginX();
        y = map_getBeginY();

        //On recentre la cam�ra
        map_setStartX(map_getBeginX() - (SCREEN_WIDTH / 2));
        map_setStartY(map_getBeginY() - (SCREEN_HEIGHT / 2));
    }
    //Si on a warp� en haut
    else if (map_getWarpDirection() == UP)
    {
        //On change la valeur en y du h�ros pour qu'il se
        //trouve en bas de la map
        y = map_getMaxY() - h - 1;

        //On recentre la cam�ra
        map_setStartY(map_getMaxY() - SCREEN_HEIGHT);
    }
    //Si on a warp� en bas
    else if (map_getWarpDirection() == DOWN)
    {
        //On change la valeur en y du h�ros pour qu'il se
        //trouve en haut de la map
        y = 1;

        //On recentre la cam�ra
        map_setStartY(0);
    }
    //Si on a warp� � gauche
    else if (map_getWarpDirection() == LEFT)
    {
        //On change la valeur en x du h�ros pour qu'il se
        //trouve � droite de la map
        x = map_getMaxX() - w - 1;

        //On recentre la cam�ra
        map_setStartX(map_getMaxX() - SCREEN_WIDTH);
    }
    //Si on a warp� � droite
    else if (map_getWarpDirection() == RIGHT)
    {
        //On change la valeur en x du h�ros pour qu'il se
        //trouve � gauche de la map
        x = 1;

        //On recentre la cam�ra
        map_setStartX(0);
    }
}

