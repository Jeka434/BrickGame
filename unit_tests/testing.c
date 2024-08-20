#include "test_tetris.h"

int main() {
  run_tests();
  return 0;
}

void run_tests() {
  Suite *list[] = {suite_tetris(), NULL};

  for (Suite **cur = list; *cur; cur++) run_one_test(*cur);
}

void run_one_test(Suite *test) {
  SRunner *sr = srunner_create(test);
  srunner_set_fork_status(sr, CK_FORK);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}
