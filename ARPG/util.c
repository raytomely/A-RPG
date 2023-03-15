#include "util.h"

int listdir(void)
{
  DIR *dp;
  struct dirent *ep;
  dp = opendir ("./");
  if (dp != NULL)
  {
    while ((ep = readdir (dp)) != NULL)
      puts (ep->d_name);

    (void) closedir (dp);
    return 0;
  }
  else
  {
    perror ("Couldn't open the directory");
    return -1;
  }
}

void sleep(void)
{
    static int old_time = 0,  actual_time = 0;
    actual_time = SDL_GetTicks();
    if (actual_time - old_time < 16) // if less than 16 ms has passed
    {
        SDL_Delay(16 - (actual_time - old_time));
        old_time = SDL_GetTicks();
    }
    else
    {
        old_time = actual_time;
    }
}

SDL_Surface *create_surface32(int width, int height)
{
    SDL_Surface *surface;
    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
    surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, rmask, gmask, bmask, amask);
    convert_surface(&surface);
    return surface;
}

SDL_Surface *copy_surface(SDL_Surface *surface)
{
    return SDL_ConvertSurface(surface, surface->format, SDL_SWSURFACE);
}

void setPixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    if (x >= surface->w || y >= surface->h || x < 0 || y < 0)
        return;
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    *(Uint32 *)p = pixel;
}

Uint32 getpixel32(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    return *(Uint32 *)p;
}

void convert_surface(SDL_Surface **surface)
{
    SDL_Surface *temp_surf = &(**surface);
    *surface = SDL_DisplayFormat(temp_surf);
    SDL_FreeSurface(temp_surf);
}

void convert_surface_alpha(SDL_Surface **surface)
{
    SDL_Surface *temp_surf = &(**surface);
    *surface = SDL_DisplayFormatAlpha(temp_surf);
    SDL_FreeSurface(temp_surf);
}

int get_file_size(FILE* file)
{
    fseek (file, 0, SEEK_END);
    int file_size = ftell(file);
    fseek (file, 0, SEEK_SET);
    return file_size;
}


void blit_flipped_old(SDL_Surface *src, SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *dstrect)
{
    int x, y, x2;
    Uint32 pixel, alpha_pixel = src->format->colorkey;

    for(y = 0; y < srcrect->h; y++)
    {
        x2 = srcrect->w - 1;
        for(x = 0; x < srcrect->w; x++)
        {
            pixel = getpixel32(src, srcrect->x + x, srcrect->y + y);
            if(pixel != alpha_pixel)
                setPixel32(dst, dstrect->x + x2, dstrect->y + y, pixel);
            x2--;
        }
    }
}


void blit_flipped(SDL_Surface *src, SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *dstrect)
{
    int x, y, x2, bpp;
    Uint32 pixel, alpha_pixel = src->format->colorkey;

    // first do trivial rejections of bitmap, is it totally invisible?
    if ((dstrect->x >= dst->w) || (dstrect->y >= dst->h) ||
       ((dstrect->x + srcrect->w) <= 0) || ((dstrect->y + srcrect->h) <= 0))
            return;

    // clip rectangles
    // upper left hand corner first
    if (dstrect->x < 0)
    {
        //srcrect->x -= dstrect->x;
        srcrect->w += dstrect->x;
        dstrect->x = 0;
    }

    if (dstrect->y < 0)
    {
        srcrect->y -= dstrect->y;
        srcrect->h += dstrect->y;
        dstrect->y = 0;
    }

    // now lower left hand corner
    if (dstrect->x + srcrect->w > dst->w)
    {
        srcrect->x -= dstrect->x;
        srcrect->w = dst->w - dstrect->x;
        dstrect->w = dst->w;
    }

    if (dstrect->y + srcrect->h > dst->h)
    {
        srcrect->h = dst->h - dstrect->y;
        dstrect->h = dst->h;
    }

    // compute starting address in dst surface
    bpp = dst->format->BytesPerPixel;
    Uint32 *dst_buffer = (Uint32 *)((Uint8 *)dst->pixels + dstrect->y * dst->pitch + dstrect->x * bpp);

    // compute starting address in src surface to scan data from
    bpp = src->format->BytesPerPixel;
    Uint32 *src_bitmap = (Uint32 *)((Uint8 *)src->pixels + srcrect->y * src->pitch + srcrect->x * bpp);

    for(y = 0; y < srcrect->h; y++)
    {
        x2 = srcrect->w - 1;
        for(x = 0; x < srcrect->w; x++)
        {
            pixel = src_bitmap[x];
            if(pixel != alpha_pixel)
                dst_buffer[x2] = pixel;
            x2--;
        }
        dst_buffer += dst->w;
        src_bitmap += src->w;
    }
}
