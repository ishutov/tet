#include "sdlfunc.h";

/* Инициализация SDL */
int initSDL(void)
{ 
    int result = EXIT_SUCCESS;

    if ( SDL_Init( SDL_INIT_VIDEO) < 0 )
    {
        fprintf(stderr, "Error in initialize SDL: %s\n", SDL_GetError() );
        result =  EXIT_FAILURE;
    }

    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Error in initialize SDL_ttf : %s\n", TTF_GetError());
        result =  EXIT_FAILURE;
    }

    return result;

}

/* Получить пиксель */
Uint32 getPixel(SDL_Surface *surface, int x, int y)
{ 
    int bpp = surface->format->BytesPerPixel;
    /* p - адрес пикселя */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       
    }    
}


/* Установка пикселя */
void putPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;    
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        }
        else
        {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }    
}