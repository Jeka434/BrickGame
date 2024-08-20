#ifndef BRICKGAME_V1_0_SRC_BRICK_GAME_TETRIS_INC_TETRIS_H_
#define BRICKGAME_V1_0_SRC_BRICK_GAME_TETRIS_INC_TETRIS_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if defined(_WIN32) && defined(_MSC_VER)
#include <windows.h>
int clock_gettime(int _, struct timespec *spec);
#define CLOCK_REALTIME 0
#endif

#include "figures.h"
#include "fsm.h"
#include "objects.h"

StateTetris_t *getState(void);
AllInfo_t *getAllInfo(void);
GameInfo_t *getGameInfo(void);

void initAllInfo(void);
void destroyGame(void);

GameInfo_t makeGameInfo(AllInfo_t *info);
void updateAllInfo(AllInfo_t *info);

bool isEndGame(AllInfo_t *info);
bool isCollision(AllInfo_t info);

void setTetrisScore(int high_score);
int getTetrisScore(void);
int getPoints(int **field);
int calculatePoints(int count);
void eraseLine(int **field, int row);
bool checkLine(int **field, int row);

#endif  // BRICKGAME_V1_0_SRC_BRICK_GAME_TETRIS_INC_TETRIS_H_
