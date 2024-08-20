#ifndef BRICKGAME_V1_0_SRC_GUI_CLI_RACE_LOOP_H_
#define BRICKGAME_V1_0_SRC_GUI_CLI_RACE_LOOP_H_

#include "../../brick_game/common/common.h"
#include "game_interface.h"
#include "../requests/reqs_race.h"

namespace s21 {

class RaceNcurses : public GameInterface {
 public:
  RaceNcurses() = default;

 protected:
  GameInfo_t updateCurrentState() override;
  void userInput(UserAction_t action, bool hold) override;

 private:
  Race::Requests requests_;
};

}  // namespace s21

#endif  // BRICKGAME_V1_0_SRC_GUI_CLI_RACE_LOOP_H_
