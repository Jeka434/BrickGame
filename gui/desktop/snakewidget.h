#ifndef BRICKGAME_V2_0_SRC_GUI_DESKTOP_SNAKEWIDGET_H
#define BRICKGAME_V2_0_SRC_GUI_DESKTOP_SNAKEWIDGET_H

#include "gamewidget.h"
#include "../../brick_game/snake/controller/controller.h"

namespace s21 {

class SnakeWidget : public GameWidget {
  Q_OBJECT
 public:
  explicit SnakeWidget(QWidget *parent = nullptr);

protected:
  void userInput(UserAction_t action, bool hold) override;
  GameInfo_t updateCurrentState() override;

private:
  SnakeGame model_;
  Controller controller_;
};

}  // namespace s21

#endif  // BRICKGAME_V2_0_SRC_GUI_DESKTOP_SNAKEWIDGET_H
