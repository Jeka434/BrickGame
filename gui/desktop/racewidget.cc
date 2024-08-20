#include "racewidget.h"

using namespace s21;

RaceWidget::RaceWidget(QWidget *parent)
    : GameWidget{parent}, requests_{} {
  setWindowTitle("Race");
}

void RaceWidget::userInput(UserAction_t action, bool hold) {
  requests_.userInput(action, hold);
}

GameInfo_t RaceWidget::updateCurrentState() {
  return requests_.updateCurrentState();
}
