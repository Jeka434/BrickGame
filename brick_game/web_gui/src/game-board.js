import {
    GAME_BOARD_WIDTH, GAME_BOARD_HEIGHT,
    TETRIS_NEXT_FIELD_WIDTH, TETRIS_NEXT_FIELD_HEIGHT
} from './config.js';

export class GameBoard {
    constructor($gameBoard) {
        this.element = $gameBoard;
        this.tiles = [];
        for (let i = 0; i < GAME_BOARD_WIDTH; ++i) {
            for (let j = 0; j < GAME_BOARD_HEIGHT; ++j) {
                const $tile = document.createElement('div');
                $tile.classList.add('tile');
                $tile.id = `position-${i}-${j}`;
                this.tiles.push($tile);
                this.element.append($tile);
            }
        }
    }

    getTile(x, y) {
        return this.tiles[y * GAME_BOARD_WIDTH + x];
    }

    enableTile(x, y) {
        this.getTile(x, y).classList.add('active');
    }

    disableTile(x, y) {
        this.getTile(x, y).classList.remove('active');
    }
}

export class TetrisNextField {
    constructor($tetrisNextField) {
        this.element = $tetrisNextField;
        this.tiles = [];

        for (let i = 0; i < TETRIS_NEXT_FIELD_WIDTH; i++) {
            for (let j = 0; j < TETRIS_NEXT_FIELD_HEIGHT; j++) {
                const $tile = document.createElement('div');
                $tile.classList.add('tile');
                $tile.id = `position-next-${i}-${j}`;
                this.tiles.push($tile);
                this.element.append($tile);
            }
        }
    }

    getTile(x, y) {
        return this.tiles[y * TETRIS_NEXT_FIELD_WIDTH + x];
    }

    enableTile(x, y) {
        this.getTile(x, y).classList.add('active');
    }

    disableTile(x, y) {
        this.getTile(x, y).classList.remove('active');
    } 
}
