#ifndef BRICKGAME_V2_0_SRC_GUI_DESKTOP_TETRISWIDGET_H
#define BRICKGAME_V2_0_SRC_GUI_DESKTOP_TETRISWIDGET_H

#include "gamewidget.h"
extern "C" {
#include "../../brick_game/tetris/inc/tetris.h"
}

namespace s21 {

class TetrisWidget : public GameWidget {
  Q_OBJECT
 public:
  explicit TetrisWidget(QWidget *parent = nullptr);

protected:
  void drawPlayerInfo(QPainter* p) override;
  void userInput(UserAction_t action, bool hold) override;
  GameInfo_t updateCurrentState() override;
};

}  // namespace s21

#endif  // BRICKGAME_V2_0_SRC_GUI_DESKTOP_TETRISWIDGET_H
