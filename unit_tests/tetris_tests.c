#include <check.h>
#include <unistd.h>

#include "test_tetris.h"

START_TEST(Test_snake_1) {
  initAllInfo();

  StateTetris_t *state = getState();
  ck_assert_int_eq(*state, Start);
  userInput(Start, false);
  GameInfo_t info = updateCurrentState();
  ck_assert(info.score == 0);
  ck_assert(info.level == 1);

  ck_assert_int_eq(*getState(), Spawn);
  userInput(Left, false);
  info = updateCurrentState();
  ck_assert_int_eq(*getState(), Moving);

  while (*getState() != Attaching) {
    userInput(Down, true);
    updateCurrentState();
  }

  ck_assert_int_eq(*getState(), Attaching);
  userInput(NoAction, false);
  updateCurrentState();

  ck_assert(*getState() == Spawn);
  userInput(Right, false);
  updateCurrentState();

  ck_assert(*getState() == Moving);

  userInput(Up, false);
  updateCurrentState();

  ck_assert(*getState() == Moving);

  for (int i = 0; i < 20; i++) {
    userInput(Right, false);
    updateCurrentState();
  }

  for (int i = 0; i < 20; i++) {
    userInput(Left, false);
    updateCurrentState();
  }

  for (int i = 0; i < 20; i++) {
    userInput(Action, false);
    updateCurrentState();
  }
}

START_TEST(Test_snake_2) {
  initAllInfo();

  StateTetris_t *state = getState();
  ck_assert_int_eq(*state, Start);
  userInput(Start, false);
  GameInfo_t info = updateCurrentState();
  ck_assert(info.score == 0);
  ck_assert(info.level == 1);

  ck_assert_int_eq(*getState(), Spawn);
  userInput(Left, false);
  info = updateCurrentState();
  ck_assert_int_eq(*getState(), Moving);

  while (*getState() != Shifting) {
    usleep(40000);
    userInput(NoAction, false);
    updateCurrentState();
  }

  ck_assert_int_eq(*getState(), Shifting);
}

START_TEST(Test_snake_3) {
  initAllInfo();

  StateTetris_t *state = getState();
  ck_assert_int_eq(*state, Start);
  userInput(Start, false);
  GameInfo_t info = updateCurrentState();
  ck_assert(info.score == 0);
  ck_assert(info.level == 1);
  ck_assert_int_eq(*getState(), Spawn);

  userInput(Pause, false);
  updateCurrentState();
  ck_assert_int_eq(*getState(), Spawn);

  userInput(Terminate, false);
  updateCurrentState();
  ck_assert_int_eq(*getState(), End);
}

Suite *suite_tetris() {
  Suite *s;
  TCase *tc;

  s = suite_create("Tetris test");
  tc = tcase_create("Tetris test");

  tcase_add_test(tc, Test_snake_1);
  tcase_add_test(tc, Test_snake_2);
  tcase_add_test(tc, Test_snake_3);

  suite_add_tcase(s, tc);

  return s;
}
