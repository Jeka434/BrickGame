#include "snakewidget.h"

using namespace s21;

SnakeWidget::SnakeWidget(QWidget *parent)
    : GameWidget{parent}, model_{}, controller_{&model_} {
  setWindowTitle("Snake");
}

void SnakeWidget::userInput(UserAction_t action, bool hold) {
  controller_.userInput(action, hold);
}

GameInfo_t SnakeWidget::updateCurrentState() {
  return controller_.updateCurrentState();
}
