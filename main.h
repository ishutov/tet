#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

/* Размер тетрамино */
#define BLOCK 6
/* Количество линий */
#define LINES 22
/* Количество строк */
#define COLUMNS 10
/* Задержка */
#define DELAY 300
#define DELAY_KEYS 60
/* Расстояние между тетрамино и окном */
#define SPACE_BTW_TETR_FRAME 10
/* Скорость */
#define SPEED 20
/* Граница Х */
#define BORD_X   640/2 - (COLUMNS*BLOCK)
/* Граница Y */
#define BORD_Y   480/2 - (LINES*BLOCK)/2

#endif

