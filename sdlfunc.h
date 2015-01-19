#ifndef SDLFUNC_H
#define SDLFUNC_H

#include "main.h"
int initSDL(void);
Uint32 getPixel(SDL_Surface *surface, int x, int y);
void putPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

#endif