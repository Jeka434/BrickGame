from libcpp cimport bool
import os
import sys
import random
import inspect

# Include paths
current_dir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parent_dir = os.path.dirname(current_dir)
sys.path.insert(0, parent_dir)

from common.interface import GameInterface, Action, State, GAME_BOARD_WIDTH, GAME_BOARD_HEIGHT
from common.cgame cimport GameInfo_t, UserAction_t, make_field

cdef extern from "<stdlib.h>":
    cdef int rand()
    cdef void srand(unsigned int)

cdef extern from "inc/tetris.h":
    cdef void initAllInfo()
    cdef void destroyGame()

cdef extern from "inc/fsm.h":
    cdef void userInput(UserAction_t, bool)
    cdef GameInfo_t updateCurrentState()


cdef class CyTetris:
    def __init__(self):
        super().__init__()
        initAllInfo()

    def user_input(self, action: Action, hold: bool) -> None:
        userInput(action, hold)

    def __del__(self):
        destroyGame()

    def update_current_state(self) -> State:
        if os.name == "nt":
            srand(random.randint(0, 1000000))
        return make_field(updateCurrentState())


class Tetris(GameInterface):
    def __init__(self):
        super().__init__()
        self.game = CyTetris()

    def user_input(self, action: Action, hold: bool) -> None:
        self.game.user_input(action, hold)

    def update_current_state(self) -> State:
        return self.game.update_current_state()
