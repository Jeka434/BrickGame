#include "model.h"

namespace s21 {

// class Point
Point::Point() : x{}, y{} {}

Point::Point(int x, int y) : x{x}, y{y} {}

Point Point::randomPoint(std::vector<Point> &snake) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<> x_dis(0, WIDTH - 1);
  static std::uniform_int_distribution<> y_dis(0, HEIGHT - 1);
  Point res;
  do {
    res.x = x_dis(gen);
    res.y = y_dis(gen);
  } while (std::any_of(snake.begin(), snake.end(),
                       [&](Point p) { return p.x == res.x && p.y == res.y; }));
  return res;
}

Point &Point::operator=(const Point &other) {
  if (this != &other) {
    x = other.x;
    y = other.y;
  }
  return *this;
}

// class SnakeGame
SnakeGame::SnakeGame() : info{} {
  info.field = new int *[HEIGHT];
  for (int i = 0; i < HEIGHT; ++i) {
    info.field[i] = new int[WIDTH]{};
  }
  state = StartGame;
  snake_direction = DownDirection;
  next_direction = DownDirection;
  info.score = 0;
  info.high_score = getSnakeScore();
  info.pause = start = false;
  info.speed = info.level = 1;
  initSnakeVector();
  last_move_time = std::chrono::system_clock::now();
}

SnakeGame::~SnakeGame() {
  for (int i = 0; i < HEIGHT; ++i) {
    delete[] info.field[i];
  }
  delete[] info.field;
}

void SnakeGame::userInput(UserAction_t action, bool hold) {
  auto pause = info.pause;
  switch (action) {
    case Start:
      start = true;
      break;
    case Pause:
      if (state != StartGame) info.pause = !pause;
      break;
    case Terminate:
      state = End;
      break;
    case Left:
      if (snake_direction != RightDirection) {
        next_direction = LeftDirection;
      }
      break;
    case Right:
      if (snake_direction != LeftDirection) {
        next_direction = RightDirection;
      }
      break;
    case Up:
      if (snake_direction != DownDirection) {
        next_direction = UpDirection;
      }
      break;
    case Down:
      if (snake_direction != UpDirection) {
        next_direction = DownDirection;
      }
      break;
    case Action:
      if (hold) moveSnake();
      break;
    default:
      break;
  }
}

GameInfo_t SnakeGame::updateCurrentState() {
  if (!info.pause && start) {
    std::chrono::time_point<std::chrono::system_clock> current;
    switch (state) {
      case StartGame: {
        initStartInfo();
        state = Moving;
        break;
      }
      case Spawn: {
        randomApple();
        state = Moving;
        break;
      }
      case Shifting: {
        moveSnake();
        break;
      }
      case Moving: {
        using namespace std::literals;
        current = std::chrono::system_clock::now();
        auto difference = (current - last_move_time) / 1ms;
        if (difference >= 630 - 30 * info.speed) {
          state = Shifting;
        }
        break;
      }
      case End: {
        clearField();
        snake.clear();
        break;
      }
      default:
        break;
    }
  }
  connectFiguresAndField();
  return info;
}

int SnakeGame::getSnakeScore() {
  int high_score = 0;
  std::ifstream fs("./snake_score.txt");
  if (fs.is_open()) {
    fs >> high_score;
    fs.close();
  }
  return high_score;
}

void SnakeGame::setSnakeScore(int high_score) {
  std::ofstream fs("./snake_score.txt");
  if (fs.is_open()) {
    fs << high_score;
    fs.close();
  }
}

void SnakeGame::randomApple() {
  Point tmp = Point::randomPoint(snake);
  apple.x = tmp.x;
  apple.y = tmp.y;
}

void SnakeGame::initStartInfo() {
  clearField();
  snake.clear();
  initSnakeVector();
  randomApple();
  snake_direction = DownDirection;
  next_direction = DownDirection;
  connectFiguresAndField();
};

void SnakeGame::initSnakeVector() {
  snake.clear();
  snake.emplace_back(WIDTH / 2, HEIGHT / 2 + 1);
  snake.emplace_back(WIDTH / 2, HEIGHT / 2);
  snake.emplace_back(WIDTH / 2, HEIGHT / 2 - 1);
  snake.emplace_back(WIDTH / 2, HEIGHT / 2 - 2);
}

void SnakeGame::clearField() const {
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      info.field[i][j] = 0;
    }
  }
}

void SnakeGame::connectSnakeAndField() const {
  for (const auto &p : snake) {
    info.field[p.y][p.x] = 1;
  }
}

void SnakeGame::connectAppleAndField() const {
  info.field[apple.y][apple.x] = 1;
}

void SnakeGame::connectFiguresAndField() const {
  clearField();
  connectAppleAndField();
  connectSnakeAndField();
}

bool isOutsideBorders(int x, int y) {
  bool res = false;
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) res = true;
  return res;
}

bool isCollisionWithBody(int x, int y, std::vector<Point> &snake) {
  bool res = false;
  if (std::any_of(++snake.begin(), snake.end(),
                  [&](Point p) { return p.x == x && p.y == y; })) {
    res = true;
  }
  return res;
}

bool SnakeGame::checkCollision() {
  Point tmp = snake.front();
  bool res = false;
  if (isOutsideBorders(tmp.x, tmp.y) ||
      isCollisionWithBody(tmp.x, tmp.y, snake)) {
    res = true;
  }
  return res;
}

void SnakeGame::updateInfo() {
  info.score += 1;
  if (info.high_score < info.score) info.high_score = info.score;
  if (info.level < 10) info.level = 1 + info.score / 5;
  info.speed = info.level;
};

void SnakeGame::moveSnake() {
  if (!info.pause && start) {
    Point tmp{snake.front()};
    switch (next_direction) {
      case UpDirection:
        tmp.y -= 1;
        break;
      case DownDirection:
        tmp.y += 1;
        break;
      case RightDirection:
        tmp.x += 1;
        break;
      case LeftDirection:
        tmp.x -= 1;
        break;
      default:
        break;
    }
    snake.insert(snake.begin(), tmp);
    if (tmp.x == apple.x && tmp.y == apple.y) {
      state = Spawn;
      updateInfo();
    } else if (checkCollision()) {
      clearField();
      snake.clear();
      info.score = 0;
      info.speed = info.level = 1;
      setSnakeScore(info.high_score);
      state = StartGame;
      start = false;
    } else {
      state = Moving;
      snake.pop_back();
    }
    snake_direction = next_direction;
  }
  last_move_time = std::chrono::system_clock::now();
  connectFiguresAndField();
}

}  // namespace s21
