#ifndef STRATEGY_IBOT_H
#define STRATEGY_IBOT_H

#include <string>
#include <memory>
#include "../position.h"
#include "../RL/UltimateTicTacToeGame.h"

class IBot {
public:
  IBot();
  virtual pos makeMove(int time) = 0;
  virtual ~IBot();

  std::shared_ptr<UltimateTicTacToeGame> environment;
};


#endif //STRATEGY_IBOT_H
