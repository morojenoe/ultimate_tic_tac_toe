#include <algorithm>

#include "IBot.h"
#include "../rng.h"
#include "RandomBot.h"


pos RandomBot::makeMove(int time) {
  auto possible_actions = this->environment->GetPossibleActions();
  for (size_t i = 0; i < possible_actions.size(); ++i) {

  }
  return possible_actions[rng.NextInt(0, (int)possible_actions.size() - 1)];
}

RandomBot::RandomBot() : rng((unsigned long long)time(nullptr)) {

}
