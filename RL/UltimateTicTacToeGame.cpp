#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>
#include <cassert>

#include "UltimateTicTacToeGame.h"
#include "../position.h"
#include "../debug_helpers.h"


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

int UltimateTicTacToeGame::GetRound() {
  return this->current_round;
}

int UltimateTicTacToeGame::GetMove() {
  return this->current_move;
}

std::shared_ptr<UltimateTicTacToeGame>
UltimateTicTacToeGame::DoAction(const pos &action, double &reward) {
  auto next_env = std::make_shared<UltimateTicTacToeGame>();
  next_env->setBoard(this->board);
  next_env->setMacroboard(this->macroboard);
  next_env->setMyBotId(this->my_bot_id);
  next_env->setPlayerNames(this->player_names);
  next_env->setMyBotName(this->my_bot_name);

  next_env->ApplyAction(action);
  reward = 0;
  if (next_env->IsTerminal())
    reward = 100;
  return next_env;
}

bool UltimateTicTacToeGame::IsTerminal() {
  std::vector<int> board;
  for (int i = 0; i < 9; ++i) {
    board.push_back(this->GetStateInSmallBoard(this->ExtractSmallBoard(i)));
  }
  bool isThereMove = false;
  for (int i = 0; i < 9; ++i) {
    isThereMove = isThereMove || this->CanMove(this->ExtractSmallBoard(i));
  }
  return this->GetStateInSmallBoard(board) != 0 || !isThereMove;
}

int UltimateTicTacToeGame::GetMacroboardPos(const pos &move) {
  return this->macroboard[move.posInMacroboard()];
}

int UltimateTicTacToeGame::GetBoardPos(const pos &move) {
  return this->board[move.posInBoard()];
}

void UltimateTicTacToeGame::ApplyAction(const pos &action) {
  assert(this->GetMacroboardPos(action) == -1);
  assert(this->GetBoardPos(action) == 0);
  this->board[action.posInBoard()] = this->my_bot_id;
  this->macroboard = std::vector<int>(9, 0);
  for (int i = 0; i < 9; ++i) {
    this->macroboard[i] = this->GetStateInSmallBoard(this->ExtractSmallBoard(i));
  }
  auto nextSquare = action.nextSquareToMove();
  if (this->CanMove(this->ExtractSmallBoard(nextSquare.posInMacroboard()))) {
    this->macroboard[nextSquare.posInMacroboard()] = -1;
  } else {
    for (int i = 0; i < 9; ++i) {
      if (this->CanMove(this->ExtractSmallBoard(i)))
        this->macroboard[i] = -1;
    }
  }
}

int UltimateTicTacToeGame::GetStateInSmallBoard(const std::vector<int> &board) const {
  for (int r = 0; r < 3; ++r) {
    if (this->IsWinBunch(this->board[pos(r, 0).posInBoard()],
                         this->board[pos(r, 1).posInBoard()],
                         this->board[pos(r, 2).posInBoard()])) {
      return this->board[pos(r, 0).posInBoard()];
    }
  }
  for (int c = 0; c < 3; ++c) {
    if (this->IsWinBunch(this->board[pos(0, c).posInBoard()],
                         this->board[pos(1, c).posInBoard()],
                         this->board[pos(2, c).posInBoard()])) {
      return this->board[pos(0, c).posInBoard()];
    }
  }
  if (this->IsWinBunch(pos(0, 0).posInBoard(),
                       pos(1, 1).posInBoard(),
                       pos(2, 2).posInBoard())) {
    return pos(0, 0).posInBoard();
  }
  if (this->IsWinBunch(pos(0, 2).posInBoard(),
                       pos(1, 1).posInBoard(),
                       pos(2, 0).posInBoard())) {
    return pos(0, 2).posInBoard();
  }
  return 0;
}

std::vector<int> UltimateTicTacToeGame::ExtractSmallBoard(int id) const {
  std::vector<int> board;
  int row = (id / 3) * 3;
  int col = (id % 3) * 3;
  for (int r = row; r < row + 3; ++r) {
    for (int c = col; c < col + 3; ++c) {
      board.push_back(this->board[pos(r, c).posInBoard()]);
    }
  }
  return board;
}

bool UltimateTicTacToeGame::IsWinBunch(int first, int second, int third) const {
  return first == second && second == third && first != 0;
}

bool UltimateTicTacToeGame::IsDraw(const std::vector<int> &small_board) const {
  return this->GetStateInSmallBoard(small_board) == 0 &&
          std::all_of(small_board.begin(), small_board.end(), [](int player) {
            return player != 0;
          });
}

bool UltimateTicTacToeGame::CanMove(const std::vector<int> &small_board) const {
  return this->GetStateInSmallBoard(small_board) == 0 &&
          std::any_of(small_board.begin(), small_board.end(), [](int player) {
            return player == 0;
          });
}
