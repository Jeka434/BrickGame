#include "controller.h"

namespace s21 {

Controller::Controller(SnakeGame *model) : model{model} {}

void Controller::userInput(UserAction_t action, bool hold) {
  model->userInput(action, hold);
}

GameInfo_t Controller::updateCurrentState() {
  return model->updateCurrentState();
}

}  // namespace s21
