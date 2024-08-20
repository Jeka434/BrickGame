#ifndef BRICKGAME_V1_0_SRC_UNIT_TESTS_TEST_TETRIS_H
#define BRICKGAME_V1_0_SRC_UNIT_TESTS_TEST_TETRIS_H

#include <check.h>

#include "../brick_game/tetris/inc/tetris.h"

void run_one_test(Suite *test);
void run_tests();

Suite *suite_tetris();

#endif  // BRICKGAME_V1_0_SRC_UNIT_TESTS_TEST_TETRIS_H
