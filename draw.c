#include "draw.h"
#include "sdlfunc.h"

/* Отрисовка интерфейса */
void drawInterface(SDL_Surface *screen)
{
  SDL_Rect draw;
  SDL_Surface *text;
  char *textOnScreen;
  SDL_Color colorText = {255, 255, 0, 0};
  SDL_Rect textPosition;
  TTF_Font *font;	
  text = NULL;

  /* Загрузка шрифта */
  font = TTF_OpenFont("data/font.ttf", 32);
	
  /* Название */
  textOnScreen = (char*)malloc(sizeof(char*) * strlen("iTetris"));
  sprintf(textOnScreen, "iTetris");                
  text = TTF_RenderText_Solid(font, textOnScreen, colorText);
  textPosition.x = screen->w/2 - text->w/2;
  textPosition.y = text->h;
  textPosition.h = text->h;
  textPosition.w = text->w;
  SDL_FillRect(screen, &textPosition, SDL_MapRGB(screen->format, 0, 0, 0));
  SDL_BlitSurface(text, NULL, screen, &textPosition);
	    
  /* Игровое окно */
  /* Левая вертикальная */
  draw.x = BORD_X;
  draw.y = BORD_Y;
  draw.w = BLOCK;
  draw.h = BLOCK*LINES;
  SDL_FillRect(screen, &draw, SDL_MapRGB(screen->format, 170, 170, 170));

  /* Правая вертикальная */
  draw.x = COLUMNS*BLOCK + BLOCK + BORD_X;
  SDL_FillRect(screen, &draw, SDL_MapRGB(screen->format, 170, 170, 170));

  /* Нижняя горизонтальная */
  draw.x = BORD_X;
  draw.y = BLOCK*LINES + BORD_Y;
  draw.w = BLOCK + BLOCK*COLUMNS + BLOCK;
  draw.h = BLOCK;
  SDL_FillRect(screen, &draw, SDL_MapRGB(screen->format, 170, 170, 170));

  /* Окно с будущим тетрамино */
  /* Левая вертикальная */
  draw.x = COLUMNS*BLOCK + SPACE_BTW_TETR_FRAME + BLOCK + BORD_X;
  draw.y = BORD_Y;
  draw.w = BLOCK;
  draw.h = BLOCK * 7;
  SDL_FillRect(screen, &draw, SDL_MapRGB(screen->format, 170, 170, 170));

  /* Правая вертикальная */
  draw.x += draw.h;
  SDL_FillRect(screen, &draw, SDL_MapRGB(screen->format, 170, 170, 170));

  /* Верхняя горизонтальная */
  draw.x = COLUMNS*BLOCK + SPACE_BTW_TETR_FRAME + BLOCK + BORD_X;
  draw.y = BORD_Y;
  draw.w = draw.h;
  draw.h = BLOCK;
  SDL_FillRect(screen, &draw, SDL_MapRGB(screen->format, 170, 170, 170));

  /* Нижняя горизонтальная */
  draw.y = BLOCK*6 + BORD_Y;
  SDL_FillRect(screen, &draw, SDL_MapRGB(screen->format, 170, 170, 170));	   
}

/* Отрисовка следующего тетрамино */
void drawNextBlock(SDL_Surface *ecran, SDL_Surface *numberNextTetromino)
{
  SDL_Rect nextPositionBlock;    
    
  /* Установка координат тетрамино */
  nextPositionBlock.x = (COLUMNS*BLOCK + SPACE_BTW_TETR_FRAME + BLOCK) + ((BLOCK * 7)/2) - (numberNextTetromino->w/2) + BORD_X;
  nextPositionBlock.y = ((BLOCK * 7)/2) - (numberNextTetromino->h/2) + BORD_Y;

  /* Отрисовка тетрамино */
  SDL_BlitSurface(numberNextTetromino, NULL, ecran, &nextPositionBlock);
}
