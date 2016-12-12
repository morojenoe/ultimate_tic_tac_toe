#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "position.h"
#include "rng.h"
#include "IBot.h"
#include "RandomBot.h"

using namespace std;

#define MY_DEBUG

#ifdef MY_DEBUG
#define dbgx(x) {cerr << #x << " = " << x << endl;}
#define dbg(...) {fprintf(stderr, __VA_ARGS__); fflush(stderr);}
#else
#define dbgx(x) {}
#define dbg(...) {}
#endif


void place_move(const pos &p) {
  printf("place_move %d %d\n", p.y, p.x);
  fflush(stdout);
}

vector<std::string> &split(const char * const s, char delim, std::vector<std::string> &elems) {
  stringstream ss(s);
  string item;
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

void setSetting(const std::string& type, const std::string& value, IBot *bot) {
  if (type == "timebank") {
    bot->setTimebank(stringToInt(value));
  }
  else if (type == "time_per_move") {
    bot->setTimePerMove(stringToInt(value));
  }
  else if (type == "player_names") {
    vector<string> names;
    split(value.c_str(), ',', names);
    bot->setPlayerNames(names);
  }
  else if (type == "your_bot") {
    bot->setMyBotName(value);
  }
  else if (type == "your_botid") {
    bot->setMyBotId(stringToInt(value));
  }
  else {
    dbgx("Unknown setting <" + type + ">.");
  }
}

void update(const std::string& player, const std::string& type, const std::string& value, IBot *bot) {
  if (player != "game" && player != bot->getBotName()) {
    // It's not my update!
    return;
  }

  if (type == "round") {
    bot->setRound(stringToInt(value));
  }
  else if (type == "move") {
    bot->setMove(stringToInt(value));
  }
  else if (type == "macroboard" || type == "field") {
    vector<string> rawValues;
    split(value.c_str(), ',', rawValues);
    vector<int> transformedValues(rawValues.size());
    transform(rawValues.begin(), rawValues.end(), transformedValues.begin(), stringToInt);
    if (type == "field")
      bot->setBoard(transformedValues);
    else
      bot->setMacroboard(transformedValues);
  }
  else {
    dbgx("Unknown update <" + type + ">.");
  }
}

void processCommand(const vector<string> &command, IBot *bot) {
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
        dbgx("Unknown command <" + command[0] + ">.");
    }
}

int main() {
  string line;
  vector<string> command;
  IBot *bot = new RandomBot();
  while (getline(cin, line)) {
    processCommand(split(line.c_str(), ' ', command), bot);
  }
  return 0;
}
