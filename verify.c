#include "verify.h"
#include "sdlfunc.h"
#include "main.h"
#include "draw.h"

/* Проверка на заполненность линии */
int verifyFullLine(SDL_Surface *screen)
{	
  Uint32 pixelsScreen;
  Uint8 rCompScreen, gCompScreen, bCompScreen;
  int sumCompScreen;	
  int x, y;

  /* Количество заполненных */
  int count = 0;
  /* Количество заполненных линий */
  int numberFullLines = 0;
  /* Проверяемая линия */
  SDL_Rect positionLine;
	        	
  /* Параметры проверяемой линии */
  positionLine.x = BLOCK + BORD_X;
  positionLine.y = BORD_Y;

  /* Проверка для каждой линии, если ряд окрашен */    
  for (y = 0; y < LINES; y++)
  {
    count = 0;
    for (x = 0; x < COLUMNS; x++)
    {            
      pixelsScreen = getPixel(screen, positionLine.x+x*BLOCK, positionLine.y+y*BLOCK);
      SDL_GetRGB(pixelsScreen, screen->format, &rCompScreen, &gCompScreen, &bCompScreen);
      sumCompScreen = rCompScreen + gCompScreen + bCompScreen;
			            
      if (sumCompScreen != 0)
      {
        count ++;
      }
    }

    /* Если количество равно рядам, то значит, что вся линия заполнена */
    if (count == COLUMNS)
    {
      /* "Сжигание" последней линии */
      SDL_Rect Ecr, copEcr;
      Ecr.x = copEcr.x = BORD_X;
      Ecr.y = BORD_Y;
      Ecr.w = copEcr.w = COLUMNS*BLOCK + BLOCK;
      Ecr.h = copEcr.h = positionLine.y + y*BLOCK - (480/2 - (LINES*BLOCK)/2);
      copEcr.y = Ecr.y+BLOCK;			            
      SDL_BlitSurface(screen, &Ecr, screen, &copEcr);

      /* +1 к количеству заполненных линий */
      numberFullLines ++;
    }
  }

  return numberFullLines;
}
