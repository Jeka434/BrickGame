#ifndef BRICKGAME_V1_0_SRC_GUI_CLI_GAME_ADAPTER_H
#define BRICKGAME_V1_0_SRC_GUI_CLI_GAME_ADAPTER_H

#ifdef __cplusplus
#include "snake_loop.h"
#include "race_loop.h"
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void run_snake();
EXTERNC void run_race();

#undef EXTERNC

#endif  // BRICKGAME_V1_0_SRC_GUI_CLI_GAME_ADAPTER_H
