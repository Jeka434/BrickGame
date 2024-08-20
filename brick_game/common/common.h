#ifndef BRICKGAME_V1_0_SRC_BRICK_GAME_COMMON_COMMON_H_
#define BRICKGAME_V1_0_SRC_BRICK_GAME_COMMON_COMMON_H_

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20

typedef enum UserAction_t {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  NoAction
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

#endif  // BRICKGAME_V1_0_SRC_BRICK_GAME_COMMON_COMMON_H_
