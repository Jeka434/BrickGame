import unittest
from unittest.mock import patch
import time
from game import *


class TestRace(unittest.TestCase):
    def setUp(self):
        self.race = Race()

    def test_initial_state(self):
        self.assertEqual(self.race.fsm, RaceFSM.Start)
        self.assertEqual(self.race.current_state.score, 0)
        self.assertEqual(self.race.current_state.level, 1)
        self.assertEqual(self.race.current_state.speed, 1)
        self.assertTrue(self.race.current_state.pause)

    @patch('builtins.open')
    @patch('time.time', return_value=1000.0)
    def test_user_input_start(self, mock_time, mock_open):
        self.race.user_input(Action.Start, hold=False)
        self.assertFalse(self.race.current_state.pause)

    @patch('time.time', return_value=1000.0)
    def test_user_input_pause(self, mock_time):
        self.race.user_input(Action.Start, hold=False)
        self.assertFalse(self.race.current_state.pause)
        self.race.fsm = RaceFSM.Moving
        self.race.user_input(Action.Pause, hold=False)
        self.assertTrue(self.race.current_state.pause)
        self.race.user_input(Action.Pause, hold=False)
        self.assertFalse(self.race.current_state.pause)

    @patch('time.time', return_value=1000.0)
    def test_user_input_terminate(self, mock_time):
        self.race.user_input(Action.Start, hold=False)
        self.race.user_input(Action.Terminate, hold=False)
        self.assertTrue(self.race.terminated)

    def test_user_input_move_left(self):
        self.race.current_state.pause = False
        self.race.fsm = RaceFSM.Moving
        self.race.car_pos = CarPosition.Center
        self.race.user_input(Action.Left, hold=False)
        self.assertEqual(self.race.car_pos, CarPosition.Left)

    def test_user_input_move_right(self):
        self.race.current_state.pause = False
        self.race.fsm = RaceFSM.Moving
        self.race.car_pos = CarPosition.Center
        self.race.user_input(Action.Right, hold=False)
        self.assertEqual(self.race.car_pos, CarPosition.Right)

    def test_shift_function(self):
        self.race.car_pos = CarPosition.Center
        initial_score = self.race.current_state.score
        self.race.cars[-1] = CarPosition.Left
        self.race.shift()
        self.assertEqual(self.race.cars_passed, 1)
        self.assertEqual(self.race.current_state.score, initial_score + 1)

    def test_collided(self):
        self.race.car_pos = CarPosition.Center
        self.race.cars = (GAME_BOARD_HEIGHT + ENEMY_CAR_SIZE - 2) * [CarPosition.Empty] + [CarPosition.Center]
        self.assertTrue(self.race.collided())

    def test_update_current_state_start(self):
        self.race.user_input(Action.Start, hold=False)
        self.race.update_current_state()
        self.assertEqual(self.race.fsm, RaceFSM.Spawn)

    def test_update_current_state_spawn(self):
        self.race.fsm = RaceFSM.Spawn
        self.race.update_current_state()
        self.assertEqual(self.race.fsm, RaceFSM.Moving)
        self.assertNotEqual(self.race.cars[0], CarPosition.Empty)

    @patch('time.time', return_value=1001.0)
    def test_update_current_state_moving(self, mock_time):
        self.race.fsm = RaceFSM.Moving
        self.race.current_state.pause = False
        self.race.last_shifted = 0.0
        self.race.update_current_state()
        self.assertEqual(self.race.fsm, RaceFSM.Shifting)

    def test_update_current_state_collided(self):
        self.race.fsm = RaceFSM.Collided
        self.race.update_current_state()
        self.assertEqual(self.race.fsm, RaceFSM.GameOver)
        self.assertTrue(self.race.current_state.pause)

    def test_update_current_state_game_over(self):
        self.race.fsm = RaceFSM.GameOver
        self.race.current_state.pause = False
        self.race.update_current_state()
        self.assertEqual(self.race.fsm, RaceFSM.Start)
        self.assertEqual(self.race.current_state.score, 0)

    def test_get_field(self):
        self.race.cars[10] = CarPosition.Center
        field = [
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
            0, 0, 0, 1, 1, 1, 0, 0, 0, 0,
            0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
            0, 0, 0, 1, 1, 1, 0, 0, 0, 0,
            0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
            0, 0, 0, 1, 1, 1, 0, 0, 0, 0,
            0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
            0, 0, 0, 1, 1, 1, 0, 0, 0, 0
        ]
        self.assertEqual(self.race.get_field(), list(map(lambda x: x == 1, field)))


if __name__ == '__main__':
    unittest.main()
