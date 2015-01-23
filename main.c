#include "main.h"
#include "draw.h"
#include "verify.h"
#include "sdlfunc.h"
#include "random.h"
#include "image.h"
#include "gameover.h"
#include "stats.h"
#include "text.h"

/* Экран */
SDL_Surface *screen = NULL;		

/* Нынешний уровень */
int currentLevel;

/* Определенный уровень */
int defaultLevel;

/* Номер тетрамино (минимальный, максимальный) */
int numberBlockMin, numberBlockMax;

/* Следующий тетрамино */
SDL_Surface *nextTetromino = NULL;

/* Нынешний тетрамино */
SDL_Surface *currentTetromino = NULL;

/* Номер следующего тетрамино */
int numberNextTetromino;

/* Номер нынешнего тетрамино */
int numberCurrentTetromino;

/* Новый экран */
SDL_Surface *screen_new = NULL;

/* Позиция нынешнего тетрамино */
SDL_Rect positionOfTetromino;

/* Количество линий */
int numberLines = 0;

/* Общее количество линий */
int numberAllLines = 0;

/* Переменная для продолжения игры */
int stillGo = 1;

/* Счет */
long score = 0;

/* Проверка - может ли двигаться тетрамино */
SDL_Rect checkBlockMove(SDL_Rect currentPositionBlock, int _x, int _y)
{
    SDL_Rect next;	
    Uint32 pixelsTetromino, pixelsScreen;
	
    /* RGB экрана и тетрамино */
    Uint8 rCompScreen, gCompScreen, bCompScreen;
    Uint8 rCompBlock, gCompBlock, bCompBlock;
    int sumCompScreen, sumCompBlock;

    int posX = currentPositionBlock.x;
    int posY = currentPositionBlock.y;
    int x, y;       
    int result = 1;
        
    for (x = 0; x < currentTetromino->w; x++)
    {
        for (y = 0; y < currentTetromino->h; y++)
        {
            /* Проверка на цвет */
            pixelsTetromino = getPixel(currentTetromino, x, y);
            SDL_GetRGB(pixelsTetromino, currentTetromino->format, &rCompBlock, &gCompBlock, &bCompBlock);
            sumCompBlock = rCompBlock + gCompBlock + bCompBlock;
			            
            if (sumCompBlock != 0)
            {
                /* Окраска в черный */
                putPixel(screen, posX+x, posY+y, SDL_MapRGB(screen->format, 0, 0, 0));
            }
        }
    }
	
    /* Задание местоположения тетрамино */
    posX = currentPositionBlock.x + _x*BLOCK;
    posY = currentPositionBlock.y + _y*BLOCK;

     /* Проверка пикселей */	
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
			
            /* Если тетрамино и блок окрашены, невозможно движение */            
            if ((sumCompBlock != 0) && (sumCompScreen != 0))
            {
                result = 0;
            }
        }
    }

    /* Если движение невозможно */
    if (!result)
    {
        /* Отрисовка тетрамино */
        SDL_BlitSurface(screen, NULL, screen_new, &positionOfTetromino);
        SDL_BlitSurface(currentTetromino, NULL, screen, &currentPositionBlock);

        /* Если внизу */
		if (_y == 1)
        {
            /* Проверка на заполненные линии */
            int numberFullLines = verifyFullLine(screen);
            SDL_BlitSurface(screen, NULL, screen_new, &positionOfTetromino);

            /* Добавление очков */
            switch (numberFullLines)
            {
            case 1:
                score += (40 * (currentLevel +1));
                break;
            case 2:
                score += (100 * (currentLevel +1));
                break;
            case 3:
                score += (300 * (currentLevel +1));
                break;
            case 4:
                score += (1200 * (currentLevel +1));
                break;
            default:
                break;
            }

            /* Статистика */
            numberLines += numberFullLines;
            numberAllLines += numberFullLines;

            /* Каждый 10 линий - новый уровень */
            if (numberLines >= 10)
            {
                currentLevel += 1;
                numberLines -= 10;
            }

            /* Новая статистика */
            drawStats(screen, currentLevel, numberLines, score);

            /* Новый тетрамино */
	    next.x = COLUMNS*BLOCK + SPACE_BTW_TETR_FRAME + BLOCK + BLOCK + BORD_X;
	    next.y = BLOCK + BORD_Y;
	    next.w = BLOCK * 6;
	    next.h = BLOCK * 5;            
            SDL_FillRect(screen, &next, SDL_MapRGB(screen->format, 0, 0, 0));
			            
	    currentPositionBlock.x = (COLUMNS/2)*BLOCK + BORD_X;
	    currentPositionBlock.y = BORD_Y;
			            
            numberCurrentTetromino = numberNextTetromino;

            /* Случайный выбор следующего тетрамино, загрузка картинки, отрисовка */
	    numberNextTetromino=random(numberBlockMin,numberBlockMax);            
            nextTetromino = loadImage(numberNextTetromino);
            drawNextBlock(screen, nextTetromino);

            /* Загрузка картинки нынешнего тетрамино */
            currentTetromino = loadImage(numberCurrentTetromino);
			
            /* Проверка на конец игры */
            if (verifyGameOver(screen, currentTetromino, currentPositionBlock) == 0)
            {
                stillGo = 0;
            }
        }

    }

    /* Если движение возможно */
    else
    {       
        currentPositionBlock.x += _x*BLOCK;
	currentPositionBlock.y += _y*BLOCK;

        /* Отрисовка тетрамино с новыми координатами */
        SDL_BlitSurface(screen, NULL, screen_new, &positionOfTetromino);
        SDL_BlitSurface(currentTetromino, NULL, screen, &currentPositionBlock);
    }
	   
    screen_new = NULL;   
    return currentPositionBlock;	    
}

/* Проверка - может ли поворачиваться тетрамино */
int checkBlockRotate(SDL_Rect currentPositionBlock, int _numberCurrentTetromino, int _numberNextTetromino)
{
    /* Основа из проверки на движение*/
    int result;   
    Uint32 pixelsTetromino, pixelsScreen;
    Uint8 rCompScreen, gCompScreen, bCompScreen;
    Uint8 rCompBlock, gCompBlock, bCompBlock;    
    int sumCompScreen, sumCompBlock;
    int posX = currentPositionBlock.x;
    int posY = currentPositionBlock.y;
    int x,y;
    int rotate = 1;
	    
    for (x = 0; x < currentTetromino->w; x++)
    {
        for (y = 0; y < currentTetromino->h; y++)
        {            
            pixelsTetromino = getPixel(currentTetromino, x, y);
            SDL_GetRGB(pixelsTetromino, currentTetromino->format, &rCompBlock, &gCompBlock, &bCompBlock);
            sumCompBlock = rCompBlock + gCompBlock + bCompBlock;
			         
            if (sumCompBlock != 0)
            {            
                putPixel(screen, posX+x, posY+y, SDL_MapRGB(screen->format, 0, 0, 0));
            }
        }
    }
	    
    currentTetromino = loadImage(_numberNextTetromino);

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
                rotate = 0;
            }
        }
    }

    /* Невозможен поворот */
    if (!rotate)
    {        
        currentTetromino = loadImage(_numberCurrentTetromino);
        SDL_BlitSurface(screen, NULL, screen_new, &positionOfTetromino);
        SDL_BlitSurface(currentTetromino, NULL, screen, &currentPositionBlock);        
        result = 0;
    }
    /* Возможен поворот */
    else
    {        
        SDL_BlitSurface(screen, NULL, screen_new, &positionOfTetromino);
        SDL_BlitSurface(currentTetromino, NULL, screen, &currentPositionBlock);        
        result = 1;
    }

    screen_new = NULL;    
    return result;   
}

/* Событие */
SDL_Rect checkEvent(SDL_Rect currentPositionBlock)
{	
	SDL_Event event;   
        
    while ( SDL_PollEvent(&event) )
    {
        switch (event.type)
        {
            /* Выход */
        case SDL_QUIT:
            exit(0);
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                /* Движение влево */
            case SDLK_LEFT:
                currentPositionBlock = checkBlockMove(currentPositionBlock,  -1, 0);
                break;
                /* Движение вправо */
            case SDLK_RIGHT:
                currentPositionBlock = checkBlockMove(currentPositionBlock,  1, 0);
                break;
                /* Движение вниз */
            case SDLK_DOWN:
                currentPositionBlock = checkBlockMove(currentPositionBlock,  0, 1);
                break;
                /* Сброс вниз */                
            case SDLK_SPACE:
                do
                {
                    currentPositionBlock = checkBlockMove(currentPositionBlock,  0, 1);
                }
				while (currentPositionBlock.y != BORD_Y);
                break;
                /* Поворот тетрамино */                                
            case SDLK_UP:
                if (numberCurrentTetromino % 4 == 0)
                {
                    if (checkBlockRotate(currentPositionBlock, numberCurrentTetromino, numberCurrentTetromino - 3) == 1)
                    {
                        numberCurrentTetromino -=3;
                    }
                }
                else
                {
                    if (checkBlockRotate(currentPositionBlock, numberCurrentTetromino, numberCurrentTetromino + 1) == 1)
                    {
                        numberCurrentTetromino += 1;
                    }
                }
                break;
                /* Пауза */
            case SDLK_p:                
                pause(screen, 1);
                SDL_Flip(screen);
                while (1)
                {
                    if (SDL_PollEvent(&event))
                    {
                        /* Снятие паузы */
                        if (event.type == SDL_KEYDOWN)
                        {
                            pause(screen, 0);
                            break;
                        }
                    }
                }
                break;
                /* Заново */
            case SDLK_r:
                stillGo = 0;
                break;
                /* Выход */
            case SDLK_ESCAPE:
                exit(0);
                break;
            default:
                break;
            }

        default:
            break;
        }

    }
    
    return currentPositionBlock;
}


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
    
    /* Окно игры */
    makewindow();  
    do
    {
	SDL_Event event;
	unsigned int ticks;
        
	/* Очистка экрана */
        SDL_Rect clear;
        clear.x = clear.y = 0;
        clear.h = screen->h;
        clear.w = screen->w;
        SDL_FillRect(screen, &clear, SDL_MapRGB(screen->format, 0,0,0));
        SDL_Flip(screen);

        /* Движок игры */
        engine();
		        
        ticks = 500 + SDL_GetTicks();
        while (ticks != SDL_GetTicks())
        {
            while (SDL_PollEvent(&event));
        }
        if ( SDL_WaitEvent(&event))
        {
            /* При нажатии 'R' - заново */
            if (event.key.keysym.sym == SDLK_r)
            {
                score = 0;                
                numberLines = 0;
                numberAllLines = 0;
                stillGo = 1;
                quit = 0;
            }
            else quit = 1;
        }

    }
    while (quit == 0);
	   
    return EXIT_SUCCESS;
    
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
	
    SDL_Rect currentPositionBlock;	 
    Uint32 ticks=-DELAY,ticks_keys=0;
       
    /* Координаты тетрамино в начале */
    currentPositionBlock.x = (COLUMNS/2)*BLOCK + BORD_X;
    currentPositionBlock.y = BORD_Y;

    /* Случайный выбор нынешнего и следующего тетрамино */
    numberCurrentTetromino=random(numberBlockMin,numberBlockMax);
    numberNextTetromino=random(numberBlockMin,numberBlockMax);
    
    /* Загрузка картинки тетрамино */
    nextTetromino = loadImage(numberNextTetromino);
    currentTetromino = loadImage(numberCurrentTetromino);

    /* Интерфейс */
    drawInterface(screen);
    drawNextBlock(screen, nextTetromino);
	
    /* Повтор */
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

    /* Новый экран */
    screen_new = SDL_CreateRGBSurface(SDL_HWSURFACE, screen->w, screen->h, 32, 0, 0, 0, 0);
    positionOfTetromino.x = positionOfTetromino.y = 0;
    SDL_BlitSurface(screen, NULL, screen_new, &positionOfTetromino);
}
