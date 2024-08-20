#ifndef BRICKGAME_V2_0_SRC_GUI_DESKTOP_GAMEWIDGET_H
#define BRICKGAME_V2_0_SRC_GUI_DESKTOP_GAMEWIDGET_H

#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>

#include "../../brick_game/common/common.h"

#define SQUARE_SIZE 30
#define WIDGET_HEIGHT (FIELD_HEIGHT * SQUARE_SIZE)
#define WIDGET_WIDTH (FIELD_WIDTH * SQUARE_SIZE)
#define FRAME_RATE 30

namespace s21 {

class GameWidget : public QWidget {
  Q_OBJECT
 public:
  explicit GameWidget(QWidget *parent = nullptr);
  ~GameWidget() override;

 signals:
  void gameOver(GameWidget *);

 protected:
  void paintEvent(QPaintEvent *e) override;
  void keyPressEvent(QKeyEvent *e) override;
  virtual void userInput(UserAction_t action, bool hold) = 0;
  virtual GameInfo_t updateCurrentState() = 0;
  virtual void drawField(QPainter *p);
  virtual void drawPlayerInfo(QPainter *p);

  GameInfo_t info_;

 private:
  QTimer *timer_;

 private slots:
  void update_paint();
};

}  // namespace s21

#endif  // BRICKGAME_V2_0_SRC_GUI_DESKTOP_GAMEWIDGET_H
