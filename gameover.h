#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "main.h"
int verifyGameOver(SDL_Surface *screen, SDL_Surface *currentTetromino, SDL_Rect currentPositionBlock);
void gameOver(SDL_Surface *screen, long score, int numberFullLines, int currentLevel);

#endif
