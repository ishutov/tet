#include "main.h"

/* Экран */
SDL_Surface *screen = NULL;		

int main(int argc, char** argv)
{
	return 0;
}

/* Создание окна */
void makewindow()
{	
    screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);    
    SDL_WM_SetCaption ("iTetris", NULL);
    SDL_Flip(screen);
}
