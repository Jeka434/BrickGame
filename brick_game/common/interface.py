from pydantic import BaseModel
from enum import IntEnum

GAME_BOARD_WIDTH = 10
GAME_BOARD_HEIGHT = 20


class Action(IntEnum):
    Start = 0
    Pause = 1
    Terminate = 2
    Left = 3
    Right = 4
    Up = 5
    Down = 6
    Action = 7


class State(BaseModel):
    field: list[bool] = [False] * GAME_BOARD_WIDTH * GAME_BOARD_HEIGHT
    next: list[bool] = []
    score: int = 0
    highScore: int = 0
    level: int = 1
    speed: int = 0
    pause: bool = True


class GameInterface:
    def __init__(self):
        pass

    def user_input(self, action: Action, hold: bool):
        pass

    def update_current_state(self) -> State:
        pass
