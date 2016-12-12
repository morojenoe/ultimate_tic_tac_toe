#ifndef STRATEGY_IBOT_H
#define STRATEGY_IBOT_H

#include <string>
#include "position.h"

class IBot {
public:
  virtual pos makeMove(int time) = 0;
  virtual ~IBot();

  void setTimebank(int timebank);
  void setTimePerMove(int time_per_move);
  void setPlayerNames(const std::vector<std::string> &playerNames);
  void setMyBotName(std::string myBotName);
  void setMyBotId(int bot_id);
  void setRound(int round);
  void setMove(int move);
  void setBoard(const std::vector<int> &board);
  void setMacroboard(const std::vector<int> &macroboard);
  std::string getBotName();

protected:
  // static settings
  int timebank;
  int time_per_move;
  std::vector<std::string> player_names;
  std::string my_bot_name;
  int my_bot_id;

  // dynamic settings
  int current_round;
  int current_move;
  int board[9][9];
  int macroboard[3][3];
};


#endif //STRATEGY_IBOT_H
