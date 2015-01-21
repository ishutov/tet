#ifndef STATS_H
#define STATS_H

#include "main.h"
void pause(SDL_Surface *screen, int yesno);
void drawStats(SDL_Surface *screen, int currentLevel, int linesNextLevel, long score);
void drawHighscore(SDL_Surface *screen);

#endif
