#include <iostream>
#include <sstream>
#include <algorithm>

#include "UltimateTicTacToeGame.h"


int UltimateTicTacToeGame::CalculateNumberOfSquaresPlayerWin(
        const std::vector<int> &board, int player_id) {
  return std::accumulate(board.begin(), board.end(), 0,
                         [&](int result, int cell_player) {
                           return result + ((cell_player == player_id)? 1 : 0);
                         });
}

int UltimateTicTacToeGame::GetNumberOfBigSquaresIWin() {
  return this->CalculateNumberOfSquaresPlayerWin(this->macroboard,
                                                 this->my_bot_id);
}

int UltimateTicTacToeGame::GetNumberOfBigSquaresOpponentWin() {
  return this->CalculateNumberOfSquaresPlayerWin(this->macroboard,
                                                 this->opponent_bot_id);
}

void UltimateTicTacToeGame::setTimebank(int timebank) {
  this->timebank = timebank;
}

void UltimateTicTacToeGame::setTimePerMove(int time_per_move) {
  this->time_per_move = time_per_move;
}

void UltimateTicTacToeGame::setPlayerNames(const std::vector<std::string> &playerNames) {
  this->player_names = playerNames;
}

void UltimateTicTacToeGame::setMyBotName(std::string myBotName) {
  this->my_bot_name = myBotName;
}

void UltimateTicTacToeGame::setMyBotId(int bot_id) {
  this->my_bot_id = bot_id;
  this->opponent_bot_id = 3 - bot_id;
}

void UltimateTicTacToeGame::setRound(int round) {
  this->current_round = round;
}

void UltimateTicTacToeGame::setMove(int move) {
  this->current_move = move;
}

void UltimateTicTacToeGame::setBoard(const std::vector<int> &board) {
  this->board = board;
}

void UltimateTicTacToeGame::setMacroboard(const std::vector<int> &macroboard) {
  this->macroboard = macroboard;
}

std::string UltimateTicTacToeGame::getBotName() {
  return my_bot_name;
}

void UltimateTicTacToeGame::DoAction(const pos &action, double &reward) {

}

std::vector<pos> UltimateTicTacToeGame::GetPossibleActions() {
  std::vector<pos> free_cells;
  for (int i = 0; i < board.size(); ++i) {
    int blockId = ((i/27)*3) + (i%9)/3;
    if (this->macroboard[blockId] == -1 && this->board[i] == 0) {
      free_cells.push_back(pos(i / 9, i % 9));
    }
  }
  return free_cells;
}
