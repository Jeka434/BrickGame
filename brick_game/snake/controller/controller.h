#ifndef BRICKGAME_V2_0_SRC_BRICK_GAME_SNAKE_CONTROLLER_CONTROLLER_H_
#define BRICKGAME_V2_0_SRC_BRICK_GAME_SNAKE_CONTROLLER_CONTROLLER_H_

#include "../../common/common.h"
#include "../model/model.h"

namespace s21 {

class Controller {
 public:
  explicit Controller(SnakeGame *model);
  void userInput(UserAction_t action, bool hold);
  GameInfo_t updateCurrentState();

 private:
  SnakeGame *model;
};

}  // namespace s21

#endif  // BRICKGAME_V2_0_SRC_BRICK_GAME_SNAKE_CONTROLLER_CONTROLLER_H_
