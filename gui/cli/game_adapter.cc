#include "game_adapter.h"

using namespace s21;

void run_snake() {
  SnakeGame model{};
  Controller controller{&model};
  SnakeNcurses view{&controller};
  view.run();
}

void run_race() {
  RaceNcurses race;
  race.run();
}
