#ifndef STRATEGY_ULTIMATETICTACTOEGAME_H
#define STRATEGY_ULTIMATETICTACTOEGAME_H

#include <string>

#include "IEnvironment.h"

class UltimateTicTacToeGame : IEnvironment {
public:
  UltimateTicTacToeGame() = default;

  int GetNumberOfBigSquaresIWin();
  int GetNumberOfBigSquaresOpponentWin();

  void DoAction(const pos &action, double &reward) override;
  std::vector<pos> GetPossibleActions() override;

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
  int opponent_bot_id;

  // dynamic settings
  int current_round;
  int current_move;
  std::vector<int> board;
  std::vector<int> macroboard;

private:
  int CalculateNumberOfSquaresPlayerWin(
          const std::vector<int> &board, int player_id);
};


#endif //STRATEGY_ULTIMATETICTACTOEGAME_H
