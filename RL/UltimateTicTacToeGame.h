#ifndef STRATEGY_ULTIMATETICTACTOEGAME_H
#define STRATEGY_ULTIMATETICTACTOEGAME_H

#include <string>
#include <vector>
#include <memory>

#include "../position.h"

class UltimateTicTacToeGame {
public:
  UltimateTicTacToeGame() = default;

  int GetNumberOfBigSquaresIWin();
  int GetNumberOfBigSquaresOpponentWin();

  std::vector<pos> GetPossibleActions();
  std::shared_ptr<UltimateTicTacToeGame> DoAction(const pos &action, double &reward);

  bool IsTerminal();

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

  int GetRound();
  int GetMove();

  int GetMacroboardPos(const pos &move);
  int GetBoardPos(const pos &move);

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
  void ApplyAction(const pos &action);
  int GetStateInSmallBoard(const std::vector<int> &board) const;
  std::vector<int> ExtractSmallBoard(int id) const;
  bool IsWinBunch(int first, int second, int third) const;
  bool IsDraw(const std::vector<int> &small_board) const;
  bool CanMove(const std::vector<int> &small_board) const;
};


#endif //STRATEGY_ULTIMATETICTACTOEGAME_H
