/* Пауза */
void pause(SDL_Surface *screen, int yesno)
{
  SDL_Color colorText = {255, 255, 255, 0};
  SDL_Rect textPosition;
  SDL_Surface *text;
  TTF_Font *font;
  char *textOnScreen;
	   
  /* Текст паузы */
  text = NULL;
  font = TTF_OpenFont("data/font.ttf", 12);	
  textOnScreen = (char*)malloc(sizeof(char*) * strlen("Pause"));	
  sprintf(textOnScreen, "Pause");	
  text = TTF_RenderText_Solid(font, textOnScreen, colorText);	
  textPosition.x = screen->w/2+220;
  textPosition.y = 10;
  textPosition.h = text->h;
  textPosition.w = text->w;
	
  /* 1 - пауза, 0 - снятие с паузы */
  switch (yesno)
  {        
  case 0:        
      SDL_FillRect(screen, &textPosition, SDL_MapRGB(screen->format, 0, 0, 0));
      break;
	
  case 1:        
      SDL_BlitSurface(text, NULL, screen, &textPosition);
      break;

  default:
      break;
  }
	    
  TTF_CloseFont(font);
  SDL_FreeSurface(text);
  textOnScreen = NULL;
}

/* Статистика */
void drawStats(SDL_Surface *screen, int currentLevel, int linesNextLevel, long score)
{
  SDL_Color colorText = {255, 255, 255, 0};
  SDL_Rect textPosition;
  TTF_Font *font ;
  SDL_Surface *text;
  char *textOnScreen;
  text = NULL;

  /* Шрифт */
  font = TTF_OpenFont("data/font.ttf", 12);
	
  /* Текст */
  textOnScreen = (char*)malloc(sizeof(char*) * 255);
	
  /* Координаты */
  textPosition.x = COLUMNS*BLOCK + SPACE_BTW_TETR_FRAME + BLOCK + BORD_X;
  textPosition.y = BLOCK * 7 + SPACE_BTW_TETR_FRAME + BORD_Y;

  /* Уровень */
  sprintf(textOnScreen,"Level :");
  text = TTF_RenderText_Solid(font, textOnScreen, colorText);
  textPosition.h = text->h;
  textPosition.w = screen->w - textPosition.x;
  SDL_FillRect(screen, &textPosition, SDL_MapRGB(screen->format, 0, 0, 0));
  SDL_BlitSurface(text, NULL, screen, &textPosition);
	    
  sprintf(textOnScreen,"%d", currentLevel);
  textPosition.y += text->h + 1;
  text = TTF_RenderText_Solid(font, textOnScreen, colorText);
  textPosition.h = text->h;
  textPosition.w = screen->w - textPosition.x;
  SDL_FillRect(screen, &textPosition, SDL_MapRGB(screen->format, 0, 0, 0));
  SDL_BlitSurface(text, NULL, screen, &textPosition);

  /* Очки */
  sprintf(textOnScreen,"Points :");
  textPosition.y += text->h + 1;
  text = TTF_RenderText_Solid(font, textOnScreen, colorText);
  textPosition.h = text->h;
  textPosition.w = screen->w - textPosition.x;
  SDL_FillRect(screen, &textPosition, SDL_MapRGB(screen->format, 0, 0, 0));
  SDL_BlitSurface(text, NULL, screen, &textPosition);
	    
  sprintf(textOnScreen,"%ld", score);
  textPosition.y += text->h + 1;
  text = TTF_RenderText_Solid(font, textOnScreen, colorText);
  textPosition.h = text->h;
  textPosition.w = screen->w - textPosition.x;
  SDL_FillRect(screen, &textPosition, SDL_MapRGB(screen->format, 0, 0, 0));
  SDL_BlitSurface(text, NULL, screen, &textPosition);
	
  /* Количество линий до следующего уровня : */
  sprintf(textOnScreen,"Lines to achieve next level :");
  textPosition.y += text->h + 1;
  text = TTF_RenderText_Solid(font, textOnScreen, colorText);
  textPosition.h = text->h;
  textPosition.w = screen->w - textPosition.x;
  SDL_FillRect(screen, &textPosition, SDL_MapRGB(screen->format, 0, 0, 0));
  SDL_BlitSurface(text, NULL, screen, &textPosition);

  sprintf(textOnScreen,"%d", 10-linesNextLevel);
  textPosition.y += text->h + 1;
  text = TTF_RenderText_Solid(font, textOnScreen, colorText);
  textPosition.h = text->h;
  textPosition.w = screen->w - textPosition.x;
  SDL_FillRect(screen, &textPosition, SDL_MapRGB(screen->format, 0, 0, 0));
  SDL_BlitSurface(text, NULL, screen, &textPosition);
	    
  TTF_CloseFont(font);
  SDL_FreeSurface(text);
  textOnScreen = NULL;
}

/* Рекорд */
void drawHighscore(SDL_Surface *screen)
{
    long highscoreLines, highscoreScore, highscoreLevel;
    char input[10];
    char *result;
    SDL_Surface *text;
    TTF_Font *font;
    SDL_Color colorText = {255, 255, 255, 0};
    SDL_Rect textPosition;
    char *textOnScreen;
    
    /* Файл с рекордом */
    FILE *file;
    file = fopen("data/score.txt", "r");
	
    /* Счет */    
    result = fgets(input, sizeof input, file);
    highscoreScore = strtol(input, NULL, 10);

    /* Линии */
    result =fgets(input, sizeof input, file);
    highscoreLines = strtol(input, NULL, 10);

    /* Уровень */
    result =fgets(input, sizeof input, file);
    highscoreLevel = strtol(input, NULL, 10);
    
    fclose(file);
	
    /* Отрисовка рекорда */
    text = NULL;
    font = TTF_OpenFont("data/font.ttf", 12);	
    
    textOnScreen = (char*)malloc(sizeof(char*) * strlen("BEST SCORE: LEVEL: LINES: ")+10+10+10);
    sprintf(textOnScreen, "BEST SCORE: %ld LEVEL: %ld LINES: %ld", highscoreScore, highscoreLevel, highscoreLines);
	
    text = TTF_RenderText_Solid(font, textOnScreen, colorText);	
    textPosition.x = screen->w/2 - text->w/2;
    textPosition.y = screen->h - text->h - SPACE_BTW_TETR_FRAME;
    SDL_FillRect(screen, &textPosition, SDL_MapRGB(screen->format, 0, 0, 0));

    SDL_BlitSurface(text, NULL, screen, &textPosition);
	    
}

