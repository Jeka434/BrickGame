import random
from enum import Enum
import os
import sys
import inspect
import time

current_dir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parent_dir = os.path.dirname(current_dir)
sys.path.insert(0, parent_dir)

from common.interface import GameInterface, GAME_BOARD_HEIGHT, GAME_BOARD_WIDTH, Action, State

MAIN_CAR_SIZE = 4
ENEMY_CAR_SIZE = 5
CARS_TO_LEVEL_UP = 5
MAX_LEVEL = 10
MAX_SPEED = 10
CAR_SPAWN_RATE = 13
SPEED_TIME_RATIO = 0.4


class CarPosition(Enum):
    Empty = 0
    Left = 1
    Center = 2
    Right = 3


class RaceFSM(Enum):
    Start = 0
    Spawn = 1
    Moving = 2
    Shifting = 3
    Collided = 4
    GameOver = 5


def read_high_score() -> int:
    try:
        with open("race_score.txt", "r") as f:
            return int(f.read())
    except IOError:
        return 0


def write_high_score(high_score: int) -> None:
    with open("race_score.txt", "w") as f:
        f.write(str(high_score))


class Race(GameInterface):
    def __init__(self, high_score: int = -1):
        super().__init__()
        self.fsm: RaceFSM = RaceFSM.Start
        self.current_state: State = State(highScore=high_score if high_score >= 0 else read_high_score(), speed=1)
        self.cars: list[CarPosition] = [CarPosition.Empty] * (GAME_BOARD_HEIGHT + ENEMY_CAR_SIZE - 1)
        self.last_car_spawned: int = CAR_SPAWN_RATE + 1
        self.terminated: bool = False
        self.car_pos: CarPosition = CarPosition.Center
        self.cars_passed: int = 0
        self.last_shifted: float = time.time()
        self.time_to_shift: float = 0
        self.pause_time: float = 0

    def get_field(self) -> list[bool]:
        field = [False] * GAME_BOARD_WIDTH * GAME_BOARD_HEIGHT
        for i, pos in enumerate(self.cars):
            car_offset = 0
            match pos:
                case CarPosition.Empty:
                    continue
                case CarPosition.Center:
                    car_offset = 3
                case CarPosition.Right:
                    car_offset = 6
            if i < GAME_BOARD_HEIGHT:
                field[GAME_BOARD_WIDTH * i + car_offset + 1] = True
            if 0 <= i - 2 < GAME_BOARD_HEIGHT:
                field[GAME_BOARD_WIDTH * (i - 2) + car_offset + 1] = True
            if 0 <= i - 4 < GAME_BOARD_HEIGHT:
                field[GAME_BOARD_WIDTH * (i - 4) + car_offset + 1] = True
            if 0 <= i - 1 < GAME_BOARD_HEIGHT:
                for j in range(3):
                    field[GAME_BOARD_WIDTH * (i - 1) + car_offset + j] = True
            if 0 <= i - 3 < GAME_BOARD_HEIGHT:
                for j in range(3):
                    field[GAME_BOARD_WIDTH * (i - 3) + car_offset + j] = True
        car_offset = 0
        match self.car_pos:
            case CarPosition.Center:
                car_offset = 3
            case CarPosition.Right:
                car_offset = 6
        field[GAME_BOARD_WIDTH * 16 + car_offset + 1] = not field[GAME_BOARD_WIDTH * 16 + car_offset + 1]
        field[GAME_BOARD_WIDTH * 18 + car_offset + 1] = not field[GAME_BOARD_WIDTH * 18 + car_offset + 1]
        for i in range(3):
            field[GAME_BOARD_WIDTH * 17 + car_offset + i] = not field[GAME_BOARD_WIDTH * 17 + car_offset + i]
            field[GAME_BOARD_WIDTH * 19 + car_offset + i] = not field[GAME_BOARD_WIDTH * 19 + car_offset + i]
        return field

    def shift(self) -> None:
        if self.cars[-1] != CarPosition.Empty:
            self.cars_passed += 1
            self.current_state.score += 1
            if self.current_state.score > self.current_state.highScore:
                self.current_state.highScore = self.current_state.score
            if self.cars_passed == self.current_state.level * CARS_TO_LEVEL_UP and self.current_state.level < MAX_LEVEL:
                self.current_state.level += 1
                self.current_state.speed += 1
        self.cars = [CarPosition.Empty] + self.cars[:-1]
        self.last_car_spawned += 1
        self.current_state.field = self.get_field()
        self.last_shifted = time.time()
        if self.collided():
            self.fsm = RaceFSM.Collided
        elif self.last_car_spawned >= CAR_SPAWN_RATE:
            self.fsm = RaceFSM.Spawn
        else:
            self.fsm = RaceFSM.Moving

    def collided(self) -> bool:
        return any(filter(lambda x: x == self.car_pos, self.cars[1 - MAIN_CAR_SIZE - ENEMY_CAR_SIZE:]))

    def user_input(self, action: Action, hold: bool) -> None:
        if action == Action.Terminate:
            self.terminated = True
            write_high_score(self.current_state.highScore)
        match self.fsm:
            case RaceFSM.Start | RaceFSM.GameOver:
                if action == Action.Start:
                    self.current_state.pause = False
            case RaceFSM.Moving:
                if self.current_state.pause and action not in [Action.Pause, Action.Terminate]:
                    return
                match action:
                    case Action.Pause:
                        self.current_state.pause = not self.current_state.pause
                        if self.current_state.pause:
                            self.pause_time = time.time()
                        else:
                            self.time_to_shift += time.time() - self.pause_time
                    case Action.Left:
                        if self.car_pos == CarPosition.Center:
                            self.car_pos = CarPosition.Left
                        elif self.car_pos == CarPosition.Right:
                            self.car_pos = CarPosition.Center
                    case Action.Right:
                        if self.car_pos == CarPosition.Center:
                            self.car_pos = CarPosition.Right
                        elif self.car_pos == CarPosition.Left:
                            self.car_pos = CarPosition.Center
                    case Action.Up:
                        self.shift()
                if self.collided():
                    self.current_state.field = self.get_field()
                    self.fsm = RaceFSM.Collided

    def update_current_state(self) -> State:
        match self.fsm:
            case RaceFSM.Start:
                if not self.current_state.pause:
                    self.current_state.field = self.get_field()
                    self.fsm = RaceFSM.Spawn
            case RaceFSM.Spawn:
                self.last_shifted = time.time()
                self.last_car_spawned = 0
                self.cars[0] = random.choice((CarPosition.Left, CarPosition.Center, CarPosition.Right))
                self.fsm = RaceFSM.Moving
            case RaceFSM.Moving:
                if (time.time() - self.last_shifted > SPEED_TIME_RATIO / self.current_state.speed and
                        not self.current_state.pause):
                    self.fsm = RaceFSM.Shifting
            case RaceFSM.Shifting:
                self.shift()
            case RaceFSM.Collided:
                self.current_state.pause = True
                self.fsm = RaceFSM.GameOver
            case RaceFSM.GameOver:
                if not self.current_state.pause:
                    self.__init__(self.current_state.highScore)
                return self.current_state
        return self.current_state
