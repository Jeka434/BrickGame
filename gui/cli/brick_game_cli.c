#include "brick_game_cli.h"

int main() {
  init_ncurses();
  int key = getch();
  while (key != 27) {
    erase();
    mvprintw(1, 7, "BrickGame v3.0");
    mvprintw(3, 1, "Tetris - Press 'T' to start");
    mvprintw(4, 2, "Snake - Press 'S' to start");
    mvprintw(5, 3, "Race - Press 'R' to start");
    mvprintw(6, 3, "Exit - Press 'Esc'");
    if (key == 't' || key == 'T') {
      clear();
      game_tetris();
    } else if (key == 's' || key == 'S') {
      clear();
      run_snake();
    } else if (key == 'r' || key == 'R') {
      clear();
      run_race();
    }
    key = getch();
  }
  end_ncurses();
  return 0;
}

void init_ncurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
  timeout(50);
  curs_set(0);
}

void end_ncurses() { endwin(); };
