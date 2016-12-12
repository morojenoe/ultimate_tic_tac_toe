#include <algorithm>
#include <sstream>
#include <vector>
#include <iostream>

#include "IBot.h"
#include "../rng.h"
#include "../position.h"
#include "RandomBot.h"

pos RandomBot::makeMove(int time) {
  std::vector<int> freeCells;
  for (int i = 0; i < 81; ++i){
    if (macroboard[(i / 9) / 3][(i % 9) / 3] == -1 && board[i / 9][i % 9] == 0){
      freeCells.push_back(i);
    }
  }
  int randomCell = freeCells[this->rng.NextInt() % freeCells.size()];
  return pos(randomCell / 9, randomCell % 9);
}
