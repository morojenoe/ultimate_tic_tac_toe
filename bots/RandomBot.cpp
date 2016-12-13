#include <algorithm>

#include "IBot.h"
#include "../rng.h"
#include "../position.h"
#include "RandomBot.h"

pos RandomBot::makeMove(int time) {
  auto possible_actions = this->environment.get()->GetPossibleActions();
  return possible_actions[rng.NextInt(0, (int)possible_actions.size() - 1)];
}
