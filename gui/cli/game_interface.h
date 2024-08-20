#ifndef BRICKGAME_V1_0_SRC_GUI_CLI_GAME_INTERFACE_H_
#define BRICKGAME_V1_0_SRC_GUI_CLI_GAME_INTERFACE_H_

#include <ncurses.h>

#include "../../brick_game/common/common.h"

namespace s21 {

class GameInterface {
 public:
  virtual void run();
  virtual ~GameInterface() = default;
 private:
  UserAction_t getAction(int user_input);
  void showGame(WINDOW *field, WINDOW *player, GameInfo_t game);
  void showField(WINDOW *field, GameInfo_t game);
  void showInfo(WINDOW *player, GameInfo_t game);

 protected:
  virtual GameInfo_t updateCurrentState() = 0;
  virtual void userInput(UserAction_t action, bool hold) = 0;
};

}  // namespace s21

#endif  // BRICKGAME_V1_0_SRC_GUI_CLI_GAME_INTERFACE_H_
