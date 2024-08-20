#ifndef BRICKGAME_V3_0_SRC_GUI_REQUESTS_RACE_REQUESTS_H_
#define BRICKGAME_V3_0_SRC_GUI_REQUESTS_RACE_REQUESTS_H_

#include <string>
#include <map>
#include <exception>

#include "HTTPRequest.hpp"
#include "json.hpp"
#include "../../brick_game/common/common.h"

namespace s21::Race {

struct Game {
  int id;
  std::string name;
};

inline void to_json(nlohmann::json& j, const Game& g) {
  j = nlohmann::json{{"id", g.id}, {"name", g.name}};
}

inline void from_json(const nlohmann::json& j, Game& g) {
  j.at("id").get_to(g.id);
  j.at("name").get_to(g.name);
}

class Requests {
public:
  Requests();
  ~Requests();
  GameInfo_t updateCurrentState();
  void userInput(UserAction_t action, bool hold);

 private:
  std::vector<Game> GET_games();
  void POST_games_id(int game_id);
  void POST_actions(int action_id, bool hold);
  GameInfo_t GET_state();
  GameInfo_t retrieveState();

private:
  const std::string api_path = "http://localhost:8080/api";
  std::string resp_body;
  int status_code = 0;
  int **field = nullptr;
};

}

#endif  // BRICKGAME_V3_0_SRC_GUI_REQUESTS_RACE_REQUESTS_H_
