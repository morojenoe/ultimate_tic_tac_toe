#include <algorithm>
#include <sstream>
#include <iostream>

#include "IBot.h"

IBot::~IBot() {}

void IBot::setTimebank(int timebank) {
  this->timebank = timebank;
}

void IBot::setTimePerMove(int time_per_move) {
  this->time_per_move = time_per_move;
}

void IBot::setPlayerNames(const std::vector<std::string> &playerNames) {
  this->player_names = playerNames;
}

void IBot::setMyBotName(std::string myBotName) {
  this->my_bot_name = myBotName;
}

void IBot::setMyBotId(int bot_id) {
  this->my_bot_id = bot_id;
}

void IBot::setRound(int round) {
  this->current_round = round;
}

void IBot::setMove(int move) {
  this->current_move = move;
}

void IBot::setBoard(const std::vector<int> &board) {
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      this->board[i][j] = board[i*9 + j];
    }
  }
}

void IBot::setMacroboard(const std::vector<int> &macroboard) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      this->macroboard[i][j] = macroboard[i*3 + j];
    }
  }
}

std::string IBot::getBotName() {
  return my_bot_name;
}
