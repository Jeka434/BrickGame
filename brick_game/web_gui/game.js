import { applyRootStyles } from './src/utils.js';
import { GameBoard, TetrisNextField } from './src/game-board.js';
import { rootStyles, keyCodes, GAME_BOARD_WIDTH, GAME_BOARD_HEIGHT, SLEEP_TIMEOUT, TETRIS_NEXT_FIELD_WIDTH, TETRIS_NEXT_FIELD_HEIGHT } from './src/config.js';
import { API_URL } from './src/config.js';

applyRootStyles(rootStyles);
const gameBoard = new GameBoard(document.querySelector('#game-board'));
const tetrisNextField = new TetrisNextField(document.querySelector('#tetris-next'));

document.addEventListener('keydown', async function (event) {
    if (keyCodes.start.includes(event.code)) {
        await userInput(0, false);
        console.log('start');
    }
    if (keyCodes.pause.includes(event.code)) {
        await userInput(1, false);
        console.log('pause');
    }
    if (keyCodes.terminate.includes(event.code)) {
        await userInput(2, false);
        console.log('terminate');
        SetFieldVisibility('hidden');
        SetEntryMenuVisibility('visible');
    }
    if (keyCodes.left.includes(event.code)) {
        await userInput(3, false);
        console.log('left');
    }
    if (keyCodes.right.includes(event.code)) {
        await userInput(4, false);
        console.log('right');
    }
    if (keyCodes.up.includes(event.code)) {
        await userInput(5, false);
        console.log('up');
    }
    if (keyCodes.down.includes(event.code)) {
        await userInput(6, false);
        console.log('down');
    }
    if (keyCodes.action.includes(event.code)) {
        const game_name = document.getElementById('game-name');
        if (game_name.textContent === 'Snake') {
            await userInput(7, true);
        } else {
            await userInput(7, false);
        }
        console.log('action');
    }
});

document.addEventListener('DOMContentLoaded', async function(){
    await CreateMenu();
});

async function CreateMenu(){
    const response = await fetch(API_URL + '/games');

    if (response.ok) {
        const data = await response.json();
        const list = document.getElementById('game-list');

        MakeButtons(list, data);
    }
}

function MakeButtons(list, data){
    data['games'].forEach(element => {
        let li = document.createElement('li');
        li.classList.add('button-li');
        let button = document.createElement('button');
        button.classList.add('button');
        button.type = 'button';
        button.addEventListener('click', function () {
            OnClickedButton(element['id']);
            SetGameName(element['name']);
            SetNextVisibility('visible', element['name']);
        });
        button.textContent = element['name'];
        li.appendChild(button);
        list.appendChild(li);
    });
}

async function OnClickedButton(id){
    SetEntryMenuVisibility('hidden');
    SetFieldVisibility('visible');
    await GameLoop(id);
}

function SetGameName(name){
    const game_name = document.getElementById('game-name');
    game_name.textContent = name;
}

function SetEntryMenuVisibility(value){
    const list = document.getElementById('game-list');
    const project_name = document.getElementById('project-name');

    list.style.visibility = value;
    project_name.style.visibility = value;
}

function SetFieldVisibility(value){
    const game_name = document.getElementById('game-name');
    const field = document.getElementById('field');

    game_name.style.visibility = value;
    field.style.visibility = value;
}

function SetNextVisibility(value, game_name){
    const next = document.getElementById('tetris-next');
    const next_par = document.getElementById('tetris-next-par');

    if (game_name === 'Tetris' && value === 'visible') {
        next.style.visibility = 'visible';
        next_par.style.visibility = 'visible';
    } else {
        next.style.visibility = 'hidden';
        next_par.style.visibility = 'hidden';
    }
}

function setField(data){
    const field = data['field'];

    for (let i = 0; i < GAME_BOARD_HEIGHT; i++) {
        for (let j = 0; j < GAME_BOARD_WIDTH; j++) {
            if (field[j + i * GAME_BOARD_WIDTH]) {
                gameBoard.enableTile(j, i);
            } else {
                gameBoard.disableTile(j, i);
            }
        }
    }
}

function setNextField(data) {
    const field = data['next'];

    for (let i = 0; i < TETRIS_NEXT_FIELD_HEIGHT; i++) {
        for (let j = 0; j < TETRIS_NEXT_FIELD_WIDTH; j++) {
            if (field[j + i * TETRIS_NEXT_FIELD_WIDTH]) {
                tetrisNextField.enableTile(j, i);
            } else {
                tetrisNextField.disableTile(j, i);
            }
        }
    }
}

function setState(data){
    const high_score_element = document.getElementById('high-score-par');
    const score_element = document.getElementById('score-par');
    const level_element = document.getElementById('level-par');
    const speed_element = document.getElementById('speed-par');

    score_element.textContent = 'Score: ' + data['score'];
    high_score_element.textContent = 'High score: ' + data['highScore'];
    level_element.textContent = 'Level: ' + data['level'];
    speed_element.textContent = 'Speed: ' + data['speed'];

    if (data['next']) {
        setNextField(data);
    }

    setField(data);
}

async function PostGameId(id){
    try{
        const response = await fetch(API_URL + '/games/' + id.toString(), {
            method: 'POST'
        });
    } catch (error) {
        console.error('Response error');
    }
}

async function userInput(action_id, hold){
    const response = fetch(API_URL + '/actions', {
        method: 'POST',
        headers: {
            "Content-Type": 'application/json',
        },
        body: JSON.stringify({action_id: action_id, hold: hold}),
    });
}

async function updateCurrentState(){
    const response = await fetch(API_URL + '/state');

    if (!response.ok) {
        throw new Error("Request error");
    }
        
    return await response.json();
}

async function sleep(ms){
    return new Promise(resolve => {
        setTimeout(resolve, ms);
    });
}

async function GameLoop(id){
    await PostGameId(id);

    while (true) {
        try {
            const data = await updateCurrentState();
            setState(data);
            await sleep(SLEEP_TIMEOUT);
        } catch (_) {
            break;
        }
    }

    SetNextVisibility('hidden', 'Any');
}
