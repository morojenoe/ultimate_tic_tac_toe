#ifndef STRATEGY_IACTION_H
#define STRATEGY_IACTION_H


#include <memory>
#include "../position.h"
#include "UltimateTicTacToeGame.h"

class IAgent {
public:
  IAgent() {}
  virtual ~IAgent() {}

  virtual pos GetAction(const std::shared_ptr<UltimateTicTacToeGame> &environment) = 0;
};


#endif //STRATEGY_IACTION_H
