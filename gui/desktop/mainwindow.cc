#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace s21;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui_(new Ui::MainWindow),
      tetris_(nullptr),
      snake_(nullptr),
      race_(nullptr) {
  ui_->setupUi(this);
  setFixedSize(300, 200);
  connect(ui_->tetrisButton, &QPushButton::clicked, this, &MainWindow::tetrisRun);
  connect(ui_->snakeButton, &QPushButton::clicked, this, &MainWindow::snakeRun);
  connect(ui_->raceButton, &QPushButton::clicked, this, &MainWindow::raceRun);
}

MainWindow::~MainWindow() {
  delete tetris_;
  delete snake_;
  delete race_;
  delete ui_;
}

void MainWindow::gameClosed(s21::GameWidget* widget) {
  if (tetris_ == widget) {
    delete tetris_;
    tetris_ = nullptr;
  } else if (snake_ == widget) {
    delete snake_;
    snake_ = nullptr;
  } else if (race_ == widget) {
    delete race_;
    race_ = nullptr;
  }
  show();
}

void MainWindow::tetrisRun() {
  hide();
  tetris_ = new TetrisWidget(this);
  connect(tetris_, &TetrisWidget::gameOver, this, &MainWindow::gameClosed);
  tetris_->show();
}

void MainWindow::snakeRun() {
  hide();
  snake_ = new SnakeWidget(this);
  connect(snake_, &SnakeWidget::gameOver, this, &MainWindow::gameClosed);
  snake_->show();
}

void MainWindow::raceRun() {
  hide();
  race_ = new RaceWidget(this);
  connect(race_, &RaceWidget::gameOver, this, &MainWindow::gameClosed);
  race_->show();
}
