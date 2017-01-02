#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cassert>

#include "position.h"
#include "bots/IBot.h"
#include "bots/RandomBot.h"
#include "bots/RLBot.h"
#include "debug_helpers.h"

void place_move(const pos &p) {
  printf("place_move %d %d\n", p.c, p.r);
  fflush(stdout);
}

std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
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
                const std::shared_ptr<IBot> &bot) {
  if (type == "timebank") {
    bot->environment->setTimebank(stringToInt(value));
  }
  else if (type == "time_per_move") {
    bot->environment->setTimePerMove(stringToInt(value));
  }
  else if (type == "player_names") {
    std::vector<std::string> names = split(value, ',');
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
            const std::string& value, const std::shared_ptr<IBot> &bot) {

  if (player != "game" && player != bot->environment->getBotName()) {
    // It's not my update!
    return;
  }

  if (type == "round") {
    bot->environment->setRound(stringToInt(value));
  }
  else if (type == "move") {
    bot->environment->setMove(stringToInt(value));
  }
  else if (type == "macroboard" || type == "field") {
    std::vector<std::string> rawValues = split(value, ',');
    std::vector<int> transformedValues(rawValues.size());
    transform(rawValues.begin(), rawValues.end(), transformedValues.begin(), stringToInt);
    if (type == "field")
      bot->environment->setBoard(transformedValues);
    else
      bot->environment->setMacroboard(transformedValues);
  }
  else {
    dbg("Unknown update <%s>.", type.c_str());
  }
}

void processCommand(const std::vector<std::string> &command,
                    const std::shared_ptr<IBot> &bot) {
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
    processCommand(split(line.c_str(), ' '), bot);
  }
  auto bot_for_dump = dynamic_cast<RLBot*>(bot.get());
  auto agent = bot_for_dump->getAgent();
  agent.dumpWeights();
  return 0;
}
