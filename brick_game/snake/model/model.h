#ifndef BRICKGAME_V2_0_SRC_BRICK_GAME_SNAKE_MODEL_MODEL_H_
#define BRICKGAME_V2_0_SRC_BRICK_GAME_SNAKE_MODEL_MODEL_H_

#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>

#include "../../common/common.h"

namespace s21 {

#define WIDTH 10
#define HEIGHT 20

typedef enum StateSnake_t {
  StartGame,
  Spawn,
  Moving,
  Shifting,
  End
} StateSnake_t;

typedef enum Direction {
  UpDirection,
  DownDirection,
  RightDirection,
  LeftDirection
} Direction;

class Point {
 public:
  int x;
  int y;
  Point();
  Point(int x, int y);
  static Point randomPoint(std::vector<Point>& snake);
  Point(const Point& other) = default;
  Point& operator=(const Point& other);
};

class SnakeGame {
 public:
  SnakeGame();
  ~SnakeGame();
  void userInput(UserAction_t action, bool hold);
  GameInfo_t updateCurrentState();

#ifndef BRICKGAME_TEST
 private:
#endif
  static int getSnakeScore();
  static void setSnakeScore(int high_score);
  void initStartInfo();
  void initSnakeVector();
  void randomApple();
  void clearField() const;
  void connectSnakeAndField() const;
  void connectAppleAndField() const;
  void connectFiguresAndField() const;
  bool checkCollision();
  void updateInfo();
  void moveSnake();

#ifndef BRICKGAME_TEST
 private:
#endif
  GameInfo_t info;
  StateSnake_t state;
  std::vector<Point> snake;
  Direction snake_direction;
  Direction next_direction;
  Point apple;
  bool start;
  std::chrono::time_point<std::chrono::system_clock> last_move_time;
};

}  // namespace s21

#endif  // BRICKGAME_V2_0_SRC_BRICK_GAME_SNAKE_MODEL_MODEL_H_
