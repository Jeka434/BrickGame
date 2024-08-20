#include "tetriswidget.h"

using namespace s21;

TetrisWidget::TetrisWidget(QWidget *parent) : GameWidget{parent} {
  setWindowTitle("Tetris");
  initAllInfo();
}

void TetrisWidget::userInput(UserAction_t action, bool hold) {
  ::userInput(action, hold);
}

GameInfo_t TetrisWidget::updateCurrentState() {
  return ::updateCurrentState();
}

void TetrisWidget::drawPlayerInfo(QPainter* p) {
  GameWidget::drawPlayerInfo(p);
  if (info_.next) {
    int len = getAllInfo()->next->length;
    for (int i = 0; i < len; ++i) {
      for (int j = 0; j < len; ++j) {
        if (info_.next[i][j]) {
          p->setBrush(Qt::black);
        } else {
          p->setBrush(Qt::white);
        }
        p->drawRect(30 * j + 310, 30 * i + 30, 30, 30);
      }
    }
  }
  QFont font;
  font.setPointSize(14);
  p->setFont(font);
  p->drawText(305, 25, "Next:");
}
