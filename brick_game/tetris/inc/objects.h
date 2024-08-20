#ifndef BRICKGAME_V1_0_SRC_BRICK_GAME_TETRIS_INC_OBJECTS_H_
#define BRICKGAME_V1_0_SRC_BRICK_GAME_TETRIS_INC_OBJECTS_H_

#include <stdbool.h>
#include <time.h>

#include "../../common/common.h"

typedef enum StateTetris_t {
  StartGame,
  Spawn,
  Moving,
  Shifting,
  Attaching,
  End
} StateTetris_t;

typedef struct Figure_t {
  int **coordinates;
  int length;
  int x, y;
} Figure_t;

typedef struct PlayerInfo_t {
  int score;
  int high_score;
  int level;
  int speed;
  bool pause;
  bool start;
} PlayerInfo_t;

typedef struct AllInfo_t {
  int **field;
  Figure_t *current;
  Figure_t *next;
  PlayerInfo_t player;
  struct timespec last_drop_time;
} AllInfo_t;

#endif  // BRICKGAME_V1_0_SRC_BRICK_GAME_TETRIS_INC_OBJECTS_H_
