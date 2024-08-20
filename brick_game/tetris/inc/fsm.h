#ifndef BRICKGAME_V1_0_SRC_BRICK_GAME_TETRIS_INC_FSM_H_
#define BRICKGAME_V1_0_SRC_BRICK_GAME_TETRIS_INC_FSM_H_

#include "objects.h"
#include "tetris.h"

GameInfo_t updateCurrentState(void);
void userInput(UserAction_t action, bool hold);

#endif  // BRICKGAME_V1_0_SRC_BRICK_GAME_TETRIS_INC_FSM_H_
