#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cassert>

#include "position.h"
#include "bots/IBot.h"
#include "bots/RandomBot.h"
#include "bots/RLBot.h"

#define MY_DEBUG

#ifdef MY_DEBUG
#define dbgx(x) {cerr << #x << " = " << x << endl;}
#define dbg(...) {fprintf(stderr, __VA_ARGS__); fflush(stderr);}
#else
#define dbgx(r) {}
#define dbg(...) {}
#endif


void place_move(const pos &p) {
  printf("place_move %d %d\n", p.c, p.r);
  fflush(stdout);
}

std::vector<std::string> split(const std::string &s, const std::string &&delims) {
  std::vector<std::string> result;

  std::string cur_str = "";
  for (auto it = s.begin(); it != s.end(); ++it) {
    if (std::find(delims.begin(), delims.end(), *it) == delims.end()) {
      cur_str += *it;
    } else {
      if (cur_str == "")
        dbg("empty string extracted in split function");
      result.push_back(cur_str);
      cur_str = "";
    }
  }
  if (cur_str != "") {
    result.push_back(cur_str);
  }

  return result;
}

int stringToInt(const std::string &s) {
  std::istringstream ss(s);
  int result;
  ss >> result;
  return result;
}

void setSetting(const std::string& type, const std::string& value,
                std::shared_ptr<IBot> bot) {
  if (type == "timebank") {
    bot.get()->environment->setTimebank(stringToInt(value));
  }
  else if (type == "time_per_move") {
    bot.get()->environment->setTimePerMove(stringToInt(value));
  }
  else if (type == "player_names") {
    std::vector<std::string> names = split(value, ",");
    bot->environment->setPlayerNames(names);
  }
  else if (type == "your_bot") {
    bot->environment->setMyBotName(value);
  }
  else if (type == "your_botid") {
    bot->environment->setMyBotId(stringToInt(value));
  }
  else {
    dbg("Unknown setting <%s>.", type.c_str());
  }
}

void update(const std::string& player, const std::string& type,
            const std::string& value, std::shared_ptr<IBot> bot) {

  if (player != "game" && player != bot.get()->environment->getBotName()) {
    // It's not my update!
    return;
  }

  if (type == "round") {
    bot.get()->environment->setRound(stringToInt(value));
  }
  else if (type == "move") {
    bot.get()->environment->setMove(stringToInt(value));
  }
  else if (type == "macroboard" || type == "field") {
    std::vector<std::string> rawValues = split(value, ",;");
    std::vector<int> transformedValues(rawValues.size());
    transform(rawValues.begin(), rawValues.end(), transformedValues.begin(), stringToInt);
    if (type == "field")
      bot.get()->environment->setBoard(transformedValues);
    else
      bot.get()->environment->setMacroboard(transformedValues);
  }
  else {
    dbg("Unknown update <%s>.", type.c_str());
  }
}

void processCommand(const std::vector<std::string> &command,
                    std::shared_ptr<IBot> bot) {
    if (command[0] == "action") {
        auto point = bot->makeMove(stringToInt(command[2]));
        place_move(point);
    }
    else if (command[0] == "update") {
        update(command[1], command[2], command[3], bot);
    }
    else if (command[0] == "settings") {
        setSetting(command[1], command[2], bot);
    }
    else {
        dbg("Unknown command <%s>.", command[0].c_str());
    }
}

int main() {
  std::string line;
  std::shared_ptr<IBot> bot = std::make_shared<RLBot>();
  while (getline(std::cin, line)) {
    processCommand(split(line.c_str(), " "), bot);
  }
  return 0;
}
