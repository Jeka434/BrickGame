#ifndef BRICKGAME_V1_0_SRC_BRICK_GAME_TETRIS_INC_FIGURES_H_
#define BRICKGAME_V1_0_SRC_BRICK_GAME_TETRIS_INC_FIGURES_H_

#include <stdlib.h>
#include <time.h>

#include "objects.h"
#include "tetris.h"

Figure_t *randomFigure(void);
void freeFigure(Figure_t *figure);
int getLength(int id);
int **getFigure(int id, int length);

bool moveLeft(AllInfo_t *info);
bool moveRight(AllInfo_t *info);
bool moveDown(AllInfo_t *info);
void rotation(AllInfo_t *info);

void connectionFigure(AllInfo_t *info);
void spawnFigure(AllInfo_t *info);

int **initMatrix(int rows, int cols);
void freeMatrix(int **matrix, int length);

#endif  // BRICKGAME_V1_0_SRC_BRICK_GAME_TETRIS_INC_FIGURES_H_
