#include "RLBot.h"
#include <memory>

pos RLBot::makeMove(int time) {
  auto pos_to_move = this->agent.GetAction(this->environment);
  double reward = 0.0;
  auto next_env = this->environment->DoAction(pos_to_move, reward);
  this->agent.UpdateQValues(this->environment, pos_to_move, next_env, reward);
  this->environment = next_env;
  return pos_to_move;
}

ApproximateQAgent RLBot::getAgent() {
  return this->agent;
}
