#include "RLBot.h"
#include <memory>

pos RLBot::makeMove(int time) {
  return this->agent.GetAction(std::shared_ptr<IEnvironment>(this->environment));
}
