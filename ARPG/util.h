#include <SDL/SDL.h>
#include <dirent.h>

Uint32 getpixel32(SDL_Surface *surface, int x, int y);
SDL_Surface *create_surface32(int width, int height);
SDL_Surface *copy_surface(SDL_Surface *surface);
void convert_surface(SDL_Surface **surface);
void convert_surface_alpha(SDL_Surface **surface);
int get_file_size(FILE* file);
void sleep(void);
void blit_flipped(SDL_Surface *src, SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *dstrect);
