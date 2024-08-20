#ifndef BRICK_GAME_V2_0_SRC_GUI_DESKTOP_RACEWIDGET_H_
#define BRICK_GAME_V2_0_SRC_GUI_DESKTOP_RACEWIDGET_H_

#include "gamewidget.h"
#include "../requests/race_requests.h"

namespace s21 {

class RaceWidget: public GameWidget {
  Q_OBJECT
 public:
  explicit RaceWidget(QWidget *parent = nullptr);

protected:
  void userInput(UserAction_t action, bool hold) override;
  GameInfo_t updateCurrentState() override;

private:
  Race::Requests requests_;
};

}  // namespace s21

#endif  // BRICK_GAME_V2_0_SRC_GUI_DESKTOP_RACEWIDGET_H_
