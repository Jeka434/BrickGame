#ifndef BRICKGAME_V1_0_SRC_GUI_CLI_SNAKE_LOOP_H_
#define BRICKGAME_V1_0_SRC_GUI_CLI_SNAKE_LOOP_H_

#include "game_interface.h"
#include "../../brick_game/snake/controller/controller.h"

namespace s21 {

class SnakeNcurses: public GameInterface {
 public:
  explicit SnakeNcurses(Controller *controller);

 protected:
  GameInfo_t updateCurrentState() override;
  void userInput(UserAction_t action, bool hold) override;

 private:
  Controller *controller;
};

}  // namespace s21

#endif  // BRICKGAME_V1_0_SRC_GUI_CLI_SNAKE_LOOP_H_
