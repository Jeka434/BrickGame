#include "race_requests.h"

using namespace s21::Race;

Requests::Requests() {
  field = new int*[FIELD_HEIGHT];
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    field[i] = new int[FIELD_WIDTH]{};
  }
  int id = -1;
  auto games = GET_games();
  for (const auto& game : games) {
    if (game.name == "Race") {
      id = game.id;
      break;
    }
  }
  if (id != -1) {
    POST_games_id(id);
  }
}

Requests::~Requests() {
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    delete[] field[i];
  }
  delete[] field;
}

GameInfo_t Requests::updateCurrentState() { return GET_state(); }

void Requests::userInput(UserAction_t action, bool hold) {
  POST_actions(action, hold);
}

std::vector<Game> Requests::GET_games() {
  std::vector<Game> result;

  try {
    http::Request request{api_path + "/games"};
    const auto response = request.send("GET");
    status_code = response.status.code;
    resp_body = {response.body.begin(), response.body.end()};
  } catch (const std::exception& e) {}

  if (status_code == 200) {
    result = nlohmann::json::parse(resp_body)["games"].get<std::vector<Game>>();
  }

  return result;
}

void Requests::POST_games_id(int game_id) {
  std::string res;

  try {
    http::Request request{api_path + "/games/" + std::to_string(game_id)};
    const auto response = request.send("POST");
    resp_body = {response.body.begin(), response.body.end()};
    status_code = response.status.code;
  } catch (const std::exception& e) {}
}

void s21::Race::Requests::POST_actions(int action_id, bool hold) {
  std::string body;

  body += "{\"action_id\": " + std::to_string(action_id);
  body += ", \"hold\": ";

  if (hold) {
    body += "true}";
  } else {
    body += "false}";
  }

  try {
    http::Request request{api_path + "/actions"};
    const auto response =
        request.send("POST", body, {{"Content-Type", "application/json"}});
    resp_body = {response.body.begin(), response.body.end()};
    status_code = response.status.code;
  } catch (const std::exception& e) {}
}

GameInfo_t Requests::GET_state() {
  GameInfo_t result = {};

  try {
    http::Request request{api_path + "/state"};
    const auto response = request.send("GET");
    status_code = response.status.code;
    resp_body = {response.body.begin(), response.body.end()};
  } catch (const std::exception& e) {}

  if (status_code == 200) {
    result = retrieveState();
  }
  return result;
}

GameInfo_t Requests::retrieveState() {
  auto json = nlohmann::json::parse(resp_body);
  int i = 0, j = 0;

  for (const bool cell : json["field"]) {
    field[i][j] = cell;
    j++;
    if (j == FIELD_WIDTH) {
      i++;
      j = 0;
    }
  }

  return GameInfo_t{
      field,         nullptr,       json["score"], json["highScore"],
      json["level"], json["speed"], json["pause"]};
}
