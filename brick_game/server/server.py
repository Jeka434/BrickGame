from flask import Flask, request, Response, render_template
import os
import sys
import inspect

current_dir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parent_dir = os.path.dirname(current_dir)
web_gui_dir = os.path.join(parent_dir, "web_gui")
sys.path.insert(0, parent_dir)

from common.interface import GameInterface, Action

from tetris.game import Tetris
from snake.game import Snake
from race.game import Race

games_list = [
    {
        "id": 0,
        "name": "Tetris"
    },
    {
        "id": 1,
        "name": "Snake"
    },
    {
        "id": 2,
        "name": "Race"
    }
]

current_game: GameInterface | None = None

app = Flask(__name__, static_folder=web_gui_dir, template_folder=web_gui_dir)


@app.route("/", methods=["GET"])
def index():
    return render_template("index.html")


@app.route("/api/games", methods=["GET"])
def games():
    return {"games": games_list}


@app.route("/api/games/<int:game_id>", methods=["POST"])
def start_game(game_id: int):
    global current_game
    if current_game is not None:
        return Response("Game is already running", status=409, content_type="application/json")
    for game in games_list:
        if game_id == game["id"]:
            current_game = eval(f"{game['name']}()")
            return Response(status=200, content_type="application/json")
    return Response("Game id not found", status=404, content_type="application/json")


@app.route("/api/actions", methods=["POST"])
def action():
    global current_game
    if (current_game is None
            or type(request.json["hold"]) is not bool or type(request.json["action_id"]) is not int
            or request.json["action_id"] < 0 or request.json["action_id"] >= len(Action)):
        return Response("Error in request body or game is not running", status=400, content_type="application/json")
    current_game.user_input(Action(request.json["action_id"]), request.json["hold"])
    if Action(request.json["action_id"]) == Action.Terminate:
        current_game = None
    return Response(status=200, content_type="application/json")


@app.route("/api/state", methods=["GET"])
def state():
    if current_game is None:
        return Response("Game is not running", status=400, content_type="application/json")
    return current_game.update_current_state().dict()


if __name__ == "__main__":
    app.run(debug=False, port=8080)
