#include "image.h"

/* Загрузка картинки тетрамино */
SDL_Surface *loadImage(int number)
{    
  SDL_Surface *image = NULL;	    
  char *filename = (char*)malloc(sizeof(char*) * (strlen("data/")+3+strlen(".png")));
  sprintf(filename, "data/%d.png", number);
	image = IMG_Load(filename);
	return image;    
}
