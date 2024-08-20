#include "snake_loop.h"

namespace s21 {

SnakeNcurses::SnakeNcurses(Controller *c) : controller{c} {}

GameInfo_t SnakeNcurses::updateCurrentState() {
  return controller->updateCurrentState();
}

void SnakeNcurses::userInput(UserAction_t action, bool hold) {
  controller->userInput(action, hold);
}

}  // namespace s21
