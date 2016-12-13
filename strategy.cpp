#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "position.h"
#include "bots/IBot.h"
#include "bots/RandomBot.h"

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

std::vector<std::string> &split(const char * const s, char delim,
                                std::vector<std::string> &elems) {
  std::stringstream ss(s);
  std::string item;
  elems.clear();
  while (getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
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
    bot.get()->environment.get()->setTimebank(stringToInt(value));
  }
  else if (type == "time_per_move") {
    bot.get()->environment.get()->setTimePerMove(stringToInt(value));
  }
  else if (type == "player_names") {
    std::vector<std::string> names;
    split(value.c_str(), ',', names);
    bot.get()->environment.get()->setPlayerNames(names);
  }
  else if (type == "your_bot") {
    bot.get()->environment.get()->setMyBotName(value);
  }
  else if (type == "your_botid") {
    bot.get()->environment.get()->setMyBotId(stringToInt(value));
  }
  else {
    dbg("Unknown setting <%s>.", type.c_str());
  }
}

void update(const std::string& player, const std::string& type,
            const std::string& value, std::shared_ptr<IBot> bot) {

  if (player != "game" && player != bot.get()->environment.get()->getBotName()) {
    // It's not my update!
    return;
  }

  if (type == "round") {
    bot.get()->environment.get()->setRound(stringToInt(value));
  }
  else if (type == "move") {
    bot.get()->environment.get()->setMove(stringToInt(value));
  }
  else if (type == "macroboard" || type == "field") {
    std::vector<std::string> rawValues;
    split(value.c_str(), ',', rawValues);
    std::vector<int> transformedValues(rawValues.size());
    transform(rawValues.begin(), rawValues.end(), transformedValues.begin(), stringToInt);
    if (type == "field")
      bot.get()->environment.get()->setBoard(transformedValues);
    else
      bot.get()->environment.get()->setMacroboard(transformedValues);
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
  std::vector<std::string> command;
  std::shared_ptr<IBot> bot = std::make_shared<RandomBot>();
  while (getline(std::cin, line)) {
    processCommand(split(line.c_str(), ' ', command), bot);
  }
  return 0;
}
