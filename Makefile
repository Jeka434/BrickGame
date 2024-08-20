PROJECT_NAME=BrickGame

CC=gcc
CPP=g++
PYTHON=python3

WFLAGS=-Wall -Werror -Wextra
CFLAGS=-c $(WFLAGS)
CPP_STD=-std=c++17

DIR_CLI=gui/cli/
DIR_DESKTOP=gui/dir/
DIR_REQ=gui/requests/

SRC_TETRIS=brick_game/tetris/figures.c brick_game/tetris/fsm.c brick_game/tetris/tetris.c
SRC_SNAKE=brick_game/snake/model/model.cc brick_game/snake/controller/controller.cc

FRONTEND_TETRIS=$(wildcard gui/cli/*.c) 
FRONTEND_SNAKE=$(wildcard gui/cli/*.cc gui/requests/*.cc)

OBJ_TETRIS=$(SRC_TETRIS:.c=.o)
OBJ_SNAKE=$(SRC_SNAKE:.cc=.o)

OBJ_FRONT_TETRIS=$(FRONTEND_TETRIS:.c=.o)
OBJ_FRONT_SNAKE=$(FRONTEND_SNAKE:.cc=.o)


all: cli desktop setup_tetris setup_snake

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cc
	$(CPP) $(CPP_STD) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build/

cli: build $(OBJ_FRONT_TETRIS) $(OBJ_FRONT_SNAKE) libtetris.a libsnake.a
	$(CPP) $(CPP_STD) -o build/$(PROJECT_NAME)_cli $(OBJ_FRONT_TETRIS) $(OBJ_FRONT_SNAKE) -lncurses -L. -lsnake -ltetris

desktop: build
	cmake -S gui/desktop -B build
	cmake --build build

tests: clean tests_tetris tests_snake tests_race

gcov_report: clean gcov_tetris gcov_snake

libtetris.a: $(OBJ_TETRIS)
	ar rc $@ $(OBJ_TETRIS)

libsnake.a: $(OBJ_SNAKE)
	ar rc $@ $(OBJ_SNAKE)

setup_tetris:
	cd brick_game/tetris/ && $(PYTHON) setup.py build_ext --inplace

setup_snake:
	cd brick_game/snake/ && $(PYTHON) setup.py build_ext --inplace

server:
	$(PYTHON) brick_game/server/server.py

install: clean cli desktop

uninstall:
	rm -rf build/

dist: install
	tar -cvzf $(PROJECT_NAME).tgz build

dvi: clean
	cd dvi && latex description.tex
	cd dvi && rm -rf description.log description.aux
	cd dvi && dvipdf description.dvi

style:
	clang-format -style=Google -n unit_tests/*.* brick_game/tetris/*.c brick_game/tetris/inc/*.h \
		brick_game/snake/controller/*.* brick_game/snake/model/*.* $(FRONTEND_SNAKE) $(FRONTEND_TETRIS)

tests_tetris:
	$(CC) -DTETRIS_TEST $(WFLAGS) $(SRC_TETRIS) unit_tests/*.c -o tetris_tests -lcheck -lm -lsubunit
	./tetris_tests

tests_snake:
	$(CPP) -DBRICKGAME_TEST $(WFLAGS) $(CPP_STD) $(SRC_SNAKE) unit_tests/*.cpp -o snake_tests -lgtest
	./snake_tests

tests_race:
	cd brick_game/race/; python3 -m coverage run -m unittest test_race.py && python3 -m coverage html
	open brick_game/race/htmlcov/index.html

gcov_tetris:
	$(CC) -DTETRIS_TEST $(SRC_TETRIS) unit_tests/*.c -o tetris_tests -lcheck -lm -lsubunit --coverage
	./tetris_tests
	lcov -c -d . --no-external -o tetris_gcov.info
	genhtml -o gcov_report_tetris tetris_gcov.info
	open gcov_report_tetris/index.html

gcov_snake:
	$(CPP) -DBRICKGAME_TEST $(CPP_STD) $(SRC_SNAKE) unit_tests/*.cpp -o snake_tests -lgtest --coverage
	./snake_tests
	lcov -c -d . --no-external -o snake_gcov.info
	genhtml -o gcov_report_snake snake_gcov.info
	open gcov_report_snake/index.html

clean: uninstall
	rm -rf *.a
	rm -rf $(OBJ_TETRIS) $(OBJ_SNAKE) $(OBJ_FRONT_TETRIS) $(OBJ_FRONT_SNAKE)
	rm -rf brick_game/tetris/build/ brick_game/snake/build
	rm -rf dvi/*.pdf dvi/*.aux dvi/*.log dvi/*.dvi
	rm -rf snake_tests tetris_tests gcov_report*
	rm -rf *.gcda *.gcno *.info *score.txt
	rm -rf brick_game/race/htmlcov brick_game/race/.coverage
	rm -rf brick_game/server/*score.txt race_score.txt brick_game/race/race_score.txt
	rm -rf brick_game/snake/game.cpp brick_game/tetris/game.c
	rm -rf brick_game/snake/*.so brick_game/tetris/*.so
