#include "gamewidget.h"

namespace s21 {

GameWidget::GameWidget(QWidget* parent) : info_{} {
  setFixedSize(470, 605);
  setFocusPolicy(Qt::StrongFocus);
  timer_ = new QTimer(this);
  connect(timer_, &QTimer::timeout, this, &GameWidget::update_paint);
  timer_->start(FRAME_RATE);
}

GameWidget::~GameWidget() { delete timer_; }

void GameWidget::paintEvent(QPaintEvent* e) {
  QWidget::paintEvent(e);
  QPainter p(this);
  drawField(&p);
  drawPlayerInfo(&p);
}

void GameWidget::keyPressEvent(QKeyEvent* e) {
  UserAction_t action = NoAction;
  if (e->key() == Qt::Key_Down) {
    action = Down;
  } else if (e->key() == Qt::Key_Up) {
    action = Up;
  } else if (e->key() == Qt::Key_Left) {
    action = Left;
  } else if (e->key() == Qt::Key_Right) {
    action = Right;
  } else if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) {
    action = Start;
  } else if (e->key() == Qt::Key_Escape) {
    action = Terminate;
  } else if (e->key() == 'p' || e->key() == 'P') {
    action = Pause;
  } else if (e->key() == 'z' || e->key() == 'Z') {
    action = Action;
  }
  bool hold = action == Action;
  userInput(action, hold);
  info_ = updateCurrentState();
  if (action == Terminate) {
    timer_->stop();
    emit gameOver(this);
  }
}

void GameWidget::drawField(QPainter* p) {
  if (info_.field == nullptr) {
    return;
  }
  p->drawRect(0, 0, WIDGET_WIDTH, WIDGET_HEIGHT);
  for (int i = 0; i < FIELD_HEIGHT; ++i) {
    for (int j = 0; j < FIELD_WIDTH; ++j) {
      if (info_.field[i][j]) {
        p->setBrush(Qt::black);
      } else {
        p->setBrush(Qt::white);
      }
      p->drawRect(SQUARE_SIZE * j, SQUARE_SIZE * i, SQUARE_SIZE, SQUARE_SIZE);
    }
  }
}

void GameWidget::drawPlayerInfo(QPainter* p) {
  QFont font;
  font.setPointSize(14);
  p->setFont(font);
  p->drawText(305, 175, "Score: " + QString::number(info_.score));
  p->drawText(305, 205, "High score: " + QString::number(info_.high_score));
  p->drawText(305, 235, "Level: " + QString::number(info_.level));
  p->drawText(305, 265, "Speed: " + QString::number(info_.speed));
  if (info_.pause) {
    p->drawText(305, 295, "Paused");
  }
}

void GameWidget::update_paint() {
  info_ = updateCurrentState();
  update();
}

}  // namespace s21
