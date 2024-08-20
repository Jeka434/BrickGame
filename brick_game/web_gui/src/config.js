export const GAME_BOARD_WIDTH = 10;
export const GAME_BOARD_HEIGHT = 20;
export const TETRIS_NEXT_FIELD_WIDTH = 4;
export const TETRIS_NEXT_FIELD_HEIGHT = 4;

export const rootStyles = {
    '--tile-color': '#eee',
    '--tile-size': '20px',
    '--tile-active-color': '#222',
    '--game-board-gap': '2px',
    '--game-board-width': GAME_BOARD_WIDTH,
    '--game-board-height': GAME_BOARD_HEIGHT,
    '--game-board-background': '#333',
    '--next-row-size': 4,
};

export const API_URL = "http://127.0.0.1:8080/api";

export const SLEEP_TIMEOUT = 15;
export const keyCodes = {
    start: ['Enter'],
    up: ['ArrowUp', 'KeyW', 'KeyI'],
    right: ['ArrowRight', 'KeyD', 'KeyL'],
    down: ['ArrowDown', 'KeyS', 'KeyK'],
    left: ['ArrowLeft', 'KeyA', 'KeyJ'],
    pause: ['KeyP'],
    terminate: ['Escape'],
    action: ['KeyZ']
};

