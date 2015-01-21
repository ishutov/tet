#include "gameover.h"
#include "sdlfunc.h"

/* Проверка на окончание игры */
int verifyGameOver(SDL_Surface *screen, SDL_Surface *currentTetromino, SDL_Rect currentPositionBlock)
{   	
  Uint32 pixelsTetromino, pixelsScreen;
  Uint8 rCompScreen, gCompScreen, bCompScreen;
  Uint8 rCompBlock, gCompBlock, bCompBlock;           
  int sumCompScreen, sumCompBlock;	
	int posX = currentPositionBlock.x;
  int posY = currentPositionBlock.y;
	int x,y;      
	int result = 1;
    
	/* Проверка пикселей тетрамино */    
  for (x = 0; x < currentTetromino->w; x++)
  {
    for (y = 0; y < currentTetromino->h; y++)
    {
      pixelsScreen = getPixel(screen, posX+x, posY+y);
      pixelsTetromino = getPixel(currentTetromino, x, y);
      SDL_GetRGB(pixelsScreen, screen->format, &rCompScreen, &gCompScreen, &bCompScreen);
      SDL_GetRGB(pixelsTetromino, currentTetromino->format, &rCompBlock, &gCompBlock, &bCompBlock);

      sumCompScreen = rCompScreen + gCompScreen + bCompScreen;
      sumCompBlock = rCompBlock + gCompBlock + bCompBlock;

      if ((sumCompBlock != 0) && (sumCompScreen != 0))
      {
        result = 0;
      }
    }
  }
	    
  return result;
}

/* Конец игры */
void gameOver(SDL_Surface *screen, long score, int numberFullLines, int currentLevel)
{
	SDL_Color colorText = {255, 255, 0, 0};
  SDL_Rect textPosition;
	long highscoreLines, highscoreScore, highscoreLevel;
  char input[10];
	char *result;
	FILE *file;
	char *textOnScreen;       
  SDL_Surface *text = NULL;

  /* Загрузка шрифта */
  TTF_Font *font = TTF_OpenFont("data/font.ttf", 32);
	
  /* Надпись Game Over */
  textOnScreen = (char*)malloc(sizeof(char*) * strlen("Game over!"));	
  sprintf(textOnScreen, "Game over!");    
  text = TTF_RenderText_Solid(font, textOnScreen, colorText);
  textPosition.x = screen->w/2 - text->w/2 ;
  textPosition.y = screen->h/2 - text->h/2 ;
  textPosition.h = text->h;
  textPosition.w = text->w;
  SDL_FillRect(screen, &textPosition, SDL_MapRGB(screen->format, 0, 0, 0));
  SDL_BlitSurface(text, NULL, screen, &textPosition);

  /* Файл score.txt */
  file = fopen("data/score.txt", "r");
	    
  /* Лучший счет */    
  result = fgets(input, sizeof input, file);
	highscoreScore = strtol(input, NULL, 10);

  /* Лучшие линии */
	result =fgets(input, sizeof input, file);
  highscoreLines = strtol(input, NULL, 10);

  /* Лучший уровень */
  result =fgets(input, sizeof input, file);
	highscoreLevel = strtol(input, NULL, 10);
    
	fclose(file);
	
  /* Проверка на побитие рекорда */
  if (highscoreScore < score)
  {
    /* Запись нового рекорда */
    FILE *newfile;
		SDL_Color colorText = {255, 255, 0, 0};
    SDL_Rect textPosition;
		newfile = fopen("data/score2.txt", "w");
    fprintf(newfile, "%ld\n%d\n%d\n",score, numberFullLines, currentLevel);

    /* Надпись нового рекорда */
    TTF_CloseFont(font);
    font = TTF_OpenFont("data/font.ttf", 12);
    textOnScreen = (char*)malloc(sizeof(char*) * strlen("But you have the best Score"));
    sprintf(textOnScreen, "But you have the best Score");
    text = TTF_RenderText_Solid(font, textOnScreen, colorText);
    textPosition.y = screen->h - screen->h/4;
    textPosition.x = screen->w/2 - text->w/2 ;
    textPosition.h = text->h;
    textPosition.w = text->w;
    SDL_FillRect(screen, &textPosition, SDL_MapRGB(screen->format, 0, 0, 0));

    SDL_BlitSurface(text, NULL, screen, &textPosition);

    fclose(newfile);

		/* Сохранение нового файла */
		remove("data/score.txt");
		rename("data/score2.txt", "data/score.txt");
  }

  /* Старт заново */
  TTF_CloseFont(font);
  font = TTF_OpenFont("data/font.ttf", 12);
  textOnScreen = (char*)malloc(sizeof(char*) * strlen("Press 'R' for restart"));
  sprintf(textOnScreen, "Press 'R' for restart");

  text = TTF_RenderText_Solid(font, textOnScreen, colorText);

  textPosition.y = screen->h - screen->h/8;
  textPosition.x = screen->w/2 - text->w/2 ;
  textPosition.h = text->h;
  textPosition.w = text->w;
  SDL_FillRect(screen, &textPosition, SDL_MapRGB(screen->format, 0, 0, 0));

  SDL_BlitSurface(text, NULL, screen, &textPosition);
	    
  TTF_CloseFont(font);
  SDL_FreeSurface(text);
  textOnScreen = NULL;
}
