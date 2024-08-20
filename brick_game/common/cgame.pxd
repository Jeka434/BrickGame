from interface import State, GAME_BOARD_WIDTH, GAME_BOARD_HEIGHT


cdef extern from "common.h":
    ctypedef struct GameInfo_t:
        int **field
        int **next
        int score
        int high_score
        int level
        int speed
        int pause

    ctypedef enum UserAction_t:
        Start
        Pause
        Terminate
        Left
        Right
        Up
        Down
        Action
        NoAction


cdef inline make_field(GameInfo_t cstate):
    field = [False] * GAME_BOARD_WIDTH * GAME_BOARD_HEIGHT
    for i in range(GAME_BOARD_HEIGHT):
        for j in range(GAME_BOARD_WIDTH):
            field[i * GAME_BOARD_WIDTH + j] = cstate.field[i][j] != 0
    next_field = []
    if cstate.next:
        next_field = [False] * 16
        for i in range(4):
            for j in range(4):
                next_field[i * 4 + j] = cstate.next[i][j] != 0
    return State(field=field, next=next_field, score=cstate.score,
                 highScore=cstate.high_score, level=cstate.level,
                 speed=cstate.speed, pause=cstate.pause)
