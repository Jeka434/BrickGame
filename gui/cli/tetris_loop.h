#ifndef BRICKGAME_V1_0_SRC_GUI_CLI_TETRIS_LOOP_H_
#define BRICKGAME_V1_0_SRC_GUI_CLI_TETRIS_LOOP_H_

#include <ncurses.h>

#include "../../brick_game/tetris/inc/tetris.h"

void game_tetris(void);
UserAction_t getAction(int user_input);

void showGame(WINDOW *field, WINDOW *player, GameInfo_t game);
void showField(WINDOW *field, GameInfo_t game);
void showNext(WINDOW *player, GameInfo_t game);
void showInfo(WINDOW *player, GameInfo_t game);

#endif  // BRICKGAME_V1_0_SRC_GUI_CLI_TETRIS_LOOP_H_
