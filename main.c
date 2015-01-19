#include "main.h"

/* Экран */
SDL_Surface *screen = NULL;		

/* Нынешний уровень */
int currentLevel;

/* Определенный уровень */
int defaultLevel;

/* Номер тетрамино (минимальный, максимальный) */
int numberBlockMin, numberBlockMax;

int main(int argc, char** argv)
{
    TTF_Font *font;
    SDL_Rect textPosition;
    SDL_Surface *text = NULL;	
    char *levelText;
	
    /* Параметры игры */
    currentLevel = defaultLevel = 0;
    numberBlockMin = 1;
    numberBlockMax = 28;

    /* SDL_ttf , SDL*/
    atexit(TTF_Quit);    
    atexit(SDL_Quit);
	 
    /* Инициализация SDL и SDL_ttf*/
    initSDL();
	
    {
	int start=0, widthText, heightText;		
	SDL_Color colorText = {255, 255, 255, 255};
	SDL_Color yellow = {255,255,0,0};
        
	/* Создание меню */
	makewindow();		                
        widthText = 15;
        heightText = 37;
        
	/* Название */
	write(screen, "iTetris", yellow, screen->w/2-(strlen("iTetris")*widthText)/2, 90);
        		
        /* Уровень */		
        write(screen, "LEVEL", colorText, screen->w/2-50, 250);		
	write(screen, "0", colorText, screen->w/2-10, 300);
        write(screen, "-", colorText, screen->w/2-80, 250);
        write(screen, "+", colorText, screen->w/2+65, 250);
        
	/* Старт */
	write(screen, "START", colorText, screen->w/2-40, 400);
		
	/* Нажмите любую клавишу для выхода */		
	font = TTF_OpenFont("data/font.ttf", 10);	
	text = TTF_RenderText_Solid(font, "Press any key to exit", colorText);
	textPosition.x = screen->w/2+140;
	textPosition.y = 10;
	textPosition.h = text->h;
	textPosition.w = text->w;
	SDL_FillRect(screen, &textPosition, SDL_MapRGB(screen->format, 0, 0, 0));
	SDL_BlitSurface(text, NULL, screen, &textPosition);
        SDL_Flip(screen);
        
        /* Меню */
        do
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {                
                switch (event.type)
                {				
			
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				default:
				break;											
			}		
					
                case SDL_QUIT:
                    exit(1);
                    break;

                case SDL_MOUSEBUTTONUP:
                {                    
                    /* Кнопка "Уровень" */
                    if ((event.button.y >= 250) && (event.button.y <= 250 + heightText ))
                    {
			SDL_Rect clear;
                        if ( (event.button.x >= screen->w/2-80) && (event.button.x <= screen->w/2-80 + strlen("-")*widthText) )
                        {

                            if (defaultLevel == 0)
                            {
                                defaultLevel=10;
                            }
                            else 
                            {
                            	defaultLevel--;
                            }

                        }
                        else if ( (event.button.x >= screen->w/2+65) && (event.button.x <= screen->w/2+65 + strlen("+")*widthText)  )
                        {

                            if (defaultLevel ==10)
                            {
                                defaultLevel=0;
                            }
                            else
                            {
                                defaultLevel++;
                            }

                        }
                        currentLevel = defaultLevel;                        
                        
			/* Очистка экрана и отрисовка нового уровня */						
			clear.y = 300;
                        clear.x = 0;
                        clear.h = heightText;
                        clear.w = screen->w;						
                        SDL_FillRect(screen, &clear, SDL_MapRGB(screen->format, 0,0,0));                        
			levelText = (char*) malloc(3*sizeof(char*));
                        sprintf(levelText, "%d", defaultLevel);						
                        write(screen, levelText, colorText, screen->w/2-8, 300);
                    }               

                    /* Кнопка "Старт" */
		    if ( (event.button.x >= screen->w/2-40) && (event.button.x <= screen->w/2 + strlen("START")*widthText) && (event.button.y >= 400) && (event.button.y <= 400 + heightText ))
                    {
                        start = 1;
                    }

                }
                break;
                
		default:
                    break;
                }
            }
            SDL_Flip(screen);
        }
        while (start != 1);
    }
}

/* Создание окна */
void makewindow()
{	
    screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);    
    SDL_WM_SetCaption ("iTetris", NULL);
    SDL_Flip(screen);
}

/* Движок */
void engine()
{
	
}
