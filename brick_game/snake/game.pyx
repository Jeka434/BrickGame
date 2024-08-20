from libcpp cimport bool
import os
import sys
import inspect

current_dir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parent_dir = os.path.dirname(current_dir)
sys.path.insert(0, parent_dir)

from common.interface import GameInterface, Action, State, GAME_BOARD_WIDTH, GAME_BOARD_HEIGHT
from common.cgame cimport GameInfo_t, UserAction_t, make_field

cdef extern from "model/model.h" namespace "s21":
    cdef cppclass SnakeGame:
        SnakeGame()

cdef extern from "controller/controller.h" namespace "s21":
    cdef cppclass Controller:
        Controller(SnakeGame *)
        void userInput(UserAction_t, bool)
        GameInfo_t updateCurrentState()


cdef class CySnake:
    cdef Controller *cnt_obj
    cdef SnakeGame *model_obj

    def __init__(self):
        self.model_obj = new SnakeGame()
        self.cnt_obj = new Controller(self.model_obj)

    def user_input(self, action: Action, hold: bool):
        self.cnt_obj.userInput(action, hold)

    def __del__(self):
        del self.cnt_obj
        del self.model_obj

    def update_current_state(self):
        return make_field(self.cnt_obj.updateCurrentState())


class Snake(GameInterface):
    def __init__(self):
        super().__init__()
        self.game = CySnake()

    def user_input(self, action: Action, hold: bool) -> None:
        self.game.user_input(action, hold)

    def update_current_state(self) -> State:
        return self.game.update_current_state()
