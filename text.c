#include "text.h"

/* Отрисовка любого текста */
void write(SDL_Surface *screen, const char* textOnScreen, SDL_Color colorText, int posX, int posY)
{    
  SDL_Surface *text = NULL;
  SDL_Rect textPosition; 
  TTF_Font *font = TTF_OpenFont("data/font.ttf", 22);
		   
  text = TTF_RenderText_Solid(font, textOnScreen, colorText);
  textPosition.x = posX;
  textPosition.y = posY;
  textPosition.h = text->h;
  textPosition.w = text->w;
  SDL_FillRect(screen, &textPosition, SDL_MapRGB(screen->format, 0, 0, 0));
  SDL_BlitSurface(text, NULL, screen, &textPosition);
}
