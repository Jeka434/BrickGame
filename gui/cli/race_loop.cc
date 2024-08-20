#include "race_loop.h"

GameInfo_t s21::RaceNcurses::updateCurrentState() {
  return requests_.updateCurrentState();
}

void s21::RaceNcurses::userInput(UserAction_t action, bool hold) {
  requests_.userInput(action, hold);
}
