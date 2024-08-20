#ifndef BRICKGAME_V2_0_SRC_GUI_DESKTOP_MAINWINDOW_H
#define BRICKGAME_V2_0_SRC_GUI_DESKTOP_MAINWINDOW_H

#include <QMainWindow>

#include "snakewidget.h"
#include "tetriswidget.h"
#include "racewidget.h"

namespace s21 {

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

 private slots:
  void gameClosed(s21::GameWidget *widget);
  void tetrisRun();
  void snakeRun();
  void raceRun();

 private:
  Ui::MainWindow *ui_;
  TetrisWidget *tetris_;
  SnakeWidget *snake_;
  RaceWidget *race_;
};

}  // namespace s21

#endif  // BRICKGAME_V2_0_SRC_GUI_DESKTOP_MAINWINDOW_H
